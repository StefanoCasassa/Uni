#include "tragitto.h"

// verifica se un Tragitto e vuoto
bool tragitto::isEmpty(Tragitto tr) {
  return (tr == tragittoVuoto);
}

// inserisce una Tappa in un Tragitto
void tragitto::insert(Tragitto &tr, Tappa t) {
  
    Tragitto k=tr;
    TragittoElem* aux=new TragittoElem;
    aux->tappa=t;
    if (k==nullptr) {
      tr=aux;
      aux->next=nullptr;
      return;
    }
    while (k->next!=nullptr){
      k=k->next;
    }
    aux->next=k->next;
    k->next=aux;
    return;
}

// ritorna FALSE se il Tragitto e vuoto
// altrimenti rimuove la prima Tappa del Tragitto 
//    e la assegna al secondo parametro e ritorna TRUE
bool tragitto::extract(Tragitto &tr, Tappa &t) {
  if (tr==nullptr) return false;
  t=tr->tappa;
  Tragitto k=tr;
  tr=tr->next;
  delete k;
  return true;
}

// stampa un Tragitto (formato: N volte [distanza citta'])
void printTragitto(tragitto::Tragitto tr) {

  while (tr!=nullptr) {
    cout<<" "<<tr->tappa.distanza<<" "<<tr->tappa.citta<<" ";
    tr=tr->next;
  }
}
