find_path(
          FIM_INCLUDE_DIR
          NAMES version.h
          HINTS ENV CPACKAGE
          PATH_SUFFIXES FIM/include
)
unset(FIM_LIBRARY CACHE)         
unset(FIM_DLL CACHE)         
If (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    If(${LIB_TYPE_STATIC})         
    find_library(FIM_LIBRARY
                    NAMES libFIMd
                    HINTS ENV CPACKAGE
                    PATH_SUFFIXES FIM/lib
                    )
    ELSE()
    find_library(FIM_LIBRARY
                    NAMES FIMd
                    HINTS ENV CPACKAGE
                    PATH_SUFFIXES FIM/lib
    )
    find_file(FIM_DLL
                NAMES FIMd.dll
                HINTS ENV CPACKAGE
                PATH_SUFFIXES FIM/bin
    )
    ENDIF()
ELSE()#release build
    If(${LIB_TYPE_STATIC})         
    find_library(FIM_LIBRARY
                    NAMES libFIM
                    HINTS ENV CPACKAGE
                    PATH_SUFFIXES FIM/lib
                    )
    ELSE()
    find_library(FIM_LIBRARY
                    NAMES FIM
                    HINTS ENV CPACKAGE
                    PATH_SUFFIXES FIM/lib
    )      
    find_file(FIM_DLL
                NAMES FIM.dll
                HINTS ENV CPACKAGE
                PATH_SUFFIXES FIM/bin
    )    
    ENDIF()

ENDIF()
include(FindPackageHandleStandardArgs)
If(${LIB_TYPE_STATIC})
SET(FIM_DLL "not used")
ENDIF()
find_package_handle_standard_args(FIM  DEFAULT_MSG
                                  FIM_LIBRARY FIM_INCLUDE_DIR FIM_DLL)
#the first "FIM" is the package name
mark_as_advanced(FIM_LIBRARY FIM_INCLUDE_DIR FIM_DLL)                               
set(FIM_LIBRARIES ${FIM_LIBRARY} )
set(FIM_INCLUDE_DIRS ${FIM_INCLUDE_DIR} )