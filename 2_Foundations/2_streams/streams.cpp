#include <vsg/all.h>
#include <iostream>

int main(int, char**)
{
    vsg::vec3 position = {1.0, 2.0, 3.0};

    vsg::dquat rotation(vsg::radians(90.0), vsg::dvec3(0.0, 0.0, 1.0));

    vsg::mat4 matrix = { 2.0, 0.0, 0.0, 0.0,
                        0.0, 2.0, 0.0, 0.0,
                        0.0, 0.0, 2.0, 0.0,
                        0.0, 0.0, 0.0, 1.0};

    auto place = vsg::stringValue::create("Paris");

    std::cout<<"position = "<<position<<std::endl;
    std::cout<<"rotation = "<<rotation<<std::endl;
    std::cout<<"matrix = "<<matrix<<std::endl;
    std::cout<<"place = "<<place<<std::endl;

    return 0;
}
