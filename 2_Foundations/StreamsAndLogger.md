---
layout: page
title: Streams & Logger
permalink: /foundations/StreamsAndLogger
---

A significant part of developing software is the process of reporting and logging results for the purpose of QA and debugging. C++ provides the std::ostream/std::istream operators for convenient textual formatting of output and input of standard types, and the VulkanSceneGraph extends this to include native types. The library then adds additional support for textual recording with an extensible thread safe logger class.

## istream & ostream operators

The [include/vsg/io/stream.h header](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/stream.h#L31) provides a collection of << and >> operators for a range of types making it convenient to use them with input/output streams:

~~~ cpp
vsg::vec3 position = {1.0, 2.0, 3.0};

vsg::dquat rotation(vsg::radians(90.0), vsg::dvec3(0.0, 0.0, 1.0));

vsg::mat4 matrix = { 2.0, 0.0, 0.0, 0.0,
                    0.0, 2.0, 0.0, 0.0,
                    0.0, 0.0, 2.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};

auto place = vsg::stringValue::create("Paris");

std::cout<<"position = "<<position<<std::endl;
std::cout<<"rotation = "<<rotation<<std::endl;
std::cout<<"matrix = "<<matrix<<std::endl;
std::cout<<"place = "<<place<<std::endl;
~~~

Console output from this block of code:

~~~ sh
position = 1 2 3
rotation = 0 0 0.707107 0.707107
matrix =
    2 0 0 0
    0 2 0 0
    0 0 2 0
    0 0 0 1

place = ref_ptr<vsg::stringValue>(vsg::stringValue 0x7fc82dac6010)
~~~

stream.h includes a vsg::make_string(..) template function that makes it easier to compose strings from all types that support the << stream operator, including the support for vsg types.

~~~ cpp
std::string str = vsg::make_string("You can compose a string from numbers i.e PI = ", 3.14, ", and vsg types like vsg::vec3 position = ", position);
std::cout<<"str = "<<str<<std::endl;
~~~

Console output:

~~~ sh
str = You can compose a string from numbers i.e PI = 3.14, and vsg types like vsg::vec3 position = 1 2 3
~~~


## vsg::Logger

The [Logger.h header](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Logger.h#L25) provides the vsg::Logger base class and a series of subclasses that specialize it for different usage cases.

The [vsglog](https://github.com/vsg-dev/vsgExamples/blob/master/examples/io/vsglog/vsglog.cpp) example illustrates the use of the standard vsg::Logger capabilities and how to write a custom Logger class. Console output from vsglog:

~~~ sh
$ vsglog
debug: debug string
info: info cstring
Warning: warn cstring
ERROR: error cstring
info: info2 cstring
info: time 10ms, vector = (10 20 30)
info: second time 10ms, vector = (10 20 30)

custom debug : debug string
custom info : info string
custom warn : warn string
custom error : error string
custom info : here is a matrix  = {
    1 0 0 0
    0 1 0 0
    0 0 1 0
    0 0 0 1
}
custom debug : string log debug
custom debug : cstring log debug
custom info : log info
custom warn : log warn
custom error : log error
~~~

The [vsglog_mt](https://github.com/vsg-dev/vsgExamples/blob/master/examples/io/vsglog/vsglog.cpp) example illustrates a multithreaded vsg::Logger. Console output from vsglog_mt:

~~~ sh
$ vsglog_mt -n 10 -t 3
main | info: set thread prefix for thread::id = 140104473138752 to thread 0 |
main | info: set thread prefix for thread::id = 140104464746048 to thread 1 |
main | info: set thread prefix for thread::id = 140104456353344 to thread 2 |
main | info: Adding 10 MyOperations.
main | info: Starting to process operations.
thread 0 | info: info() operation 0
thread 0 | debug: log() operation 0
thread 0 | info: info() operation 2
thread 0 | Warning: log() operation 2
main | info: info() operation 1
main | info: log() operation 1
thread 1 | info: info() operation 3
thread 1 | ERROR: log() operation 3
thread 2 | info: info() operation 4
thread 2 | debug: log() operation 4
thread 2 | info: info() operation 5
thread 2 | info: log() operation 5
thread 0 | info: info() operation 6
thread 0 | Warning: log() operation 6
thread 0 | info: info() operation 7
thread 0 | ERROR: log() operation 7
thread 0 | info: info() operation 9
thread 0 | info: log() operation 9
main | info: info() operation 8
main | debug: log() operation 8
main | info: Finished processing operations.
main | info: OperationThreads destroyed.
~~~


Prev: [File System](FileSystem.md) | Next : [Block memory management with vsg::Allocator](Allocator.md)

