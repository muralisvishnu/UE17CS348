#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>
#include <queue>
using namespace std;

queue<int> Q;
condition_variable w_var;
condition_variable r_var;
mutex m;
bool finished;

void producer(int num_items){
    int i = 0;
    while (i < num_items){
        unique_lock<mutex> lock(m);
        w_var.wait(lock);
        Q.push(i);
        cout << "Produced " << i << endl;
        w_var.notify_one();
        r_var.notify_one();
        i++;
    }
    finished = true;
}

void consumer(){
    int read = 0;
    while (!finished){
        while (!Q.size() == 0){
            unique_lock<mutex> lock(m);
            r_var.wait(lock);
            read = Q.front();
            Q.pop();
            cout << "Consumed " << read << endl;     
            w_var.notify_one();
        }
    }
}

int main(){
    int i = 30;
    finished = false;
    w_var.notify_one();
    thread prod(&producer,i);
    thread cons(&consumer);
    prod.join();
    cons.join();
    return 0;
}
