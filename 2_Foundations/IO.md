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

While the implementation of ReaderWriter that have external dependencies is only compiled when they are available, the public interface for all possible ReaderWriter is declared in the [include/vsgXchange](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/) directory.  The way the fixed public interface is decoupled from optionall built implementation is using the [Fascade Design Pattern](https://en.wikipedia.org/wiki/Facade_pattern), with the public ReaderWriter classes deferring their implementations provided by either a fallback non op implementation or the full implementation when the dependency is available.  The available ReaderWriter's, the asscoiated dependencies and the formats supported are:

| ReaderWriter | 3rd Dependency | Features |
| [vsgXchange::all](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/all.h#L35) | | Composite ReaderWriter that bundles all supported ReaderWriter's support by core VSG and vsgXchange |
fonts as vsg::Font. |
| [vsgXchange::images](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/images.h#L34) | | Bundles all supported image ReaderWriters |
| [vsgXchange::models](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/models.h#L34) | | Bundles all supported model ReaderWriters |
| [vsgXchange::stbi](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/images.h#L42) |  | Support for PNG, JPEG, GIF images |
| [vsgXchange::dds](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/images.h#L65) |  | Support for DDS images |
| [vsgXchange::curl](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/curl.h#L34) | [libcurl](https://curl.se/libcurl/) | Support for reading from http and https |
| [vsgXchange::freetype](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/freetype.h#L34) | [Freetype](https://www.freetype.org/) | Support for reading TrueType etc. | [vsgXchange::GDAL](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/gdal.h#L35) | [GDAL](https://gdal.org/) | Support for reading GIS Imagery and DEM data |
| [vsgXchange::openexr](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/images.h#L97) | [OpenEXP](https://www.openexr.com/) | Support for reading .exr images |
| [vsgXchange::assimp](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/models.h#L41) | [assimp](https://www.assimp.org/) | Support for reading GLTF, OBJ, 3DS, LWO etc |
| [vsgXchange::osg2vsg](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/models.h#L41) | [osg2vsg](https://github.com/vsg-dev/osg2vsg) | Support for OpenSceneGraph supported image and model formats |

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

At runtime to list the supported features you call the ReaderWriter::getFeatures(Features&)) method. To list all the supported features you can also run the **vsgconv** utility program in the console:

~~~ sh
$ vsgconv --features
vsgXchange::all
    vsgXchange::curl provides support for 0 extensions, and 2 protocols.
        Protocols       Supported ReaderWriter methods
        ----------      ------------------------------
        http            read(vsg::Path, ..)
        https           read(vsg::Path, ..)

        vsg::Options::Value  type
        -------------------  ----
        CURLOPT_SSL_OPTIONS  uint32_t

    vsg::VSG provides support for 2 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .vsgb           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)
        .vsgt           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)

    vsg::spirv provides support for 1 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .spv            read(vsg::Path, ..) write(vsg::Path, ..)

    vsg::glsl provides support for 16 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .comp           read(vsg::Path, ..) write(vsg::Path, ..)
        .frag           read(vsg::Path, ..) write(vsg::Path, ..)
        .geom           read(vsg::Path, ..) write(vsg::Path, ..)
        .glsl           read(vsg::Path, ..) write(vsg::Path, ..)
        .hlsl           read(vsg::Path, ..) write(vsg::Path, ..)
        .mesh           read(vsg::Path, ..) write(vsg::Path, ..)
        .rahit          read(vsg::Path, ..) write(vsg::Path, ..)
        .rcall          read(vsg::Path, ..) write(vsg::Path, ..)
        .rchit          read(vsg::Path, ..) write(vsg::Path, ..)
        .rgen           read(vsg::Path, ..) write(vsg::Path, ..)
        .rint           read(vsg::Path, ..) write(vsg::Path, ..)
        .rmiss          read(vsg::Path, ..) write(vsg::Path, ..)
        .task           read(vsg::Path, ..) write(vsg::Path, ..)
        .tesc           read(vsg::Path, ..) write(vsg::Path, ..)
        .tese           read(vsg::Path, ..) write(vsg::Path, ..)
        .vert           read(vsg::Path, ..) write(vsg::Path, ..)

    vsg::txt provides support for 7 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .bat            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .json           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .md             read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .sh             read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .text           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .txt            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .xml            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)

    vsgXchange::cpp provides support for 1 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .cpp            write(vsg::Path, ..)

    vsgXchange::stbi provides support for 9 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .bmp            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)
        .jpe            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)
        .jpeg           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)
        .jpg            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)
        .pgm            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .png            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)
        .ppm            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .psd            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .tga            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)

        vsg::Options::Value  type
        -------------------  ----
        jpeg_quality         int

    vsgXchange::dds provides support for 1 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .dds            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)

    vsgXchange::ktx provides support for 2 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .ktx            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ktx2           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)

    vsgXchange::openexr provides support for 1 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .exr            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..) write(vsg::Path, ..) write(std::ostream, ..)

    vsgXchange::freetype provides support for 11 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .cef            read(vsg::Path, ..)
        .cff            read(vsg::Path, ..)
        .cid            read(vsg::Path, ..)
        .fnt            read(vsg::Path, ..)
        .fon            read(vsg::Path, ..)
        .otf            read(vsg::Path, ..)
        .pfa            read(vsg::Path, ..)
        .pfb            read(vsg::Path, ..)
        .ttc            read(vsg::Path, ..)
        .ttf            read(vsg::Path, ..)
        .woff           read(vsg::Path, ..)

        vsg::Options::Value  type
        -------------------  ----
        quad_margin_ratio    float
        texel_margin_ratio   float

    vsgXchange::assimp provides support for 70 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .3d             read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .3ds            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .3mf            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ac             read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ac3d           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .acc            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .amf            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ase            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ask            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .assbin         read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .b3d            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .blend          read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .bsp            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .bvh            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .cob            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .csm            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .dae            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .dxf            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .enff           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .fbx            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .glb            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .gltf           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .hmp            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ifc            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ifczip         read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .iqm            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .irr            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .irrmesh        read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .lwo            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .lws            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .lxo            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .md2            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .md3            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .md5anim        read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .md5camera      read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .md5mesh        read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .mdc            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .mdl            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .mesh           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .mesh.xml       read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .mot            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ms3d           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ndo            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .nff            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .obj            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .off            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ogex           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .pk3            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ply            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .pmx            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .prj            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .q3o            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .q3s            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .raw            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .scn            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .sib            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .smd            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .step           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .stl            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .stp            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .ter            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .uc             read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .vta            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .x              read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .x3d            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .x3db           read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .xgl            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .xml            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .zae            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)
        .zgl            read(vsg::Path, ..) read(std::istream, ..) read(uint8_t* ptr, size_t size, ..)

        vsg::Options::Value      type
        -------------------      ----
        crease_angle             float
        discard_empty_nodes      bool
        generate_sharp_normals   bool
        generate_smooth_normals  bool
        two_sided                bool

    vsgXchange::GDAL provides support for 93 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .ACE2           read(vsg::Path, ..)
        .asc            read(vsg::Path, ..)
        .bag            read(vsg::Path, ..)
        .bil            read(vsg::Path, ..)
        .bin            read(vsg::Path, ..)
        .blx            read(vsg::Path, ..)
        .bmp            read(vsg::Path, ..)
        .bt             read(vsg::Path, ..)
        .byn            read(vsg::Path, ..)
        .cal            read(vsg::Path, ..)
        .ct1            read(vsg::Path, ..)
        .cub            read(vsg::Path, ..)
        .dat            read(vsg::Path, ..)
        .ddf            read(vsg::Path, ..)
        .dem            read(vsg::Path, ..)
        .dgrda          read(vsg::Path, ..)
        .dt0            read(vsg::Path, ..)
        .dt1            read(vsg::Path, ..)
        .dt2            read(vsg::Path, ..)
        .dwg            read(vsg::Path, ..)
        .err            read(vsg::Path, ..)
        .ers            read(vsg::Path, ..)
        .fits           read(vsg::Path, ..)
        .gen            read(vsg::Path, ..)
        .gff            read(vsg::Path, ..)
        .gif            read(vsg::Path, ..)
        .gpkg           read(vsg::Path, ..)
        .grb            read(vsg::Path, ..)
        .grb2           read(vsg::Path, ..)
        .grc            read(vsg::Path, ..)
        .grd            read(vsg::Path, ..)
        .grib2          read(vsg::Path, ..)
        .gsb            read(vsg::Path, ..)
        .gtx            read(vsg::Path, ..)
        .gvb            read(vsg::Path, ..)
        .gxf            read(vsg::Path, ..)
        .h5             read(vsg::Path, ..)
        .hdf            read(vsg::Path, ..)
        .hdf5           read(vsg::Path, ..)
        .hdr            read(vsg::Path, ..)
        .heic           read(vsg::Path, ..)
        .hf2            read(vsg::Path, ..)
        .hgt            read(vsg::Path, ..)
        .img            read(vsg::Path, ..)
        .isg            read(vsg::Path, ..)
        .j2k            read(vsg::Path, ..)
        .jls            read(vsg::Path, ..)
        .jp2            read(vsg::Path, ..)
        .jpeg           read(vsg::Path, ..)
        .jpg            read(vsg::Path, ..)
        .json           read(vsg::Path, ..)
        .kml            read(vsg::Path, ..)
        .kmz            read(vsg::Path, ..)
        .kro            read(vsg::Path, ..)
        .lbl            read(vsg::Path, ..)
        .lcp            read(vsg::Path, ..)
        .map            read(vsg::Path, ..)
        .mbtiles        read(vsg::Path, ..)
        .mem            read(vsg::Path, ..)
        .mpl            read(vsg::Path, ..)
        .mpr            read(vsg::Path, ..)
        .mrf            read(vsg::Path, ..)
        .n1             read(vsg::Path, ..)
        .nat            read(vsg::Path, ..)
        .nc             read(vsg::Path, ..)
        .ntf            read(vsg::Path, ..)
        .pdf            read(vsg::Path, ..)
        .pgm            read(vsg::Path, ..)
        .pix            read(vsg::Path, ..)
        .png            read(vsg::Path, ..)
        .pnm            read(vsg::Path, ..)
        .ppi            read(vsg::Path, ..)
        .ppm            read(vsg::Path, ..)
        .prf            read(vsg::Path, ..)
        .rda            read(vsg::Path, ..)
        .rgb            read(vsg::Path, ..)
        .rik            read(vsg::Path, ..)
        .rst            read(vsg::Path, ..)
        .rsw            read(vsg::Path, ..)
        .sdat           read(vsg::Path, ..)
        .sg-grd-z       read(vsg::Path, ..)
        .sigdem         read(vsg::Path, ..)
        .sqlite         read(vsg::Path, ..)
        .ter            read(vsg::Path, ..)
        .tga            read(vsg::Path, ..)
        .tif            read(vsg::Path, ..)
        .tiff           read(vsg::Path, ..)
        .toc            read(vsg::Path, ..)
        .vrt            read(vsg::Path, ..)
        .webp           read(vsg::Path, ..)
        .xml            read(vsg::Path, ..)
        .xpm            read(vsg::Path, ..)
        .xyz            read(vsg::Path, ..)

    osg2vsg::OSG provides support for 3 extensions, and 0 protocols.
        Extensions      Supported ReaderWriter methods
        ----------      ------------------------------
        .vsga           read(vsg::Path, ..)
        .vsgb           read(vsg::Path, ..)
        .vsgt           read(vsg::Path, ..)

        vsg::Options::Value  type
        -------------------  ----
        original_converter   bool
        read_build_options   string
        write_build_options  string
~~~

## vsgconv



## Serializaton

## vsg::Path and file system functions

## i/ostream support for native types

## Logger

Prev: [Visitors](Visitors.md) | Next : [Block memory management with vsg::Allocator](../2_Foundations/Allocator.md)

