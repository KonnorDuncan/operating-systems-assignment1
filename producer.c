// Konnor Duncan
// Operating Systems CS33211

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 2

sem_t empty, full;
pthread_mutex_t mutex;

int table[BUFFER_SIZE];
int id = 0;


void* producer (void* arg){
  while(true){
    //wait and lock
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    //produce new item
    table[id] = rand() % 100;
    std::cout << "Producer made < " << table[id] << " >" << std::endl;
    id = (id + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    // delay
    sleep(3);
  }
  pthrad_exit(NULL);
}

int main(){
  int shm_fd;

  //create shared memory object
  shm_fd = shm_open("/hw1_mem", O_CREAT | O_RDWR, 666);
  ftruncate(shm_fd, sizeof(sem_t) * 2 + sizeof(pthread_mutex_t) + sizeof(int) * TABLE_SIZE);

  //map the shared memory segment
  empty = (sem_t*)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  full = (sem_t*)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, sizeof(sem_t));
  mutex = (pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, sizeof(sem_t) * 2);
  table = (int*)mmap(NULL, sizeof(int) * TABLE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, sizeof(sem_t) * 2 + sizeof(pthread_mutex_t));
  

  
  //initialize semaphores and mutex
  sem_init(empty, 1, BUFFER_SIZE);
  sem_init(full, 1, 0);
  pthread_mutex_init(&mutex, NULL);

  //create thread
  pthread_t prod_thread;
  pthread_create(&prod_thread, NULL, producer, NULL);
  //join thread
  pthread_join(prod_thread, NULL);

  //destroy semaphores and mutex
  pthread_mutex_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);
  
  //close shared memory
  munmap(empty, sizeof(sem_t));
  munmap(full, sizeof(sem_t));
  munmap(mutex, sizeof(pthread_mutex_t));
  munmap(table, sizeof(int) * TABLE_SIZE);
  close(shm_fd);
  shm_unlink("/hw1_mem");
  return 0;
}
