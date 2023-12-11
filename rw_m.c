#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int data = 0;
int readers_count = 0;
pthread_mutex_t mutex;
pthread_mutex_t data_mutex;
pthread_mutex_t reader_exit_mutex;
int running = 1;

void *reader(void *arg)
{
    int reader_id = *(int *)arg;

    while (running)
    {
        pthread_mutex_lock(&mutex);
        readers_count++;
        if (readers_count == 1)
        {
            pthread_mutex_lock(&data_mutex);
        }
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading data: %d\n", reader_id, data);
        usleep(100000);

        pthread_mutex_lock(&mutex);
        readers_count--;

        if (readers_count == 0)
        {
            pthread_mutex_unlock(&data_mutex);
        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&reader_exit_mutex);
        printf("Reader %d is leaving\n", reader_id);
        pthread_mutex_unlock(&reader_exit_mutex);

        usleep(100000);
    }

    return NULL;
}

void *writer(void *arg)
{
    int writer_id = *(int *)arg;

    while (running)
    {
        pthread_mutex_lock(&data_mutex);

        data++;
        printf("Writer %d is writing data: %d\n", writer_id, data);

        pthread_mutex_unlock(&data_mutex);

        printf("Writer %d is leaving\n", writer_id);
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

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&data_mutex, NULL);
    pthread_mutex_init(&reader_exit_mutex, NULL);

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

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&data_mutex);
    pthread_mutex_destroy(&reader_exit_mutex);

    return 0;
}
