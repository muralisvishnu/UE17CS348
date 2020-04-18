#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

int square(int x){
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << this_thread::get_id() << endl;
    return x*x;
}
int main(){
    auto a = async(&square,10);
    int v = a.get();
    cout << "Returned value is " << v << endl;
    return 0;
}
