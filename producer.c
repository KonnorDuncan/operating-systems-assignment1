// Konnor Duncan
// Operating Systems CS33211

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 2

sem_t empty, full;
pthread_mutex_t mutex;

int table[TABLE_SIZE];
int id = 0;

void* producer (void* arg){
  while(true){
    //wait and lock
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    //produce new item
    table[id] = rand() % 100;
    std::cout << "Producer made < " << table[id] << " >" << std::endl;
    item_id = (item_id + 1) % TABLE_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    // delay
    sleep(1);
  }
  pthrad_exit(NULL);
}

int main(){
  pthread_t prod_thread;

  // Initialize semaphores and mutex
  sem_init(&empty, 0, TABLE_SIZE);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&mutex, NULL);

  // Create thread
  pthread_create(&prod_thread, NULL, producer, NULL);
  // Join thread
  pthread_join(prod_thread, NULL);

  // Destroy semaphores and mutex
  sem_destroy(&empty);
  sem_destroy(&full);
  pthread_mutex_destroy(&mutex);

  return 0;
}
