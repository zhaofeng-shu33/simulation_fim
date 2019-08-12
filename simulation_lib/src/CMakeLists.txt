#add_executable(${TARGET} ${TARGET_SRC})
#dependes on whether BUILD_SHARED_LIBS is on
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
#when building a DLL, CMake will add the preprocessor definition ${libTarget}_EXPORTS
add_library(${libTarget} node.cpp link.cpp network.cpp)
#required when building DLL, some functions from CLAPACK should be statically incoperated into the dll
target_link_libraries(${libTarget} PRIVATE ${LAPACK_LIBRARIES})

install(TARGETS ${libTarget} ARCHIVE DESTINATION lib
LIBRARY DESTINATION lib
RUNTIME DESTINATION bin
)
