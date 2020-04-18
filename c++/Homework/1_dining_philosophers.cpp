#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <stdlib.h>
#include <chrono>
#include <map>
#include <mutex>
#include <vector>
using namespace std;

queue <int> q;
mutex* chopsticks;
mutex protect_bowl;

int isempty(){
    protect_bowl.lock();
    int res = q.empty();
    protect_bowl.unlock();
    return res;
}
void philosopher(int my_id, int numdiners){
    //thinks - sleep
    //eats - consume from queue
    //repeat until there's nothing left - death
    cout << "Philosopher " << my_id << " started" << endl;
    while (!isempty()){
        //get chopsticks to eat
        chopsticks[my_id].lock();
        chopsticks[(my_id+1)%numdiners].lock();
        //eat
        protect_bowl.lock();
        cout << "Phil index " << my_id << " Consumed " << q.front() << endl;
        q.pop();
        protect_bowl.unlock();
        chopsticks[my_id].unlock();
        chopsticks[(my_id+1)%numdiners].unlock();
        this_thread::sleep_for(chrono::milliseconds(100));//think
    }
        cout << "Phil index " << my_id << " Died" << endl;
}

int main(int argc , char ** argv){
    if (argc < 2){
        fprintf(stderr,"Please enter number of diners\n");
        return 0;
    }
    int numdiners = atoi(argv[1]);
    //create ricebowl
    
    for (int i = 0 ; i < numdiners; i++){
        q.push(rand()%1000);
    }
    chopsticks = (mutex*)malloc(sizeof(mutex)*numdiners);
    vector<thread> v;
    for (int i = 0; i < numdiners*2; i++){
        v.push_back(thread(&philosopher,i,numdiners));
    }
    for (auto& diner:v){
        diner.join();
    }
    return 0;
}   