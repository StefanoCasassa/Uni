// FILE DA MODIFICARE
#include <iostream>
#include <fstream>
#include "ASD-doubly-linked-list.h"

using namespace list;
using namespace std;

/*Descrizione da come e' fatta  la struttura node. */
/*I dettagli interni non saranno visibili dal main*/
struct list::node {  
  Elem info;
  node *prev;
  node *next;
};

/**************************************************/
/*      funzioni da implementare                    */
/**************************************************/
  
/* crea la lista vuota */
void list::createEmpty(List& li){
	node* aux=new node;
  li=aux;
  aux->prev=aux;
  aux->next=aux;
}

/* "smantella" la lista (tranne la sentinella) */
void list::clear(List& li){
	List cur=li->next;
  List prev=li;
  while (cur!=li){
    prev=cur;
    cur=cur->next;
    delete prev;
  }
  li->next=li;
  li->prev=li;
}

/* restituisce true se la lista e' vuota */
bool list::isEmpty(const List& li){
  return (li->next==li);
}

/* restituisce la dimensione della lista */
unsigned int list::size(const List& li){
	int k=0;
  List cur=li->next;
  while (cur!=li){
    k++;
    cur=cur->next;
  }
  return k;
}

/* restituisce l'elemento in posizione pos */
/* se pos non e corretta, solleva una eccezione di tipo string*/
Elem list::get(unsigned int pos, const List& li){
	unsigned int k=0;
  List cur=li->next;
  
  while (k!=pos && cur!=li){
    k++;
    cur=cur->next;
  }
  std::string err="!";
  if (cur==li) throw err;
  return cur->info;
}

/* modifica l'elemento in posizione pos */
/* se pos non e' corretta, solleva una eccezione di tipo string*/
void list::set(unsigned int pos, Elem el, const List& li){
	unsigned int k=0;
  List cur=li->next;
  
  while (k!=pos && cur!=li){
    k++;
    cur=cur->next;
  }
  std::string err="Posizione Errata";
  if (cur==li) throw err;
  cur->info=el;
}

/* inserisce l'elemento in posizione pos*/
/*shiftando a destra gli altri elementi */
/*se pos non e' corretta, solleva una eccezione di tipo string*/
void list::add(unsigned int pos, Elem el, const List& li){
	unsigned int k=0;
  List cur=li->next;
  if (pos!=0) {
    while (k!=pos && cur!=li){
      k++;
      cur=cur->next;
    }
  }
  std::string err;
  if (cur==li && k!=pos) throw err;
  List aux=new node;
  aux->info=el;
  aux->prev=cur->prev;
  cur->prev->next=aux;
  aux->next=cur;
  cur->prev=aux;
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem el, const List& li){
  List aux=new node;
  aux->info=el;
  aux->prev=li->prev;
  aux->next=li;
  li->prev->next=aux;
  li->prev=aux;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem el, const List& li) {
  List aux=new node;
  aux->info=el;
  li->next->prev=aux;
  aux->next=li->next;
  aux->prev=li;
  li->next=aux;
}

/* cancella l'elemento in posizione pos dalla lista */
/* se pos non e' corretta, solleva una eccezione di tipo string*/
void list::removePos(unsigned int pos,const List& li){
	unsigned int k=0;
  List cur=li->next;
  
  while (k!=pos && cur!=li){
    k++;
    cur=cur->next;
  }
  std::string err="!";
  if (cur==li) throw err;
  cur->next->prev=cur->prev;
  cur->prev->next=cur->next;
  delete cur;
}

/* cancella tutte le occorrenze dell'elemento elem*/
/*se presenti, dalla lista */
void list::removeEl(Elem el,const List& li){
	List cur=li->next;
  while (cur!=li){
    if (cur->info==el){
      List aux=cur;
      cur=cur->next;
      cur->prev=aux->prev;
      cur=aux->prev;
      cur->next=aux->next;

    }
    cur=cur->next;
  }
}

/**************************************************/
/*      funzioni implementate                    */
/**************************************************/
  
/* riempie una lista da file */
void list::readFromFile(string name_file, const List& li){
  ifstream infile;
  string read_data;
  infile.open(name_file);
  while (getline (infile,read_data)){
    if(read_data.length()>0){
      addRear(stoi(read_data),li);
    }
  }
}

/* riempie una lista da standard input */
void list::readFromStdin(const List& li){
  cout << "Inserire una sequenza di numeri separati da spazi seguiti da END per terminare\n";
  string read_data;
  cin>>read_data;
  while(read_data!="END"){
    addRear(stoi(read_data),li);
    cin>>read_data;
  }
}

/* stampa la lista */
void list::print(const List& li){
  if(li==li->next){
    cout<<"vuota";
  }
  List cur = li->next;  // q "salta la sentinella" e va alla testa della lista
  while (cur != li) {   
    cout << cur->info;
    cur= cur->next;
    if(cur!=li) cout<<" <-> ";
  }
  cout<<endl;
}

/* produce una string contenendo la lista*/
std::string list::tostring(const List& li){
  string out="";
  if(li==li->next){
    out+="vuota";
  }
  List cur = li->next;  // q "salta la sentinella" e va alla testa della lista
  while (cur != li) {   
    out+=to_string(cur->info);
    cur= cur->next;
    if(cur!=li) out+=" <-> ";
  }
  return out;
}
