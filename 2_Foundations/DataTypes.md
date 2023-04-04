---
layout: page
title: Data Types
permalink: /foundations/DataTypes
---

The scene graph needs to manage data that is held on the CPU and to be able to map this data to memory GPU in a coherent way.  The types of data may a single value, 1D, 2D and 3D arrays, with a range types, and used for a wide range of tasks - repreenting vertices, normals, texture coords arrays through to 1D, 2D and 3D textures.

The [vsg::Data](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Data.h) base class provides a common interface for all the different types of data, then a series of template classes provide support for both built-in types and user defined types for single value and fixed sized 1D, 2D and 3D arrays:

* [vsg::Value](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Value.h) - single value
* [vsg::Array](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array.h) - 1D array
* [vsg::Array2D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array2D.h) - 2D array
* [vsg::Array3D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array3D.h) - 3D array

Containers that have their sized fixed at allocation time, rather than dynamically resizable containers like std::vector<>, are used to ensure coherency with the fixed sized GPU resources they will map to.

## vsg::Data base class

The [vsg::Data](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Data.h) is a pure vertiual base class that subclasses from vsg::Object to gain it's support for intrusive referfence counting, Meta Data and Run-Time Type Information (RTTI) support. Will go into the details of [Meta Data](MetaData.md) and [RTTI](Visitor.md) support later in this chapter.

The vsg::Data::Propeties struct provides the definition of data properites that the individual data values, these properties are used to set the associated Vulkan data on the GPU as well as help specify how the data is allocated and used.  Follows in the definition of Data::Properties take directly from the include/vsg/core/Data.h header:

~~~ cpp
/* Properties used for specifying the format of the data, use of mipmaps, block compressed data and origin.
    * Default of no mipmapping and {1,1,1} is uncompressed.
    * A single block (Block64/Block128) is stored as a single value with the Data object. */
struct VSG_DECLSPEC Properties
{
    Properties() = default;
    Properties(const Properties& rhs) = default;
    explicit Properties(VkFormat in_format) :
        format(in_format) {}

    VkFormat format = VK_FORMAT_UNDEFINED;
    uint32_t stride = 0;
    uint8_t maxNumMipmaps = 0;
    uint8_t blockWidth = 1;
    uint8_t blockHeight = 1;
    uint8_t blockDepth = 1;
    uint8_t origin = TOP_LEFT;               /// Hint for setting up texture coordinates, bit 0 x/width axis, bit 1 y/height axis, bit 2 z/depth axis. Vulkan origin for images is top left, which is denoted as 0 here.
    int8_t imageViewType = -1;               /// -1 signifies undefined VkImageViewType, if value >=0 then value should be treated as valid VkImageViewType.
    DataVariance dataVariance = STATIC_DATA; /// hint as how the data values may change during the lifetime of the vsg::Data.
    AllocatorType allocatorType = ALLOCATOR_TYPE_VSG_ALLOCATOR;

    int compare(const Properties& rhs) const;
    Properties& operator=(const Properties& rhs);
};
~~~

The vsg::Data defines a set of pure virtual methods that all concrete sublcasses from vsg::Data must provide:
~~~ cpp
        virtual std::size_t valueSize() const = 0;
        virtual std::size_t valueCount() const = 0;

        virtual bool dataAvailable() const = 0;
        virtual std::size_t dataSize() const = 0;

        virtual void* dataPointer() = 0;
        virtual const void* dataPointer() const = 0;

        virtual void* dataPointer(size_t index) = 0;
        virtual const void* dataPointer(size_t index) const = 0;

        virtual void* dataRelease() = 0;

        virtual std::uint32_t dimensions() const = 0;

        virtual std::uint32_t width() const = 0;
        virtual std::uint32_t height() const = 0;
        virtual std::uint32_t depth() const = 0;
~~~

## vsg::Value

## vsg::Array

## vsg::Array2D

## vsg::Array3D



Prev: Next: [Math Types](MathTypes.md)| Next: [Meta Data](MetaData.md)

