# simulation_lib

cmake build system,tested on windows only

## General Consideration

On windows platform, there is no such thing called C++ library path, therefore CMAKE can not automatically find
all the header files and libraries needed to build the user program. There has been some attempt to deal with this
problem --- Using Windows Registry or set external packages path manually.  

I use the second approach, but to simplify the hard-coded file path. I install C++ packages to a fixed position on my
disk "F:\install" and I set a global environment variable "CPACKAGE=F:\install".

To find all necessary packages, I wrote some CMAKE_FILE_MODULES in cmake/Modules/ to automate this process. 
*I tested such approach extensively using "nmake" to generate win32 lib,dll,exe. But for visual studio generator, there is a small problem related to 
build types binding with libraries and dlls*

## Dependency
To successfully build simulation_lib, the following is required:
    * Visual Studio Toolset installed
    * Boost Package installed at ${CPACKAGE}/Boost
    * CLAPACK Package installed at ${CPACKAGE}/CLAPACK
   
## Build Commands
    * cd simulation_lib
    * mkdir build
    * cd build
    * cmake -G "NMake Makefiles" ..\
    * nmake
    * cd test
    * ctest
    * cd..
    * nmake install

The last step installed the FIM_Package to ${CPACKAGE}\FIM

The default command builds win32 static debug version. You can specify other options to generate other three versions.
    * CMAKE_BUILD_TYPE=Debug,Release
    * BUILD_SHARED_LIBS=ON,OFF

If Dynamic Link Version is built, the corresponding DLL (FIMd.dll or FIM.dll) is copied automatically to build directory for the build/test/*.exe to run

