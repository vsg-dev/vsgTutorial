#include <vsg/all.h>

#include <iostream>

int main(int, char**)
{
    auto scene = vsg::Object::create();

    auto background_process = [](vsg::observer_ptr<vsg::Object> in_scene)
    {
        std::cout<<"   Background thread : has started."<<std::endl;
        while(true)
        {
            // get reference pointer to scene object to make sure it stays alive while we analyse it.
            if (auto ref_scene = in_scene.ref_ptr())
            {
                // do analysis of the scene
                std::cout<<"   Background thread : has ref_scene = "<<ref_scene<<", referenceCount = "<<ref_scene->referenceCount()<<std::endl;
            } // ref_scene ref_ptr<> pointer will destruct and release reference
            else
            {
                std::cout<<"    Background thread : no longer has scene object to work on, so returning."<<std::endl;
                return;
            }

            // sleep for a second, any time the actual scene object could destruct
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    };

    auto thread = std::thread(background_process, vsg::observer_ptr<vsg::Object>(scene));

    for(int i=0; i<50; ++i)
    {
        std::cout<<"Main thread : scene = "<<scene<<" referenceCount = "<<scene->referenceCount()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    scene = {}; // remove reference to object

    std::cout<<"Main thread : removed reference to scene object, scene = "<<scene<<std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    thread.join();

    std::cout<<"Main thread : background thread has been joined "<<std::endl;
}
