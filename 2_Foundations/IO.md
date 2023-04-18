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

Customization and extension of reading and writing is provided by the [vsg::Options](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/Options.h) object that can be passed to the vsg;:read(..) and vsg::write(..) methods. You can pass in the ReaderWriters that you wish to used, placing them in the order you want them invoked. vsg::Options is subclassed from vsg::Object so has all the standard meta data capabilities and adds IO specific settings. The most common task will be passing in the paths to search for files, and the ReaderWriters to check, such as adding in support for the ReaderWriter's provided by vsgXchange. The usage pattern is:

~~~ cpp
#include <vsg/all.h>
#include <vsgXchange/all.h>

int main(int, char**)
{
    // create the options object that will tell the vsg::read() function what to use when reading files/istreams
    auto options = vsg::Options::create();

    // set up the paths
    options->paths = vsg::getEnvPaths("VSG_FILE_PATH");

    // assign the ReaderWriter's to use when read/writing
    options->add(vsgXchange::all::create());

    // load GLTF model using vsgXchange::assimp that is included in vsgXchange::all, passing in options so read knows what to use
    auto model = vsg::read_cast<vsg::Node>("FlightHelmet.gltf", options);

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

In later chapters we'll revist the features of vsg::Options in more depth.

## ReaderWriter

The vsg::ReaderWriter base class provides the mechanism for implementing support for both native and 3rd party file formats.  The [Chain of Responsibility Design Pattern](https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern) is used with each ReaderWriter implementation taking responsibility for whether it can handle reading from or writing to a file or strean. The ReaderWriter's are invoked by the vsg::read(..)/vsg::write() calls in the order that they appear in the vsg::Options::readerWriters list, and if none can handle the read/write then the built in ReaderWriter's are called as fallback.

There are three types of each of virtual RaderWriter::read(..) methods that take filename, istream or block of memory as the source to read, and two type of virtual ReaderWrite::write(..) methods that take a filename or ostream to write to.  A virtual ReaderWrier::getFeatures(..) method provides a way to reporting to applications that read/write features are supported. The full public interface to [ReaderWriter](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/ReaderWriter.h#L33) is:
~~~ cpp
/// Base class from providing support for reading and/or writing various file formats and IO protocols
class VSG_DECLSPEC ReaderWriter : public Inherit<Object, ReaderWriter>
{
public:
    using vsg::Object::read;
    using vsg::Object::write;

    /// convenience method for casting a read object to a specified type.
    template<class T>
    vsg::ref_ptr<T> read_cast(const vsg::Path& filename, vsg::ref_ptr<const vsg::Options> options = {}) const
    {
        auto object = read(filename, options);
        return vsg::ref_ptr<T>(dynamic_cast<T*>(object.get()));
    }

    /// convenience method for casting a read object to a specified type.
    template<class T>
    vsg::ref_ptr<T> read_cast(std::istream& fin, vsg::ref_ptr<const vsg::Options> options = {}) const
    {
        auto object = read(fin, options);
        return vsg::ref_ptr<T>(dynamic_cast<T*>(object.get()));
    }

    /// convenience method for casting a read object to a specified type.
    template<class T>
    vsg::ref_ptr<T> read_cast(const uint8_t* ptr, size_t size, vsg::ref_ptr<const vsg::Options> options = {}) const
    {
        auto object = read(ptr, size, options);
        return vsg::ref_ptr<T>(dynamic_cast<T*>(object.get()));
    }

    /// read object from file, return object on success, return null ref_ptr<> if format not supported, or return ReadError on failure.
    virtual vsg::ref_ptr<vsg::Object> read(const vsg::Path& /*filename*/, vsg::ref_ptr<const vsg::Options> = {}) const { return vsg::ref_ptr<vsg::Object>(); }

    /// read object from input stream, return object on success, return null ref_ptr<> if format not supported, or return ReadError on failure.
    virtual vsg::ref_ptr<vsg::Object> read(std::istream& /*fin*/, vsg::ref_ptr<const vsg::Options> = {}) const { return vsg::ref_ptr<vsg::Object>(); }

    /// read object from memory block, return object on success, return null ref_ptr<> if format not supported, or return ReadError on failure.
    virtual vsg::ref_ptr<vsg::Object> read(const uint8_t* /*ptr*/, size_t /*size*/, vsg::ref_ptr<const vsg::Options> = {}) const { return vsg::ref_ptr<vsg::Object>(); }

    /// write object to file, return true on success, return false on failure.
    virtual bool write(const vsg::Object* /*object*/, const vsg::Path& /*filename*/, vsg::ref_ptr<const vsg::Options> = {}) const { return false; }

    /// write object to output stream, return true on success, return false on failure.
    virtual bool write(const vsg::Object* /*object*/, std::ostream& /*fout*/, vsg::ref_ptr<const vsg::Options> = {}) const { return false; }

    /// read the command line arguments for any options appropriate for this ReaderWriter
    virtual bool readOptions(Options&, CommandLine&) const { return false; }

    enum FeatureMask
    {
        READ_FILENAME = (1 << 0),
        READ_ISTREAM = (1 << 1),
        READ_MEMORY = (1 << 2),
        WRITE_FILENAME = (1 << 3),
        WRITE_OSTREAM = (1 << 4)
    };

    struct Features
    {
        std::map<vsg::Path, FeatureMask> protocolFeatureMap;
        std::map<vsg::Path, FeatureMask> extensionFeatureMap;
        std::map<std::string, std::string> optionNameTypeMap;
    };

    /// get the Features supported by this ReaderWriter
    virtual bool getFeatures(Features&) const { return false; }
};
VSG_type_name(vsg::ReaderWriter);
~~~

## vsgXchange - aliases and fascades

The [vsgXchange library](https://github.com/vsg-dev/vsgXchange) is a companion library that provides support for a range of 3rd party image and model file formats and http support. A number of these features require external dependencies that are checked for by CMake when building vsgXchange, if they are found the associated ReaderWriter is built and included in the vsgXchange::all composite ReaderWriter, you can assign this to the vsg::Options object as in the example above to add support for all the available formats, or you can add each ReaderWriter individually. Doing the later allows you to control the order in which ReaderWriters are invoked as well select just the ones that are important to your application and reduce the overall footprint of your application.

While the implementation of ReaderWriter that have external dependencies is only compiled when they are available, the public interface for all possible ReaderWriter is declared in the [include/vsgXchange](https://github.com/vsg-dev/vsgXchange/blog/master/include/vsgXchange/) directory.  The way the fixed public interface is decoupled from optionall built implementation is using the Fascade Design Pattern, with the public ReaderWriter classes deferring their implementations provided by either a fallback non op implementation or the full implementation when the dependency is available.  The available ReaderWriter's, the asscoiated dependencies and the formats supported are:

| ReaderWriter | 3rd Dependency | Features |
| [vsgXchange::all](https://github.com/vsg-dev/vsgXchange/blog/master/include/vsgXchange/all.h) | | Composite ReaderWriter that bundles all supported ReaderWriter's support by core VSG and vsgXchange |
| [vsgXchange::curl](https://github.com/vsg-dev/vsgXchange/blog/master/include/vsgXchange/curl.h) | [libcurl](https://curl.se/libcurl/) | Implements support for reading from http and https |
| [vsgXchange::images](https://github.com/vsg-dev/vsgXchange/blog/master/include/vsgXchange/images.h) | | Composite ReaderWriter that bunles all supported image ReaderWriters |
| [vsgXchange::models](https://github.com/vsg-dev/vsgXchange/blog/master/include/vsgXchange/models.h) | | Composite ReaderWriter that bunles all supported model ReaderWriters |


vsgXchange's CMake scripts automatically generated include/vsgXchange/Version.h header provides #define's for each ReaderWriter so you can test at compile time if you so wish, and each optionally compiled ReaderWriter has a flag to say whether it's supported or not, so you can test for it at runtime, follows in what you'll see the Version.h header's if you have built against all the dependencies:

~~~ cpp
    /// standard Features
    #define vsgXchange_all
    #define vsgXchange_images
    #define vsgXchange_models
    #define vsgXchange_stbi
    #define vsgXchange_dds
    #define vsgXchange_ktx
    #define vsgXchange_spv
    #define vsgXchange_cpp

    /// optional Features
    #define vsgXchange_freetype
    #define vsgXchange_assimp
    #define vsgXchange_OSG
    #define vsgXchange_GDAL
    #define vsgXchange_CURL
    #define vsgXchange_OpenEXR
~~~

## Serializaton

## vsg::Path and file system functions

## i/ostream support for native types

## Logger

Prev: [Visitors](Visitors.md) | Next : [Block memory management with vsg::Allocator](../2_Foundations/Allocator.md)

