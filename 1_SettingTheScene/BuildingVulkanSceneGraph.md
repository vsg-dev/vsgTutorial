---
layout: page
title: Building VulkanSceneGraph software
permalink: /SettingTheScene/BuildingVulkanSceneGraph
---

To conclude this chapter we'll look at building the VulkanSceneGraph projects and a minimal standalone **hello world** application.

All VulkanSceneGraph projects, including the vsgTutorial exercises, are written in C++17 and using CMake as the cross-platform build system. To aid integration of the VulkanSceneGraph projects with other software, CMake config files are installed along with headers and libraries.  CMake config files provide details of the libraries, header locations and any compiler definitions that are required when building software that use VulkanSceneGraph libraries and help to avoid issues when working across different platforms and with differences in static and dynamic library builds.

The first task is to check out the main repositories and vsgTutorial for its exercises, for brevity we'll assume you have a Debian-based system and install headers, libraries and cmake files locally and set env paths up to find the install locations, this way there is no need to install to system directories. If you have other types of system use one of the alternative build instructions:
* Windows - to be written (looking for volunteers to write this.)
* macOS - to be written (looking for volunteers to write this.)

First we'll set up some environment variable, for ease of use you may wish to put this into a resource file like .bashrc:

~~~ sh
# env vars useful for locating source projects, installed libraries and binaries
export INSTALL_DIR=~/Install
export PROJECT_DIR=~/Projects
export PATH=${PATH}:${INSTALL_DIR}/bin
export LD_LIBRARY_PATH=${D_LIBRARY_PATH}:${INSTALL_DIR}/lib

# env vars that are used to find example data, and locating where to cache files downloaded from HTTP during database paging
export VSG_FILE_PATH=${PROJECT_DIR}/vsgExamples/data
export VSG_FILE_CACHE=${PROJECT_DIR}/vsgFileCache

# only required if you use VulkanSDK rather than installing vulkan from distro repositories
export VULKAN_SDK=${INSTALL_DIR}/VulkanSDK
export PATH=${PATH}:${VULKAN_SDK}/bin
~~~

Next install dependencies, under debian these are:

~~~ sh
# dependencies useful for building the VulkanSceneGraph
sudo apt-get install git g++
sudo apt-get install cmake cmake-curses-gui

# install Vulkan and the validation layers, alternatively you can download and install the VulkanSDK, see below.
sudo apt-get install libvulkan-dev vulkan-tools vulkan-validationlayers

# dependencies used by vsgXchange
sudo apt-get install libassimp-dev libfreetype-dev libopenexr-dev
~~~

If you want to use the VulkanSDK instead of distro vulkan package you download it from [LunarG](https://vulkan.lunarg.com/sdk/home):

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

To generate the make system, build and install:

~~~ sh
cd VulkanSceneGraph
cmake . -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
make -j 16
make install

cd ../vsgXchange
cmake . -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
make -j 16
make install

cd ../vsgExamples
cmake . -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
make -j 16
make install
~~~

To test out examples:

~~~ sh
vsgdraw
vsgviewer models/lz.vsgt
vsgdynamictextures
~~~

---

Prev: [VulkanSceneGraph Library](VulkanSceneGraphLibrary.md) | Next : [Hello World](HelloWorld.md)
