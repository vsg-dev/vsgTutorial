---
layout: page
title: vsgXchange - reading and writing 3rd party fonts, images and models
permalink: /foundations/vsgXchange
---

The [vsgXchange library](https://github.com/vsg-dev/vsgXchange) is a companion library that provides support for a range of 3rd party image and model file formats and http support. A number of these features require external dependencies that are checked for by CMake when building vsgXchange, if they are found the associated ReaderWriter is built and included in the vsgXchange::all composite ReaderWriter, you can assign this to the vsg::Options object as in the example above to add support for all the available formats, or you can add each ReaderWriter individually. Doing the later allows you to control the order in which ReaderWriters are invoked as well select just the ones that are important to your application and reduce the overall footprint of your application.

## Supported formats

While the implementation of ReaderWriter that have external dependencies is only compiled when they are available, the public interface for all possible ReaderWriter is declared in the [include/vsgXchange](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/) directory.  The way the fixed public interface is decoupled from optionall built implementation is using the [Fascade Design Pattern](https://en.wikipedia.org/wiki/Facade_pattern), with the public ReaderWriter classes deferring their implementations provided by either a fallback non op implementation or the full implementation when the dependency is available.  The available ReaderWriter's, the asscoiated dependencies and the formats supported are:

| ReaderWriter | 3rd Dependency | Features |
| [vsgXchange::all](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/all.h#L35) | | Composite ReaderWriter that bundles all supported ReaderWriter's support by core VSG and vsgXchange |
fonts as vsg::Font. |
| [vsgXchange::images](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/images.h#L34) | | Bundles all supported image ReaderWriters |
| [vsgXchange::models](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/models.h#L34) | | Bundles all supported model ReaderWriters |
| [vsgXchange::stbi](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/images.h#L42) |  | Support for PNG, JPEG, GIF images |
| [vsgXchange::dds](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/images.h#L65) |  | Support for DDS images |
| [vsgXchange::cpp](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/cpp.h#L34) | | Write objects to .cpp files for compiling into programs |
| [vsgXchange::curl](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/curl.h#L34) | [libcurl](https://curl.se/libcurl/) | Support for reading from http and https |
| [vsgXchange::freetype](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/freetype.h#L34) | [Freetype](https://www.freetype.org/) | Support for reading TrueType etc. |
| [vsgXchange::GDAL](https://github.com/vsg-dev/vsgXchange/blob/master/include/vsgXchange/gdal.h#L35) | [GDAL](https://gdal.org/) | Support for reading GIS Imagery and DEM data |
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

At runtime to list the supported features you call the ReaderWriter::getFeatures(Features&)) method, this return true when the ReaderWriter is implemented and adds the supported features to the feature structure, and return false is nothing format is supported - such as when vsgXchange is not compiled against the required dependency.

## vsgconv

The vsgXchange library provides a [vsgconv](https://github.com/vsg-dev/vsgXchange/blob/master/applications/vsgconv/vsgconv.cpp#L41) utility program that you can use in the console to convert between different file formats:

~~~ sh
vsgconv FlightHelmet.gltf helmet.vsgb
~~~

To list all the features supported by vsgXchange you can also run the **vsgconv** utility program in the console with the --features option:

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

# Using cpp to create compilable objects

The vsgXchange::cpp ReaderWriter enables programmers to convert all vsg::Object types to source files that can be including into build of applications, this can be used for data, scene graphs or shaders/shadersets.  You can use vsgconv to do this conversion in the console:

~~~ sh
vsgconv shaders/shader.vert shader_vert.cpp
~~~

The generated shader_vert.cpp looks like:

~~~ cpp
#include <vsg/io/VSG.h>
#include <vsg/io/mem_stream.h>
static auto shader_vert = []() {
static const char str[] =
R"(#vsga 1.0.5
Root id=1 vsg::ShaderStage
{
  userObjects 0
  stage 1
  entryPointName "main"
  module id=2 vsg::ShaderModule
  {
    userObjects 0
    hints id=0
    source "#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 0) uniform ProjectionMatrix { mat4 matrix; } projection;
layout(set = 0, binding = 1) uniform ViewMatrix { mat4 matrix; } view;
layout(set = 0, binding = 2) uniform ModelMatrix { mat4 matrix; } model;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = projection.matrix * view.matrix * model.matrix * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}"
    code 454
     119734787 65536 524299 54 0 131089 1 393227 1 1280527431 1685353262 808793134
     0 196622 0 1 720911 0 4 1852399981 0 10 34 45
     46 50 52 196611 2 450 589828 1096764487 1935622738 1918988389 1600484449 1684105331
     1868526181 1667590754 29556 262149 4 1852399981 0 393221 8 1348430951 1700164197 2019914866
     0 393222 8 0 1348430951 1953067887 7237481 196613 10 0 458757 14
     1785688656 1769235301 1632464495 2020176500 0 327686 14 0 1920229741 30825 327685 16
     1785688688 1769235301 28271 327685 20 2003134806 1920229709 30825 327686 20 0 1920229741
     30825 262149 22 2003134838 0 327685 26 1701080909 1952533868 7891314 327686 26
     0 1920229741 30825 262149 28 1701080941 108 327685 34 1867542121 1769236851 28271
     327685 45 1734439526 1869377347 114 262149 46 1866690153 7499628 393221 50 1734439526
     1131963732 1685221231 0 327685 52 1700032105 1869562744 25714 327752 8 0 11
     0 196679 8 2 262216 14 0 5 327752 14 0 35
     0 327752 14 0 7 16 196679 14 2 262215 16 34
     0 262215 16 33 0 262216 20 0 5 327752 20 0
     35 0 327752 20 0 7 16 196679 20 2 262215 22
     34 0 262215 22 33 1 262216 26 0 5 327752 26
     0 35 0 327752 26 0 7 16 196679 26 2 262215
     28 34 0 262215 28 33 2 262215 34 30 0 262215
     45 30 0 262215 46 30 1 262215 50 30 1 262215
     52 30 2 131091 2 196641 3 2 196630 6 32 262167
     7 6 4 196638 8 7 262176 9 3 8 262203 9
     10 3 262165 11 32 1 262187 11 12 0 262168 13
     7 4 196638 14 13 262176 15 2 14 262203 15 16
     2 262176 17 2 13 196638 20 13 262176 21 2 20
     262203 21 22 2 196638 26 13 262176 27 2 26 262203
     27 28 2 262167 32 6 3 262176 33 1 32 262203
     33 34 1 262187 6 36 1065353216 262176 42 3 7 262176
     44 3 32 262203 44 45 3 262203 33 46 1 262167
     48 6 2 262176 49 3 48 262203 49 50 3 262176
     51 1 48 262203 51 52 1 327734 2 4 0 3
     131320 5 327745 17 18 16 12 262205 13 19 18 327745
     17 23 22 12 262205 13 24 23 327826 13 25 19
     24 327745 17 29 28 12 262205 13 30 29 327826 13
     31 25 30 262205 32 35 34 327761 6 37 35 0
     327761 6 38 35 1 327761 6 39 35 2 458832 7
     40 37 38 39 36 327825 7 41 31 40 327745 42
     43 10 12 196670 43 41 262205 32 47 46 196670 45
     47 262205 48 53 52 196670 50 53 65789 65592
  }
  NumSpecializationConstants 0
}
)";
vsg::VSG io;
return io.read_cast<vsg::ShaderStage>(reinterpret_cast<const uint8_t*>(str), sizeof(str));
};
~~~

In the above example the vsgconv utility has automatically compiles the GLSL shader source to SPIRV code for you, so at runtime there is no need for the VSG to compile the shader. You can then invoke this from your C++ code:

~~~ cpp

#include "shader_vert.cpp"

{
...
    auto shader = shader_vert();
...
}
~~~

Prev: [read/write](ReaderWriter.md) | Next : [Serialization, Paths and Logger](../2_Foundations/SerializationPathsaAndLogger.md)

