---
layout: page
title: Visitors
permalink: /foundations/Visitors
---

The vsg::Visitor and vsg::ConstVisitor base classes are a variation of the [Visitor Desgin Pattern](https://en.wikipedia.org/wiki/Visitor_pattern) designed specifically for scene graphs. The particular challenge for scene graphs is that not only can there be many different types of objects in a scene graph, but how the children should be visited can also vary from node to node and from visitor to visitor.

To resolve this the Design Pattern's Object::accept(..)/Viistor::apply() method pairing is accompanied by a Object::traverse(..) method which is coupled with the Visitor taking resonisibility of traversal calling the Ojbect::traverse() method when/where it is approproate. In this section will see how this is implemented, how you write and use your own visitors and advantages that this Visitor Design Pattern variation provides.

## vsg::Object, vsg::Visitor and vsg::ConstVisitor API

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


The [vsg::Visitor](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Visitor.h) and [vsg::ConstVisitor](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/ConstVisitor.h) based class provide virtual apply(..) methods for each type that that visitor supports. Almost all scene graph related objects have entries in the Visitor & ConstVisitor classes, follows is a small snippet of these (click the [Visitor.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Visitor.h#L148) link for the full list):

~~~ cpp
// Values
virtual void apply(stringValue&);
virtual void apply(boolValue&);
virtual void apply(intValue&);
virtual void apply(uintValue&);
virtual void apply(floatValue&);
virtual void apply(doubleValue&);
virtual void apply(vec2Value&);
virtual void apply(vec3Value&);
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

Those familiar with the OpenSceneGraph will note similarities the [osg::NodeVisitor](https://github.com/OpenSceneGraph/OpenSceneGraph/blob/master/include/osg/NodeVisitor), both implementations follow the same Visitor Design Pattern variation but the VulkanSceneGraph generalizes it to work on almost all object types and has both const and non const versions, whther it's data objects, scene graph nodes through to UI events the VulkanSceneGraph Visitors can handle all these usage cases. The osg::NodeVisitor has support for 25 different node types, while the VulkanSceneGraph supports 214 different object types.

## Cascading apply()

The default apply(..) implementations provided by vsg::Visitor and vsg::ConstVisitor are designed to cascade from the best match back up the inheritance chain to the more and more general types, following is a edit/annotaed snipet from [Visitor.cpp](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/src/vsg/core/Visitor.cpp):

~~~ cpp
void Visitor::apply(Object&)
{
    // if Visitor::apply(Object&) isn't implemented by Visitor subclass this
    // method is implemented by is a non op
}

void Visitor::apply(Data& value)
{
    // if Visitor::apply(Data& value) isn't implemented by Visitor subclass this
    // default implementation will be invoked and cast to parent class Object and call above method
    apply(static_cast<Object&>(value));
}

void Visitor::apply(stringValue& value)
{
    // if Visitor::apply(stringValue& value) isn't implemented by Visitor subclass this
    // default implementation will be invoked and cast to parent class Data and call above method
    apply(static_cast<Data&>(value));
}
~~~

This cascading simplifies implementations so they only need to override specific apply(..) methods of interest, and let the default implementations handle all the other types for you, we'll use this in all the custom Visitor examples below.

## Traversal under your control

By design none of the default apply(..) methods provide by vsg::Visitor nd vsg::ConstViisotr provide traversal support, the decision on which objects to traverse and how to traverse them is left to visitor subclasses.  The vsg::Object::traverse(..) method can be used by Visitor subclasses to handle traversal of an objects children when this is required, or Visitor subclasses can implement their own traversal of an objects children.

One of the advantages of giving responsibility to the visitor implementation is you can do operations before and after traversing a subgraph, for instance we use this to increment/decrment a indent as we traverse a graph, follows is snippet from the PrintVisitor example that we'll expand upon later in this section.

~~~ cpp
struct PrintVisitor : public vsg::Inherit<vsg::ConstVisitor, PrintVisitor>
{
    size_t indent = 0;
    void apply(const vsg::Object& object) override
    {
        for(size_t i=0; i<indent; ++i) std::cout<<" ";
        std::cout<<"Visiting "<<object.className()<<std::endl;

        indent += 4;
        object.traverse(*this);
        indent -= 4;
    }
...
};
~~~

The scene graph also has nodes that add 64bit node and traversal [masks](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Mask.h) that can be used by visitors to determine which branches to follow, the visitor base classes provide the following members to facilitate visitors using traversal masks:

~~~ cpp
Mask traversalMask = MASK_ALL;
Mask overrideMask = MASK_OFF;
~~~

The principle behind masks is a subgraph will be visited when the result of '(nodeMask | visitor.overrideMask) & visitor.traversalMask)!=0'. In the 3 and 4th chapters we'll go into the use of node and traversal masks in detail when introduce the scene graph nodes and application level classes that use them.

## PrintVisitor example

The following [PrintVisitor](https://github.com/vsg-dev/vsgTutorial/blob/master/2_Foundations/2_PrintVisitor/) example does traversal of a graph and provide methods to print out speciifc properties associated with types of interest:

~~~ cpp
struct PrintVisitor : public vsg::Inherit<vsg::ConstVisitor, PrintVisitor>
{
    size_t indent = 0;
    void apply(const vsg::Object& object) override
    {
        for(size_t i=0; i<indent; ++i) std::cout<<" ";
        std::cout<<"Visiting "<<object.className()<<std::endl;

        indent += 4;
        object.traverse(*this);
        indent -= 4;
    }

    void apply(const vsg::stringValue& value) override
    {
        for(size_t i=0; i<indent; ++i) std::cout<<" ";
        std::cout<<"Visiting "<<value.className()<<" "<<value.value()<<std::endl;
    }

    void apply(const vsg::vec3Value& value) override
    {
        for(size_t i=0; i<indent; ++i) std::cout<<" ";
        std::cout<<"Visiting "<<value.className()<<" "<<value.value()<<std::endl;
    }

    void apply(const vsg::doubleArray& array) override
    {
        for(size_t i=0; i<indent; ++i) std::cout<<" ";
        std::cout<<"Visiting "<<array.className()<<" { ";

        for(auto v : array) std::cout<<v<<" ";

        std::cout<<"}"<<std::endl;
    }
};

// create a small graph
auto leaf = vsg::Objects::create();
leaf->addChild(vsg::vec3Value::create(1.0f, 2.0f, 3.0f));

auto nested = vsg::Objects::create();
nested->addChild(leaf);
nested->addChild(vsg::doubleArray::create({4.0, 5.0, 6.0}));

auto root = vsg::Objects::create();
root->addChild(vsg::stringValue::create("Everybody Loves Raymond"));
root->addChild(nested);

// consutruct our visitor and then pass it to root node to invoke the visitor.
PrintVisitor print;
root->accept(print);
~~~

The console output from this example is:

~~~
Visiting vsg::Objects
    Visiting vsg::stringValue Everybody Loves Raymond
    Visiting vsg::Objects
        Visiting vsg::Objects
            Visiting vsg::vec3Value 1 2 3
        Visiting vsg::doubleArray { 4 5 6 }
~~~

---

Prev: [Run Time Time Identification (RTTI)](RTTI.md)| Next: [IO](IO.md)

