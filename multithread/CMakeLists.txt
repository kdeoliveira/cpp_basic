

add_executable(multithread multithread.cpp)
add_executable(posix_thread posix_thread.cpp)
add_executable(posix_semaphore posix_semaphore.cpp)
add_executable(posix_class posix_class.cpp)
add_executable(process process.cpp)





target_link_libraries(
    posix_thread pthread
)

target_link_libraries(
    multithread pthread
)

target_link_libraries(
    posix_semaphore pthread
)

target_link_libraries(
    posix_class pthread
)