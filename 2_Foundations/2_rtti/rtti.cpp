#include <vsg/all.h>

#include <iostream>

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

int main(int, char**)
{
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

}
