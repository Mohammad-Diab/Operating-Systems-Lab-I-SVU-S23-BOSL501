#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>

#define SHARED_MEM_NAME "/shared_memo"
#define SEMAPHORE_NAME "/my_semaphore1"

int main() {
    int shm_fd;
    char *shm_ptr;
    sem_t *my_semaphore;

    // Create shared memory
    shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1024); // Set the size of shared memory

    // Map the shared memory segment to the address space of the process
    shm_ptr = (char *)mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Create or open a semaphore
    my_semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, 1); // Semaphore initialized with 1

    // Writing to shared memory
    for (char c = 'A'; c <= 'Z'; ++c) {
        sem_wait(my_semaphore); // Wait until the semaphore is available
        sprintf(shm_ptr, "%c", c);
        sem_post(my_semaphore); // Release the semaphore after writing
        sleep(1); // Sleep for synchronization (for demonstration purposes)
        shm_ptr++; // Move to the next character in shared memory
    }

    // Close the semaphore
    sem_close(my_semaphore);

    // Unmap and close the shared memory
    munmap(shm_ptr, 1024);
    close(shm_fd);

    return 0;
}
