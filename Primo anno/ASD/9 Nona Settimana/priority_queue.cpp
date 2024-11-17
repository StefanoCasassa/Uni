/**************************************************************************/
/*          Coda con priorita' implementata come heap binario             */
/**************************************************************************/

#include "priority_queue.h"


// Funzioni ausiliarie che non appartengono al TDD 

// tra i due indici, restituisce quello che corrisponde al timestamp inferiore
int minTimeStamp(priorityQueue::PriorityQueue pq, int index1, int index2)
{
  if (index1 >= pq.size && index2 >= pq.size)
    // entrambi gli indici sono fuori dal limite dello heap
    return -1; 
  if (index1 >= pq.size)
    // il primo e' fuori, restituisco il secondo
    return index2;
  if (index2 >= pq.size)
    // il secondo e' fuori, restituisco il primo
    return index1;
      
  // entrambi sono dentro lo heap, scelgo quello con timestamp inferiore
  if (pq.data[index1].timeStamp < pq.data[index2].timeStamp)
    return index1; 
    else return index2;
}



//void moveDown(...) {// TODO}
void swap(priorityQueue::PriorityQueue& pq,int a,int b){
    priorityQueue::Elem k=pq.data[a];
    pq.data[a]=pq.data[b];
    pq.data[b]=k;
}
void moveDown(priorityQueue::PriorityQueue& pq,int i){
  if (2*i+2==pq.size) {
    if (pq.data[2*i+1].timeStamp<pq.data[i].timeStamp) swap(pq,i,2*i+1);
      return;
  }
  while (2*i+2<pq.size && (pq.data[i].timeStamp>pq.data[2*i+1].timeStamp || pq.data[i].timeStamp>pq.data[2*i+2].timeStamp)){
    if (pq.data[2*i+1].timeStamp<=pq.data[2*i+2].timeStamp) {
      swap(pq,i,2*i+1);
      i=2*i+1;
      if (2*i+2==pq.size) {
        if (pq.data[2*i+1].timeStamp<pq.data[i].timeStamp) swap(pq,i,2*i+1);
        break;
      }
      }
    else {
      swap(pq,i,2*i+2);
      i=2*i+2;
      if (2*i+2==pq.size) {
        if (pq.data[2*i+1].timeStamp<pq.data[i].timeStamp) swap(pq,i,2*i+1);
        break;
      }
      }
    }

}
//void moveUp(...) {// TODO}
void moveUp(priorityQueue::PriorityQueue& pq,int i){
  while (i>0){
    if (i%2==0 && pq.data[i/2-1].timeStamp>pq.data[i].timeStamp) swap(pq,i,i/2-1);
    else if (i%2==1 && pq.data[i/2].timeStamp>pq.data[i].timeStamp) swap(pq,i,i/2);
    else break;
    }
}

// Funzioni del TDD PriorityQueue

// crea una PriorityQueue di dimensione dim
priorityQueue::PriorityQueue priorityQueue::createEmptyPQ(int dim) {
  PriorityQueue pq;
  pq.data=new Elem[dim];
  pq.size=0;
  pq.maxsize=dim; 
  return pq;
}

// verifica se una PriorityQueue e' vuota
bool priorityQueue::isEmpty(const PriorityQueue &pq)
{
  return (pq.size==0);
} 

// inserisce un Elem in una PriorityQueue (nella posizione corretta) e ritorna TRUE
// nel caso in cui la PriorityQueue sia piena ritorna FALSE
// suggerimento: inserire in fondo e poi chiamare la funzione ausiliaria moveUp(...)
//   per ripristinare proprieta' dell'ordinamento a heap
bool priorityQueue::insert(PriorityQueue &pq, const Elem &elem) {
  if (pq.size==pq.maxsize) return false;
  pq.data[pq.size]=elem;
  pq.size++;
  moveUp(pq,pq.size-1);
  return true;
}

// ritorna FALSE se PriorityQueue e' vuota 
// altrimenti TRUE e l'Elem minimo nella PriorityQueue in res
// (cioe' quello radice in posizione 0)
bool priorityQueue::findMin(const PriorityQueue &pq, Elem &res) {

  if (pq.size==0) return false;
  res=pq.data[0];
  return true;
}

// ritorna FALSE se PriorityQueue e' vuota 
// altrimenti TRUE ed elimina l'Elem minimo nella PriorityQueue
// (cioe' quello radice in posizione 0)
// suggerimento: sostituiamo la radice dell'albero con l'ultimo elemento
//   e poi chiamare la funzione ausiliaria moveDown(...)
//   per ripristinare proprieta' dell'ordinamento a heap
bool priorityQueue::deleteMin(PriorityQueue &pq) {  
  if (pq.size==0) return false;
  pq.data[0]=pq.data[pq.size-1];
  pq.size--;
  moveDown(pq,0);
  return true;
}