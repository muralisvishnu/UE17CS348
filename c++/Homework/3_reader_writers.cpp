#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <mutex>

using namespace std;

int readcount = 0;
mutex shvar_mutex;
mutex writing;
mutex readc;
condition_variable wr;
int shared_var = 0;

void reader(int id){
    readc.lock();
    readcount++;
    if (readcount == 0){
        //first reader, wait for writers
        unique_lock<mutex> lock(writing);
        readc.unlock();
        wr.wait(lock);
    }else{
        readc.unlock();
    }
    //perform read
    shvar_mutex.lock();
    cout << "Thread " << id << " reads " << shared_var << endl;
    shvar_mutex.unlock();
    readc.lock();
    readcount --;
    if (readcount == 0){
        //last reader
        wr.notify_one();
    }
    readc.unlock();
}

void writer(int id){
    unique_lock<mutex> lock(writing);
    wr.wait(lock);
    shvar_mutex.lock();
    shared_var = id;
    cout << "Shared var updated to " << id <<endl;
    shvar_mutex.unlock();
    wr.notify_one();
}

int main (int argc ,char ** argv){
    if (argc < 3){
        fprintf(stderr,"Please enter number of writers and readers\n");return 0;
    }
    int numreaders = atoi(argv[1]);
    int numwriters = atoi(argv[2]);

    vector<thread> v;
    for (int i = 0 ; i < numreaders; i++){
        v.push_back(thread(&reader,i));
    }
    for (int i = 0; i < numwriters ;i++){
        v.push_back(thread(&writer,i));
    }
    for (int i = numreaders ; i < numreaders*2; i++){
        v.push_back(thread(&reader,i));
    }
    for(auto& th:v){
        th.join();
    }
    return 0;
}