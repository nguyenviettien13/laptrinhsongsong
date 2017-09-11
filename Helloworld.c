#include <omp.h>
#include <stdio.h>
int main()
{
#pragma omp parallel //the hien rang cau lenh tiep theo se duoc thuc hien song song
    printf("Hello from thread %d, nthreads %d \n",
           omp_get_thread_num(),   // tra ve so thu tu luong ma no dang chay tinh tu 0
           omp_get_num_threads()); //tra ve tong so luong vat ly
}