add_library(
    shared_mem STATIC shared_mem.hpp
)

set(CMAKE_C_FLAGS_DEBUG "-lX11 -lGL -lpthread -lpng -lrt -lstdc++fs -std=c++17 -g")
set(CMAKE_CXX_FLAGS "-std=c++17 -lpthread -lrt -g")

set_target_properties(
    shared_mem PROPERTIES LINKER_LANGUAGE CXX   
)

add_executable(
    signal_event signal_event.cpp
)

add_executable(
    signal_receive signal_receive.cpp
)


add_executable(
    shared_mem_consumer shared_mem_consumer.cpp
)

add_executable(
    shared_mem_producer shared_mem_producer.cpp
)
target_include_directories(
    shared_mem PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/"
)

target_link_libraries(
    shared_mem_consumer shared_mem
)

target_link_libraries(
    shared_mem_consumer rt pthread
)

target_link_libraries(
    shared_mem_producer rt pthread
)


add_executable(
    pipe_fork pipe_fork.cpp
)

add_executable(
    message_queue message_queue.cpp
)

target_link_libraries(
    message_queue rt pthread
)