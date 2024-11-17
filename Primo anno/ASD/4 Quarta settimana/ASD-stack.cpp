// FILE DA MODIFICARE
#include "ASD-stack.h"

using namespace stack;
using namespace std;

/**************************************************/
/*      funzioni da implementare                  */
/**************************************************/
/* restituisce lo stack vuoto */
Stack stack::createEmpty(){
   Stack st;
   st.data=nullptr;
   st.size=0;
   st.maxsize=0;
   return st;
}

/* restituisce true se lo stack e' vuoto */
bool stack::isEmpty(const Stack& st){
    return (st.size==0);
}

Stack Resize(Stack& st){
   Stack st2;
   if (st.maxsize==st.size) {
      st2.data=new Elem[st.maxsize+BLOCKDIM];
      st2.maxsize=st.maxsize+BLOCKDIM;
   }
   else {
      st2.data=new Elem[st.maxsize-BLOCKDIM];
      st2.maxsize=st.maxsize-BLOCKDIM;
   }
   st2.size=st.size;
      for (unsigned i=0;i<st.size;++i){
         st2.data[i]=st.data[i];
      }
      delete [] st.data;
      return st2;
}

/* aggiunge elem in cima (operazione safe, si può sempre fare) */
/* NB: se stack implementato con array dinamico, 
   quando necessario implementare ridimensionamento in espansione*/
void stack::push(const Elem el, Stack& st){
   if (st.maxsize==st.size) st=Resize(st);
   st.size++;
   st.data[st.size-1]=el;
}

/* toglie dallo stack l'ultimo elemento e lo restituisce */
/* se lo stack è vuoto solleva una eccezione di tipo string */
/* NB: se stack implementato con array dinamico, 
   quando necessario implementare ridimensionamento in contrazione*/
Elem stack::pop(Stack& st){
   string err="Errore";
   if (isEmpty(st)) throw err;
   Elem ret=st.data[st.size-1];
   --st.size;
   if (st.maxsize-st.size>10) st=Resize(st);
	return ret;
} 
