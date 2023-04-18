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

The [vsg::Input](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Input.h#L37) base class provides the low level pure virtual methods that are implemented by the concrete implementation of Input like vsg::BinaryInput and vsg::AsciiInput as well as methods that meant to be used by the read(Input&) methods to implement the serialization of classes. The later methods take the form of input.read(proptertyName, value):

~~~ cpp
/// treat non standard type as raw data,
template<typename T>
void read(const char* propertyName, ref_ptr<T>& arg)
{
    if (!matchPropertyName(propertyName)) return;
    arg = read().cast<T>();
}

template<typename T>
void readObjects(const char* propertyName, T& values)
{
    if (!matchPropertyName(propertyName)) return;

    uint32_t numElements = 0;
    read(1, &numElements);
    values.resize(numElements);

    using element_type = typename T::value_type::element_type;
    const char* element_name = type_name<element_type>();

    for (uint32_t i = 0; i < numElements; ++i)
    {
        read(element_name, values[i]);
    }
}

template<typename T>
void readValues(const char* propertyName, std::vector<T>& values)
{
    if (!matchPropertyName(propertyName)) return;

    uint32_t numElements = 0;
    read(1, &numElements);
    values.resize(numElements);

    for (uint32_t i = 0; i < numElements; ++i)
    {
        read("element", values[i]);
    }
}

template<typename T>
void readValues(const char* propertyName, std::set<T>& values)
{
    if (!matchPropertyName(propertyName)) return;

    uint32_t numElements = 0;
    read(1, &numElements);

    for (uint32_t i = 0; i < numElements; ++i)
    {
        T v;
        read("element", v);
        values.insert(v);
    }
}

/// match property name and read value(s)
template<typename... Args>
void read(const char* propertyName, Args&... args)
{
    if (!matchPropertyName(propertyName)) return;

    // use fold expression to expand arguments and map to appropriate read method
    (read(1, &(args)), ...);
}

/// read object of a particular type
ref_ptr<Object> readObject(const char* propertyName)
{
    if (!matchPropertyName(propertyName)) return ref_ptr<Object>();

    return read();
}

/// read object of a particular type
template<class T>
ref_ptr<T> readObject(const char* propertyName)
{
    if (!matchPropertyName(propertyName)) return ref_ptr<T>();

    ref_ptr<Object> object = read();
    return ref_ptr<T>(dynamic_cast<T*>(object.get()));
}

/// read object of a particular type
template<class T>
void readObject(const char* propertyName, ref_ptr<T>& arg)
{
    if (!matchPropertyName(propertyName)) return;

    arg = read().cast<T>();
}

/// read a value of particular type
template<typename T>
T readValue(const char* propertyName)
{
    T v{};
    read(propertyName, v);
    return v;
}

/// read a value as a type, then cast it another type
template<typename W, typename T>
void readValue(const char* propertyName, T& value)
{
    W read_value{};
    read(propertyName, read_value);
    value = static_cast<T>(read_value);
}
~~~

The [vsg::Output](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Output.h#L37) base class methods mirror those in vsg::Input, providing the pure virtual methods that are used to implement the low serialization, and then higher level user facing methods that are used by end users, the later take the form output.write(property, value);

~~~ cpp
template<typename T>
void write(const char* propertyName, const ref_ptr<T>& object)
{
    writePropertyName(propertyName);
    write(object);
}

template<typename T>
void writeObjects(const char* propertyName, const T& values)
{
    uint32_t numElements = static_cast<uint32_t>(values.size());
    write(propertyName, numElements);

    using element_type = typename T::value_type::element_type;
    const char* element_name = type_name<element_type>();

    for (uint32_t i = 0; i < numElements; ++i)
    {
        write(element_name, values[i]);
    }
}

template<typename T>
void writeValues(const char* propertyName, const std::vector<T>& values)
{
    uint32_t numElements = static_cast<uint32_t>(values.size());
    write(propertyName, numElements);

    for (uint32_t i = 0; i < numElements; ++i)
    {
        write("element", values[i]);
    }
}

template<typename T>
void writeValues(const char* propertyName, const std::set<T>& values)
{
    uint32_t numElements = static_cast<uint32_t>(values.size());
    write(propertyName, numElements);

    for (auto& v : values)
    {
        write("element", v);
    }
}

/// match propertyname and write value(s)
template<typename... Args>
void write(const char* propertyName, Args&... args)
{
    writePropertyName(propertyName);

    // use fold expression to expand arguments and map to appropriate write method
    (write(1, &(args)), ...);

    writeEndOfLine();
}

void writeObject(const char* propertyName, const Object* object)
{
    writePropertyName(propertyName);
    write(object);
}

/// write a value casting it specified type i.e. output.write<uint32_t>("Value", value);
template<typename W, typename T>
void writeValue(const char* propertyName, T value)
{
    W v{static_cast<W>(value)};
    write(propertyName, v);
}
~~~

## Ascii and Binary support

Prev: [vsgXchange](vsgXchange.md) | Next : [File Systems](FileSystem.md)

