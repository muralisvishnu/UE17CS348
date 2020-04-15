#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>
// source : https://docs.oracle.com/cd/E19455-01/806-5257/attrib-16/index.html

void thread_actions(void* number){
        sleep(3);
        printf("Hello from thread number %ld %d\n",pthread_self(),*(int*)number);
}

int main(){
    pthread_t t1, t2; int a = 1; int b = 2;
    pthread_attr_t t1attr,t2attr;
    int priot1 = 23;
    int priot2 = 87;
    struct sched_param param1, param2;
    pthread_attr_init(&t1attr);
    pthread_attr_init(&t2attr);
    pthread_attr_getschedparam(&t1attr,&param1);
    pthread_attr_getschedparam(&t2attr,&param2);
    param1.sched_priority = priot1;
    param2.sched_priority = priot2;
    pthread_setschedparam(&t1attr, SCHED_FIFO, &param1);
    pthread_setschedparam(&t2attr, SCHED_FIFO, &param2);
    pthread_create(&t1, NULL, thread_actions, &a);
    pthread_create(&t2, NULL, thread_actions, &b);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0; 
}
