#include <iostream> 
#include <cmath>
#include <limits>

using namespace std;


const int N=4;
const int M=10;
const int O=33;
const double PRECISIONVALUE=0.0001;
double normaInf(double** matrix,int riga,int col){
    double aux=0.0;
    double Tot=0.0;
    for (int i=0;i<riga;i++){
        for (int j=0;j<col;j++){
            aux+=abs(matrix[i][j]);
        }
        if (aux>Tot) Tot=aux;
        aux=0;
    }
    return Tot;
}

void stampa(double** matrix,int riga,int col){
      for (int i=0;i<riga;i++){
        for (int j=0;j<col;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main () {
    //1.1
    double **matrix = new double*[N];
    for (int i=0;i<N;i++){
        matrix[i]=new double[N];
    }
    double val[N*N]={3,1,-1,0,0,7,-3,0,0,-3,9,-2,0,0,4,-10};
    int indx=0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrix[i][j]=val[indx++];
        }
        
    }
    stampa(matrix,N,N);
    cout<<endl<<normaInf(matrix,N,N)<<endl<<endl;
    
    //1.1.1
    double val2[N*N]={2,4,-2,0,1,3,0,1,3,-1,1,2,0,-1,2,1};
    indx=0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrix[i][j]=val2[indx++];
        }
        
    }
    stampa(matrix,N,N);
    cout<<endl<<normaInf(matrix,N,N)<<endl<<endl;

    for (int i=0;i<N;i++){
        delete matrix[i];
    }
    delete matrix;


    //1.2
    matrix = new double*[M];
    for (int i=0;i<M;i++){
        matrix[i]=new double[M];
    }

    for (int i=1;i<=M;i++){
        for (int j=1;j<=M;j++){
            matrix[i-1][j-1]=tgamma((i+j-2)+1) / (tgamma((i-1)+1) * tgamma((j-1)+1));
        }
        
    }
    stampa(matrix,M,M);
    cout<<endl<<normaInf(matrix,M,M)<<endl<<endl;
    for (int i=0;i<M;i++){
        delete matrix[i];
    }
    delete matrix;

    //1.3
    matrix = new double*[O];
    for (int i=0;i<O;i++){
        matrix[i]=new double[O];
    }

    for (int i=0;i<O;i++){
        for (int j=0;j<O;j++){
            if (abs(i-j)<PRECISIONVALUE) matrix[i][j]=2;
            else if (abs(i-j)<1+PRECISIONVALUE) matrix[i][j]=-1;
            else matrix[i][j]=0;
        }
    }
    
    stampa(matrix,O,O);
    cout<<endl<<normaInf(matrix,O,O)<<endl<<endl;
    for (int i=0;i<O;i++){
        delete matrix[i];
    }
    delete matrix;
}