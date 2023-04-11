---
layout: page
title: Visitors
permalink: /foundations/Visitors
---

Th vsg::Visitor and vsg::ConstVisitor base classes a variation of the [Visitor Desgin Pattern](https://en.wikipedia.org/wiki/Visitor_pattern) designed specifically for scene graphs. The particular challenge for scene graphs is that not only can there be many different types of objects in a scene graph, but how the children should be visited can also vary from node to node, and from visitor to visitor. To resolve this the Design Pattern's Object::accept(..)/Viistor::apply() method pairing is extended to include Object::traverse(..) method which is coupled with Visitor taking resonisibility of traversal calling the Ojbect::traverse() method when/where it is approproate.

## vsg::Visitor and vsg::ConstVisitor

The [vsg::Object](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Object.h) class provides virtual non const and const accept() and traverse() methods that shold be implemeneted by subclasses:

~~~ cpp
virtual void accept(Visitor& visitor);
virtual void traverse(Visitor&) {}

virtual void accept(ConstVisitor& visitor) const;
virtual void traverse(ConstVisitor&) const {}
~~~

The [vsg::Inherit<>](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Inherit.h) template class provided implementations for the accept(Visitor&) and accept(ConstVisitor&) virtual functions, note the visitor.apply(..) which follows the Visitor Design Pattern convention of a Object::accept(..)/Visitor::apply(..) pairing:

~~~ cpp
void accept(Visitor& visitor) override { visitor.apply(static_cast<Subclass&>(*this)); }
void accept(ConstVisitor& visitor) const override { visitor.apply(static_cast<const Subclass&>(*this)); }
~~~


The [vsg::Visitor](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Visitor.h) and [vsg::ConstVisitor](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/ConstVisitor.h) based class provide virtual apply(..) methods for each type that that visitor supports. Almost all scene graph related objects have entries in the Visitor & ConstVisitor classes, follows is a small snippet of these :

~~~ cpp

// Values
virtual void apply(stringValue&);
virtual void apply(boolValue&);
virtual void apply(intValue&);
virtual void apply(uintValue&);
virtual void apply(floatValue&);
virtual void apply(doubleValue&);
virtual void apply(vec2Value&);
virtual void apply(vec4Value&);
...

// Arrays
virtual void apply(byteArray&);
virtual void apply(ubyteArray&);
virtual void apply(shortArray&);
virtual void apply(ushortArray&);
virtual void apply(intArray&);
virtual void apply(uintArray&);
virtual void apply(floatArray&);
virtual void apply(doubleArray&);
virtual void apply(vec2Array&);
virtual void apply(vec3Array&);
...

// Nodes
virtual void apply(Node&);
virtual void apply(Compilable&);
virtual void apply(Commands&);
virtual void apply(Group&);
virtual void apply(QuadGroup&);
virtual void apply(LOD&);
...
~~~


---

Prev: [Run Time Time Identification (RTTI)](RTTI.md)| Next: [IO](IO.md)

