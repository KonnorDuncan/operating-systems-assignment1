// Konnor Duncan
// Operating Systems CS33211

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 2

sem_t* empty, full;
pthread_mutex_t* mutex;
int* table;
int id = 0;

void* consumer(void* arg) {
  while (true) {
    sem_wait(full);
    pthread_mutex_lock(mutex);

    // Consume item
    std::cout << "Consumed item: " << table[item_id - 1] << std::endl;
    table[id - 1] = 0;

    pthread_mutex_unlock(mutex);
    sem_post(empty);

    //delay
    sleep(2);
  }
  pthread_exit(NULL);
}

int main() {
  int shm_fd;

  //open shared memory
  shm_fd = shm_open("/hw1_mem", O_RDWR, 666);
  //map the shared memory segment to process address space
  empty = (sem_t*)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  full = (sem_t*)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, sizeof(sem_t));
  mutex = (pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, sizeof(sem_t) * 2);
  table = (int*)mmap(NULL, sizeof(int) * TABLE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, sizeof(sem_t) * 2 + sizeof(pthread_mutex_t));

  

  //create consumer thread
  pthread_t cons_thread;
  pthread_create(&cons_thread, NULL, consumer, NULL);

  //join consumer thread
  pthread_join(cons_thread, NULL);

  //unmap shared memory
  munmap(empty, sizeof(sem_t));
  munmap(full, sizeof(sem_t));
  munmap(mutex, sizeof(pthread_mutex_t));
  munmap(table, sizeof(int) * TABLE_SIZE);
  close(shm_fd);

  return 0;
}
