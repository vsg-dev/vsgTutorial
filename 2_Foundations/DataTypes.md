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

The vsg::Data defines a set of pure virtual methods that all concrete subclasses from vsg::Data must provide, these methods provide scene graph and applications that ability to query the size of values in the data container, ppinter to the data and dimnensions of the data. The methods are:

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

### Data::Properites

The vsg::Data::Properties struct provides the definition of data properites that the individual data values, these properties are used to set the associated Vulkan data on the GPU as well as help specify how the data is allocated and used. Follows in the definition of Data::Properties take directly from the include/vsg/core/Data.h header:

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

The vsg::Data subclasses provide defaults for Data::Properites members, but in the case of the Properties.format you will need to set this to an appropriate value as this can't be determined by data type alone. When using Data objects on the CPU or when using them for vertex array and unform values the format value is not referenced so you can leave it blank, it's only when using Data objects as texture will the format be checked. However when loading data image files these will set the format for you so it's only in the case of user created image data that you'll need to set the format.  The range of values for the format member can be found in the Vulkan documentation on [VkFormat](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFormat.html).  In the vsg::Array2D section below we'll provide an example of setting format.

## vsg::Value

When you need a single value, either for just sharing CPU only needs, or for mapping to GPU memory such as a single per instance vertex attribute or uniform value you can use the [vsg::Value](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Value.h) template class. The Value.h header also provides a set of pre-defined types that wrap the most common basic types you'd use with the scene graph, from vsg::boolValue to vsg::dboxValue.

For the list of types defined look at the bottom of the [Value.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Value.h#L169) header and additional material related versions are provided by the [material.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/state/material.h) header.

~~~ cpp
// create a vec3Value object using user specified initializer on the heap
// note create() passes back a ref_ptr<vec3Value> so C++ compiler will set the auto translation variable type to this
auto translation = vsg::vec3Value::create(vsg::vec3(100.0f, 200.0f, 300.0f));

// create a default constructed vsg::mat4Value on heap and then assign a value to it
auto transform = vsg::mat4Value::create();
transform->value() = vsg::translation(vsg::vec3(100.0f, 200.0f, 300.0f));

// create a PBR material and set the diffuseFactor
auto material = PbrMaterialValue::create();
material->value().diffuseFactor = vsg::vec4(1.0f, 0.0f, 0.0f, 1.0f);
~~~

## vsg::Array

For an fixed size array of values you use the [vsg::Array](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array.h) template class. Like Value.h, Array.h provides definitions of the most command array types, the full list is found at the bottom of [vsg::Array](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array.h#L360).

Examples:
~~~ cpp
auto vertices = vsg::vec3Array::create(2);
vertices->set(0, vsg::vec3(0.0f, 0.0f, 0.0f));
vertices->set(1, vsg::vec3(1.0f, 0.0f, 0.0f));

auto texcoords = vsg::vec2::create(2);
texcoords->at(0) = vsg::vec2(0.0f, 0.0f));
texcoords->at(1) = vsg::vec2(1.0f, 0.0f));

auto colors = vsg::vec3::create({
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
    });
~~~

## vsg::Array2D

For an fixed size 2D array of values you use the [vsg::Array2D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array2D.h) template class. The full list of pre defined array3D types, the full list is found at the bottom of [vsg::Array2D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array2D.h#L350).

Example:
~~~ cpp
auto image = vsg::vec4Array2D::create({
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
    });

// we must set the format for texture image so that Vulkan knows how to store it
image->properites.format = VK_FORMAT_R32G32B32A32_SFLOAT;
~~~

## vsg::Array3D

For an fixed size 3D array of values you use the [vsg::Array3D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array.h) template class. The full list of pre defined array3D types, the full list is found at the bottom of [vsg::Array3D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array3D.h#L369).

Examples:
~~~ cpp
// create a float 2x2x2 volume with VK_FORMAT_R32_SFLOAT format
auto volume = vsg::floatArray3D::create(2, 2, 2, VK_FORMAT_R32_SFLOAT);
volume->set(0, 0, 0, 0.0f);
volume->set(1, 0, 0, 0.1f);
volume->set(0, 1, 0, 0.2f);
volume->set(1, 1, 0, 0.3f);
volume->set(0, 0, 1, 0.4f);
volume->set(1, 0, 1, 0.5f);
volume->set(0, 1, 1, 0.6f);
volume->set(1, 1, 1, 0.7f);
~~~

## Iterators

~~~ cpp
auto colors = vsg::vec4Array2D(4, 4, VK_FORMAT_R32G32B32A32_SFLOAT);

for(auto& color : colors)
{
    color.set(1.0f, 1.0f, 1.0f, 1.0f)
}

~~~

## Dynamic data

To support synchronizing dynamic data changes with the associated GPU memory the vsg::Data class provides the Data::Properities.dataVariance setting for specifiying how the data will vary during its lifetime, and a modified count that is used to track updates to the data. The options for dataVariance are:

~~~ cpp
enum DataVariance : uint8_t
{
    STATIC_DATA = 0,                       /** treat data as if doesn't not change .*/
    STATIC_DATA_UNREF_AFTER_TRANSFER = 1,  /** unref this vsg::Data after the data has been transferred to the GPU memory .*/
    DYNAMIC_DATA = 2,                      /** data is updated prior to the record traversal and will need transferring to GPU memory.*/
    DYNAMIC_DATA_TRANSFER_AFTER_RECORD = 3 /** data is updated during the record traversal and will need transferring to GPU memory.*/
};
~~~

The public methods for updating and checking the modified count are:

~~~ cpp
        /// increment the ModifiedCount to signify the data has been modified
        void dirty() { ++_modifiedCount; }

        /// get the Data's ModifiedCount and return true if this changes the specified ModifiedCount
        bool getModifiedCount(ModifiedCount& mc) const
        {
            if (_modifiedCount != mc)
            {
                mc = _modifiedCount;
                return true;
            }
            else
                return false;
        }

        /// return true if Data's ModifiedCount is different than the specified ModifiedCount
        bool differentModifiedCount(const ModifiedCount& mc) const { return _modifiedCount != mc; }
~~~

Typical usage:

~~~ cpp

// create data value on heap and set the property to dynamic
auto color = vsg::vec4Value::create();
color->properites.dataVariance = vsg::DYNAMIC_DATA;

// create viewer and compile scene graph to Vulkan, the compile traversal will collate all dynamic data into a vsg::TransferTask so they can be checked each frame.

// later in code, such as main loop
color->set(vsg::vec4(1.0f, 0.0f, 0.0f, 1.0f));
color->dirty();

// viewer recordAndSubmt() will vsg::TransferTask to copy across any modified data.
~~~

The [vsgdyamicvertex](https://github.com/vsg-dev/vsgExamples/tree/master/examples/state/vsgdynamicvertex) and [vsgdyamictexture](https://github.com/vsg-dev/vsgExamples/tree/master/examples/state/vsgdynamictexture) in the [vsgExamples repository](https://github.com/vsg-dev/vsgExamples) provide illustation of dyanamic upsdate of vertex arrays and texture respectively.

Prev: Next: [Math Types](MathTypes.md)| Next: [Meta Data](MetaData.md)

