add_executable(node_test node_test.cpp)
target_link_libraries(node_test ${libTarget} ${Boost_SERIALIZATION_LIBRARY})
add_executable(link_test link_test.cpp)
target_link_libraries(link_test ${libTarget} ${Boost_SERIALIZATION_LIBRARY})

add_executable(network_test network_test.cpp)
target_link_libraries(network_test ${libTarget} ${LAPACK_LIBRARIES} ${Boost_SERIALIZATION_LIBRARY})
enable_testing()
add_test(node_test node_test.exe)
add_test(link_test link_test.exe)
add_test(network_test network_test.exe)
If(${BUILD_SHARED_LIBS})
If("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
SET(LIB_DLL ${CMAKE_BINARY_DIR}/src/${libTarget}${CMAKE_DEBUG_POSTFIX}.dll)
ELSE()
SET(LIB_DLL ${CMAKE_BINARY_DIR}/src/${libTarget}.dll)
ENDIF()

add_custom_command(TARGET network_test POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy ARGS ${LIB_DLL} ${CMAKE_BINARY_DIR}/test/)

ENDIF()
