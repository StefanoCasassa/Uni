#include <iostream>
#include "ASD-sort.h"
using namespace std;
const int N=10;
int main(){
    vector<int> v;
    int k;
    for (int i=0;i<N;++i){
        cin>>k;
        v.push_back(k);
    }
    quickSortRandom(v);
    for (int i=0;i<N;++i){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}