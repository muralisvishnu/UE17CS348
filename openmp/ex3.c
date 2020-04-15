#include <stdio.h>
#include <omp.h>
#define MAX_THREADS 4
int main(){
    static long num_steps = 10000;
    int num_threads_allocated = 0;
    double step = 1.0/(double)num_steps;
    omp_set_num_threads(MAX_THREADS);
    double sum = 0.0;
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        if (tid ==0) num_threads_allocated = omp_get_num_threads();
        long count = 0; double x;
       
        for (count = tid; count < num_steps; count += num_threads){
            x = (double)(count)*step;
            #pragma omp atomic
            sum += (4.0/(1.0+x*x))*step ;
        }
    }
    printf("value of PI is %lf\n",sum);
}