find_path(
          FIM_INCLUDE_DIR
          NAMES node.h
          HINTS "linear_network_simulation"
          PATH_SUFFIXES FIM
)
unset(FIM_LIBRARY CACHE)         
unset(FIM_DLL CACHE)         

If(${LIB_TYPE_STATIC})         
find_library(FIM_LIBRARY
                NAMES FIM
                )
ELSE()
find_library(FIM_LIBRARY
                NAMES FIM
                HINTS "linear_network_simulation"
)      
find_file(FIM_DLL
            NAMES FIM.dll
            HINTS "linear_network_simulation"
            PATH_SUFFIXES FIM/bin
)    
ENDIF()

include(FindPackageHandleStandardArgs)
If(${LIB_TYPE_STATIC})
SET(FIM_DLL "not used")
ENDIF()
find_package_handle_standard_args(FIM  DEFAULT_MSG
                                  FIM_LIBRARY FIM_INCLUDE_DIR FIM_DLL)
#the first "FIM" is the package name
mark_as_advanced(FIM_LIBRARY FIM_INCLUDE_DIR FIM_DLL)
set(FIM_LIBRARIES ${FIM_LIBRARY})
set(FIM_INCLUDE_DIRS ${FIM_INCLUDE_DIR})
