#include <iostream>
using namespace std;

const int N=10;

void swap(int A[],unsigned a, unsigned b){
    int aux=A[a];
    A[a]=A[b];
    A[b]=aux;
}

unsigned Partizione(int A[], unsigned l, unsigned r){
    int p=A[l];
    unsigned i=l+1;
    for (unsigned j=l+1;j<=r;++j){
        if (A[j]<p){
            swap(A[j],A[i]);
            ++i;
        }
    }
    swap(A[l],A[i-1]);
    return (i-1);
}

void qs(int A[],unsigned inizio, unsigned fine){
    if (fine==inizio) return;
    unsigned p=Partizione(A,inizio,fine);
    if (p!=inizio) 
        qs(A,inizio,p-1);
    if (p!=fine)
        qs(A,p+1,fine);
    
}
void quickSort(int A[]){
    qs(A,0,N-1);
}
int main(){
    int A[N];
    for (int i=0;i<N;++i){
        cin>>A[i];
    }
    quickSort(A);
    for (int i=0;i<N;++i){
        cout<<A[i]<<" ";
    }
    cout<<endl;
}