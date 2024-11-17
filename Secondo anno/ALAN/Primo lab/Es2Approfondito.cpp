#include <iostream> 
#include <cmath>
#include <limits>
using namespace std;
double fattoriale(double k){
    if (k==1||k==0) return 1;
    return k*fattoriale(k-1);
}
int main(){
    double x[4]={0.5,-0.5,30,-30};
    double ris=0;
    double ris2=0;
    for(int l=0;l<4;l++){
        int j=0;
        while (j<200){
            for (int i=0;i<=j;i++){
                ris+=pow(x[l],i)/fattoriale(i);
            }
            cout<<"ALG1 Per "<<j<<" e x= "<<x[l]<<" viene "<<ris<<endl;
            j++;
            ris=0;
        }
        
        cout<<endl;
            ris2=exp(x[l]);
            cout<<"Per x= "<<x[l]<<" l'esponenziale viene "<<ris2<<endl;
            ris2=0;
        cout<<endl;
    int ze=0;
        while (ze<200){
            for (int i=0;i<=ze;i++){
                ris+=pow(x[l],i)/fattoriale(i);
            }
            
            cout<<"ALG2 Per "<<ze<<" e x= "<<-1*x[l]<<" viene "<<1/ris<<endl;
            ris=0;
            ze++;
        }
        
        cout<<endl;
            ris2=exp(x[l]);
            cout<<"Per x= "<<-1*x[l]<<" l'esponenziale viene "<<1/ris2<<endl;
            ris2=0;
        cout<<endl;
    }
    cout<<endl;


    
}