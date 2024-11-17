#include <thread>
#include <unistd.h>
#include <iostream>
#include <chrono>
using namespace std;

void functionOne(){
    for (int i=0;i<1000;i++){
        cout<< "+"<<endl;
        this_thread::sleep_for(std::chrono::seconds(1));

    }
}

void functionTwo(){
    for (int i=0;i<2000;i++){
        cout<< "-"<<endl;
        this_thread::sleep_for(std::chrono::seconds(1));

    }
}

int main (){
   
    thread worker1(functionOne);
    thread worker2(functionTwo);
    worker1.detach();
    worker2.detach();
    

}