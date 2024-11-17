#include <cstdlib>
#include <ctime>
#include <iostream>

#include "ASD-sort.h"

using namespace std;

/**************************************************/
/*       funzioni ausiliare                      */
/**************************************************/

/*scambia le posizione i e j in v assumendo che siano posizione correte*/
void swap_ind(vector<int>& v, int i, int j)
{ 
  int tmp = v.at(j);
  v.at(j) = v.at(i);
  v.at(i) = tmp;
}

/**************************************************/
/*       funzioni da implementare                 */
/**************************************************/
   unsigned partizione(vector<int> &v,unsigned l, unsigned r){
      int p=v[l];
      unsigned i=l+1;
      for (unsigned j=l+1;j<=r;++j){
         if (v[j]<p){
            swap_ind(v,i,j);
            ++i;
         }
      }
      swap_ind(v,(i-1),l);
      return (i-1);
   }
   void quickSortTrivialAux(vector<int>& v,unsigned start,unsigned end){
      if (end==start) return;
      unsigned p=partizione(v,start,end);
      if (p!=start)
         quickSortTrivialAux(v,start,p-1);
      if (p!=end)
         quickSortTrivialAux(v,p+1,end);
   }
/*quicksort con scelta banale del pivot*/
void quickSortTrivial(vector<int>& v){
   /* Implementare quickSort banale con partizione in place */
   quickSortTrivialAux(v,0,v.size()-1);
}
unsigned partizione2(vector<int> &v,unsigned l, unsigned r){
      int c=rand()%(r-l)+l;
      swap_ind(v,c,l);
      int p=v[l];
      unsigned i=l+1;
      for (unsigned j=l+1;j<=r;++j){
         if (v[j]<p){
            swap_ind(v,i,j);
            ++i;
         }
      }
      swap_ind(v,(i-1),l);
      return (i-1);
   }
void quickSortRandomAux(vector<int> &v,unsigned start,unsigned end){
      if (end==start) return;
      unsigned p=partizione2(v,start,end);
      if (p!=start)
         quickSortRandomAux(v,start,p-1);
      if (p!=end)
         quickSortRandomAux(v,p+1,end);
   }
/*quicksort randomizzato*/
void quickSortRandom(vector<int>& v){
   quickSortRandomAux(v,0,v.size()-1);
}


/**************************************************/
/*      funzioni implementate                     */
/**************************************************/

/* selection sort in place*/
void selectionSort(vector<int>& v){
   unsigned int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   { 
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j){
        if (v.at(current_min_index) > v.at(j)){
            current_min_index = j;
         }
     }
     swap_ind(v, i, current_min_index);
   }
}

/* insertion sort in place*/
void insertionSort(vector<int>& v){
   unsigned int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i){ 
      current=i; 
      prev=i-1;
      while(v.at(current)<v.at(prev)){
         swap_ind(v, current, prev);
         --current;
         if(prev>0){
            --prev;
         }else{
            break;
         }
      }
   }
}

/* bubble sort in place*/
void bubbleSort(vector<int>& v){
   unsigned int size = v.size();
   bool swapped=false;
   do{
      swapped=false;
      for (unsigned int i=1; i<size; ++i){
         if(v.at(i-1)>v.at(i)){ 
            swap_ind(v,i-1,i);
            swapped = true;
         }
      }
   }while(swapped);
}

/*merge sort in place*/
void merge(vector<int>& v, unsigned int beg, unsigned int cent, unsigned int end){
   unsigned int p1=beg;
   unsigned int p2=cent;
   vector<int> mv;
   while(p1<cent && p2<end){
      if(v.at(p1)<=v.at(p2)){
         mv.push_back(v.at(p1));
         ++p1;
      }else{
         mv.push_back(v.at(p2));
         ++p2;
      }
   }
   while(p1<cent){
      mv.push_back(v.at(p1));
      ++p1; 
   }
   while(p2<end){
      mv.push_back(v.at(p2));
      ++p2; 
   }
   for(unsigned int i=0;i<mv.size();++i){
      v.at(beg+i)=mv.at(i);
   }
}

void mergeSort(vector<int>& v){
   unsigned int s=v.size();
   for(unsigned int width=1;width<s;width=2*width){
      for(unsigned int i=0;i<s;i=i+2*width){
         if(i+width<s){
            unsigned int end=(i+2*width<=s)?(i+2*width):s;
            merge(v,i,i+width,end);
         }
      }
   }
}