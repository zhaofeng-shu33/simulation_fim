[![Build Status](https://api.travis-ci.com/zhaofeng-shu33/simulation_fim.svg?branch=master)](https://travis-ci.com/zhaofeng-shu33/simulation_fim/)

# simulation_lib

`cmake` build system

## General Consideration

On windows platform, you should use [vcpkg](https://github.com/Microsoft/vcpkg) to fix the dependencies. 

## Dependency
To successfully build simulation_lib, the following is required:


* Boost
* lapack Package

On different platforms, we use different wrapper. On Windows, `clapack` is used;
On linux, `lapacke` is used.

## Build Commands
```shell
cd simulation_lib
mkdir build
cd build
cmake ..
```

The last step installed the FIM_Package to ${CPACKAGE}\FIM

The default command builds win32 static debug version. You can specify other options to generate other three versions.

    * CMAKE_BUILD_TYPE=Debug,Release
    * BUILD_SHARED_LIBS=ON,OFF

If Dynamic Link Version is built, the corresponding DLL (FIMd.dll or FIM.dll) is copied automatically to build directory for the build/test/*.exe to run

