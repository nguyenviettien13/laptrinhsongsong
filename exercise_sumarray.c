#include <omp.h>
#include <stdio.h>

int main()
{
    int array1[10];
    int array2[10];
    int arrayresult[10];
    for (int i = 0; i < 10; i++)
    {
        array1[i] = i;
    }
    for (int i = 0; i < 10; i++)
    {
        array2[i] = i;
    }
    omp_set_num_threads(5);
    int id;
    int start, finish;
    int i;
#pragma omp parallel private(i, id, start, finish)
    {
        id = omp_get_thread_num();
        start = id * 2;
        finish = start + 2;
        for (int i = start; i < finish; i++)
        {
            arrayresult[i] = array1[i] + array2[i];
                }
    }

    for (i = 0; i < 10; i++)
    {
        printf("%d \n", arrayresult[i]);
    }

    return 0;
}