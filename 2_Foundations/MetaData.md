---
layout: page
title: Meta Data
permalink: /foundations/Auxiliary
---

All subclass from vsg::Object have support Meta Data - named data that you can assign to objects, retrieve them and serailize them.  The API in vsg::Object to provide Meta Data uses template combinated with the vsg::Value<> data type to adapt standard C++ types like int, float and string, as well as VulkanSceneGraph types like vsg::vec3 etc.

~~~ cpp
    /// meta data access methods
    /// wraps the value with a vsg::Value<T> object and then assigns via setObject(key, vsg::Value<T>)
    template<typename T>
    void setValue(const std::string& key, const T& value);

    /// specialization of setValue to handle passing c strings
    void setValue(const std::string& key, const char* value) { setValue(key, value ? std::string(value) : std::string()); }

    /// get specified value type, return false if value associated with key is not assigned or is not the correct type
    template<typename T>
    bool getValue(const std::string& key, T& value) const;
~~~

It's important to use the same types when getting values, if the type used in getValue() doesn't match the type used in setValue() the getValue() method will return false.

~~~ cpp
{
    float value = 1.0f;
    object->setValue("value", value);
}

{
    float float_value;
    if (object->getValue("value", float_value))
    {
        std::cout<<"found float value = "<<float_value<<std::endl;
    }
    else
    {
        std::cout<<"no float value found."<<std::endl;
    }

    double double_value;
    if (object->getValue("value", double_value))
    {
        std::cout<<"found double value = "<<double_value<<std::endl;
    }
    else
    {
        std::cout<<"no double value found."<<std::endl;
    }

    std::string str_value;
    if (object->getValue("value", str_value))
    {
        std::cout<<"found str value = "<<str_value<<std::endl;
    }
    else
    {
        std::cout<<"no std::string value found."<<std::endl;
    }
}
~~~




Prev: Next: [vsg::observer_ptr<>](observer_ptr.md)| Next: [vsg::Allocator](Allocator.md)

