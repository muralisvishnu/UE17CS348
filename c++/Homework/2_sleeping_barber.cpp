#include <thread>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <vector>
#include <queue>
using namespace std;

condition_variable barber;
condition_variable cust;
mutex cust_count;
mutex operation;
int customer_count = 0;
int done_work = 0;
int num_chairs = 0;
int total_customers = 0;
queue<int> chairs;

void customer(int id){
    cust_count.lock();
    total_customers--;
    if (customer_count < num_chairs){
        //update counter and wait
        cout << "Customer " << id << " added to queue" << endl;
        customer_count++;
        chairs.push(id);
        if (total_customers == 0){
            done_work =1;
        }
        barber.notify_one();
    }else{
     cout << "Customer " << id << " left" << endl;
    }
    cust_count.unlock();
}

void barber_method(){
    while (done_work == 0){
        unique_lock<mutex> lock(operation);
        barber.wait(lock);
        while(!chairs.empty()){
            cust_count.lock();
            customer_count--;
            //read from queue - perform haircut
            cout << "Barber hair cut for " << chairs.front() << endl;
            chairs.pop();
            cust_count.unlock();
        }
    }
}

int main(int argc, char** argv){
    if (argc < 3){
        fprintf(stderr,"Input number of chairs and customers\n");return 0;
    }
    num_chairs = atoi(argv[1]);
    int num_customers = atoi(argv[2]);
    vector<thread> threads;
    thread barber_thread = thread(&barber_method);
    total_customers = num_customers;
    for (int i = 0; i < num_customers ;i++){
        threads.push_back(thread(&customer,i));
    }
    
    for(auto& customer:threads){
        customer.join();
    }
    barber_thread.join();
    return 0;
}