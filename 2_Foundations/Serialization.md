---
layout: page
    title: Serializaton
permalink: /foundations/Serializaton
---

The VulkanSceneGraph provides extensible serailization support so that all scene graph objects can be read/written from files and streams. This can be used with the native .vsgb binary and .vsgt ascii formats formats as well work with users defined input/ouput through to reading data compiled directly into example as illustrated in use of the vsgXchange::cpp ReaderWriter illustrated in the previous section on vsgXchange.

## vsg::Object, vsg::Input and vsg::Output bas classes

The serializtion support is built upon vsg::Object base class that provides virtual read(Input&) and write(Output&) methods that users override to implement support for their own member variables, and the vsg::Input and vsg::Output classes that provide a standarizaed interface for reading and writing data.  The [vsg::Object](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Object.h#L88) methods are:

~~~ cpp
virtual void read(Input& input);
virtual void write(Output& output) const;
~~~

The [vsg::Input](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Input.h#L37) base class provides the low level pure virtual methods that are implemented by the concrete implementation of Input like vsg::BinaryInput and vsg::AsciiInput as well as set of template methods that meant to be used by the read(Input&) methods to implement the serialization of class members. The later methods take the form of input.read(proptertyName, value):

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

## Ascii and Binary support

Prev: [vsgXchange](vsgXchange.md) | Next : [File Systems](FileSystem.md)

