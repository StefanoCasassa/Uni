#include <iostream> 
#include <cmath>
#include <limits>

using namespace std;

const int N=4;
const int M=10;
const int O=33;
const double PRECISIONVALUE=0.0001;
double normaInf(double** &matrix,int riga,int col){
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

void stampa(double** &matrix,int riga,int col){
    cout<<endl;
      for (int i=0;i<riga;i++){
        for (int j=0;j<col;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}
void Bcalc(double** &matrix,int riga,int col,double* &b){ //calcolo il vettore b di lunghezza "riga" (N,M,O) assumendo vettore X=(1,1,1,1,...,1)
    double aux=0.0;
    double Tot=0.0;
    for (int i=0;i<riga;i++){
        for (int j=0;j<col;j++){
            aux+=matrix[i][j];
        }
        b[i]=aux;
        aux=0;
    }
}
void pivot(double** &matrix,int riga,int col){ //i è la riga sul quale si lavora
    bool pvt=false;                           //trovato il pivot
    double *auxP=nullptr;
    int j=0;                                  //colonna su cui lavoro
    for (int i=0;i<riga;i++){
        pvt=false;
        int k=i;
        while (k<riga){                        //cerco il pvt
            if ((matrix[k][j])!=0) {
                auxP=matrix[i];
                matrix[i]=matrix[k];
                matrix[k]=auxP;
                pvt=true;
                break;
            }
            k++;
        }
        if (pvt) {
            for (int l=i+1;l<riga;l++){
                double el=0;
                if (abs(matrix[l][j])>0.0000001) {
                    el=matrix[l][j]/matrix[i][j];
                    for (int co=j;co<col;co++){
                            matrix[l][co]=matrix[l][co]-(matrix[i][co]*el);
                    }
                }
            }


        }
        j++;
        if (!pvt) i--; //se non esiste il pvt in questa colonna
        if (j==col) break; //se mancano dei pivot
        
    }
}
void deleteMatrix(double**&matrix,int riga){
    for (int i=0;i<riga;++i){
        delete[] matrix[i];
    }
    delete[] matrix;
}
double ** inizializza(int riga,int col){
    double **matrix = new double*[riga];
    for (int i=0;i<riga;i++){
        matrix[i]=new double[col];
    }
    return matrix;
}
double** createAXb(double** &matrix,int riga,int col,double* &b){
    double **matrixAb=inizializza(riga,col+1);
    for (int i=0;i<riga;i++){ //inserisco i valori in Ab
        for (int j=0;j<col;j++){
            matrixAb[i][j]=matrix[i][j];
        }
        matrixAb[i][col]=b[i];
        
    }
    return matrixAb;
}
int main () {
    //2.1.1
    double **matrix = inizializza(N,N);
    double val[N*N]={3,1,-1,0,0,7,-3,0,0,-3,9,-2,0,0,4,-10};
    int indx=0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrix[i][j]=val[indx++];
        }
        
    }
    cout<<endl<<"Matrice Base\n";
    stampa(matrix,N,N);
    cout<<endl<<"Norma: "<<normaInf(matrix,N,N)<<endl;

    double *b=new double[N];
    Bcalc(matrix,N,N,b);

    double **matrixAb = createAXb(matrix,N,N,b);
    cout<<endl<<"Matrice Ab\n";
    stampa(matrixAb,N,N+1); 
    pivot(matrixAb,N,N+1);
    cout<<endl<<"Matrice Ab con eliminazione Gaussiana\n";
    stampa(matrixAb,N,N+1);

    delete[] b;
    deleteMatrix(matrix,N);
    deleteMatrix(matrixAb,N);

    //2.1.2
    matrix = inizializza(N,N);
    double val2[N*N]={2,4,-2,0,1,3,0,1,3,-1,1,2,0,-1,2,1};
    indx=0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrix[i][j]=val2[indx++];
        }
        
    }
    cout<<endl<<"Matrice Base\n";
    stampa(matrix,N,N);
    cout<<endl<<"Norma: "<<normaInf(matrix,N,N)<<endl;
    b=new double[N];
    Bcalc(matrix,N,N,b);

    matrixAb = createAXb(matrix,N,N,b);  
    cout<<endl<<"Matrice Ab\n";          
    stampa(matrixAb,N,N+1);
    pivot(matrixAb,N,N+1);
    cout<<endl<<"Matrice Ab con eliminazione Gaussiana\n";
    stampa(matrixAb,N,N+1);

    delete[] b;
    deleteMatrix(matrix,N);
    deleteMatrix(matrixAb,N);




    //2.1.2
    matrix = inizializza(M,M);

    for (int i=1;i<=M;i++){
        for (int j=1;j<=M;j++){
            matrix[i-1][j-1]=tgamma((i+j-2)+1) / (tgamma((i-1)+1) * tgamma((j-1)+1));
        }
        
    }
    cout<<endl<<"Matrice Base\n";
    stampa(matrix,M,M);
    cout<<endl<<"Norma: "<<normaInf(matrix,M,M)<<endl;
    b=new double[M];
    Bcalc(matrix,M,M,b);

    matrixAb = createAXb(matrix,M,M,b);  
    cout<<endl<<"Matrice Ab\n";          
    stampa(matrixAb,M,M+1);
    pivot(matrixAb,M,M+1);
    cout<<endl<<"Matrice Ab con eliminazione Gaussiana\n";
    stampa(matrixAb,M,M+1);

    delete[] b;
    deleteMatrix(matrix,M);
    deleteMatrix(matrixAb,M);
    //2.1.3
    matrix = inizializza(O,O);

    for (int i=0;i<O;i++){
        for (int j=0;j<O;j++){
            if (abs(i-j)<PRECISIONVALUE) matrix[i][j]=2;
            else if (abs(i-j)<1+PRECISIONVALUE) matrix[i][j]=-1;
            else matrix[i][j]=0;
        }
    }
    
    cout<<endl<<"Matrice Base\n";
    stampa(matrix,O,O);
    cout<<endl<<"Norma: "<<normaInf(matrix,O,O)<<endl;
    b=new double[O];
    Bcalc(matrix,O,O,b);

    matrixAb = createAXb(matrix,O,O,b);  
    cout<<endl<<"Matrice Ab\n";          
    stampa(matrixAb,O,O+1);
    pivot(matrixAb,O,O+1);
    cout<<endl<<"Matrice Ab con eliminazione Gaussiana\n";
    stampa(matrixAb,O,O+1);

    delete[] b;
    deleteMatrix(matrix,O);
    deleteMatrix(matrixAb,O);
}