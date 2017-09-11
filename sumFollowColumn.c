#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

//type
//variable
int arr[1000][1000];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//const
//function
void initArray()
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 1000; j++)
        {
            srand(time(NULL));
            arr[i][j] = rand() % 1 + 1;
        }
    }
}

int main()
{
    initArray();

    int sum = 0;
    omp_set_num_threads(10);
    int id;
    int privatesum;
    int startc;
    int finishc;
    int i;
    int j;
#pragma omp parallel private(id, privatesum, startc, finishc, i, j)

    {
        id = omp_get_thread_num();
        privatesum = 0;
        startc = id * 100;
        finishc = startc + 100;
        for (i = startc; i < finishc; i++)
        {
            for (j = 0; j < 1000; j++)
            {
                privatesum += arr[i][j];
            }
        }
        pthread_mutex_lock(&mutex);
        sum += privatesum;
        pthread_mutex_unlock(&mutex);
    }
    printf("%d", sum);
}