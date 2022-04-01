cmake_minimum_required(VERSION 3.0.0)
project(tutorial VERSION 0.1.0)

include(CTest)
enable_testing()


add_subdirectory(multithread)
add_subdirectory(timer)
add_subdirectory(ipc)


add_executable(type_erasure type_erasure.cpp)
add_executable(variadic variadic.cpp)
add_executable(basics basics.cpp)
add_executable(type_erasure_idioms type_erasure_idioms.cpp)
add_executable(type_erasure_proxy type_erasure_proxy.cpp)



add_subdirectory(stdlib)

set(CMAKE_C_FLAGS_DEBUG "-lX11 -lGL -lpthread -lpng -lrt -lstdc++fs -std=c++17 -g")
set(CMAKE_CXX_FLAGS "-std=c++17 -lpthread -lrt -g")



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


target_link_libraries(
    type_erasure pthread
)