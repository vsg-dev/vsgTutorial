---
layout: page
title: vsg::ref_ptr<> & vsg::Object base class
permalink: /foundations/BaseClassesAndSmartPointers
---

To provide robust, thread-safe, high performance memory management the VulkanSceneGraph uses intrusive reference counting and block memory allocation.  The three main classes that provide this functionality are the vsg::Object base class, the vsg::ref_ptr<> smart pointer class and the vsg::Allocator singleton.  The vsg::Auxiliary class and vsg::observer_ptr<> smart pointer provide additional meta data and weak pointer functionality.  In this section we'll cover the vsg::Object base class and the vsg::ref_ptr<> smart pointer and then cover the vsg::Auxiliary, vsg::observer_ptr<> and vsg::Allocator in the following two sections.

## Intrusive vs non-intrusive reference counting

Reference counting is widely used in applications to facilitate robust sharing of objects allocated on the heap.  The two main approaches used in C++ applications are intrusive and non-intrusive reference counting, each have strengths and weaknesses.

Standard C++ provides the std::shared_ptr<> smart pointer that uses non-intrusive counting.  The design requires the shared_ptr<> to hold two pointers, one to the object being managed and one to a shared reference count.  The advantage of non intrusive reference counting is that it can be used with all types, from bool to std::vector to user classes.  The disadvantage of the shared_ptr<> is that it's twice the size of a C pointer which has significant performance consequences which we'll discuss in detail below.

With intrusive reference counting the count is placed into the object, in the case of the VulkanSceneGraph this is provided by the vsg::Object base classes atomic _referenceCount member variable which is accessed via the ref() and unref() methods that increment and decrement the count and when the count goes to zero the object is automatically deleted.  To ensure that the ref() and unref() methods are called consistently the vsg::ref_ptr<> smart pointer is provided, similar in role to the std::shared_ptr<>, but having the advantage that it only requires a single C pointer so is the same size as a C pointer, and half the memory footprint of the std::shared_ptr<>.  The disadvantage with intrusive reference counting is that you can not use it directly with types like bool etc.

For the case of a scene graph we have a data structure where the internal nodes of the graph are primarily pointers to data objects or other nodes in the scene graph, if you double the size of the pointer you almost double the size of internal nodes in the graph.  Increasing the size of the nodes means you require more memory and crucially can fit less nodes into cache which means more cache misses and lower CPU utilization.  Benchmarking done comparing the traversal speeds of a scene graph using std::shared_ptr<> vs one with vsg::ref_ptr<> shows that the intrusive reference counted scene graph is 15% faster.

## Creating objects and smart pointers

The standard C++ shared_ptr<> declaration is in the form:

~~~ cpp
struct MyClass
{
    MyClass(const std::string& in_name) : name(in_name) {}

    std::string name;
    double value = 0.0;
};

// allocates a MyClass object on the heap and assigns to std::shared_ptr<MyClass>
auto ptr = std::make_shared<MyClass>("fred");
~~~

The equivalent with the VulkanSceneGraph requires MyClass to be subclassed from vsg::Object to add the intrusive reference counting:

~~~ cpp
struct MyClass : public vsg::Object
{
    MyClass(const std::string& in_name) : name(in_name) {}

    std::string name;
    double value = 0.0;
};

// allocates a MyClass object on the heap and assigns to vsg::ref_ptr<MyClass>
vsg::ref_ptr<MyClass> ptr(new MyClass("ginger"));
~~~

The VulkanSceneGraph has another feature that makes it even cleaner to allocate objects robustly and add RTTI features - the vsg::Inherit<> template class.  vsg::Inherit is an example of the [Curiously Recurring Template Pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern), while a somewhat non-intuitive idiom it neatly solves a problem of how to implement class specific extensions to a base class in a consistent and robust way.

We'll cover more of these features of vsg::Object and vsg::Inherit later in the tutorial, for now we'll just focus on the benefits for conveniently allocating objects.  With the following revised code we leverage the create() method provided by vsg::Inherit<> that allocates the memory and calls the constructor of the object using the parameters you pass to create(..) and returns a vsg::ref_ptr<> of the appropriate type.  Usage is simply:

~~~ cpp
struct MyClass : public vsg::Inherit<vsg::Object, MyClass>
{
    MyClass(const std::string& in_name) : name(in_name) {}

    std::string name;
    double value = 0.0;
};

// allocates a MyClass object on the heap, using vsg::Allocator, and assigns to vsg::ref_ptr<MyClass>
auto ptr = MyClass::create("ginger");
~~~

While the declaration of the MyClass is a little more complicated the benefit is cleaner and more expressive object creation syntax, that requires less code to type than either of the ref_ptr<T>(new T()) and std::make_shared<T>() usage.  The use of the T::create(..) method is used throughout the VulkanSceneGraph codebase - it doesn't just make it more convenient for end users, it makes life easier for the developers of software as well.

## The strengths of smart pointers

The main reason for smart pointers is to make it easier to develop robust applications, and in the case of the vsg::ref_ptr<>/vsg::Object combination there is no memory or performance overhead over using C pointers except for specific usage cases.  The following are a few examples of how smart pointers lead to cleaner and more robust code.

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

    c_ptr->unref(); // decrement referenceCount to 0 and delete MyClass
}

// 3. Using ref_ptr<>
{
    auto ptr = MyClass::create(); // allocate MyClass on heap, assign to ref_ptr<MyClass> which increments its referenceCount.

    //
    // do the processing we want
    //

} // when ptr destructs it automatically decrements its referenceCount which hits 0 and leads to the object being deleted.
~~~

Cases 1 & 2 are fine as long as the code blocks never exit prematurely, but what happens if there is an early return or an exception thrown in the processing section? It will leak the object allocated on the heap.  With case 3 using ref_ptr<> an early return from the block will always invoke the ref_ptr<> destructor and always clean up the memory associated with it - the code isn't just simpler it's far more robust as well.

Reference counting also helps when passing back objects out from the scope of a code block:

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

    delete c_ptr; // explicitly delete object, cleans up memory but causes a dangling pointer
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

    c_ptr->unref(); // decrement referenceCount to 1 so no deletion!
}
other_ptr->value = 10.0; // assignment safe as object is still on the heap
other_ptr->unref(); // decrement referenceCount to 0 and delete MyClass

// 6. Using ref_ptr<>
vsg::ref_ptr<MyClass> other_ptr;
{
    auto ptr = MyClass::create(); // allocate MyClass on heap, assign to ref_ptr<MyClass> which increments its referenceCount to 1.

    //
    // do the processing we want
    //

    other_ptr = ptr; // smart pointer assignment automatically increases reference count to 2

} // when ptr destructs it automatically decrements its referenceCount which hits 1, no deletion!
other_ptr->value = 10.0; // assignment safe as object is still on the heap
~~~

In case 4 it is possible to fix the seg fault by moving the delete to after the last use of other_ptr, however if the processing section returns early or throws an exception the memory will leak.  Case 5 will work correctly as long as the processing section doesn't return early or throws an exception in which case it will leak the allocated object.  Again case 6 is both cleaner and handles the early return case correctly, cleaning up any objects that have been allocated and no longer have an external reference.

These examples illustrate why smart pointers are so useful and why you'll find them used throughout the VulkanSceneGraph codebase and applications that use it:
1. Less code to write
2. More expressive code
3. More robust code

## Don't mix delete, std::shared_ptr<> & std::ref_ptr<>

The code examples above implement MyClass by subclassing from vsg::Inherit<> which makes it possible to seamlessly use MyClass::create() and ref_ptr<>, but it's possible also to write and compile code that still uses std::shared_ptr<>.  We strongly recommend against doing so as you create a situation where there are two independent reference counting mechanisms attempting to manage a single object.

~~~ cpp
struct MyClass : public vsg::Inherit<vsg::Object, MyClass>
{
    MyClass(const std::string& in_name) : name(in_name);
    std::string name;
    double value = 1.0;
};

auto vsg_ptr = MyClass::create("carrie");

// will compile but create dangling pointers once either vsg_ptr or std_ptr goes out of scope
std::shared_ptr<MyClass> std_ptr(vsg_ptr.ptr());

// we could even just delete the object directly and mess up both vsg_ptr and std_ptr.
delete vsg_ptr.get();
~~~

The way to prevent this misuse is to use a protected or private destructor when the object is always meant to be allocated on the heap.

~~~ cpp
class MyClass : public vsg::Inherit<vsg::Object, MyClass>
{
public:
    MyClass(const std::string& in_name) : name(in_name);
    std::string name;
    double value = 1.0;
protected:
    virtual ~MyClass() {} // hide the destructor from shared_ptr<> and explicit deletion.
};

auto vsg_ptr = MyClass::create("carrie");

// will no longer compile
std::shared_ptr<MyClass> std_ptr(vsg_ptr.ptr());

// will no longer compile
delete vsg_ptr.get();
~~~

The VulkanSceneGraph uses this pattern throughout the codebase so when you see the destructor declared in the protected or private section of the class you know that instances of that class are meant to be only declared on the heap and meant to be used with vsg::ref_ptr<>.  The T::create() support provided by vsg::Inherit<> achieves both these requirements.

## Don't mix stack allocation and reference counting

Another potential issue when using smart pointers and reference counting is when objects are allocated on the stack rather than on the heap.  Stack allocation happens automatically for variables within a scope and all the allocated objects are automatically destructed at the end of the scope.  The examples using std::shared_ptr<> and vsg::ref_ptr<> leverage this behavior, using the destruction of the smart pointers to unreference the objects they have shared ownership of.  The problem occurs if a user allocates objects on the stack and then attempts to reference count them as well.  The following example illustrates this:

~~~ cpp

class MyClass : public vsg::Inherit<vsg::Object, MyClass>
{
public:
    MyClass(const std::string& in_name) : name(in_name);
    std::string name;
    double value = 1.0;
};

vsg::ref_ptr<MyClass> ptr;
{
    MyClass object("carrie"); // object created on the stack in local scope

    // assign object to the ref_ptr<> that increments its ref count to 1.
    ptr = &object;
} // object is destructed automatically because it was allocated on stack, it doesn't matter what the ref count is.

ptr->value += 10.0; // seg fault as object was deleted on exiting its scope
~~~

This same issue occurs for std::shared_ptr<>, you simply can't prevent the destruction of objects on the stack.  If you want to manage your objects using smart pointers you must only use them with objects allocated on the heap.  Thankfully the same technique of declaring the destructor protected/private that works to prevent use with shared_ptr<> and explicitly deleting an object works to prevent stack construction as well.
~~~ cpp
class MyClass : public vsg::Inherit<vsg::Object, MyClass>
{
public:
    MyClass(const std::string& in_name) : name(in_name);
    std::string name;
    double value = 1.0;
protected:
    virtual ~MyClass() {}
};

{
    // will no longer compile
    MyClass object("carrie");
}
~~~

Most classes in the VulkanSceneGraph are declared with a protected destructor to prevent this problem usage, but there are a couple of classes like subclasses from vsg::Visitor that for convenience and efficiency may be fine to allocate on the stack and let the automatic destruction clean up the objects without needing to allocate on the heap and use smart pointers.  For these special cases developers may decide to not declare a protected destructor, but they should be wary of the potential pitfalls in doing this.  Later in this chapter we will discuss visitor classes in detail and touch upon the time when stack vs heap allocation will be preferable.

Prev: [Foundations](index.md)| Next: [vsg::observer_ptr<>](observer_ptr.md)

