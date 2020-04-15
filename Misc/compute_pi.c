#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
// Gregory-Leibniz Series
void* compute(void* args);
int main(){
        int num_threads = 0; int limit;
        printf("Enter the number of threads that you want and the limit: \n");
        scanf("%d %d",&num_threads,&limit);
        pthread_t threads[num_threads];
        int * args;
        void ** y = malloc(sizeof(num_threads));
        
        for (int i = 0; i < num_threads; i++){
                args = (void*)malloc(sizeof(int)*4);
                args[0] = i; //base
                args[1] = num_threads; //increment
                args[2] = limit;
                args[3] = i;
                pthread_create(&threads[i],NULL,compute,args);
                //printf("Dispatch thread %d\n",i);fflush(stdout);
        }
        for (int i = 0 ; i < num_threads; i++){
                pthread_join(threads[i],&y[i]);
        }
        double final_ans = 0;
        double** results = (double**)y;
        for (int i = 0; i < num_threads; i++){
                final_ans+= *(results[i]);
        }
        printf("Value of PI: %f\n",final_ans*4);
}

void* compute(void* args){
        int* arr = (int*)args;
        int base = arr[0];
        int increment = arr[1];
        int limit = arr[2];
        int id = arr[3];
        //printf("Starting compute on Thread-%d\n",id);
        double * sum = (double*)calloc(0,sizeof(double));
        
        for (int i = base; i <= limit; i+=increment){
                *sum = *sum + (pow(-1,i) / ((2*i) + 1));
                //printf("Partial result i = %d -- %f\n",i,*sum);
        }
        printf("Thread-%d final answer: %lf\n",id,*sum);
        return (void*)sum;
}