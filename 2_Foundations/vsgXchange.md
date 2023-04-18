---
layout: page
title: vsgXchange
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

Prev: [read/write](ReaderWriter.md) | Next : [Block memory management with vsg::Allocator](../2_Foundations/Allocator.md)

