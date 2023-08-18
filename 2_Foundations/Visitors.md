---
layout: page
title: Visitors
permalink: /foundations/Visitors
---

The vsg::Visitor and vsg::ConstVisitor base classes are a variation of the [Visitor Design Pattern](https://en.wikipedia.org/wiki/Visitor_pattern) designed specifically for scene graphs. The particular challenge for scene graphs is that not only can there be many different types of objects in a scene graph, but how the children should be visited can also vary from node to node and from visitor to visitor.

To resolve this the Design Pattern's Object::accept(..)/Visitor::apply() method pairing is accompanied by an Object::traverse(..) method which is coupled with the Visitor taking responsibility of traversal calling the Object::traverse(..) method when/where it is appropriate. In this section we will see how this is implemented, how you write and use your own visitors and the advantages that this Visitor Design Pattern variation provides.

## vsg::Object, vsg::Visitor and vsg::ConstVisitor API

The [vsg::Object](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Object.h) class provides virtual non const and const accept() and traverse() methods that should be implemented by subclasses:

~~~ cpp
virtual void accept(Visitor& visitor);
virtual void traverse(Visitor&) {}

virtual void accept(ConstVisitor& visitor) const;
virtual void traverse(ConstVisitor&) const {}
~~~

The [vsg::Inherit<>](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Inherit.h) template class provides implementations for the accept(Visitor&) and accept(ConstVisitor&) virtual functions, note the visitor.apply(..) which follows the Visitor Design Pattern convention of an Object::accept(..)/Visitor::apply(..) pairing:

~~~ cpp
void accept(Visitor& visitor) override { visitor.apply(static_cast<Subclass&>(*this)); }
void accept(ConstVisitor& visitor) const override { visitor.apply(static_cast<const Subclass&>(*this)); }
~~~


The [vsg::Visitor](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Visitor.h) and [vsg::ConstVisitor](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/ConstVisitor.h) base classes provide virtual apply(..) methods for each type that that visitor supports. Almost all scene graph related objects have entries in the Visitor & ConstVisitor classes, the following is a small snippet of these (click the [Visitor.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Visitor.h#L148) link for the full list):

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

Those familiar with the OpenSceneGraph will note similarities with the [osg::NodeVisitor](https://github.com/OpenSceneGraph/OpenSceneGraph/blob/master/include/osg/NodeVisitor), both implementations follow the same Visitor Design Pattern variation but the VulkanSceneGraph generalizes it to work on almost all object types and has both const and non const versions, whether it's data objects, scene graph nodes through to UI events the VulkanSceneGraph Visitors can handle all these use cases. The osg::NodeVisitor has support for 25 different node types, while the VulkanSceneGraph supports 214 different object types.

## Cascading apply()

The default apply(..) implementations provided by vsg::Visitor and vsg::ConstVisitor are designed to cascade from the best match back up the inheritance chain to the more and more general types, the following is an edited/annotated snippet from [Visitor.cpp](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/src/vsg/core/Visitor.cpp):

~~~ cpp
void Visitor::apply(Object&)
{
    // if Visitor::apply(Object&) isn't implemented by the Visitor subclass, this
    // method is implemented as a non op
}

void Visitor::apply(Data& value)
{
    // if Visitor::apply(Data& value) isn't implemented by the Visitor subclass, this
    // default implementation will be invoked and cast to parent class Object and call above method
    apply(static_cast<Object&>(value));
}

void Visitor::apply(stringValue& value)
{
    // if Visitor::apply(stringValue& value) isn't implemented by the Visitor subclass, this
    // default implementation will be invoked and cast to parent class Data and call above method
    apply(static_cast<Data&>(value));
}
~~~

This cascading simplifies implementations so they only need to override specific apply(..) methods of interest, and let the default implementations handle all the other types for you, we'll use this in all the custom Visitor examples below.

## Traversal under your control

By design none of the default apply(..) methods provided by vsg::Visitor and vsg::ConstVisitor undertake any type of traversal, the decision on which objects to traverse and how to traverse them is left to visitor subclasses. The vsg::Object::traverse(..) method can be used by Visitor subclasses to handle traversal of an object's children when this is required, or Visitor subclasses can implement their own traversal of an object's children.

One of the advantages of giving responsibility to the visitor implementation is you can do operations before and after traversing a subgraph, for instance we use this to increment/decrement an indent as we traverse a graph. The following is a snippet from the PrintVisitor example that we'll expand upon later in this section.

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

The scene graph also has 64bit node and traversal [masks](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Mask.h) that can be used by visitors to determine which branches to follow, the [visitor base classes](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Vistor.h#L140) provide the following members to facilitate visitors using node/traversal masks:

~~~ cpp
Mask traversalMask = MASK_ALL;
Mask overrideMask = MASK_OFF;
~~~

A subgraph will be visited when the result of `(nodeMask | visitor.overrideMask) & visitor.traversalMask)!=0`. In chapters 3 & 4 we'll go into the use of node and traversal masks in detail, showing scene graph nodes and application level classes that use them.

## PrintVisitor example

The following [PrintVisitor](https://github.com/vsg-dev/vsgTutorial/blob/master/2_Foundations/2_PrintVisitor/) example does traversal of a graph and provides methods to print out specific properties associated with types of interest:

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

// construct our visitor and then pass it to root node to invoke the visitor.
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

## Visitors provided by the VulkanSceneGraph project

The VulkanSceneGraph employs visitors for utilities for end users as well as using them to implement core features. In addition to providing useful functionality, the built in visitors also serve as a good example of the range of tasks you can tackle with them, and how to implement your own. When reviewing the following examples look for the apply(..) methods that override the base Visitor/ConstVisitor::apply(..) methods as a guide to what type of objects they handle:

### Event handling:

| Class | Header | Description |
| CountGlyphs | [text/Text.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/text/Text.h#L63) | Utility for counting text glyphs |
| CollectEvents | [ui/CollectEvents.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/ui/CollectEvents.h#L22) | Collects events |
| PlayEvents | [ui/PlayEvents.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/ui/PlayEvents.h#L22) | Plays events |
| RecordEvents | [ui/RecordEvents.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/ui/RecordEvents.h#L23) | Records events for later playback |
| PrintEvents | [ui/PrintEvents.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/ui/PrintEvents.h#L21) | Print details of events |
| ShiftEventTime | [ui/ShiftEventTime.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/ui/ShiftEventTime.h#L22) | Shifts the time of an event |
| Trackball | [app/Trackball.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/Trackball.h#L27) | Event handler that controls the Camera view matrix |
| CloseHandler | [app/CloseHandler.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/CloseHandler.h#L21) | On specified event signal viewer should be closed. |
| AnimationPathHandler | [utils/AnimationPath.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/utils/AnimationPath.h#L61) | Updates a Camera view matrix along a path |

### Utilities:

| Class | Header | Description |
| ComputeTransform | [maths/transform.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/maths/transform.h#L249) | Accumulates the transforms along a node path |
| FindCameras | [app/Camera.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/Camera.h#L46) | Find all the Cameras in a graph |
| ShaderCompiler | [utils/ShaderCompiler.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/utils/ShaderCompiler.h#L10) | Compile GLSL shaders to SPIR-V |
| ComputeBounds | [utils/ComputeBounds.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/utils/ComputeBounds.h#L21) | Compute the bounds of a subgraph |
| LoadPagedLOD | [utils/LoadPagedLOD.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/utils/LoadPagedLOD.h#L23) | Preload PagedLOD children |
| Intersector | [utils/Intersector.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/utils/Intersector.h#L21) | Intersector base class |
| ArrayState | [state/ArrayState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ArrayState.h#L24) | Track the array bindings in the scene graph during traversal |

### Application setup:

| Class | Header | Description |
| CollectResourceRequirements | [vk/ResourceRequirements.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master//include/vsg/vk/ResourceRequirements.h#L92) | Collects all the resources required by a scene graph |
| CompileTraversal | [app/CompileTraversal.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/CompileTraversal.h#L31) | Creates Vulkan objects and transfers data to the GPU |
| WindowResizeHandler | [app/WindowResizeHandler.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/WindowResizeHandler.h#L24) | Updates the GraphicsPipelines in a scene graph for new viewport dimensions |

## RecordTraversal

The RecordTraversal class is similar to the visitor classes but it's not implemented with the double dispatch (two virtual functions) that the visitor classes use. The RecordTraversal is supported by [vsg::Object](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Object.h#L85) via the two virtual methods:

~~~  cpp
virtual void accept(RecordTraversal& visitor) const;
virtual void traverse(RecordTraversal&) const {}
~~~

The part that is different are the [RecordTraversal::apply()](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/RecordTraversal.h#L97) methods which are straightforward class methods rather than virtual methods like those used in visitors. This is done to reduce the number of virtual functions being invoked during the traversal that is most critical to performance, but does mean that one can't subclass from RecordTraversal and override the apply methods - the choice is to favor performance over extensibility.

While the RecordTraversal itself is not designed to be extended, users can implement custom nodes that override the vsg::Object's virtual apply(RecordTraversal) & traverse(RecordTraversal&) methods to customize how the RecordTraversal handles the custom nodes.

## Visitor and user defined subclasses

One of the weaknesses of the Visitor Design Pattern is that the Visitor class must have a virtual apply(..) method for each supported type, if a user presents a new subclass that isn't directly supported it will be treated as the subclasses parent class. For instance if you create a vsg::MyData subclass from vsg::Data, when passed to a vsg::Visitor it will be matched to the Visitor::apply(Data&) method.

The vsgExamples repository contains the [vsgvisitorcustomtype](https://github.com/vsg-dev/vsgExamples/tree/master/examples/core/vsgvisitorcustomtype) example that illustrates two approaches to extending visitor types.

---

Prev: [Run Time Time Identification (RTTI)](RTTI.md)| Next: [read/write](ReaderWriter.md)

