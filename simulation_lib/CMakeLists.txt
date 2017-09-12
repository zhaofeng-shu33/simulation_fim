include(CPack)
##
#  CMake script for the program:
##

# Set the name of the src file
SET(TARGET "linear_network_simulation")
SET(TARGET_SRC
  ${TARGET}.cpp
  )
# if needed, copy files to the build directory
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

PROJECT(${TARGET})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(CLAPACK REQUIRED)
set(BOOST_ROOT $ENV{CPACKAGE}/Boost)
find_package(Boost 1.58 REQUIRED COMPONENTS serialization)

#foreach(loop_var ${CLAPACK_LIBRARIES})
#message(${loop_var})
#endforeach(loop_var)

#list(LENGTH ${CLAPACK_LIBRARIES} mylen)
#message(${mylen})
include_directories(${Boost_INCLUDE_DIRS} ${CLAPACK_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(
${Boost_LIBRARY_DIRS}
)
set( CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Append this string to debug lib names")
If (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
message("Debug build")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
message("release build")
else()
MESSAGE(FATAL_ERROR
      "Unknown build type ${CMAKE_BUILD_TYPE}"
       )
endif()
If(${BUILD_SHARED_LIBS})
message("DLL build")
set(libTarget FIM)
ELSE()
message("STATIC build")
set(libTarget libFIM)
ENDIF()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(include)
