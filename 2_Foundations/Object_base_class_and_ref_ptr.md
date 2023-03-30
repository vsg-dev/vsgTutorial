---
layout: page
title: vsg::Object base class & vsg::ref_ptr<>
permalink: /foundations/BaseClassesAndSmartPointers
---

To provide robust, thread-safe, high performance memory manangment the VulkanSceneGraph uses intrusive reference counting and block memory allocation. The three main classes that provide this functionality are vsg::Object base class, the vsg::ref_ptr<> smart pointer and vsg::Allocator singleton. The vsg::Auxiliary class and vsg::observer_ptr<> smart pointer provide additional meta data and weak pointer functionality.  In this section we'll convert the vsg::Object base class and the vsg::ref_ptr<> smart pointer and cover the vsg::Auxiliary, observer_ptr<> and vsg::Allocator in the follow two sections.

## Intrusive vs non-instrusive reference counting

Reference counting is widely used in application to facilitate robust sharing of objects allocated on the heap.  The two main approaches used in C++ applications are itrusive and on intrusive reference counting, each have strengths and weaknesses.

Standard C++ provides the std::shared_ptr<> smart pointer that uses non-instrusive counting. The design requires the shared_ptr<> to hold two pointers, one to the object being managed and one to a shared reference count. The advantage of non intrusive reference counting is that it can be used with all types, from bool to std::vector to user classes. The disadvantage of the shared_ptr<> is twice the size of a C pointer which has singinficant performance consequences which we'll discuss in detail below.

With intrusive reference counting the count is placed into the object, in the case of the VulkanSceneGraph is this is provided by the vsg::Object base classes atomic _referneceCount member variable which is accessed via the ref() and unref() methods that increment and decrement the count and when the count goes to zero the object is automatically deleted. To ensure that the ref() and unref() methods are called consistently the vsg::ref_ptr<> smart pointer is provided, similar in role to the std::shared_ptr<>, but has the advantage that it only requires a single C pointer so is the same size as a C pointer, and half the memory footprint of the std::shared_ptr<>.  The disadvantage with intrusive reference counting is that you can not use it directly with types like bool etc.

For the case of a scene graph we have a data structure where the internal nodes of the graph are primarily pointers to data objects or other nodes in the scene graph, if you double the size of the pointer you close to double the size of internal nodes in the graph.  Increasing the size of the nodes means you require more memory and crucially can fit less nodes into cache which means more cache misses and lower CPU utilization.  Benchmarking done comparing the traversal speeds of scene graph uses std::shared_ptr<> vs one with vsg::ref_ptr<> show that the intrusive reference counted scene graph is 15% faster.

## Creating objects and smart pointers

The standard C++ shared_ptr<> declaration is in the form:

~~~ cpp
struct MyClass
{
    MyClass(const std::string& in_name) : name(in_name) {}

    std::string name;
    double value = 0.0;
};

// allocate a MyClass object on the heap and assigns to std::shared_ptr<MyClass>
auto ptr = std::make_shared<MyClass>("fred");
~~~

While the equvilant with the VulkanSceneGraph requires MyClass to be subclass from vsg::Object to add the itrusive reference counting:

~~~ cpp
struct MyClass : public vsg::Object
{
    MyClass(const std::string& in_name) : name(in_name) {}

    std::string name;
    double value = 0.0;
};

// allocate a MyClass object on the heap and assigns to vsg::ref_ptr<MyClass>
vsg::ref_ptr<MyClass> ptr(new MyClass("ginger"));
~~~

The VulkanSceneGraph has another feature that makes it even cleaner to allocate objects robustly and add RTTI features - the vsg::Inherit<> template class. vsg::Inherit is an example the [Curiously Recurring Template Pattern (CRTP)](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern), while a somewhat non-intuitive idiom it neatly solves a problem of how to implement class specific extensions to a base class in consistent and robust way.

We'll cover more of these features of vsg::Object and vsg::Inherit later in the tutorial, for now we'll just focus on the benefits for conveniently allocating objects.  With the following revised code we leverage the create() method provided by vsg::Inerhit<> that allocates the memory and calls the constructor of the object using the parameters you pass to create(..) and returns a vsg::ref_ptr<> of the appropriate type. Usage is simply:

~~~ cpp
struct MyClass : public vsg::Inherit<vsg::Object, MyClass>
{
    MyClass(const std::string& in_name) : name(in_name) {}

    std::string name;
    double value = 0.0;
};

// allocate a MyClass object on the heap, using vsg::Allocator, and assigns to vsg::ref_ptr<MyClass>
auto ptr = MyClass::create("ginger");
~~~

While the declaration of the MyClass is little more complicated the benefit is cleaner and more expressive object creation syntax, that requires less code to type than either of the ref_ptr<T>(new T()) and std::make_shared<T>() usage. The use of the T::create(..) method is used throughout the VulkanSceneGraph codebase - it doesn't just make it more convenient for end users, it makes life easier for the developers of software as well.

## The strengths of smart pointers

The main reason for smart pointers is to make it easier to develop robust applications, and in the case of the vsg::ref_ptr<>/vsg:::Object combination there is no memory or performance overhead over using C pointers except for specific usage cases. Follows are a few examples of how smart_pointers leads to cleaner and more robust code.

Addressing memory leaks:

~~~ cpp
// 1. Using C pointers
{
    MyClass* c_ptr = new MyClass;

    //
    // do the processing we want
    //

    delete c_ptr; // need to explicitly delete object
}

// 2. Using C pointers and explicit ref/unref calls
{
    MyClass* c_ptr = new MyClass;
    c_ptr->ref(); // increment referenceCount to 1

    //
    // do the processing we want
    //

    c_ptr->unref(); // decrement refenreceCount to 0 and delete MyClass
}

// 3. Using ref_ptr<>
{
    auto ptr = MyClass:create(); // allocate MyClass on heap, assign to ref_ptr<MyClass> which increments it's referenceCount.

    //
    // do the processing we want
    //

} // when ptr destructs it automatically decrements it's referenceCount which hits 0 and leads to the object being deleted.
~~~

With case 1 & 2 are fine as long as the code block is never exits prematurely, what happens if there is a an early return or an exception thrown in the processing section? It will leak the object allocated on the heap.  With case 3 using ref_ptr<> early return from the block will always invoke the ptr destructor and always clean up the memory associated with it - the code isn't just simpler it's far more robust as well.

Referencing counting also helps when passing back objects out from the scope of a code block:

~~~ cpp
// 4. Using C pointers can lead to dangling pointers
MyClass* other_ptr = nullptr;
{
    MyClass* c_ptr = new MyClass;

    //
    // do the processing we want
    //

    // take a copy of the pointer
    other_ptr = c_ptr;

    delete c_ptr; // explicitly delete object cleans up memory but causes a dangling pointer
}
other_ptr->value = 10.0; // seg fault as the object has already been deleted

// 5. Using C pointers using explicit ref/unref calls
MyClass* other_ptr = nullptr;
{
    MyClass* c_ptr = new MyClass;
    c_ptr->ref(); // increment referenceCount to 1

    //
    // do the processing we want
    //

    other_ptr = c_ptr;
    other_ptr->ref(); // increment referenceCount to 2

    c_ptr->unref(); // decrement refenreceCount to 1 so no deletion!
}
other_ptr->value = 10.0; // assignment safe as object is still on the heap
other_ptr->unref(); // decrement refenreceCount to 0 and delete MyClass

// 6. Using ref_ptr<>
vsg::ref_ptr<MyClass> other_ptr;
{
    auto ptr = MyClass:create(); // allocate MyClass on heap, assign to ref_ptr<MyClass> which increments it's referenceCount to 1.

    //
    // do the processing we want
    //

    other_ptr = ptr; // smart pointer assignment automatically increasments reference count to 2

} // when ptr destructs it automatically decrements it's referenceCount which hits 1, no deletion!
other_ptr->value = 10.0; // assignment safe as object is still on the heap
~~~

In case 4 it is possible to fix the seg fault by moving the delete to after the last time that other_ptr is used, however if the processing section returns eary or throws an exception the memory will be lost. case 5 will work correctly as long as the processing section doesn't return early or throws an exception in which case it will leak the allocation object. Again case 6 is both cleaner and handles the early return case correctly, cleaning up any objects that have been allocated and no longer have an external reference.

These examples illustrate why smart pointers are so useful and why you'll find them used throughout the VulkanSceneGraph codebase and applications that use it:
1. Less code to write
2. More expressive code
3. More robust code

Prev: [Foundations](index.md)| Next: [Meta data, vsg::Auxiliary and vsg::observer_ptr<>](Auxiliary_and_observer_ptr.md)

