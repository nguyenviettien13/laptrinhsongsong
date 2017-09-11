#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

//type
//variable
int arr[1000][1000];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FILE *fout;

//const
//function
void initArray()
{
    fout = fopen("output.txt", "w");
    if (fout != NULL)
    {
        printf("opened successful");
    }
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
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 1000; j++)
        {
            fprintf(fout, "%d ", arr[i][j]);
        }
        fprintf(fout, "end \n");
    }
    fclose(fout);
}
int main()
{
    initArray();
    int globalmax = arr[0][0];
    omp_set_num_threads(20); //4row x 5column
    int localmax;
    int id;
    int i;
    int j;
    int startc;
    int startr;
    int finishc;
    int finishr;
    int c;
    int r;
    fprintf(stdout, "ting ting: %u\n", (unsigned)time(NULL));
#pragma omp parallel private(c, r, localmax, id, i, j, startc, startr, finishc, finishr)

    {
        id = omp_get_thread_num();
        localmax = arr[0][0];
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
                if (localmax < arr[i][j])
                    localmax = arr[i][j];
            }
        }
        pthread_mutex_lock(&mutex);
        if (globalmax < localmax)
            globalmax = localmax;
        pthread_mutex_unlock(&mutex);
    }
    printf("Sum: %d", globalmax);
}