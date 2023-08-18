---
layout: page
title: vsg::observer_ptr<> weak pointer
permalink: /foundations/observer_ptr
---

All is not perfect in the realm of reference counted smart pointers like std::shared_ptr<> and vsg::ref_ptr<>, their biggest weakness is in cases where data structures have circular references. A classic example of circular references is a parent owning a child, while the child has a smart pointer back to parent also owning the parent. When this happens the reference count for both the parent and child will remain non zero even if all other external references to them are removed - leading to a chain of objects that never get deleted.

~~~ cpp
struct Animal : public vsg::Inherit<vsg::Object, Animal>
{
    vsg::ref_ptr<Animal> parent;
    std::list<vsg::ref_ptr<Animal>> children;
};

{
    auto parent = Animal::create(); // parent object has ref count of 1
    auto child = Animal::create(); // child object has ref count of 1
    child->parent = parent; // parent object now has ref count of 2
    parent->children.push_back(child) // child object now has a ref count of 2
} // parent and child pointers destructed, decrementing ref counts of both to 1

// both the original parent object and child object still have a ref count of 1
// but there are no external references left to them so code has no knowledge of them or means to delete them
~~~

This problem exists for std::shared_ptr<> for exactly the same reasons. One way to break the chain is to use a C pointer:

~~~ cpp
struct Animal : public vsg::Inherit<vsg::Object, Animal>
{
    Animal* parent = nullptr;
    std::list<vsg::ref_ptr<Animal>> children;
};

{
    auto parent = Animal::create(); // parent object has ref count of 1
    auto child = Animal::create(); // child object has ref count of 1
    child->parent = parent.get(); // parent object ref count doesn't change as we are just assigning a C pointer
    parent->children.push_back(child) // child object now has a ref count of 2
}
// parent is destructed, decrements the parent object to 0 and the object's destructor is called.
// the destructor deletes the children list and decrements the child's reference count to 1.
// the child is destructed and decrements its reference count to 0, deleting the child.
~~~

While the use of C pointer breaks the chain in this instance, it has its own pitfalls - if a parent gets deleted but a child remains due to other references to it, the Animal::parent member will become a dangling pointer. To fix this one has to reset the Animal::parent pointer when the child is removed but doing this robustly requires careful management of adding/removing of children to/from the Animal::children list.

A common way to do this would be by adding an Animal::addChild(Animal*) and Animal::removeChild(Animal*) method. To protect from misuse one would also move the Animal::children container into protected scope to avoid misuse. However, this all adds complexity and requires tight integration of the various classes that you wish to connect.

## Weak pointers to the rescue

To address the problem of circular references and make it easier to keep pointers to objects without retaining ownership, there is another category of smart pointers - weak pointers. Weak pointers hold a pointer to an object without incrementing the object's reference count, and when the object gets deleted all the weak pointers that reference it have their pointer invalidated automatically, these weak pointers are paired with strong pointers. The std::shared_ptr<> strong pointer is paired with the std::weak_ptr<> weak pointer. For the VulkanSceneGraph the vsg::ref_ptr<> strong pointer is paired with the vsg::observer_ptr<>.

We can now rewrite the Animal example using the vsg::observer_ptr<>:

~~~ cpp
struct Animal : public vsg::Inherit<vsg::Object, Animal>
{
    vsg::observer_ptr<Animal> parent;
    std::list<vsg::ref_ptr<Animal>> children;
};

{
    auto parent = Animal::create(); // parent object has ref count of 1
    auto child = Animal::create(); // child object has ref count of 1
    child->parent = parent; // parent object ref count doesn't change as we are just assigning to a vsg::obsever_ptr<>
    parent->children.push_back(child) // child object now has a ref count of 2
}
// parent pointer is destructed and decrements the parent object's ref count to 0 and the parent object destructor is called.
// The destructor deletes the children list which decrements the child's reference count to 1.
// The child pointer is destructed and decrements its reference count to 0, deleting the child.
~~~

## Using observer_ptr<> & ref_ptr<> together

The vsg::observer_ptr<> is also useful for cases where applications want to keep a pointer to a resource that has a lifetime that is independently managed, but you occasionally want to access it if it's still in memory. The following observer_ptr example program uses a background thread that periodically checks a shared resource, only taking a reference to it when required to prevent it from being deleted whilst being used, and exiting the thread when that resource was deleted by the main thread.

~~~ cpp
{% include_relative 2_observer_ptr/observer_ptr.cpp %}
~~~

When we compile and run the [observer_ptr](https://github.com/vsg-dev/vsgTutorial/tree/master/2_Foundations/2_observer_ptr) exercise, we should note the changing reference count as the background thread converts its observer_ptr to ref_ptr.

~~~
Main thread : scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010) referenceCount = 1
   Background thread : has started.
   Background thread : has ref_scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010), referenceCount = 2
Main thread : scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010) referenceCount = 1
Main thread : scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010) referenceCount = 1
Main thread : scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010) referenceCount = 1
...
...
Main thread : scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010) referenceCount = 1
Main thread : scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010) referenceCount = 1
   Background thread : has ref_scene = ref_ptr<vsg::Object>(vsg::Object 0x7f8d8c585010), referenceCount = 2
Main thread : removed reference to scene object ref_ptr<vsg::Object>(nullptr)
    Background thread : no longer has scene object to work on, so returning.
Main thread : background thread has been joined
~~~

Prev: [vsg::ref_ptr<> & vsg::Object base class](Object_base_class_and_ref_ptr.md)| Next: [Math Types](MathTypes.md)

