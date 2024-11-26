%% main script

% creazione matrici
format rational
% 1. matrice esercitazione 1
A = [3 1 -1 0; 
      0 7 -3 0;
      0 -3 9 -2;
      0 0 4 -10;];

% 2. matrice tridiagonale
B=zeros(33,33);
% n = ...;
% a = 2;
% b = -1;
for i=1:33
for j=1:33
    if i==j
        B(i,j)=2;
    elseif abs(i-j)==1
        B(i,j)=-1;
    end
end
end
% A = a*diag(ones(n,1)) + b*diag(ones(n-1,1),1) +b*diag(ones(n-1,1),-1);

C=zeros(6,6);
for i=1:6
for j=1:6
   C(i,j)=(i/6).^(j-1);
end
end
% 3. matrice 6x6

% m = 6;
% 
% A = [1:m;
%      1:m;
%      ...];
%      
% A = A/m;


% gli indici in Matlab partono da 1...
% for i = 1:m
%     % eleva all'i-esima potenza la i-esima colonna di A
%     % le operazioni elemento per elemento si effettuano aggiungendo un punto
%     % prima dell'operatore
%     A(:, i)=A(:,i).^(i-1);
% end
% 
% T = gauss_method(A);
% 
% % stampa la matrice
% 
% disp(T);

disp(A);
disp(B);
disp(C);
T=gauss_method(A);
G=gauss_method(B);
S=gauss_method(C);
disp(T);
disp(G);
disp(S);

[L1, U1, P1] = lu(A);
[L2, U2, P2] = lu(B);
[L3, U3, P3] = lu(C);
disp(U1);
disp(U2);
disp(U3);