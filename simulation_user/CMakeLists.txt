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
OPTION (LIB_TYPE_STATIC "USE Static Libraries" ON)
PROJECT(${TARGET})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(CLAPACK CONFIG REQUIRED)
find_package(FIM REQUIRED)
set(BOOST_ROOT $ENV{CPACKAGE}/Boost)
find_package(Boost 1.58 REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS}
${CLAPACK_INCLUDE_DIRS}
${FIM_INCLUDE_DIRS}
)
link_directories(
${Boost_LIBRARY_DIRS}
)
If (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
message("Debug build")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
message("release build")
else()
MESSAGE(FATAL_ERROR
      "Unknown build type ${CMAKE_BUILD_TYPE}"
       )
endif()
add_executable(${TARGET} ${TARGET_SRC})
target_link_libraries(${TARGET} ${FIM_LIBRARIES} f2c lapack)

If(NOT ${LIB_TYPE_STATIC})
message("COPY ${FIM_DLL} to working directory")
file(COPY ${FIM_DLL} DESTINATION ./)
#copy the lib dll to build dir
ENDIF()  