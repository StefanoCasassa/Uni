#include "tree-chsib.h"

using namespace tree;

/* Nota: nei commenti usiamo "albero" e "puntatore a un nodo" come sinonimi, scegliendo di volta in volta
la formulazione più adatta a dare la specifica di una funzione. 
Dal punto di vista tecnico, usiamo sempre il tipo Tree sia quando operiamo su un albero, sia quando operiamo, 
a livello concettuale, su un puntatore a un nodo dell'albero. 
Questo approccio e' corretto in quanto un albero (o sottoalbero) è un puntatore a una struct di tipo treeNode:
un albero è identificato univocamente dal puntatore alla sua radice */ 



/*******************************************************************************************************/
// il nodo di un albero è caratterizzato dall'etichetta, il puntatore al primo figlio e il puntatore al prossimo fratello
// NON manteniamo il puntatore al padre, anche se sarebbe comodo per alcune funzioni (ma del tutto inutile per altre)
struct tree::treeNode {
    Label label;    
    treeNode *firstChild;
    treeNode *nextSibling;
};


/*******************************************************************************************************/
// isEmpty restituisce true se l'albero t e' vuoto, false altrimenti
bool tree::isEmpty(const Tree& t)
{  
   return (t==emptyTree);
}



/*******************************************************************************************************/
// addElem aggiunge il nodo etichettato con labelOfNodeToAdd come
// figlio del nodo etichettato con labelOfNodeInTree.
// Caso particolare: aggiunta della radice, che si ottiene
// con labelOfNodeInTree uguale a emptyLabel (= nessun padre), e ha successo
// solo se l'albero e' vuoto (in caso contrario restituisce FAIL 
// e non aggiunge nulla).
// Restituisce FAIL se non esiste un nodo nell'albero etichettato 
// con labelOfNodeInTree oppure se nell'albero esiste gia' un nodo 
// etichettato con labelOfNodeToAdd; aggiunge e restituisce OK altrimenti
Error addElemAux(Tree t,const Label labelOfNodeToAdd){
   if (t->firstChild==emptyTree) {
      Tree aux=new treeNode;
         aux->firstChild=emptyTree;
         aux->nextSibling=emptyTree;
         aux->label=labelOfNodeToAdd;
         t->firstChild=aux;
         return OK;
   }
   Tree k=t;
   k=k->firstChild;
   for (;;){
      if (k->label==labelOfNodeToAdd) return FAIL;
      if (k->nextSibling==emptyTree) {
         Tree aux=new treeNode;
         aux->firstChild=emptyTree;
         aux->nextSibling=emptyTree;
         aux->label=labelOfNodeToAdd;
         k->nextSibling=aux;
         return OK;
      }
      k=k->nextSibling;
   }
}
Error tree::addElem(const Label labelOfNodeInTree, const Label labelOfNodeToAdd, Tree& t)
{  
   if (t==emptyTree) {
      if (labelOfNodeInTree==emptyLabel) {
         Tree aux=new treeNode;
         aux->firstChild=emptyTree;
         aux->nextSibling=emptyTree;
         aux->label=labelOfNodeToAdd;
         t=aux;
         return OK;
      }
      else return FAIL;
   } 
   vector<Tree> v;
   v.push_back(t);
   Tree k=t;
   while (!v.empty()){
      if (v[v.size()-1]->label==labelOfNodeInTree) return addElemAux(v[v.size()-1],labelOfNodeToAdd);
      if (v[v.size()-1]->label==labelOfNodeToAdd) return FAIL;
      k=v[v.size()-1]->firstChild;
      v.pop_back();
      while (k!=emptyTree){
         v.push_back(k);
         k=k->nextSibling;
      }
   }
}     



/*******************************************************************************************************/
// deleteElem (versione iterativa) rimuove dall'albero il nodo etichettato con la Label l
// e collega al padre di tale nodo tutti i suoi figli
// Restituisce FAIL se si tenta di cancellare la radice e questa ha 
// dei figli (non si saprebbe a che padre attaccarli) oppure se non esiste 
// un nodo nell'albero etichettato con la Label; cancella e restituisce OK altrimenti
Error tree::deleteElemI(const Label l, Tree& t)
{
   if (l==t->label) {
      if (t->firstChild!=emptyTree) return FAIL;
      else 
      delete t; 
      t==emptyTree;
      return OK;
   }
   vector<Tree> v;
   v.push_back(t);
   Tree k=t;
   while (!v.empty()){
      if (v[v.size()-1]->firstChild!=nullptr && v[v.size()-1]->firstChild->label==l) {
         Tree aux=v[v.size()-1]->firstChild;
         while (aux->nextSibling!=nullptr) {
            aux=aux->nextSibling;
            }
            aux->nextSibling=v[v.size()-1]->firstChild->firstChild;
            aux=v[v.size()-1]->firstChild; 
            v[v.size()-1]->firstChild=aux->nextSibling;
            delete aux;
            return OK;
            
      }
      if (v[v.size()-1]->nextSibling!=nullptr && v[v.size()-1]->nextSibling->label==l) {
         Tree aux=v[v.size()-1]->nextSibling;
         while (aux->nextSibling!=nullptr) {
            aux=aux->nextSibling;
            }
            aux->nextSibling=v[v.size()-1]->nextSibling->firstChild;
            aux=v[v.size()-1]->nextSibling;
            v[v.size()-1]->nextSibling=aux->nextSibling;
            delete aux;
            return OK;
      }
      
      k=v[v.size()-1]->firstChild;
      v.pop_back();
      while (k!=emptyTree){
         
         v.push_back(k);
         k=k->nextSibling;
      }

   }

     return FAIL;     
}



/*******************************************************************************************************/
// deleteElem (versione ricorsiva): stesso comportamento della versione iterativa, ma implementata ricorsivamente
// (può anche non essere ricorsiva la deleteElemR, ma deve fare uso di funzioni ausiliarie ricorsive)
void deleteElemRAux(const Label l, Tree t,bool &k) {
   if (isEmpty(t)) return;
   if (t->firstChild!=nullptr && t->firstChild->label==l) {
         Tree aux=t->firstChild;
         while (aux->nextSibling!=nullptr) {
            aux=aux->nextSibling;
            }
            aux->nextSibling=t->firstChild->firstChild;
            aux=t->firstChild; 
            t->firstChild=aux->nextSibling;
            delete aux;
            k=true;
            return;
            
      }
      if (t->nextSibling!=nullptr && t->nextSibling->label==l) {

         Tree aux=t->nextSibling;
         while (aux->nextSibling!=nullptr) {
            aux=aux->nextSibling;
            }
            aux->nextSibling=t->nextSibling->firstChild;
            aux=t->nextSibling;
            t->nextSibling=aux->nextSibling;
            delete aux;
            k=true;
            return;
      }
      t=t->firstChild;
      while (!isEmpty(t)) {
         deleteElemRAux(l,t,k);
         t=t->nextSibling;
      }
   
}
/*Error deleteElemRAux(const Label l, Tree t) {
   if (t->firstChild!=nullptr && t->firstChild->label==l) {
         Tree aux=t->firstChild;
         while (aux->nextSibling!=nullptr) {
            aux=aux->nextSibling;
            }
            aux->nextSibling=t->firstChild->firstChild;
            aux=t->firstChild; 
            t->firstChild=aux->nextSibling;
            delete aux;
            return OK;
            
      }
      if (t->nextSibling!=nullptr && t->nextSibling->label==l) {

         Tree aux=t->nextSibling;
         while (aux->nextSibling!=nullptr) {
            aux=aux->nextSibling;
            }
            aux->nextSibling=t->nextSibling->firstChild;
            aux=t->nextSibling;
            t->nextSibling=aux->nextSibling;
            delete aux;
            return OK;
      }
      
   if (t->firstChild!=nullptr) return deleteElemRAux(l,t->firstChild);
   while (t->nextSibling!=nullptr) {
      return deleteElemRAux(l,t->nextSibling);
   }
   return FAIL;
}*/
Error tree::deleteElemR(const Label l, Tree& t)
{
     if (l==t->label) {
      if (t->firstChild!=emptyTree) return FAIL;
      else 
      delete t; 
      t==emptyTree;
      return OK;
   }
   Tree z=t;
   bool k=false;
    deleteElemRAux(l,z,k);
   if (k) return OK;
   return FAIL; 
}



/*******************************************************************************************************/
// father restituisce l'etichetta del padre del nodo con etichetta l se il nodo esiste nell'albero 
// (o sottoalbero) t e se il padre esiste. 
// Restituisce la costante emptyLabel altrimenti
Label tree::father(const Label l, const Tree& t)
{ 
   if (isEmpty(t)) return emptyLabel;
   vector<Tree> v;
   v.push_back(t);
   Tree k=t;
   Tree b;
   while (!v.empty()){
      b=v[v.size()-1];
      k=v[v.size()-1]->firstChild;
      v.pop_back();
      while (k!=emptyTree){
         if (k->label==l) return b->label;
         v.push_back(k);
         k=k->nextSibling;
      }
   }
   v.clear();
   return emptyLabel;
}



/*******************************************************************************************************/
// children restituisce una lista di Label, contenente le etichette 
// di tutti i figli nell'albero t del nodo etichettato con l
// La lista può essere implementata usando una qualunque delle strutture dati viste a lezione
// (non un Vector!!!): si riusi una implementazione del TDD list, adattandola 
// a elementi di tipo string (nelle precedenti esercitazioni gli elementi erano int)
list::List tree::children(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
    if (isEmpty(t)) return lst;
   vector<Tree> v;
   v.push_back(t);
   Tree k=t;
   while (!v.empty()){
      k=v[v.size()-1]->firstChild;
      if (v[v.size()-1]->label==l) break;
      v.pop_back();
      while (k!=emptyTree){
   
         v.push_back(k);
         k=k->nextSibling;
      }
   } 
   while (k!=nullptr) {
   list::addFront(k->label,lst);
   k=k->nextSibling;
   }
   v.clear();
   return lst;
}




/*******************************************************************************************************/
// degree restituisce il numero di archi uscenti dal nodo etichettato con l; restituisce -1 se non esiste 
// nessuna etichetta l nell'albero
int tree::degree(const Label l, const Tree& t)
{
   bool e=false;
   if (isEmpty(t)) return -1;
   vector<Tree> v;
   v.push_back(t);
   Tree k=t;
   while (!v.empty()){
      k=v[v.size()-1]->firstChild;
      if (v[v.size()-1]->label==l) {
         e=true;
         break;
      }
      v.pop_back();
      while (k!=emptyTree){
         v.push_back(k);
         k=k->nextSibling;
      }
   } 
   v.clear();
   if (!e) return -1;
   int i=0;
   while (k!=nullptr){
   i++;
   k=k->nextSibling;
   }
   return i;
  
}



/*******************************************************************************************************/
// ancestors (versione ricorsiva) restituisce una lista di Label, contenente le etichette 
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
// (può anche non essere ricorsiva la ancestorsR, ma deve fare uso di funzioni ausiliarie ricorsive)
list::List ancestorsRAux(const Tree& t,list::List &lst){
      if (list::get(0,lst)==t->label) return lst;
      list::addFront(tree::father(list::get(0,lst),t),lst);
      return ancestorsRAux(t,lst);
   }
list::List tree::ancestorsR(const Label l, const Tree& t)
{
   list::List lst = list::createEmpty();
   if (t==emptyTree || !member(l,t) || t->label==l) return lst;
   list::addFront(tree::father(l,t),lst);
   ancestorsRAux(t,lst);
   return lst;
}



/*******************************************************************************************************/
// ancestors (versione iterativa) restituisce una lista di Label, contenente le etichette 
// di tutti gli antenati del nodo l ESCLUSA l'etichetta del nodo stesso
// La lista può essere implementata usando una delle strutture dati viste a lezione
// (non un Vector)
list::List tree::ancestorsI(const Label l, const Tree& t)
{ 
   list::List lst = list::createEmpty();
   if (t==emptyTree || !member(l,t) || t->label==l) return lst;
   list::addFront(tree::father(l,t),lst);
   while (list::get(0,lst)!=t->label) {
      list::addFront(tree::father(list::get(0,lst),t),lst);
   }
   return lst;
}



/*******************************************************************************************************/
// leastCommonAncestor restituisce l'etichetta del minimo antenato comune 
// ai nodi etichettati con label1 e label2
Label tree::leastCommonAncestor(const Label label1, const Label label2, const Tree& t)
{  
   if (!member(label1,t) || !member(label2,t)) return emptyLabel;
   if (t==emptyTree) return emptyLabel;
   list::List lst1 =ancestorsI(label1,t);
   list::List lst2 =ancestorsI(label2,t);
   int i=0;
   if (lst1.list==nullptr || lst2.list==nullptr ) return emptyLabel;
   while (list::get(i,lst1)==list::get(i,lst2) && get(i,lst1)!=list::emptyElem ){
      i++;
   }
   return list::get(i-1,lst1);
}



/*******************************************************************************************************/
// member restituisce true se il nodo etichettato con la label l appartiene all'albero t e false altrimenti
bool tree::member(const Label l, const Tree& t)
{  
   if (isEmpty(t)) return false;
   vector<Tree> v;
   v.push_back(t);
   Tree k=t;
   while (!v.empty()){
      k=v[v.size()-1]->firstChild;
      if (v[v.size()-1]->label==l) {
         v.clear();
         return true;
      }
      v.pop_back();
      while (k!=emptyTree){
         v.push_back(k);
         k=k->nextSibling;
      }
   }
   v.clear();
   return false;  
}



/*******************************************************************************************************/
// numNodes restituisce il numero di nodi nell'albero t mediante una visita ricorsiva in depthfirst

int tree::numNodes(const Tree& t)
{   if(t == emptyTree) return 0;
   Tree tmp = t->firstChild;
   int c = 1;
   while(!isEmpty(tmp)){
      c += numNodes(tmp);
      tmp=tmp->nextSibling;
   }
   return c;
}


/*******************************************************************************************************/
// createEmptyTree restituisce l'albero vuoto
Tree tree::createEmpty()
{
   return emptyTree;
}



/*******************************************************************************************************/
// Visualizzazione possibilmente strutturata come visto a lezione

/*void printTree(const Tree& t) {
   if (isEmpty(t)) return;
   vector<Tree> v;
   v.push_back(t);
   Tree k=t;
   while (!v.empty()){
      k=v[v.size()-1]->firstChild;
      cout<<v[v.size()-1]->label<<endl;
      v.pop_back();
      while (k!=emptyTree){
         v.push_back(k);
         k=k->nextSibling;
      }
   }
   v.clear();
   return;
   
}*/
void printTreeAux(const Tree& t, unsigned int level){
   if(isEmpty(t)) return;
   for(unsigned int i=0;i<level;i++)
         cout << "--";
   cout << t->label << endl;

   Tree aux = t->firstChild;
   while(!isEmpty(aux)){
      printTreeAux(aux,level+1);
      aux=aux->nextSibling;
   }
}


// Visualizzazione possibilmente strutturata come visto a lezione
void printTree(const Tree& t) {
   printTreeAux(t,0);
}



/****************************************************************/
// Questa funzione NON richiede di conoscere come e' fatta la struttura dati che implementa l'albero: usa solo addElem e quindi e' ad 
// un alto livello di astrazione
// Vantaggi: codice compatto, leggibile, riutilizzabile per qualunque implementazione del TDD Tree
// Svantaggi: inefficiente: la addElem cerca ogni volta il nodo con etichetta fatherLabel, mentre basterebbe una chiamata sola per 
// trovarlo e poi si potrebbero attaccare tutti i figli a esso, senza ripetere la dispendiosa ricerca nell'albero; per renderla 
// efficiente dovrei pero' accedere direttamente alla struttura dati chiamando qualche funzione ausiliaria che operi 
// sui nodi dell'albero, rinunciando a scrivere codice modulare, chiaro e ad un ragionevole livello di astrazione... 
// Non esiste un'opzione migliore tra le due: se il codice deve essere efficiente, è opportuno scrivere una funzione ad hoc per 
// una determinata implementazione; se il codice deve essere riutilizzabile, bisogna limitarsi a usare le funzioni offerte dall'
// interfaccia del TDD in modo che la funzione continui ad andare bene anche se cambia l'implementazione
Tree readFromStream(istream& str)
{
    Tree t = createEmpty(); 
    string line;
    Label rootLabel, fatherLabel, childLabel;
    getline(str, line);  
    istringstream instream;            // uso una variabile di tipo istringstream per poter scandire i pezzi di ogni riga usando >>
    instream.clear();
    instream.str(line);
    instream >> rootLabel;             // il primo elemento che si incontra nel file e' l'etichetta della radice, per convenzione su come deve essere fatto il file
    addElem(emptyLabel, rootLabel, t); // la si inserisce nell'albero vuoto, indicando che il padre non c'e' (primo argomento emptyLabel)
    getline(str, line);                // poi si iniziano a scansionare le righe seguenti
    instream.clear();
    instream.str(line);
    while (!str.eof())  
        {        
	instream >> fatherLabel; // in ogni riga del file, il primo elemento e' l'etichetta del nodo padre e gli altri sono le etichette dei figli
        removeBlanksAndLower(fatherLabel); // normalizzo l'etichetta del padre
        while (!instream.eof())            // finche' la riga corrente non e' terminata
            { 
            instream >> childLabel;              // leggo la prossima etichetta
            removeBlanksAndLower(childLabel);    // la normalizzo
            addElem(fatherLabel, childLabel, t); // e la attacco al padre
            }
        getline(str, line);  
        instream.clear();
        instream.str(line);
        }
    str.clear();
    return t;
}



/****************************************************************/
Tree readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmpty();}  
    return readFromStream(ifs);
}

