---
layout: page
title: File System features
permalink: /foundations/FileSystem
---

C++17 in theory has almost all the file system related functionality that VulkanSceneGraph and its users will need, but unfortunately compiler support for all the std::filesystem features across all platforms was too patchy to rely upon.  To address this deficiancy the VulkanSceneGraph provides this functionality to ensure the same experience across all platforms and compatibility with older compilers.

## vsg::Path

The [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) class equivalent is the [vsg::Path](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Path.h#L27) class. This broadly mirrors std::filesystem functionality focusing on the key functionality required by the VulkanSceneGraph and its users. Like std::filesystem::path the vsg::Path class uses std::wstring under Windows and std::string on all other platforms, and where possible automatic conversion between wide strings and UTF8 strings is done. The difference in underlying type under Windows enables use of the Windows specific extensions of std::ifstream/ofstream that take wchar_t* for filenames, while all other platforms just support char_t* filenames. The vsg::Path automatically passes the native representation when using ifstream/ofstream.

~~~ cpp
vsg::Path filename = "models/lz.vsgt";

std::ifstream fin(filename); // wchar* used under Windows, char* used on other platforms
~~~

If you are working with APIs that only support std::string/char* representation for filenames then you can use the vsg::Path::string() method to make sure the path is converted to a UTF8 string. For instance [Assimp](https://github.com/assimp/assimp/blob/master/include/assimp/Importer.hpp#L487) requires std::string filenames:

~~~ cpp
Assimp::Importer importer;
auto scene = importer.ReadFile(filenameToUse.string(), flags);
~~~

The [Path.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Path.h#L210) header also provides convenience functions for manipulating paths/filenames:

~~~ cpp
using Paths = std::vector<Path>;
using PathObjects = std::map<Path, ref_ptr<Object>>;

/// return path stripped of the filename or final path component.
extern VSG_DECLSPEC Path filePath(const Path& path);

/// return file extension including the . prefix, i.e. vsg::fileExtension("file.vsgt") returns .vsgt
extern VSG_DECLSPEC Path fileExtension(const Path& path);

/// return lower case file extension including the . prefix, i.e. vsg::fileExtension("file.VSGT") returns .vsgt
/// By default prunes extras such as REST strings at the end of the extensions, uses ? as the deliminator for REST additions i.e. ".jpeg?g=42" becomes ".jpeg"
extern VSG_DECLSPEC Path lowerCaseFileExtension(const Path& path, bool pruneExtras = true);

/// return the filename stripped of any paths and extensions, i.e vsg::simpleFilname("path/file.vsgb") returns file
extern VSG_DECLSPEC Path simpleFilename(const Path& path);

/// return true if the path equals ., .. or has a trailing \.. \.., /.. or /....
extern VSG_DECLSPEC bool trailingRelativePath(const Path& path);

/// return the path minus the extension, i.e. vsg::removeExtension("path/file.png") return path/file
extern VSG_DECLSPEC Path removeExtension(const Path& path);
~~~

## File system functions

The file system functions are grouped together in the [include/vsg/io/FileSystem.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/FileSystem.h#L23) header. The file system functions from this header are:

~~~ cpp
class Options;
using Paths = std::vector<Path>;
using PathObjects = std::map<Path, ref_ptr<Object>>;

/// get the specified environmental variable.
extern VSG_DECLSPEC std::string getEnv(const char* env_var);

/// parse the specified environmental variable using platorm specific delimiter, returning list of Paths
/// delimiter used is ; under Windows, and : on all other platforms.
extern VSG_DECLSPEC Paths getEnvPaths(const char* env_var);

/// parse multiple environmental variables, merging them to return a list of Paths.
template<typename... Args>
Paths getEnvPaths(const char* env_var, Args... args)
{
    auto paths = getEnvPaths(env_var);
    auto right_paths = getEnvPaths(args...);
    paths.insert(paths.end(), right_paths.begin(), right_paths.end());
    return paths;
}

/// return file type, see include/vsg/io/Path.h for FileType enum,
extern VSG_DECLSPEC FileType fileType(const Path& path);

/// return true if a specified file/path exists on system.
extern VSG_DECLSPEC bool fileExists(const Path& path);

/// return the full filename path if specified filename can be found in the list of paths.
extern VSG_DECLSPEC Path findFile(const Path& filename, const Paths& paths);

/// return the full filename path if specified filename can be found in the options->paths list.
/// If options is null and the filename can be found using its existing path that filename is returned, otherwise empty Path{} is returned.
extern VSG_DECLSPEC Path findFile(const Path& filename, const Options* options);

/// make a directory, return true if path already exists or full path has been created successfully, return false on failure.
extern VSG_DECLSPEC bool makeDirectory(const Path& path);

/// get the contents of a directory, return {} if directory name is not a directory
extern VSG_DECLSPEC Paths getDirectoryContents(const Path& directoryName);

/// returns the path/filename of the currently executed program.
extern VSG_DECLSPEC Path executableFilePath();

/// Open a file using a the C style fopen() adapted to work with the vsg::Path.
extern VSG_DECLSPEC FILE* fopen(const Path& path, const char* mode);
~~~

Prev: [Serialization](Serialization.md) | Next : [Streams & Logger](StreamsAndLogger.md)

