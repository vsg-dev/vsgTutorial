---
layout: page
title: vsg::Auxiliary and vsg::observer_ptr<>
permalink: /foundations/Auxiliary
---

All is not perfect in the realm of reference counted smart pointers like std::shared_ptr<> and vsg::ref_ptr<>, their biggest weakness is cases where data structures has circular references. A classic example of circular references is a parent owning a child, while the child's smart pointer back to parent means the parent. When this happens the reference count for both the parent and child will remain non zero even if all other external references to them are removed - leading to a chain of objects that never gets deleted.

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
    parent->children.push_back(child) // child object now has a ref count 2
} // parent and child pointers destructed decrementing ref counts of both to 1

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
    parent->children.push_back(child) // child object now ha a ref count 2
}
// parent is descrtructed decreatment the parent object to 0 and the objects destructor is called.
// the destructor deletes the children list and destrements the child's reference count to 1.
// the child is destructed and decrements it's reference count to 0, deleting the child.
~~~

While the use of C pointer breaks the chain in this instance, it has it's own pitfalls - if a parent gets deleted but a child remains due to other references to it the Animal::parent member will become a dangling pointer.To fix this one has to reset the Animal::parent pointer when the child is removed but do this robustly requires careful management of adding/removing of chil to/from the Animal::children list.

A common wayto do this would be by adding a Animal::addChild(Animial*) and Animal::removeChild(Animal*) method. To protect from misuse one would also move the Animal::children container into protected scope to avoid misuse.  However, this all adds complexity and requires tight integration of the various classes that you wish to connect.

## Weak pointers to the rescue

To address the problem of circular refenences and make easier it keep pointers to objects without retaining ownership, there is catogory of smart pointers - weak pointers. Weak pointers hold a pointer to an object without incrementing the objects reference count, and when the object gets deleteted all the weak pointers that reference it have their pointer invalidated automatically, these weak pointers are paired with strong pointers. The std::shared_ptr<> strong pointer is paired with the std::weak_ptr<> weak pointer. For the VulkanSceneGraph the vsg::ref_ptr<> strong pointer is paired with the vsg::observer_ptr<>.

We can now rewirite the Animal example using the vsg::observer_ptr<>:

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
    parent->children.push_back(child) // child object now ha a ref count 2
}
// parent pointer is destructed and decreaments the parent object's ref count to 0 and the parent object destructor is called.
// The destructor deletes the children list which decrements the child's reference count to 1.
// The child pointer is destructed and decrements it's reference count to 0, deleting the child.
~~~

The vsg::observer_ptr<> is also useful for cases where applications want to keep a pointer to a resource that has a lifetime that is independently managed, but you occasional want to access it if it's still in memory.

~~~ cpp



~~~





Prev: [vsg::Object base class & vsg::ref_ptr<>](Object_base_class_and_ref_ptr.md)| Next: [vsg::Allocator](Allocator.md)

