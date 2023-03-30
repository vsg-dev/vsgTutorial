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

## Using vsg::Object and ref_ptr<>

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

The VulkanSceneGraph has another feature that makes it even cleaner to allocate objects robustly and add RTTI features - the vsg::Inherit<> template class. vsg::Inherit is an example the [Curiously Reaccuring Template Pattern (CRTP)](https://en.cppreference.com/w/cpp/language/crtp), while a somewhat non-intuitive idiom it neatly solves a problem of how to implement class specific extensions to a base class in consistent and robust way.

We'll cover more of these features of vsg::Object and vsg::Inherit later in the tutorial, for now we'll just focus on the benefits for conviniently allocator objects.  With the following revised code we leverage the create() method provided by vsg::Inerhit<> that allocates the memory and calls the constructor of the object using the parameters you pass to create(..) and returns a vsg::ref_ptr<> of the appropriate type. Usage is simply:

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




---

Prev: [Foundations](index.md)| Next: [Meta data, vsg::Auxiliary and vsg::observer_ptr<>](Auxiliary_and_observer_ptr.md)

