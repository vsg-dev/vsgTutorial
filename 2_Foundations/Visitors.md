---
layout: page
title: RTTI & Visitors
permalink: /foundations/Visitors
---

The VulkanSceneGarph provides a number of features that provide richer and more efficient Run Time Type Information (RTTI) and type safe operations than are provided by C++ itself. These features are provided by the vsg::Object base class and by two companion bass classes, the vsg::Visitor and vsg::ConstVisitor, that are scene graph specific implementation of Visitor Desgin Pattern, with the vsg::Inherit CRTP class providing convinient implementations of the required methods.

## RTTI features provide vsg::Object

The vsg::Object base class provides the follow methods dedicated to RTTI:

~~~ cpp
virtual const char* className() const noexcept { return type_name<Object>(); }

/// return the std::type_info of this Object
virtual const std::type_info& type_info() const noexcept { return typeid(Object); }
virtual bool is_compatible(const std::type_info& type) const noexcept { return typeid(Object) == type; }

template<class T>
T* cast() { return is_compatible(typeid(T)) ? static_cast<T*>(this) : nullptr; }

template<class T>
const T* cast() const { return is_compatible(typeid(T)) ? static_cast<const T*>(this) : nullptr; }

/// compare two objects, return -1 if this object is less than rhs, return 0 if it's equal, return 1 if rhs is greater,
virtual int compare(const Object& rhs) const;
~~~

The vsg::Object::className() method is implemented using the vsg::type_name<> template function, specializations of vsg::type_name<> are in turn provided by the VSG_type_name() and EVSG_type_name() macro functions that can be placed before/after a class defintion, both of these features are defined in [include/vsg/core/value_type.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/type_name.h). The VSG_type_name() macro can be used for classes within the vsg namespace like [vsg::Group](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/group.h). While the EVSG_type_name() version can be used for classes defined in other namespaces, such as what you see in [vsgXchange](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/all.h#L43).

The vsg::Object::type_info() methods provides a convinient way to access the std::type_info of a particular object, and vsg::Object::is_compatible(const std::type_info&) method provides a method that can not just check whether a type is the same, but whether it may be derived from that type thus compatible with treatment as that type. The vsg::Inherit<> class can be used to automatically implement the required type_info() and is_compatible() methods.

The vsg::Object::cast<>() template methods use the Object::is_compatible() method to decide whether a type can by cast directly to a desired type using static_cast<> without the high CPU overhead of invoking dynamic_cast<>.

The vsg::Object::compare(..) method provides a way of comparing two objects, both for type and the contents of the object. The int std::memcpy(..) convention is used, with negative for A<B, zero for A==B and positive for A>B.  The vsg::Inherit<> class provides a very basic compare(..) implementation but it's recommend to implement this locally for any class that holds anything more than simple types.  The [include/vsg/core/compare.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/compare.h) header provides a range of convinience template functions to make the task easier.

To illustrate these features, with the [rtti example](2_rtti/rtti.cpp) example, we'll declare a custom class in it's own namespace and use Inherit to implement the RTTI methods, EVSG_type_name to provide the human readable nameing and the implement compare() method.
~~~ cpp
namespace astro
{
    class Body : public vsg::Inherit<vsg::Object, Body>
    {
    public:

        std::string name = "Universe";
        double age = 13.4e9; // years

        int compare(const Object& rhs_object) const override
        {
            int result = Object::compare(rhs_object);
            if (result != 0) return result;

            auto& rhs = static_cast<decltype(*this)>(rhs_object);
            if ((result = vsg::compare_value(age, rhs.age))) return result;
            return vsg::compare_value(name, rhs.name);
        }
    };
}
EVSG_type_name(astro::Body)
~~~

We can then use this functionality in application code:

~~~ cpp
    // second constructed body object
    auto sun = astro::Body::create();
    sun->name = "Sun";
    sun->age = 5.603; // 4.603 billion years

    auto earth = astro::Body::create();
    earth->name = "Earth";
    earth->age = 4.543; // 4.543 billion years

    auto moon = astro::Body::create();
    moon->name = "Moon";
    moon->age = 4.51; // 4,51 billion years

    auto mars = astro::Body::create();
    mars->name = "Mars";
    mars->age = 4.603; // 4.603 billion years

    std::vector<vsg::ref_ptr<astro::Body>> bodies{sun, mars, earth, moon};

    std::cout<<"Bodies before sorting"<<std::endl;
    for(auto& body : bodies)
    {
        std::cout<<"    pointer = "<<body<<", class = "<<body->className()<<", name = "<<body->name<<", age = "<<body->age<<std::endl;
    }

    // copy the bodies container over to a more generic objects containers,
    // to illustrate how subclassing still works with more generic types
    std::vector<vsg::ref_ptr<vsg::Object>> objects(bodies.begin(), bodies.end());

    auto satellite = vsg::Object::create();
    satellite->setValue("name", "Hubble Space Telescope");
    objects.push_back(satellite);

    auto spacecraft = vsg::Object::create();
    spacecraft->setValue("name", "Apollo 11");
    objects.push_back(spacecraft);

    // use the vsg::DereferenceLess functor which implements the < operator
    // that dereferences the ref_ptr<> and compares using the custom Object::compare(),
    std::sort(objects.begin(), objects.end(), vsg::DereferenceLess());

    std::cout<<"Bodies after adding extra objects and sorting"<<std::endl;
    for(auto& object : objects)
    {
        // to access the specific Body member variables we need to cast from ref_ptr<vsg::Object> to ref_ptr<astro::Body>
        // ref_ptr<>.cast() is implemented using th vsg::Object::cast<>() to efficiently replace a dynamic_cast<>.
        if (auto body = object.cast<astro::Body>())
        {
            std::cout<<"    pointer = "<<body<<", class = "<<body->className()<<", name = "<<body->name<<", age = "<<body->age<<std::endl;
        }
        else
        {
            if (std::string name; object->getValue("name", name))
            {
                std::cout<<"    pointer = "<<object<<", class = "<<object->className()<<", name = "<<name<<std::endl;
            }
            else
            {
                std::cout<<"    pointer = "<<object<<", class = "<<object->className()<<std::endl;
            }
        }
    }
~~~

---

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

Prev: [Metadata](Metadata.md)| Next: [IO](IO.md)

