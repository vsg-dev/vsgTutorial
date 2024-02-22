---
layout: page
title: Metadata
permalink: /foundations/MetaData
---

***"data that provides information about other data"***

The vsg::Object base class has support for Metadata - user named values and objects that can be assigned to and retrieved from objects.  Metadata provides an easy way to associate application specific data with scene graph objects without requiring subclassing and extending the scene graph.  Serialization support is provided so that all the user assigned values can be stored and retrieved along with the rest of the standard scene graph objects.

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

The vsg::Object class implements these methods using a [vsg::Auxiliary](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Auxiliary.h) object that provides both observer_ptr<> support and the std::map<std::string, ref_ptr<Object>> that holds the user assigned objects.  The vsg::Auxiliary object is only created and assigned to a vsg::Object when an observer_ptr<> and/or Metadata are required.  As most scene graph objects don't require either, most objects will just have a null Auxiliary pointer.

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

These setValue(key, value)/getValue(key) methods build upon the setObject(key, value)/getObject(key) functionality using the vsg::Value<> template data class as an adapter.  This adaptation is done for users so they can just focus on the basic types they wish to use.  Object::getValue(key, value) returns true when the object of the matching Value<> is found in the Auxiliary::userObjects map, otherwise it returns false.  It is important to exactly match the types between setValue(key, value) and getValue(key, value) as no implicit type conversion is supported, i.e. setting with a float then attempting to get with a double will not find a match and return false.

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
~~~

As the Object::setValue(key, value), getValue(key, value) functionality is built upon vsg::Value, you can also get the value object:

~~~ cpp
    // you can get the underlying object using the same key:
    auto object = object->getRefObject("value");
    std::cout<<"object = "<<object<<std::end;

    // or cast it to specific type by providing the appropriate type
    if (auto value = object->getRefObject<vsg::floatValue>("value"))
    {
        std::cout<<"value = "<<value->value()<<std::emdl;
    }
}
~~~

## Listing all meta Objects/Values

The vsg::Auxiliary object assigned to a vsg::Object, in order to provide meta data support, can be queried to list all the meta Objects/Values:

~~~ cpp
auto object = vsg::Object::create();
object->setValue("name", "Adrian Mole");
object->setValue("age", 13.75);

if (auto auxiliary = object->getAuxiliary())
{
    for(auto& [key, object] : auxiliary->userObjects)
    {
        if (auto s = dynamic_cast<vsg::stringValue*>(object.get())) std::cout<<"metadata key = "<<key<<", stringValue = "<<s->value()<<std::endl;
        else if (auto d = dynamic_cast<vsg::doubleValue*>(object.get())) std::cout<<"metadata key = "<<key<<", doubleValue = "<<d->value()<<std::endl;
        else std::cout<<"metadata key = "<<key<<", object = "<<object<<std::endl;
    }
}
else
{
    std::cout<<"No vsg::Auxiliary assigned to Object."<<std::endl;
}
~~~

In the next section we'll discover other ways of determining the type of objects which avoid the need to use the awkward and costly dynamic_cast<> between types.

Prev: [Data Types](DataTypes.md)| Next: [Run-Time Type Information (RTTI)](RTTI.md)
