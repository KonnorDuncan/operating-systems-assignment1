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
int item_id = 0;

void* consumer(void* arg) {
  while (true) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    // Consume item
    std::cout << "Consumed item: " << table[item_id - 1] << std::endl;
    table[item_id - 1] = 0;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    //delay
    sleep(2);
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t cons_thread;

  // Initialize semaphores and mutex
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&mutex, NULL);

  // Create consumer thread
  pthread_create(&cons_thread, NULL, consumer, NULL);

  // Join consumer thread
  pthread_join(cons_thread, NULL);

  // Destroy semaphores and mutex
  sem_destroy(&empty);
  sem_destroy(&full);
  pthread_mutex_destroy(&mutex);

    return 0;
}
