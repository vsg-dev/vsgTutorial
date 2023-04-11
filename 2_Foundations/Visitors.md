---
layout: page
title: Visitors
permalink: /foundations/Visitors
---

Th vsg::Visitor and vsg::ConstVisitor base class that are scene graph centric implementations of [Visitor Desgin Pattern](https://en.wikipedia.org/wiki/Visitor_pattern). The particular challenge for scene graphs is that not only can there be many different types in a scene graph but how the children of each shoud be visited can also vary.


As a scene graph is graph data structure, the hiearchy is important to most operations on the scene graph, and operations that you can apply to it can be done on many objects within the hierarchy, and how traversersal should be be done

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

Prev: [Run Time Time Identification (RTTI)](RTTI.md)| Next: [IO](IO.md)

