// FILE DA MODIFICARE
#include <string>
#include <iostream>
#include "ASD-aritexpr.h"
#include "ASD-token.h"
#include "ASD-stack.h"

using namespace stack;
using namespace std;

/*Calcula il valore intero dell'espressione aritmetica st*/
/*se st non corrisponde ad un expression aritmetica*/
/*solleva un eccezione di tipo string*/
/*con valore: "Lexical Error" se st non è composta da tokens*/
/*e valore: "Syntactical Error" se st è ben formata*/


int compute_arithmetic_expr(const string& st){
	string stAux=st;
	string serr="Syntactical error";
	Stack s=createEmpty();
	Elem tok;

	bool d=true;

	try{
		d = nextToken(stAux,tok);
	}
	catch (string err){	
		throw err;
	}
	push(tok,s);
	if (tok.k==NUMERO){
		if (stAux.size()==0) return s.data[s.size-1].val;
		else throw serr;
	}
	
	while (d){
		do {
			try{
				d = nextToken(stAux,tok);
			}
			catch (string err){	
				throw err;
			}
			if (!d) throw serr;
			push(tok,s); 
		} while (tok.k!=PARENTESI_CHIUSA);
		
	
		token z,b,a,c;
		a.k=NUMERO;
		c.k=NUMERO;
		b.k=OP_SOMMA;
		if (s.data[s.size-1].k==PARENTESI_CHIUSA) {
			pop(s);
			}
		else throw serr;
		if (s.data[s.size-1].k==NUMERO) {
			a=s.data[s.size-1];
			pop(s);
			}
		else throw serr;
		
			if (s.data[s.size-1].k==OP_MOLTIPLICAZIONE || s.data[s.size-1].k==OP_SOMMA || s.data[s.size-1].k==OP_SOTTRAZIONE) {
				b.k=s.data[s.size-1].k;
				pop(s);
			}
	
		if (s.data[s.size-1].k==NUMERO) {
			c.val=s.data[s.size-1].val;
			pop(s);
			} 
		else throw serr;

		if (s.data[s.size-1].k==PARENTESI_APERTA) {
			pop(s); 
			}
		else throw serr;

		z.k=NUMERO;
		if (b.k==OP_MOLTIPLICAZIONE){
			z.val=a.val*c.val;
			push(z,s);

		}
		if (b.k==OP_SOMMA){
			
			z.val=c.val+a.val;
			push(z,s);
			
		}
		if (b.k==OP_SOTTRAZIONE){
			z.val=c.val-a.val;
			push(z,s);
			
		}
		string stAux1=stAux;
		try{
				d = nextToken(stAux1,tok);
			}
			catch (string err){	
				throw err;
			}
		}
	
	return s.data[s.size-1].val;
	}
