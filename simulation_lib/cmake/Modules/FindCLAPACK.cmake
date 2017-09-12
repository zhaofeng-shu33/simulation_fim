find_path (
          CLAPACK_INCLUDE_DIR
          NAMES clapack.h
          HINTS ENV CPACKAGE
          PATH_SUFFIXES CLAPACK/include
         )
unset(CLAPACK_LIBRARY1 CACHE)         
unset(CLAPACK_LIBRARY2 CACHE)         
unset(CLAPACK_LIBRARY3 CACHE)         

If (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  find_library(CLAPACK_LIBRARY1
                NAMES blasd.lib
                HINTS ENV CPACKAGE
                PATH_SUFFIXES CLAPACK/lib
                )
  find_library(CLAPACK_LIBRARY2
                NAMES lapackd.lib
                HINTS ENV CPACKAGE
                PATH_SUFFIXES CLAPACK/lib
                )
  find_library(CLAPACK_LIBRARY3
                NAMES libf2cd.lib
                HINTS ENV CPACKAGE
                PATH_SUFFIXES CLAPACK/lib
                )
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  find_library(CLAPACK_LIBRARY1
                NAMES blas.lib
                HINTS ENV CPACKAGE
                PATH_SUFFIXES CLAPACK/lib
                )
  find_library(CLAPACK_LIBRARY2
                NAMES lapack.lib
                HINTS ENV CPACKAGE
                PATH_SUFFIXES CLAPACK/lib
                )
  find_library(CLAPACK_LIBRARY3
                NAMES libf2c.lib
                HINTS ENV CPACKAGE
                PATH_SUFFIXES CLAPACK/lib
                )

else()
endif()
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CLAPACK  DEFAULT_MSG
                                  CLAPACK_LIBRARY1 CLAPACK_INCLUDE_DIR)
mark_as_advanced(CLAPACK_LIBRARY1 CLAPACK_INCLUDE_DIR)                               
set(CLAPACK_LIBRARIES ${CLAPACK_LIBRARY1} ${CLAPACK_LIBRARY2} ${CLAPACK_LIBRARY3})
set(CLAPACK_INCLUDE_DIRS ${CLAPACK_INCLUDE_DIR} )