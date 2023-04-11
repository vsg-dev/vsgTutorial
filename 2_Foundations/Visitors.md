---
layout: page
title: RTTI & Visitors
permalink: /foundations/Visitors
---

The VulkanSceneGarph provides a number of features that provide richer and more efficient Run Time Type Information (RTTI) and type safe operations than are provided by C++ itself. These features are provided by via vsg::Object base class and by two companion bass classes, the vsg::Visitor and vsg::ConstVisitor, that are scene graph specific implementation of Visitor Desgin Pattern, with the vsg::Inherit CRTP class providing convinient implementations of the required methods.

## RTTI features provide vsg::Object

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

