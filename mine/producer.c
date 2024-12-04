#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For usleep()

#define BUFFER_SIZE 5
#define MAX_OPERATIONS 30 // Increased for better demonstration

int buffer[BUFFER_SIZE], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 0; i < MAX_OPERATIONS / 2; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = rand() % 100;
        printf("Produced by thread %lu: %d\n", pthread_self(), buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        usleep(100000); // 100ms delay to simulate real-world production
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < MAX_OPERATIONS / 2; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        printf("Consumed by thread %lu: %d\n", pthread_self(), buffer[out]);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        usleep(150000); // 150ms delay to simulate real-world consumption
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
