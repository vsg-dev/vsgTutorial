---
layout: page
title: Serialization
permalink: /foundations/Serializaton
---

The VulkanSceneGraph provides extensible serialization support so that all scene graph objects can be read/written from files and streams. This can be used with the native .vsgb binary and .vsgt ascii formats as well work with users defined input/output through to reading data compiled directly into example as illustrated in the use of the vsgXchange::cpp ReaderWriter in the previous section on vsgXchange.

## vsg::Object, Input and Output base classes

The serialization support is built upon the vsg::Object base class that provides virtual read(Input&) and write(Output&) methods that users override to implement support for their own member variables, and the vsg::Input and vsg::Output classes that provide a standardized interface for reading and writing data. The [vsg::Object](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Object.h#L88) methods are:

~~~ cpp
virtual void read(Input& input);
virtual void write(Output& output) const;
~~~

The [vsg::Input](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Input.h#L37) base class provides the low level pure virtual methods that are implemented by the concrete implementation of Input like vsg::BinaryInput and vsg::AsciiInput as well as a set of template methods that are meant to be used by the read(Input&) methods to implement the serialization of class members. The later methods take the form of input.read(propertyName, value):

~~~ cpp
/// treat non standard type as raw data,
template<typename T>
void read(const char* propertyName, ref_ptr<T>& arg);

template<typename T>
void readObjects(const char* propertyName, T& values);

template<typename T>
void readValues(const char* propertyName, std::vector<T>& values);

template<typename T>
void readValues(const char* propertyName, std::set<T>& values);

/// match property name and read value(s)
template<typename... Args>
void read(const char* propertyName, Args&... args);

/// read object of a particular type
ref_ptr<Object> readObject(const char* propertyName);

/// read object of a particular type
template<class T>
ref_ptr<T> readObject(const char* propertyName);

/// read object of a particular type
template<class T>
void readObject(const char* propertyName, ref_ptr<T>& arg);

/// read a value of particular type
template<typename T>
T readValue(const char* propertyName);

/// read a value as a type, then cast it another type
template<typename W, typename T>
void readValue(const char* propertyName, T& value);
~~~

The [vsg::Output](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Output.h#L37) base class methods mirror those in vsg::Input, providing the pure virtual methods that are used to implement the low serialization, and then higher level user facing methods that are used by end users, the later take the form output.write(property, value):

~~~ cpp
template<typename T>
void write(const char* propertyName, const ref_ptr<T>& object);

template<typename T>
void writeObjects(const char* propertyName, const T& values);

template<typename T>
void writeValues(const char* propertyName, const std::vector<T>& values);

template<typename T>
void writeValues(const char* propertyName, const std::set<T>& values);

/// match propertyname and write value(s)
template<typename... Args>
void write(const char* propertyName, Args&... args);

void writeObject(const char* propertyName, const Object* object);

/// write a value casting it specified type i.e. output.write<uint32_t>("Value", value);
template<typename W, typename T>
void writeValue(const char* propertyName, T value);
~~~


## vsg::ObjectFactory

When writing out objects you can simply call **object->write(output)** and the appropriate serialization will be invoked, but when you need to serialize back into a file the appropriate objects have to be created first before their **object->read(input)** method can be invoked to read the object members. The way the VulkanSceneGraph provides a means for creating objects on demand is via the [vsg::ObjectFactory](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/ObjectFactory.h#L24) singleton class, where only one instance of the Factory exists. The vsg::ObjectFactory is an example of [Factory Method Design Pattern](https://en.wikipedia.org/wiki/Factory_method_pattern) and [Singleton Design Pattern](https://en.wikipedia.org/wiki/Singleton_pattern).

The core scene graph classes found in the VulkanSceneGraph library have creation methods automatically assigned to the vsg::ObjectFactory, and the native VSG loaders internally use the ObjectFactory to create all the required objects, so for native .vsgt and .vsgb files one doesn't need to concern oneself with the ObjectFactory - it's simply something used internally by the VSG when loading files.

For cases where applications extend the scene graph objects (like with the native::Animal example below), users have to register their class with the ObjectFactory so that loaders can create an instance of it for each object of that type that the loader needs to create and read into. The ObjectFactory.h header provides the [vsg::RegisterWithObjectFactoryProxy](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/ObjectFactory.h#L54) template helper class to make this task straightforward. The following example includes a static declaration of the proxy object so that during initialization of the application, the required creation method will be automatically registered with the vsg::ObjectFactory singleton.

## Example of implementing serialization

While the range of methods in Input and Output is extensive and potentially overwhelming, usage of these classes is usually quite straightforward, with the template<> methods automatically handling support for you. The [serialization](https://github.com/vsg-dev/vsgTutorial/tree/master/2_Foundations/2_serialization) example illustrates how to implement custom serialization.

~~~ cpp
{% include_relative 2_serialization/serialization.cpp %}
~~~

The output from running this example is:

~~~ sh
$ more animal.vsgt
#vsga 1.0.5
Root id=1 nature::Animal
{
  name "Fido"
  age 3.5
}
~~~

## vsg::Input and vsg::Output subclasses

Orthogonal to the task of implementing serializers for user defined classes the underlying vsg::Input and vsg::Output that implement the integration with the underlying file/stream/memory are also extensible. The native .vsgt Ascii and .vsgb Binary file formats that the [vsg::VSG ReaderWriter](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/VSG.h#L24) provides are implemented via subclassing from vsg::Input and vsg::Output, these subclasses provide a good illustration of what is required, the following table provides links to the relevant header and source files for each of these subclasses:

| base class | subclass | header | source |
| [vsg::Input](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Input.h#L40) | vsg::AsciiInput | [include/vsg/io/AsciiInput.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/AsciiInput.h#L26) | [src/vsg/io/AsciiInput.cpp](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/src/vsg/io/AsciiInput.cpp#L13) |
| [vsg::Output](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Output.h#L37) | vsg::AsciiOutput | [include/vsg/io/AsciiOutput.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/AsciiOutput.h#L24) | [src/vsg/io/AsciiOutput.cpp](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/src/vsg/io/AsciiOutput.cpp#L13) |
| [vsg::Input](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Input.h#L40) | vsg::BinaryInput | [include/vsg/io/BinaryInput.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/BinaryInput.h#L26) | [src/vsg/io/BinaryInput.cpp](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/src/vsg/io/BinaryInput.cpp#L13) |
| [vsg::Output](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Output.h#L37) | vsg::BinaryOutput | [include/vsg/io/BinaryOutput.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/BinaryOutput.h#L24) | [src/vsg/io/BinaryOutput.cpp](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/src/vsg/io/BinaryOutput.cpp#L13) |

The [vsg::VSG ReaderWriter selects](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/src/vsg/io/VSG.cpp#L94) the appropriate Input/Output implementation based on the file extension, so for most use cases there is never any need to create and invoke the Input/Output classes directly in your application. For most use case there will also be no need to write your own subclasses from vsg::Input and vsg::Output, a possible exception would be subclassing from vsg::Input/vsg::Output to implement the reflection support required when integrating with 3rd party languages such as Lua or Python. This type of usage is an advanced topic beyond the scope of this online book, the existing implementations linked to above will be good starting place for seeing what would be required.

Prev: [vsgXchange](vsgXchange.md) | Next : [File Systems](FileSystem.md)

