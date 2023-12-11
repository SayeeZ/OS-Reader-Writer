#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int data = 0;
int readers_count = 0;
sem_t x, y; // x:reader y:writer
int running = 1;

void *reader(void *arg)
{
    int reader_id = *(int *)arg;

    while (running)
    {
        sem_wait(&x);  //sem_wait() => decrements value by 1 //0
        readers_count++;
        if (readers_count == 1)
        {
            sem_wait(&y);
        }
        sem_post(&x);  //sem_post() => increments value by 1 //1

        printf("Reader %d is reading data: %d\n", reader_id, data);
        usleep(100000);
        printf("Reader %d is leaving \n", reader_id);
        usleep(100000);

        sem_wait(&x);
        readers_count--;
        if (readers_count == 0)
        {
            sem_post(&y);
        }
        sem_post(&x);

        usleep(100000);
    }

    return NULL;
}

void *writer(void *arg)
{
    int writer_id = *(int *)arg;

    while (running)
    {
        sem_wait(&y);

        data++;
        printf("Writer %d is writing data: %d\n", writer_id, data);
        printf("Writer %d is leaving \n", writer_id);
        usleep(100000);
        sem_post(&y);

        usleep(200000);
        sleep(2);
    }

    return NULL;
}

int main()
{
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    sem_init(&x, 0, 1);
    sem_init(&y, 0, 1);

    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    sleep(1);

    running = 0;

    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&x);
    sem_destroy(&y);

    return 0;
}
