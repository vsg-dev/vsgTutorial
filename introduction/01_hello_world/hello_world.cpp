#include <vsg/all.h>
#include <vsgXchange/all.h>

#include <iostream>

int main(int, char**)
{
    // create options object that is used to guide IO operations
    auto options = vsg::Options::create();
    options->add(vsgXchange::all::create());

    // create the scene graph using OpenStreetMap convenience function
    auto scene = vsg::TileDatabase::create();
    scene->settings = vsg::createOpenStreetMapSettings(options);
    scene->readDatabase(options);

    // create the viewer and assign window(s) to it
    auto viewer = vsg::Viewer::create();

    // create window with default traits
    auto windowTraits = vsg::WindowTraits::create();
    auto window = vsg::Window::create(windowTraits);
    viewer->addWindow(window);

    // set up the camera
    double radius = vsg::WGS_84_RADIUS_EQUATOR;
    double nearFarRatio = 0.0001;

    auto lookAt = vsg::LookAt::create(vsg::dvec3(0.0, -radius*4.5, 0.0), vsg::dvec3(0.0, 0.0, 0.0), vsg::dvec3(0.0, 0.0, 1.0));
    auto perspective = vsg::Perspective::create(30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio*radius, radius * 4.5);
    auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));

    // add close handler to respond to pressing the window close window button and pressing escape
    viewer->addEventHandler(vsg::CloseHandler::create(viewer));

    // add a trackball event handler to control the camera view use the mouse
    viewer->addEventHandler(vsg::Trackball::create(camera));

    // create a command graph to render the scene on specified window
    auto commandGraph = vsg::createCommandGraphForView(window, camera, scene);
    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

    // compile all the the Vulkan objects and transfer data required to render the scene
    viewer->compile();

    // rendering main loop
    while (viewer->advanceToNextFrame())
    {
        // pass any events into EventHandlers assigned to the Viewer
        viewer->handleEvents();

        viewer->update();

        viewer->recordAndSubmit();

        viewer->present();
    }

    // clean up done automatically thanks to ref_ptr<>
    return 0;
}
