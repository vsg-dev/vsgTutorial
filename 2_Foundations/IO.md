---
layout: page
title: Input & Output
permalink: /foundations/IO
---

The VulkanSceneGraph provides extensiuble support for reading/writing scene graph and asscated objects. Extensibility can be found at the low level of serializaton support for individual objects and high level with ReaderWriters that support reading/writing of single or collections of objects to files/streams.   Cross platform file system functionality is also provided where C++17 support is lacking. An extensible vsg::Logger and i/ostrream support for native types rounds out functionality found in the [include/vsg/io](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io) directory.

## Reading & Writing

The VulkanSceneGraph library provides extensible reading/writing support for scene graph and associated objects via the vsg::ReaderWriter class.  Subclasses of RenaderWriter provided by the VulkanSceneGraph library itself are:

* [vsg::VSG](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/vsg.h#L25) - reading/writing native .vsgt ascci & .vsgb binary file format
* [vsg::spirv](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/spirv.h#L25) - reading/wiring .spv SPIRV shader files
* [vsg::glsl](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/glsl.h#L25) - reading GLSL shader files.
* [vsg::txt](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/txt.h#L25) - reading text files as vsg::stringValue for later parsing by users
* [vsg::tile](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/tile.h#L25) - native tile based database paging

Developers may call ReaderWriter directly, but for must usage cases they will use the vsg::read() and read_cast<T>() functions that are found in [include/vsg/io/read.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h) header. The vsg::read*() functions will invoke the appropriate ReaderWriter based on the file extension, usage:

~~~ cpp
// read a file and on success return vsg::ref_ptr<vsg::Object> to the loaded object
auto object = vsg::read("object.vsgt");

// use read_cast<T> to cast to specific type and ref_ptr<T> pointer
auto data = vsg::read_cast<vsg::Data>("image.vsgt");

// use read_cast<T> to cast to specific type and ref_ptr<T> pointer
auto vertexShader = vsg::read_cast<vsg::ShaderStage>("shader.vert");
~~~

Write function are found in [include/vsg/io/write.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h), usage is in form:

~~~ cpp
// create an object
auto value = vsg::stringValue("mystring");

// write to native ascii file format
vsg::write(value, "value.vsgt");
~~~

## Options & vsgXchange intro

Customization and extension of reading and writing is provided by the [vsg::Options](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/Options.h) object that can be passed to the vsg;:read(..) and vsg::write(..) methods. You can pass in the ReaderWriters that you wish to used, placing them in the order you want them invoked. vsg::Options is subclassed from vsg::Object so has all the standard meta data capabilities and adds IO specific settings. The most common task will be passing in the paths to search for files, and the ReaderWriters to check, such as adding in support for the ReaderWriter's provided by vsgXchange:

~~~ cpp
#include <vsg/all.h>
#include <vsgXchange/all.h>

int main(int, char**)
{
    auto options = vsg::Options::create();

    // set up the paths
    options->paths = vsg::getEnvPaths("VSG_FILE_PATH");

    // assing the ReaderWriter's to use when read/writing
    options->add(vsgXchange::all::create());

    // load GLTF model use vsgXchange::assimp that is included in vsgXchange::all, passing in options so read knows what to use.
    auto model = vsg::read_cast<vsg::Node>("glTF-Sample-Models/2.0/FlightHelmet/glTF/FlightHelmet.gltf", options);
    return 0;
}

~~~


The full options available are:
~~~ cpp
class VSG_DECLSPEC Options : public Inherit<Object, Options>
{
public:
    Options();
    explicit Options(const Options& options);

    template<typename... Args>
    explicit Options(Args... args)
    {
        (add(args), ...);
    }

    Options& operator=(const Options& rhs) = delete;

    /// read command line options, assign values to this options object to later use with reading/writing files
    virtual bool readOptions(CommandLine& arguments);

    void read(Input& input) override;
    void write(Output& output) const override;

    void add(ref_ptr<ReaderWriter> rw = {});
    void add(const ReaderWriters& rws);

    ref_ptr<SharedObjects> sharedObjects;
    ReaderWriters readerWriters;
    ref_ptr<OperationThreads> operationThreads;

    /// Hint to use when searching for Paths with vsg::findFile(filename, options);
    enum FindFileHint
    {
        CHECK_ORIGINAL_FILENAME_EXISTS_FIRST, /// check the filename exists with it's original path before trying to find it in Options::paths.
        CHECK_ORIGINAL_FILENAME_EXISTS_LAST,  /// check the filename exists with it's original path after failing to find it in Options::paths.
        ONLY_CHECK_PATHS                      /// only check the filename exists in the Options::paths
    };
    FindFileHint checkFilenameHint = CHECK_ORIGINAL_FILENAME_EXISTS_FIRST;

    Paths paths;

    using FindFileCallback = std::function<Path(const Path& filename, const Options* options)>;
    FindFileCallback findFileCallback;

    Path fileCache;

    Path extensionHint;
    bool mapRGBtoRGBAHint = true;

    /// Coordinate convention to use for scene graph
    CoordinateConvention sceneCoordinateConvention = CoordinateConvention::Z_UP;

    /// Coordinate convention to assume for specified lower case file formats extensions
    std::map<Path, CoordinateConvention> formatCoordinateConventions;

    /// User defined ShaderSet map, loaders should check the available ShaderSet used the name of the type ShaderSet.
    /// Standard names are :
    ///     "pbr" will substitute for vsg::createPhysicsBasedRenderingShaderSet()
    ///     "phong" will substitute for vsg::createPhongShaderSet()
    ///     "flat" will substitute for vsg::createFlatShadedShaderSet()
    ///     "text" will substitute for vsg::createTextShaderSet()
    std::map<std::string, ref_ptr<ShaderSet>> shaderSets;

protected:
    virtual ~Options();
};
VSG_type_name(vsg::Options);
~~~

## ReaderWriter & vsgXchange



## Serializaton

## vsg::Path and file system functions

## i/ostream support for native types

## Logger

Prev: [Visitors](Visitors.md) | Next : [Block memory management with vsg::Allocator](../2_Foundations/Allocator.md)

