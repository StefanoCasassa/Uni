#include <iostream>
#include <cmath>
using namespace std;
int main(){
    float a=0;
    while(1+float(pow(2,a*(-1)))>1){
        float c=1+pow(2,a*(-1));
        printf("%.7f",c);
        cout<<" for "<<a<<endl;
        a++;
    }
    cout<<pow(2,-(a-1))<<endl;
    cout<<endl;
    double b=0;
    while(1+pow(2,b*(-1))>1){
        double z=1+pow(2,b*(-1));
        printf("%.16lf",z); //abbiamo usato printf per avere tutto il numero in output
        cout<<" for "<<b <<endl;
        b++;
    }
    cout<<pow(2,-(b-1))<<endl;
}