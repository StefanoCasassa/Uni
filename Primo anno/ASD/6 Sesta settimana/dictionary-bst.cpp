#include "dictionary.h"

using namespace dict;

//STRUCT TO BE COMPLETED
// *** NON AGGIUNGETE IL PUNTATORE AL PADRE ALLA STRUCT!!!! *** 
struct dict::bstNode {
  bstNode* leftChild;
  bstNode* rightChild;
  Elem node;
};

//Funzione da implementare
bool dict::isEmpty(const Dictionary& d){
  return (d==emptyDictionary);
}
   
//Funzione da implementare
Dictionary dict::createEmptyDict(){
  Dictionary d=emptyDictionary;
  return d;
}

Error insertElemAux(const Key k, const Value v, Dictionary& d) {
  if (k<d->node.key) {
    if (d->leftChild!=emptyNode) return insertElemAux(k,v,d->leftChild);
    bstNode* aux=new bstNode;
    aux->leftChild=emptyNode;
    aux->rightChild=emptyNode;
    Elem aux1;
    aux1.key=k;
    aux1.value=v;
    aux->node=aux1;
    d->leftChild=aux;
    return OK;
  }
  if (k>d->node.key) {
    if (d->rightChild!=emptyNode) return insertElemAux(k,v,d->rightChild);
    bstNode* aux=new bstNode;
    aux->leftChild=emptyNode;
    aux->rightChild=emptyNode;
    Elem aux1;
    aux1.key=k;
    aux1.value=v;
    aux->node=aux1;
    d->rightChild=aux;
    return OK;
  }
  
  return FAIL;
}
//Funzione da implementare
Error dict::insertElem(const Key k, const Value v, Dictionary& d){
  if (isEmpty(d)) {
    bstNode* aux=new bstNode;
    aux->leftChild=emptyNode;
    aux->rightChild=emptyNode;
    Elem aux1;
    aux1.key=k;
    aux1.value=v;
    aux->node=aux1;
    d=aux;
    return OK;
  }
  else return insertElemAux(k,v,d);
}

//Funzione da implementare
Value dict::search(const Key k, const Dictionary& d){
  if (d==emptyNode) return emptyValue;
  if (k==d->node.key) return d->node.value;
  if (k<d->node.key) return search(k,d->leftChild);
  if (k>d->node.key) return search(k,d->rightChild);
  return d->node.value;
}

//Funzione da implementare
Elem DeleteMin(Dictionary& d){
  if (d->leftChild==emptyNode && d->rightChild==emptyNode) {
      Elem b=d->node;
      delete d;
      d=emptyNode;
      return b;
  }
  if (d->leftChild==emptyNode && d->rightChild!=emptyNode) {
      Elem b=d->node;
      Dictionary aux=d;
      d=d->rightChild;
      delete aux;
      return b;
  }
  return DeleteMin(d->leftChild);
      
}

Error deleteElemAux(const Key k, Dictionary& d){
  if (isEmpty(d)) return FAIL;
  if (k<d->node.key) return deleteElemAux(k,d->leftChild);
  if (k>d->node.key) return deleteElemAux(k,d->rightChild);
  if (k==d->node.key) {
    if (d->leftChild==emptyNode && d->rightChild==emptyNode) {
      delete d;
      d=emptyNode;
      return OK;
    }
    if (d->leftChild==emptyNode && d->rightChild!=emptyNode){
      Dictionary aux=d;
      d=d->rightChild;
      delete aux;
      return OK;
    }
    if (d->leftChild!=emptyNode && d->rightChild==emptyNode){
      Dictionary aux=d;
      d=d->leftChild;
      delete aux;
      return OK;
    }
    if (d->leftChild!=emptyNode && d->rightChild!=emptyNode){
      Elem l=DeleteMin(d->rightChild);
      d->node=l;
      return OK;
    }
  }
}
Error dict::deleteElem(const Key k, Dictionary& d){
  //if (d->leftChild!=emptyNode && d->rightChild!=emptyNode) return FAIL;
  return deleteElemAux(k,d);
  
}

//Funzione da implementare
void print(const Dictionary& d) {
  if (isEmpty(d)) return;
  if (d->leftChild!=nullptr) print(d->leftChild);
  cout<<d->node.key<<": "<<d->node.value<<endl;
  if (d->rightChild!=nullptr) print(d->rightChild);
  return;
}

/****************************************************************/
/*              FUNZIONE IMPLEMENTATE                           */
/****************************************************************/
Dictionary readFromFile(string nome_file){
  ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
  if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return emptyDictionary;}  
  return readFromStream(ifs);
}

Dictionary readFromStdin(){
  cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
  Dictionary d = readFromStream((std::cin));
  // Questa serve per aggirare un bug di alcune versioni attuali di glibc.
  clearerr(stdin);
  return d;
}

Dictionary readFromStream(istream& str){
  Dictionary d = emptyDictionary; 
  string key, kcopy;
  string value;
  getline (str, key, ':'); 
  getline (str, value); 
  while (!str.eof())  
    {        
      kcopy = key;
      removeBlanksAndLower(kcopy); 
      insertElem(kcopy, value, d);
      getline (str, key, ':'); 
      getline (str, value); 
    }
  str.clear();
  return d;
}
