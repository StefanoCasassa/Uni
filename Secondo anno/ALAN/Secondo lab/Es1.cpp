#include <iostream> 
#include <cmath>
#include <limits>

using namespace std;


const int N=4;
const int M=10;
const int O=33;
const double PRECISIONVALUE=0.0001;

int main () {
    double matrix[N][N]={3,1,-1,0,0,7,-3,0,0,-3,9,-2,0,0,4,-10};
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    int aux = 0;
    int Tot = 0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            aux+=abs(matrix[i][j]);
        }
        if (aux>Tot) Tot=aux;
        aux=0;
    }
    cout<<endl<<Tot<<endl<<endl<<endl;

    double matrix2[M][M];

    for (int i=1;i<=M;i++){
        for (int j=1;j<=M;j++){
            matrix2[i-1][j-1]=tgamma((i+j-2)+1) / (tgamma((i-1)+1) * tgamma((j-1)+1));
        }
        
    }
    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            cout<<matrix2[i][j]<<" ";
        }
        cout<<endl;
    }
    double aux1 = 0;
    double Tot1 = 0;
    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            aux1+=abs(matrix2[i][j]);
        }
        if (aux1>Tot1) Tot1=aux1;
        aux1=0;
    }
    cout<<endl<<Tot1<<endl<<endl<<endl;





    double matrix3[O][O];

    for (int i=0;i<O;i++){
        for (int j=0;j<O;j++){
            if (abs(i-j)<PRECISIONVALUE) matrix3[i][j]=2;
            else if (abs(i-j)<1+PRECISIONVALUE) matrix3[i][j]=-1;
            else matrix3[i][j]=0;
        }
        
    }
    for (int i=0;i<O;i++){
        for (int j=0;j<O;j++){
            cout<<matrix3[i][j]<<" ";
        }
        cout<<endl;
    }
    double aux2 = 0;
    double Tot2 = 0;
    for (int i=0;i<O;i++){
        for (int j=0;j<O;j++){
            aux2+=abs(matrix3[i][j]);
        }
        if (aux2>Tot2) Tot2=aux2;
        aux2=0;
    }
    cout<<endl<<Tot2<<endl<<endl<<endl;
}