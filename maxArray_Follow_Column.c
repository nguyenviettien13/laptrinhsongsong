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
            arr[i][j] = rand() % 100;
        }
    }
}

int main()
{
    initArray();

    int globalmax = 0;
    omp_set_num_threads(10);
    int id;
    int localmax;
    int startc;
    int finishc;
    int i;
    int j;
#pragma omp parallel private(id, localmax, startc, finishc, i, j)

    {
        id = omp_get_thread_num();
        localmax = arr[0][0];
        startc = id * 100;
        finishc = startc + 100;
        for (i = startc; i < finishc; i++)
        {
            for (j = 0; j < 1000; j++)
            {
                if (localmax < arr[i][j])
                    localmax += arr[i][j];
            }
        }
        pthread_mutex_lock(&mutex);
        if (globalmax < localmax)
            globalmax = localmax;
        pthread_mutex_unlock(&mutex);
    }
    printf("%d", globalmax);
}