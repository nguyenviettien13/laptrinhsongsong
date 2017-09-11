/*shared and private variable
    shared(list)
    all variable 
*/

#include <omp.h>
#include <stdio.h>
int main()
{
    int id, x;
    omp_set_num_threads(10000000);
#pragma omp parallel private(id, x) //khi khai bao id va x la private thi ta phai khai bao id, x truoc
    {
        int id = omp_get_thread_num(); // tra ve so thu tu luong ma no dang chay tinh tu 0
        x = 10 * id;
        printf("\n");
        int threads = omp_get_num_threads(); //tra ve tong so luong vat ly
        printf("Hello from thread %d, nthreads %d \n", id, x);
        printf("\n");
    }
    return 0;
}
