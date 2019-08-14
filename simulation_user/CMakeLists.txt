##
#  CMake script for the program:
##

# Set the name of the src file
SET(TARGET "linear_network_simulation")
SET(TARGET_SRC
  ${TARGET}.cpp
  )
# if needed, copy files to the build directory
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
OPTION (LIB_TYPE_STATIC "USE Static Libraries" ON)
PROJECT(${TARGET} LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(LAPACK REQUIRED)
find_package(FIM REQUIRED)
set(BOOST_ROOT $ENV{CPACKAGE}/Boost)
find_package(Boost 1.53 REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS}
${CLAPACK_INCLUDE_DIRS}
${FIM_INCLUDE_DIRS}
)
add_executable(${TARGET} ${TARGET_SRC})
target_link_libraries(${TARGET} ${FIM_LIBRARIES} ${LAPACK_LIBRARIES} ${Boost_SERIALIZATION_LIBRARY})

If(NOT ${LIB_TYPE_STATIC})
message("COPY ${FIM_DLL} to working directory")
file(COPY ${FIM_DLL} DESTINATION ./)
#copy the lib dll to build dir
ENDIF()  
