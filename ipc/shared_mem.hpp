#pragma once

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define onError(msg) {perror(msg); exit(EXIT_FAILURE);}

#define BUFFER_SIZE 1024

struct shmem_object{
    sem_t* semaphore1;
    sem_t* semaphore2;
    size_t count;
    char buffer[BUFFER_SIZE];
};


typedef struct shmem_object shmem;

