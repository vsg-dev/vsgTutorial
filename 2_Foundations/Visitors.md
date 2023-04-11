---
layout: page
title: RTTI & Visitors
permalink: /foundations/Visitors
---

The VulkanSceneGarph provides a number of features that provide richer and more efficient Run Time Type Information (RTTI) and type safe operations than are provided by C++ itself. These features are provided by the vsg::Object base class and by two companion bass classes, the vsg::Visitor and vsg::ConstVisitor, that are scene graph specific implementation of Visitor Desgin Pattern, with the vsg::Inherit CRTP class providing convinient implementations of the required methods.

## RTTI features provide vsg::Object

The vsg::Object base class provides the follow methods dedicated to RTTI:

~~~ cpp
virtual const char* className() const noexcept { return type_name<Object>(); }

/// return the std::type_info of this Object
virtual const std::type_info& type_info() const noexcept { return typeid(Object); }
virtual bool is_compatible(const std::type_info& type) const noexcept { return typeid(Object) == type; }

template<class T>
T* cast() { return is_compatible(typeid(T)) ? static_cast<T*>(this) : nullptr; }

template<class T>
const T* cast() const { return is_compatible(typeid(T)) ? static_cast<const T*>(this) : nullptr; }

/// compare two objects, return -1 if this object is less than rhs, return 0 if it's equal, return 1 if rhs is greater,
virtual int compare(const Object& rhs) const;
~~~

The vsg::Object::className() method is implemented using the vsg::type_name<> template function, specializations of vsg::type_name<> are in turn provided by the VSG_type_name() and EVSG_type_name() macro functions that can be placed before/after a class defintion, both of these features are defined in [include/vsg/core/value_type.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/type_name.h). The VSG_type_name() macro can be used for classes within the vsg namespace, while the EVSG_type_name() version can be used for classes defined in other namespaces, such as what you see in [vsgXchange](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/all.h#L43).

The vsg::Object::type_info() methods provides a convinient way to access the std::type_info of a particular object, and vsg::Object::is_compatible(const std::type_info&) method provides a method that can not just check whether a type is the same, but whether it may be derived from that type thus compatible with treatment as that type. The vsg::Inherit<> class can be used to automatically implement the required type_info() and is_compatible() methods.

The vsg::Object::cast<>() template methods use the Object::is_compatible() method to decide whether a type can by cast directly to a desired type using static_cast<> without the high CPU overhead of invoking dynamic_cast<>.

The vsg::Object::compare(..) method provides a way of comparing two objects, both for type and the contents of the object. The int std::memcpy(..) convention is used, with negative for A<B, zero for A==B and positive for A>B.  The vsg::Inherit<> class provides a very basic compare(..) implementation but it's recommend to implement this locally for any class that holds anything more than simple types.  The [include/vsg/core/compare.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/compare.h) header provides a range of convinience template functions to make the task easier.

~~~ cpp

class MyClass : public vsg::Imhert<vsg::Object, MyClass>
{
public:

    std::string name = "Universe";
    double age = 13.4e9; // years

    int compare(const Object& rhs_object) const override
    {
        int result = Object::compare(rhs_object);
        if (result != 0) return result;

        auto& rhs = static_cast<decltype(*this)>(rhs_object);
        if ((result = vsg::compare_value(name, rhs.name))) return result;
        return vsg::compare_value(age, rhs.age);
    }
};

~~~

## vsg::Visitor and vsg::ConstVisitor

~~~ cpp
virtual void accept(Visitor& visitor);
virtual void traverse(Visitor&) {}

virtual void accept(ConstVisitor& visitor) const;
virtual void traverse(ConstVisitor&) const {}

virtual void accept(RecordTraversal& visitor) const;
virtual void traverse(RecordTraversal&) const {}
~~~


---

Prev: [Metadata](Metadata.md)| Next: [IO](IO.md)

