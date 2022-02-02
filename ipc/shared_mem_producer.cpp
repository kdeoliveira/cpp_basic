#include "shared_mem.hpp"
#include <cstring>
#include <string>

//File descriptor: id for a file or an input/output resource provided by the OS

int main(){

std::string shared_mem_path = "shared_mem_path";

    shm_unlink(shared_mem_path.c_str());


    //Creates the shared memory object which returns the file descriptor
    // R/W access and creates shared_mem if it doesnt exist
    // Permission access to the USR (user) or GRP (group) to that file descriptor
    // O_CREAT : creates if does not exist
    // O_TRUNC : truncates (remove content) of file if exist
    int fd = shm_open(
        shared_mem_path.c_str(), O_CREAT | O_RDWR , S_IRUSR | S_IWUSR
    );

    if(fd == -1) onError("shm_open")
    
    //Sets the file descriptor size to the structure object that will be used
    if(ftruncate(fd, sizeof(shmem)) == -1) onError("ftruncate")

    //Mapping the shared memory space to this process and returns the shared memory object itself
    // note addr and offset is not provided so OS can handle the address space
    shmem* shared_mem_object = (shmem*) mmap(
        nullptr, sizeof(*shared_mem_object), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0
    );

    if(shared_mem_object == MAP_FAILED) onError("mmap")

    //Init sempahores for sync
    //A new instance with the sem_name descriptor is created or recover if exists
    shared_mem_object->semaphore1 =  sem_open("/semaphore1", O_CREAT| O_RDWR, S_IRUSR | S_IWUSR , 0);
    shared_mem_object->semaphore2 =  sem_open("/semaphore2", O_CREAT| O_RDWR, S_IRUSR | S_IWUSR , 0);


    //Wait on semaphore 1 before accessing shared memory
    if(sem_wait(shared_mem_object->semaphore1) == -1) onError("sem_mem")
    
    //Modify the data
    for(int i {0} ; i < shared_mem_object->count ; i++){
        shared_mem_object->buffer[i] = toupper((unsigned char) shared_mem_object->buffer[i]);
    }

    //Post the second semaphore to notify the buffer has now been modified and safe to be accessed
    if(sem_post(shared_mem_object->semaphore2)) onError("sem_post")

    //Unlink the shared memory for this process
    shm_unlink(shared_mem_path.c_str());

    //Close description for semaphores (only required in one side)
    sem_close(shared_mem_object->semaphore1);
    sem_close(shared_mem_object->semaphore2);

    return EXIT_SUCCESS;
}