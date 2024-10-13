#include <iostream> 
#include <cmath>
#include <limits>
using namespace std;
int main(){
    double a,b,c;
    int d1 = 0;
    int d0 = 0;
    b=(d1+1)*pow(10,20);
    cout<<pow(10,20)+1<<endl;
    c=(-1)*b;
    for (int i=0;i<7;i++){
        a=(d0+1)*pow(10,i);
        cout<<"Output per (a+b)+c dove a = "<<a<<" b = "<<b<<" c = "<<c<<" è "<<": "<<(a+b)+c<<endl;
        cout<<"Output per a+(b+c) dove a = "<<a<<" b = "<<b<<" c = "<<c<<" è "<<": "<<a+(b+c)<<endl<<endl;
    }
    return 0;
}