#include <stdio.h>
#include <omp.h>
int main(){
    int width = 1; double sum = 0.0; int num_threads = 8;
    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        int i = omp_get_num_threads();
        int tid = omp_get_thread_num();
        double block_width = (double)width / i;
        //printf("%lf(%d)\n",block_width,tid);
        double start = tid*block_width;
        double end = (tid+1)*block_width;
        double step = block_width/20; //each is supposed to do 20
        //printf("%lf %lf %lf (%d)\n",start,end,step,tid);
        for (double k = start;k<end;k=k+step){
            sum += 4.0/(1+k*k);
        }
    }
    printf("PI is %lf\n",sum/(num_threads*20));
    return 0;
}