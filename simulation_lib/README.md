# simulation_lib

`cmake` build system

## General Consideration

On windows platform, you should use [vcpkg](https://github.com/Microsoft/vcpkg) to fix the dependencies. 

## Dependency
To successfully build simulation_lib, the following is required:

    
* Boost
* CLAPACK Package

## Build Commands
```shell
cd simulation_lib
mkdir build
cd build
cmake .. # you can add -G "NMake Makefiles" on windows platform
nmake
cd test
ctest
cd ..
nmake install
```

The last step installed the FIM_Package to ${CPACKAGE}\FIM

The default command builds win32 static debug version. You can specify other options to generate other three versions.

    * CMAKE_BUILD_TYPE=Debug,Release
    * BUILD_SHARED_LIBS=ON,OFF

If Dynamic Link Version is built, the corresponding DLL (FIMd.dll or FIM.dll) is copied automatically to build directory for the build/test/*.exe to run

