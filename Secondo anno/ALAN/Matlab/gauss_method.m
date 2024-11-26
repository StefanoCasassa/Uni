% implementare una funzione per triangolarizzare una matrice con il metodo 
% di eliminazione di Gauss
% Parametri:
% input:  A, la matrice da triangolarizzare
% output: T, la matrice triangolarizzata

function T = gauss_method(A)
    
    % ottenere le dimensioni di A tramite il comando size
    [row, col] = size(A);
    % inizializzazione della matrice di output con una matrice di zeri
    T = A;
    % gli indici in Matlab partono da 1...
    pvt=false;
    j=1;
    for i = 1:row
        pvt=false;
        k=i;
        while k<=row
            if (abs(T(k,j))>abs(T(i,j)))
                aux=T(i,:);
                T(i,:)=T(k,:);
                T(k,:)=aux;
            end
            k=k+1;
            if T(i,j)~=0
                pvt=true;
            end
        end
        if pvt
            for l=i+1:row
                el=0;
                if  abs(T(l,j))~=0
                    el=T(l,j)/T(i,j);
                    T(l,j)=0;
                    for co=j+1:col
                        T(l,co)=T(l,co)-(T(i,co)*el);
                    end
                end
            end

        end
     j=j+1;
     if pvt==false
         i=i-1;
     end
     if j==col+1
         break;

     end
end

