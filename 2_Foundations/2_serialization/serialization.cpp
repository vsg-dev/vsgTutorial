#include <vsg/all.h>
#include <iostream>

namespace nature
{
    struct Animal : public vsg::Inherit<vsg::Object, Animal>
    {
        std::string name;
        double age = 0.0;

        void read(vsg::Input& input) override
        {
            input.read("name", name);
            input.read("age", age);
        }

        void write(vsg::Output& output) const override
        {
            output.write("name", name);
            output.write("age", age);
        }
    };
}
EVSG_type_name(nature::Animal)

// register a nature::Animal::create() method to the vsg::ObjectFactory::instance() singleton
// so it can be used when reading files.
vsg::RegisterWithObjectFactoryProxy<nature::Animal> s_Register_Animal;

int main(int, char**)
{

    // create our animal object
    auto animal = nature::Animal::create();
    animal->name = "Fido";
    animal->age = 3.5;

    std::cout<<"animal = "<<animal<<", name = "<<animal->name<<", age = "<<animal->age<<std::endl;

    // write the animal object to file, using the .vsgt extension to select the VSG's native ascii file format writer.
    vsg::write(animal, "animal.vsgt");

    // load
    if (auto loaded_animal = vsg::read_cast<nature::Animal>("animal.vsgt"))
    {
        std::cout<<"loaded_animal = "<<loaded_animal<<", name = "<<loaded_animal->name<<", age = "<<loaded_animal->age<<std::endl;
    }
    else
    {
        std::cout<<"Failed to load animal file"<<std::endl;
    }

    return 0;
}
