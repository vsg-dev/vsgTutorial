---
layout: page
title: Metadata - "data that provides information about other data"
permalink: /foundations/MetaData
---

The vsg::Object base class has support for Metadata - user named values and objects that can be assigned to and retrieved from objects. Metadata provides an easy way to associate application specific data with scene graph objects without requiring subclassing and extending the scene graph. Serailization support is provided so that all the user assign values can be stored and retrieved along with the rest of the standard scene graph objects.

## Setting and getting named objects

The foundation of vsg::Object Metadata is a collection of setObject(key, object)/getObject(key)/getRefObject(key) methods to provide users a way of associating objects with string keys that they can later use to retrieve the objects:

~~~ cpp
        /// assign an Object associated with key
        void setObject(const std::string& key, ref_ptr<Object> object);

        /// get Object pointer associated with key, return nullptr if no object associated with key has been assigned
        Object* getObject(const std::string& key);

        /// get const Object pointer associated with key, return nullptr if no object associated with key has been assigned
        const Object* getObject(const std::string& key) const;

        /// get object pointer of specified type associated with key, return nullptr if no object associated with key has been assigned
        template<class T>
        T* getObject(const std::string& key) { return dynamic_cast<T*>(getObject(key)); }

        /// get const object pointer of specified type associated with key, return nullptr if no object associated with key has been assigned
        template<class T>
        const T* getObject(const std::string& key) const { return dynamic_cast<const T*>(getObject(key)); }

        /// get ref_ptr<Object> associated with key, return nullptr if no object associated with key has been assigned
        ref_ptr<Object> getRefObject(const std::string& key);

        /// get ref_ptr<const Object> pointer associated with key, return nullptr if no object associated with key has been assigned
        ref_ptr<const Object> getRefObject(const std::string& key) const;

        /// get ref_ptr<T> of specified type associated with key, return nullptr if no object associated with key has been assigned
        template<class T>
        ref_ptr<T> getRefObject(const std::string& key) { return getRefObject(key).cast<T>(); }

        /// get ref_ptr<const T>  of specified type associated with key, return nullptr if no object associated with key has been assigned
        template<class T>
        const ref_ptr<const T> getRefObject(const std::string& key) const { return getRefObject(key).cast<const T>(); }

        /// remove meta object or value associated with key
        void removeObject(const std::string& key);
~~~

The vsg::Object class implements these methods using a [vsg::Auxilary](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Axuliary.h)) object. vsg::Auxliary object provides both observer_ptr<> support and the std::map<std::string, ref_ptr<Object>> that holds the user assigned objects.  The vsg::Auxiliary object is only created and assigned to an vsg::Object when an oberver_ptr<> and/or Metadata are required, as most scene graph objects don't require either most object will just have a null Axuliary pointer.

## Setting and getting named values

To provide support for standard C++ types like std::string, float and simple scene graph types like vsg::vec4, vsg::Object provides template setValue() and getValue() methods:

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

These setValue(key, value)/getValue(key) methods build upon the setObject(key, value)/getObject(key) functionality using the vsg::Value<> template data class as an adapter. This adaptation is done for you so users can just focus on the basic types that wish to use.  Object::getValue(key, value) return true when the object of the matching Value<> is found in the Auxiliary::usersObjects map, otherwise it returns false.  It is important to exactly match the types between setValue(key, value) and getValue(key, value) as no implicit type conversion is supported, i.e. setting with a float get attempting to get with a double will not find a match and always return false.

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
~~~

As the Object::setValue(key, value), getValue(key, value) functionality is built upon vsg::Value you can also get the value object:

~~~ cpp
    // you can get the underlying object using the same key:
    auto object = object->getRefObject("value");
    std::cout<<"object = "<<object<<std::end;

    // or cast it to specific type by providing the apprpriate type
    if (auto value = object->getRefObject<vsg::floatValue>("value"))
    {
        std::cout<<"valiue = "<<value->value()<<std::emdl;
    }
}
~~~


Prev: Next: [Data Types](DataTypes.md)| Next: [vsg::Allocator](Allocator.md)

