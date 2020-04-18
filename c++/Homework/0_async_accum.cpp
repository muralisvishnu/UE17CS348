#include <iostream>
#include <future>
#include <chrono>
#include <vector>
using namespace std;

int accum = 0;

int square_sum(int x){
    return x*x;
}

int main(){
    vector<future<int>> data;
    for (int i = 0; i < 20; i++){
        data.push_back(async(&square_sum,i));
    }
    for (auto& elem:data){
       accum += elem.get();
    }
    cout << accum << endl;
    return 0;
}