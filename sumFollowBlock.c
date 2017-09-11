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
    omp_set_num_threads(20); //4row x 5column
    int privatesum;
    int id;
    int i;
    int j;
    int startc;
    int startr;
    int finishc;
    int finishr;
    int c;
    int r;
#pragma omp parallel private(c, r, privatesum, id, i, j, startc, startr, finishc, finishr)

    {
        id = omp_get_thread_num();
        privatesum = 0;
        r = id / 5;
        c = id % 5;
        startc = 200 * c;
        finishc = startc + 200;
        startr = 250 * r;
        finishr = startr + 250;
        for (i = startr; i < finishr; i++)
        {
            for (j = startc; j < finishc; j++)
            {
                privatesum += arr[i][j];
            }
        }
        pthread_mutex_lock(&mutex);
        sum += privatesum;
        pthread_mutex_unlock(&mutex);
    }
    printf("Sum: %d", sum);
}