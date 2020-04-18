#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>
#include <mutex>
#include <chrono>
using namespace std;

queue<int> buffer;
int sizeq = 0;
mutex protect;
mutex util;
condition_variable qfull;
condition_variable qempty;
int num_items;
int done = 0;
void consumer(){
    while (done == 0){
        unique_lock<mutex> lock(util);
        cout << "Consumer waiting" <<endl;
        qfull.wait(lock);
        protect.lock();
        cout << "Consumed " << buffer.front() << endl;
        buffer.pop();
        protect.unlock();
        sizeq --;
        if (sizeq > 0){
            qfull.notify_one();
        }
        qempty.notify_one();
    }
}
void producer(){
    int items_produced = 0;
    while (items_produced < num_items && sizeq < 5){
         unique_lock<mutex> lock(util);
         cout << "Producer Waiting" << endl;
         qempty.wait(lock);
         int item = rand() % 1000;
         protect.lock();
         buffer.push(item);
         sizeq++;
         items_produced++;
         cout << "Produced " << item << endl;
         protect.unlock();
         qfull.notify_one();
    }
    done = 1;
}

int main(int argc, char** argv){
    if (argc < 2){
        fprintf(stderr,"Please enter the number of elements to produce as a command line arg\n"); return 0;
    }
    num_items = atoi(argv[1]);
    thread prod = thread(&producer);
    thread cons = thread(&consumer);
    this_thread::sleep_for(chrono::milliseconds(200));
    qempty.notify_one();
    prod.join();
    cons.join();
    return 0;
}