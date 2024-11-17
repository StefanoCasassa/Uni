//FILE DA MODIFICARE
#include <iostream>
#include "ASD-token.h"

using namespace std;

/**************************************************/
/*      funzioni da implementare                  */
/**************************************************/

//funzione che estrae il prossimo token della string st
//lo mette in tok e modifica st,
//ritorna true se c'era un token da estrarre,
//ritorna false se non c'era niente da estrarre e si e arrivato alla fine di st,
//solleva una eccezione di tipo string se legge un token di tipo sconosciuto
bool nextToken(string &st, token &tok) {

string err="Lexical error";
long unsigned int i=0;
bool nospace=true;
if (st.size()==i) return false;
while (st[i]==' '){
  nospace=false;
  ++i;
}

if (st[i]=='(') 
{
  tok.k=PARENTESI_APERTA; 
  st.erase(0,i+1);
  return true;
}
if (st[i]==')') 
{
  if (nospace) throw err;
  tok.k=PARENTESI_CHIUSA; 
  st.erase(0,i+1);
  return true;
}
if (st[i]=='+') 
{
  if (nospace) throw err;
  tok.k=OP_SOMMA; 
  st.erase(0,i+1);
  return true;
}
if (st[i]=='-') 
{
  if (nospace) throw err;
  tok.k=OP_SOTTRAZIONE; 
  st.erase(0,i+1);
  return true;
}
if (st[i]=='*') 
{
  if (nospace) throw err;
  tok.k=OP_MOLTIPLICAZIONE; 
  st.erase(0,i+1);
  return true;
}
if (st[i]>='0' && st[i]<='9')
{
  long unsigned int k=i;
  while ( k<st.size() && st[k]>='0' && st[k]<='9'){
    k++;
  }
  std::string aux=st.substr(i,k-i);
  tok.val=stoi(aux);
  tok.k=NUMERO;
  st.erase(0,k);
  return true;
}
throw err;
}

