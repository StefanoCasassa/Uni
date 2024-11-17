#include "ASD-token.h"
#include "ASD-aritexpr.h"
#include "ASD-stack.h"
#include <iostream>
using namespace std;
int main(){
    string s="5848585";
    int m;
    token tok;
    try {
        nextToken(s,tok);
    }
    catch (string err){
        cerr<<err<<endl;
    }

    cout<<tok.val<<endl;
    }
