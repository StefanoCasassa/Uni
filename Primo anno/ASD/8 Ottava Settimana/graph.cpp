#include <iostream>

#include "graph.h"

using namespace graph;

struct adjList {
  Weight weight;
  adjList* next;
  vertexNode* node;
};
struct graph::vertexNode {
  Label label;
  adjList* adjlist;
  vertexNode* next;
  bool visited=false;
};

/**********************************************************************/
/*               Funzione da implementare                             */
/**********************************************************************/
// Restituisce il grafo vuoto
Graph graph::createEmptyGraph(){
  Graph g=emptyGraph;
  return g;
}

// Aggiunge nuovo vertice con etichetta la stringa.
// Se non è gia presente, ritorna true, altrimenti fallisce e ritorna false 
bool graph::addVertex(Label l, Graph& g){
  Graph k=new vertexNode;
  k->label=l;
  k->adjlist=nullptr;
  k->next=emptyGraph;
  if (g==emptyGraph) 
  {
    g=k;
    return true;
  }
  Graph z=g;
  while (z->next!=emptyGraph) {
    if (z->label==l) return false;
    z=z->next;
  }
  if (z->label==l) return false;
  z->next=k;
  return true;
}

// Aggiunge nuovo arco tra i due vertici con etichette le due stringe e peso
// l'intero. Fallisce se non sono presenti tutti e due i nodi o se l'arco
// tra i due e' gia' presente. Se fallisce ritorna false,
// altrimenti ritorna true
bool graph::addEdge(Label from, Label to, Weight w, Graph& g){
  Graph k=g;
  int count=0;
  Graph aux1;
  Graph aux2;
  while (k!=nullptr) {
    if (k->label==from) {
      ++count;
      aux1=k;
    }
    if (k->label==to) {
      ++count;
      aux2=k;
    }
    k=k->next;
  }
  if (count!=2) return false;
  adjList* copy1=aux1->adjlist;
  while (copy1!=nullptr){
    if (copy1->node->label==to) return false;
    copy1=copy1->next;
  }
  copy1=new adjList;
  copy1->weight=w;
  copy1->node=aux2;
  copy1->next=aux1->adjlist;
  aux1->adjlist=copy1;

  adjList* copy2=new adjList;
  copy2->weight=w;
  copy2->node=aux1;
  copy2->next=aux2->adjlist;
  aux2->adjlist=copy2;
  return true;
}

// Restituisce true se il grafo e' vuoto, false altrimenti
bool graph::isEmpty(const Graph& g){
  return g == emptyGraph;
}

// Ritorna il numero di vertici del grafo
unsigned int graph::numVertices(const Graph& g){
  unsigned i=0;
  Graph k=g;
  while (k!=nullptr) {
    i++;
    k=k->next;
  }
  return i;
}

// Ritorna il numero di archi del grafo
unsigned int graph::numEdges(const Graph& g){
  unsigned i=0;
  Graph k=g;
  adjList* s;
  while (k!=nullptr) {
    s=k->adjlist;
    while (s!=nullptr){
      s=s->next;
      i++;
    }
    k=k->next;
  }
  return i/2;
}

// Calcola e ritorna (nel secondo parametro) il grado del vertice.
// Restituisce un valore falso se il vertice non esiste,
// altrimenti ritorna true
bool graph::nodeDegree(Label l, unsigned int& degree, const Graph& g) {
  Graph k=g;
  degree=0;
  while (k!=nullptr && k->label!=l){
    k=k->next;
  }
  if (k==nullptr) return false;
  adjList* v=k->adjlist;
  while (v!=nullptr) {
    degree++;
    v=v->next;
  }
  return true;
}

// Verifica se due vertici sono adiacenti (ovvero se esiste un arco)
bool graph::areAdjacent(Label v1, Label v2, const Graph& g) {
  Graph k=g;
  Graph c;
  while (k!=nullptr) {
    if (k->label==v1) {
      c=k;
      break;
    }
    if (k->label==v2) {
      c=k;
      break;
    }
    k=k->next;
  }
  if (k==nullptr) return false;
  if (c->label==v1) {
    adjList* x=c->adjlist;
    while (x!=nullptr){
    if (x->node->label==v2) return true;
    x=x->next;
    }
    if (x==nullptr) return false;
  }

  if (c->label==v2) {
    adjList* x=c->adjlist;
    while (x!=nullptr){
    if (x->node->label==v1) return true;
    x=x->next;
    }
    if (x==nullptr) return false;
  }
  return false;

}

// Ritorna la lista di adiacenza di un vertice
// corrispondente alla lista dei label dei vertici adiacenti
list::List graph::adjacentList(Label v1, const Graph& g) {
  Graph k=g;
  list::List m=list::createEmpty();
  while (k!=nullptr && k->label!=v1) {
    k=k->next;
  }
  if (k==nullptr) return m;
  adjList* s=k->adjlist;
  while (s!=nullptr){
    list::addFront(s->node->label,m);
    s=s->next;
  }
  return m;
}

// Calcola, se esiste, un cammino tra due vertici
// Il primo argomento e il vertice di partenza
// Il secondo argomento e il vertice di arrivo
// Il terzo argomento conterrà la lista delle etichette degli
// vertici visitati sul cammino (senza il vertice di partenza, ne il vertice
// di arrivo)
// Si assume che il chiamante fornisca inizialmente una lista vuota.
// Il quarto argomento è il peso del cammino
// La funziona ritorna false, se il vertice di partenza e uguale al vertice
// di arrivo, o se non c'e un cammino tra i due vertici, altrimenti
// ritorna true
bool findPathR(Label v1, Label v2, list::List& path, Weight& weight, const Graph& g,Weight Last_weight,bool& o) {
  if (list::size(path)==0) return false;
  adjList *s=g->adjlist;
  while (s!=nullptr){
    if (s->node->label==v2) {
    weight=weight+s->weight;
    list::addBack(v2,path);
    o=true;
    return true;
    }
    if (s->node->visited==false) {
      s->node->visited=true;
      weight=weight+s->weight;
      list::addBack(s->node->label,path);
      findPathR(v1,v2,path,weight,s->node,s->weight,o);
      if (o) return true;
    }
    s=s->next;
  }
  weight=weight-Last_weight;
  list::removePos(list::size(path)-1,path);
  return false;
}
bool graph::findPath(Label v1, Label v2, list::List& path, Weight& weight, const Graph& g) {
  Graph k=g;
  while (k!=nullptr && k->label!=v1) {
    k=k->next;
  }
  weight=0;
  if (v1==v2) {
    list::addFront(v1,path);
    return true;
  }
  if (k==nullptr) return false;
  list::addFront(v1,path);
  k->visited=true;
  bool o=false;
  bool z=findPathR(v1,v2,path,weight,k,0,o);
  k=g;
  while (k!=nullptr) {
    k->visited=false;
    k=k->next;
  }
  return z;
}


// Svuota un grafo
void graph::clear(graph::Graph& g){
  Graph k=g;
  while (g!=nullptr){
    k=g;
    g=k->next;
    delete k;
  }

}

// Stampa il grafo
// Per ogni vertice stampa su una riga l'etichetta del vertice seguito di ':'
// poi le etichette dei vertici adiacenti con fra parentesi il peso associato,
// separate da virgole
void graph::printGraph(const graph::Graph& g) {
  //TODO
}
