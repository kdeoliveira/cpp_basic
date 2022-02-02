#include "shared_mem.hpp"
#include <cstring>
#include <string>
#include <iostream>

int main()
{
    std::string shared_mem_path = "shared_mem_path";

    std::string str = "kevin";
    size_t len = strlen(str.c_str());

    write(STDOUT_FILENO, "Consumer", sizeof(char) * 8);

    write(STDOUT_FILENO, "\n", sizeof(char));

    // Open shared memory from the same path name
    // Note that semaphore post/wait requires WRITE access
    int fd = shm_open(shared_mem_path.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd == -1) onError("shm_open")

    if (ftruncate(fd, sizeof(shmem)) == -1) onError("ftruncate")

    shmem *shared_mem_object = (shmem *)mmap(nullptr, sizeof(*shared_mem_object), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (shared_mem_object == MAP_FAILED)
        onError("mmap")

    //A new instance with the sem_name descriptor is created or recover if exists
    shared_mem_object->semaphore1 = sem_open("/semaphore1", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 0);
    shared_mem_object->semaphore2 = sem_open("/semaphore2", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 0);

    //Set the buffer to initial value
    //Note that this section does not require mutual exclusion since producer will be block for access
    shared_mem_object->count = len;
    std::memcpy(&shared_mem_object->buffer, str.c_str(), len);

    // Allow other processes to access the shared memory
    if (sem_post(shared_mem_object->semaphore1) == -1) onError("sem_post")

    // Wait on buffer modification (producer)
    if (sem_wait(shared_mem_object->semaphore2) == -1) onError("sem_wait")

    // Write buffer into the console (output)
    std::cout
    << shared_mem_object->buffer << std::endl;

    std::cout << len << std::endl;

    // Unlink the shared memory for this process
    shm_unlink(shared_mem_path.c_str());

    return EXIT_SUCCESS;
}