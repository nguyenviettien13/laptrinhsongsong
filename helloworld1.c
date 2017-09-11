#include <omp.h>
#include <stdio.h>
int main()
{
    omp_set_num_threads(10);
#pragma omp parallel //the hien rang cau lenh tiep theo se duoc thuc hien song song
    {
        int id = omp_get_thread_num();       // tra ve so thu tu luong ma no dang chay tinh tu 0
        int threads = omp_get_num_threads(); //tra ve tong so luong vat ly
        printf("Hello from thread %d, nthreads %d \n", id, thread);
    }
}