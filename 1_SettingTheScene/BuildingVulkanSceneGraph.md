---
layout: page
title: Building VulkanSceneGraph software
permalink: /SettingTheScene/BuildingVulkanSceneGraph
---

To conclude this chapter we'll look at building the VulkanSceneGraph projects and a minimal stand alone **hello world** application.

All VulkanSceneGraph projects, including the vsgTutorial exercises, are written in C++17 and using CMake as a cross platform build system. To aid integration of the VulkanSceneGraph projects with other software CMake config files are installed along with headers and libraries.  CMake config files provide details of the libraries, header locations and any compile definitions that are required when building software that use VulkanSceneGraph libraries and helps avoid issues when working across different platforms and with differences in static and dynamic library builds.

First task to check out the main repositories and vsgTutorial for it's exercises, for brevity we'll assume you debian based system and install headers, libs and cmake files locally and set env paths up to find the install locations, this way there is no need to install to system directories. If you have other types of system use one of the alternative build instructions:
* Windows - to be written (looking for volunteers to write this.)
* macOS - to be written (looking for volunteers to write this.)

First we'll set up some env var, for easy of use you may wish to put this into a resource file like .bashrc:

~~~ sh
# env vars useful for locating source projects, installed libraries and binaries
export INSTALL_DIR = ~/Install
export PROJECT_DIR = ~/Projects
export VULKAN_SDK = ${INSTALL_DIR}/VulkanSDK
export PATH = ${PATH}:${INSTALL_DIR}/bin:${VULKAN_SDK}/bin
export LD_LIBRARY_PATH = ${D_LIBRARY_PATH}:${INSTALL_DIR}/lib

# env vars that are useful for finding example data, and locating where to cache files downloading from http during database paging
export VSG_FILE_PATH = ${PROJECT_DIR}/vsgExamples/data
export VSG_FILE_CACHE = ${PROJECT_DIR}/vsgFileCache
~~~

Next install dependencies, under debian:
~~~ sh

# dependencies useful for building the VulkanSceneGraph
sudo apt-get install git g++
sudo apt-get install cmake cmake-curses-gui
sudo apt-get install libvulkan-dev vulant-tools vulkan-validationlayers

# dependencies used by vsgXchange
sudo apt-get install libassimp-dev libfreetype-dev libopenexr-dev
~~~

For Vulkan you can alternatively download the VulkanSDK download the VulkanSDK from [LunarG](https://vulkan.lunarg.com/sdk/home)

~~~ sh
wget https://sdk.lunarg.com/sdk/download/1.3.239.0/linux/vulkansdk-linux-x86_64-1.3.239.0.tar.gz
tar xvf vulkansdk-linux-x86_64-1.3.239.0.tar.gz -C ${INSTALL_DIR}
~~~

Now checkout the VulkanSceneGraph, vsgXchange, vsgExamples and vsgTutorial

~~~ sh
mkdir ${PROJECT_DIR}
cd ${PROJECT_DIR}

git clone https://github.com/vsg-dev/VulkanSceneGraph.git
git clone https://github.com/vsg-dev/vsgXchange.git
git clone https://github.com/vsg-dev/vsgExamples.git
git clone https://github.com/vsg-dev/vsgTutorial.git
~~~

The use of CMake config files really simplifies the inclusion of VulkanSceneGraph project, the hello world [CMakeLists.txt](01_hello_world/CMakeLists.txt) is less than 10 lines!

~~~ cmake
{% include_relative 01_hello_world/CMakeLists.txt %}
~~~

---



Prev: [VulkanSceneGraph Library](VulkanSceneGraphLibrary.md) | Next : [Foundations](../2_Foundations/index.md))
