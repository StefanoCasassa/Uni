// TO DO, vedi indicazioni in network.h

#include "network.h"
#include <iostream>
using namespace network;
struct Person;
struct Group;
struct Friend {
    Person* ThisFriend; //usata per la delete
    Friend* nextF;
};
struct GroupPart{
    Group* group;
    GroupPart* nextGP;
};
struct Person { 
    GroupPart* group;
    string username;
    Friend* friends;
    Person* nextP;
};
struct Partecipant {
    Person* ThisPerson;
    Partecipant* nextPart;
};
struct Group {
    string name;
    string creator;
    Partecipant* partecipant;
    Group* nextG;
};
struct Elem{
    Group* groupList;
    Person* personList;
};
struct network::st_Network {
    int size;
    Elem* elem;
};
GroupPart* emptyGP = nullptr;
Group* emptyGroup = nullptr;
Friend* emptyFriendList = nullptr;
Person* emptyPersonList = nullptr;
Partecipant* emptyPartecipantList = nullptr;
Network network::createEmptyNetwork(){
        Network k=new st_Network;
        k->size=26;
        k->elem=new Elem[26];
        for (int i=0;i<k->size;i++){
            k->elem[i].groupList=emptyGroup;
            k->elem[i].personList=emptyPersonList;
        }
        return k;
    }

    int hash1(string usr){
        int z,k;
        if (usr[0]>='a' && usr[0]<='z') {
            k = usr[0]-97;
            return k;
        }
        if (usr[0]>='A' &&  usr[0]<='Z') {
            z = usr[0]-65;
            return z;
        }
    } 
  // Ritorna true se la network net e' vuota, false altrimenti
  bool network::isEmpty(const Network& net){
    for (int i=0;i<net->size;i++){
           if (net->elem[i].groupList!=emptyGroup) return false;
           if (net->elem[i].personList!=emptyPersonList) return false;
        }
        return true;
  }

    // Se usr_Log e' uguale a "" ritorno false
    // Se usr_Log non contiene solo caratteri alfabetici, ritorna false
  bool isUser_LogOk(string usr) {
    if (usr=="") return false;
    for (long unsigned int i=0;i<usr.length();i++){
        if (usr[i]<'a' || usr[i]>'z') {
            if (usr[i]<'A' || usr[i]>'Z') return false;
        }
    }
    return true;
  }
  // Aggiunge un membro alla network net con user_Login = usr_Log
  // Se usr_Log e' gia presente ritorna false
  // Altrimenti ritorna true
  bool network::addMember(string usr_Log, Network &net) { //ordinata
    if (!isUser_LogOk(usr_Log)) return false;
    int i=hash1(usr_Log);
    Person* aux=new Person;
            aux->group=emptyGP;
            aux->friends=emptyFriendList;
            aux->username=usr_Log;
    Person* p = net->elem[i].personList;
    if (p==emptyPersonList) {
            aux->nextP=emptyPersonList;
        p=aux;
        net->elem[i].personList=p;
        return true;
    }

    if (net->elem[i].personList->username==usr_Log) return false;

    if (p->nextP==emptyPersonList) {
        if (p->username>usr_Log){
            aux->nextP=p;
            net->elem[i].personList=aux;
            return true;
        }
        else {
            p->nextP=aux;
            aux->nextP=emptyPersonList;
            return true;
        }
    }
    while (p->nextP!=emptyPersonList){
        if (p->username==usr_Log) return false;
        if (p->nextP->username>usr_Log) break;
        p=p->nextP;
    }
        aux->nextP=p->nextP;
        p->nextP=aux;
    return true;
  }

    Person* IsThisAPerson(string usr,const Network &net){ //ordinata
        if (!isUser_LogOk(usr)) return emptyPersonList;
        int i=hash1(usr);
        Person* p=net->elem[i].personList;
        bool found=false;
        while (!found && p!=emptyPersonList) {
            if (p->username==usr) {
                found = true;
                return p;
            }
            if (p->username>usr) return emptyPersonList;
            p=p->nextP;
        }
        return emptyPersonList;
    }

  // Rende amici nella network net i membri con user_Login usr_Log1 e usr_Log2
  // Se usr_Log1 o usr_Log2 (o entrambi) non sono presenti in net, ritorna false
  // Se usr_Log1 e' uguale a usr_Log2, ritorna false
  // Altrimenti ritorna true (anche se sono gia amici)
  bool network::becomeFriends(string usr_Log1, string usr_Log2, Network &net){ //ordinata
    Person* p=IsThisAPerson(usr_Log1,net);
    if (p==emptyPersonList) return false; 

    Person* c=IsThisAPerson(usr_Log2,net);
    if (c==emptyPersonList) return false; 
    if (areFriends(usr_Log1,usr_Log2,net)) return true;
    Friend* aux=new Friend;
    aux->ThisFriend=c;
    //aux->usernameF=usr_Log2;

    bool done=false;
    Friend* cur=p->friends;
    Friend* prev=emptyFriendList;
    if (p->friends==emptyFriendList) {
        p->friends=aux;
        aux->nextF=emptyFriendList;
        done=true;
    }
    else {
        while (cur!=emptyFriendList) {

            if (cur->ThisFriend->username>usr_Log2) {
                done=true;
                if (prev==emptyFriendList) {
                    aux->nextF=p->friends;
                    p->friends=aux;
                    break;
                }
                else {
                    prev->nextF=aux;
                    aux->nextF=cur;
                    break;
                }
            
            }
            prev=cur;
            cur=cur->nextF;
        }
        if (!done && cur==emptyFriendList) {
        prev->nextF=aux;
        aux->nextF=emptyFriendList;
    }
    }

   done=false;
    Friend* aux1=new Friend;
    aux1->ThisFriend=p;
    //aux1->usernameF=usr_Log1;

    cur=c->friends;
    prev=emptyFriendList;
    if (c->friends==emptyFriendList) {
        done=true;
        c->friends=aux1;
        aux1->nextF=emptyFriendList;
    }
    else {
        while (cur!=emptyFriendList) {
            if (cur->ThisFriend->username>usr_Log1) {
                done=true;
                if (prev==emptyFriendList) {
                    aux1->nextF=c->friends;
                    c->friends=aux1;
                    break;
                }
                else {
                    prev->nextF=aux1;
                    aux1->nextF=cur;
                    break;
                }
            
            }
            prev=cur;
            cur=cur->nextF;
        }
        if (!done && cur==emptyFriendList) {
            prev->nextF=aux1;
            aux1->nextF=emptyFriendList;
        }
    }
    return true;
  }

  // Ritorna true se i membri con user_Login usr_Log1 e usr_Log2 nella network sono amici
  //   (chiaramente devono anche gia' essere presenti entrambi in net)
  // Altrimenti ritorna false
  bool network::areFriends(string usr_Log1, string usr_Log2, const Network &net){ //ordinata
    Person* a=IsThisAPerson(usr_Log1,net);
    if (a==emptyPersonList) return false; 


    Person* b=IsThisAPerson(usr_Log2,net);
    if (b==emptyPersonList) return false; 

        string a1 = a->username;
        string b1 = b->username;
        Friend* fa = a->friends;
        Friend* fb = b->friends;
        bool found=false;
        while (!found && fa!=emptyFriendList){
            if (fa->ThisFriend->username==b1) found=true;
            if (fa->ThisFriend->username>b1) return false;
            fa=fa->nextF;
        }
        if (!found) return false;
        found=false;
        while (!found && fb!=emptyFriendList){
            if (fb->ThisFriend->username==a1) found=true;
            if (fb->ThisFriend->username>a1) return false;
            fb=fb->nextF;
        }
        if (!found) return false;
        return true;


  }

  Group* DoesThisGroupExist(string name,const Network &net){ //ordinata
        int i=hash1(name);
        Group* g=net->elem[i].groupList;
        while (g!=emptyGroup) {
            if (g->name==name) {
                return g;
            }
            if (g->name>name) return emptyGroup;
            g=g->nextG;
        }
        return emptyGroup;
  }
  // Aggiunge un nuovo gruppo di group_Name g_Name alla network net
  // Questo gruppo ha un unico creatore che e il membro con user_Login usr_Log
  // Tutti gli amici del creatore al momento della creazione diventano membri del gruppo
  // Se non c'e' un membro in net con user_Login usr_Log, ritorna false
  // Se g_Name esiste gia', ritorna false
  // Altrimenti ritorna true
  void addMemberToGroup(Group* &g, Person* p) {
    cout<<"k\n";
    bool done=false;
    Partecipant* cur=g->partecipant;
    Partecipant* prev=emptyPartecipantList;
    Partecipant* aux=new Partecipant;
    aux->ThisPerson=p;
    if (g->partecipant==emptyPartecipantList) {
        cout<<"z\n";
        g->partecipant=aux;
        aux->nextPart=emptyPartecipantList;
        done=true;
    }
    else {
        while (cur!=emptyPartecipantList) {
            cout<<"b\n";
            if (cur->ThisPerson->username>p->username) {
                done=true;
                cout<<"prova\n";
                if (prev==emptyPartecipantList) {
                    aux->nextPart=g->partecipant;
                    g->partecipant=aux;
                    break;
                }
                else {
                    cout<<"111z\n";
                    prev->nextPart=aux;
                    aux->nextPart=cur;
                    break;
                }
            
            }
            prev=cur;
            cur=cur->nextPart;
        }
        cout<<"da222a\n";
        if (!done && cur==emptyPartecipantList) {
            cout<<"daa\n";
            prev->nextPart=aux;
            aux->nextPart=emptyPartecipantList;
        }
    }   
    cout<<"11111\n";
    done=false;
    GroupPart* cur1=p->group;
    GroupPart* prev1=emptyGP;
    GroupPart* aux1=new GroupPart;
    aux1->group=g;
    if (p->group==emptyGP) {
        p->group=aux1;
        aux1->nextGP=emptyGP;
        done=true;
    }
    else {
        while (cur1!=emptyGP) {

            if (cur1->group->name>aux1->group->name) {
                done=true;
                if (prev1==emptyGP) {
                    aux1->nextGP=p->group;
                    p->group=aux1;
                    break;
                }
                else {
                    prev1->nextGP=aux1;
                    aux1->nextGP=cur1;
                    break;
                }
            
            }
            prev1=cur1;
            cur1=cur1->nextGP;
        }
        if (!done && cur1==emptyGP) {
            prev1->nextGP=aux1;
            aux1->nextGP=emptyGP;
        }
    }
    

  }
  bool network::createGroup(string usr_Log, string g_Name, Network &net) {
    if (DoesThisGroupExist(g_Name,net)!=emptyGroup) return false;
    Person* p=IsThisAPerson(usr_Log,net);
    if (p==emptyPersonList) return false; 
    Group* aux=new Group;
    aux->creator=usr_Log;
    aux->name=g_Name;
    cout<<"1\n";
    Group* prev=emptyGroup;
    Group* cur=net->elem[hash1(g_Name)].groupList;
    if (net->elem[hash1(g_Name)].groupList==emptyGroup) {
        net->elem[hash1(g_Name)].groupList=aux;
        aux->nextG=emptyGroup;
    }else { 
        while (cur!=emptyGroup){
            if (cur->name>g_Name) break;
            prev=cur;
            cur=cur->nextG;
        }
        if (prev==emptyGroup){
            net->elem[hash1(g_Name)].groupList=aux;
            aux->nextG=cur;
        }
        else {
            prev->nextG=aux;
            aux->nextG=cur;
        }
    }
    cout<<"2\n";
    
    Friend* f=p->friends;

    while (f!=emptyFriendList){
        cout<<"3\n";
        addMemberToGroup(aux,f->ThisFriend);
        f=f->nextF;
    }
    addMemberToGroup(aux,p);
    return true;

  }

  // Il membro con user_Login usr_Log, diventa membro del gruppo con group_Name = g_Name
  // Ritorna true se c'e' un membro usr_Log e un gruppo g_Name
  // Altrimenti ritorna false
  bool network::joinGroup(string usr_Log, string g_Name, Network &net) {
    Group* g=DoesThisGroupExist(g_Name,net);
    if (g==emptyGroup) return false;
    Person* p=IsThisAPerson(usr_Log,net);
    if (p==emptyPersonList) return false;
    Partecipant* Pa=g->partecipant;
    while (Pa!=emptyPartecipantList){
        if (Pa->ThisPerson->username==usr_Log) return true;
        Pa=Pa->nextPart;
    }
    addMemberToGroup(g,p);
    return true;

  }
  
  // Cancella il membro con user_Login = usr_Log dal network net
  // Cancella anche tutti i gruppi di cui questo membro e' il creatore
  // Ritorna true se tale membro esiste
  // Altrimenti ritorna false
  bool network::deleteMember(string usr_Log, Network &net){
    Person* p=IsThisAPerson(usr_Log,net);
    if (p==emptyPersonList) return false;
    
    Friend* f=p->friends;
    while (f!=emptyFriendList){
        cout<<"a\n";
        cout<<f->ThisFriend->username<<endl;
        leaveFriendship(p->username,f->ThisFriend->username,net);
        f=f->nextF;
        }
        p->friends=emptyFriendList;

     //This part is for deleting Friends relations
    GroupPart* l=p->group;
    GroupPart* k=emptyGP;
    while (l!=emptyGP) {
        if (l->group->creator==p->username) {
            deleteGroup(l->group->name,net);
        }
        else {
            leaveGroup(p->username,l->group->name,net);
        }
        k=l;
        l=l->nextGP;
        delete k;
    }//qui elimino dai gruppi la persona
    p->group=emptyGP;

    Person* cur=net->elem[hash1(usr_Log)].personList;
    Person* prev=emptyPersonList;
        while (cur!=emptyPersonList) {
            if (cur->username==p->username){
                if (prev==emptyPersonList) {
                    net->elem[hash1(usr_Log)].personList=net->elem[hash1(usr_Log)].personList->nextP;
                    delete cur;
                    break;
                }
                else {
                    prev->nextP=cur->nextP;
                    delete cur;
                    break;
                }
            }
            prev=cur;
            cur=cur->nextP;
        }
     //Qui elimino la persona dalla lista PersonList.
    return true;
    
  }

  // Cancella il gruppo con group_Name = g_Name dal network net
  // Ritorna true se un tale gruppo esiste
  // Altrimenti ritorna false
  bool network::deleteGroup(string g_Name, Network &net){ //QUa e ovuqnue
    Group* z=DoesThisGroupExist(g_Name,net);
    if (z==emptyGroup) return false;
    cout<<"deleteGroup\n";
    Partecipant* pa=z->partecipant;
    Partecipant* aux=emptyPartecipantList;
    while (pa!=emptyPartecipantList){
        if (pa->ThisPerson->username=="ShawCarol") cout<<"vuoto\n";
        GroupPart* cur=pa->ThisPerson->group;
        GroupPart* prev=emptyGP;
        while (cur!=emptyGP){
            if (cur->group->name==g_Name) {
                if (prev==emptyGP){
                    cout<<"deleteGroup2\n";
                    pa->ThisPerson->group=cur->nextGP;
                    delete cur;
                    if (pa->ThisPerson->username=="ShawCarol") cout<<"vuoto\n";
                    break;
                }
                else {
                    cout<<"deleteGroup2.5\n";
                    prev->nextGP=cur->nextGP;
                    delete cur;
                    if (pa->ThisPerson->username=="ShawCarol") cout<<"vuoto\n";
                    break;
                }
            }
            prev=cur;
            cur=cur->nextGP;
        }
        aux=pa;
        pa=pa->nextPart;
        delete aux;
    }
    z->partecipant=emptyPartecipantList;
    
    if (net->elem[hash1(g_Name)].groupList->name==g_Name) {
        cout<<"deleteGroup3\n";
        Group* g=net->elem[hash1(g_Name)].groupList;
        net->elem[hash1(g_Name)].groupList=net->elem[hash1(g_Name)].groupList->nextG;
        delete g;
        return true;
    }
    Group* g=net->elem[hash1(g_Name)].groupList;
    while (g->nextG!=emptyGroup){
        cout<<"deleteGroup4\n";
        if (g->nextG->name==g_Name) {
            cout<<"deleteGroup5\n";
            Group* aux1=g->nextG;
            g->nextG=aux1->nextG;
            delete aux1;
            return true;
        }
        g=g->nextG;
    }
    cout<<"deleteGroup6\n";
    return true;
  }

  // Cancella l'amicizia fra il membro usr_Log1 e il membro usr_Log2
  // Se non ci sono i membri usr_Log1 o usr_Log2, ritorna false
  // Se usr_Log1 e' uguale a usr_Log2, ritorna false
  // Altrimenti ritorna true (anche se non sono amici)
  bool network::leaveFriendship(string usr_Log1, string usr_Log2, Network &net){
    Person* p=IsThisAPerson(usr_Log1,net);
    if (p==emptyPersonList) return false;
    Person* b=IsThisAPerson(usr_Log2,net);
    if (b==emptyPersonList) return false;
    
    Friend* cur=p->friends;
    Friend* prev=emptyFriendList;
    while (cur!=emptyFriendList){
        if (cur->ThisFriend->username==b->username) {
            if (prev==emptyFriendList){
                p->friends=p->friends->nextF;
                delete cur;
                break;
            }
            else {
                prev->nextF=cur->nextF;
                delete cur;
                break;
            }
        }
        prev=cur;
        cur=cur->nextF;
    }
    cur=b->friends;
    prev=emptyFriendList;
    while (cur!=emptyFriendList){
        if (cur->ThisFriend->username==p->username) {
            if (prev==emptyFriendList){
                b->friends=b->friends->nextF;
                delete cur;
                break;
            }
            else {
                prev->nextF=cur->nextF;
                delete cur;
                break;
            }
        }
        prev=cur;
        cur=cur->nextF;
    }   
    return true;
  }

  // Il membro con user_Login = usr_Log viene rimosso dal gruppo con group_Name = g_Name
  // Se il membro e' il creatore, il gruppo vienne cancellato
  // Se non c'e' in net un membro usr_Log o un gruppo g_Name ritorna false
  // Altrimenti ritorna true (anche se il membro usr_Log non e' membro del gruppo)
  bool network::leaveGroup(string usr_Log, string g_Name, Network &net){
    Group* g=DoesThisGroupExist(g_Name,net);
    cout<<"s\n";
    if (g==emptyGroup) return false;
    Person* p=IsThisAPerson(usr_Log,net);
    cout<<"z\n";
    if (p==emptyPersonList) return false;

    if (g->creator==usr_Log) {
        cout<<"prova\n";
        deleteGroup(g_Name,net);
        return true;
    }

    if (g->partecipant==emptyPartecipantList) return true;
    cout<<"passa\n";
    Partecipant* cur=g->partecipant;
    Partecipant* prev=emptyPartecipantList;
    while (cur!=emptyPartecipantList){
        if (cur->ThisPerson->username==usr_Log) {
             cout<<"000\n";
            if (prev==emptyPartecipantList){
                g->partecipant=g->partecipant->nextPart;
                delete cur;
                break;
            }
            else {
                prev->nextPart=cur->nextPart;
                delete cur;
                break;
            }
        }
        prev=cur;
        cur=cur->nextPart;
    }
    GroupPart* l=p->group;
    GroupPart* pre=emptyGP;
    while (l!=emptyGP) {
        if (l->group->name==g->name){
            cout<<"000111\n";
            if (pre==emptyGP){
                p->group=p->group->nextGP;
                delete l;
                break;
            }
            else {
                pre->nextGP=l->nextGP;
                delete l;
                break;
            }
        }
        pre=l;
        l=l->nextGP;
    }
    return true;
  }

  // Ritorna la lista in ordine alfabetico dei user_Login dei membri del network
  list::List network::members(const Network &net){
    list::List l=list::createEmpty();
    for (int i=0;i<26;i++){
        Person*p=net->elem[i].personList;
        while (p!=emptyPersonList){
            list::Elem s=p->username;
            list::addBack(s,l);
            p=p->nextP;
        }
    }
    return l;
  }

  // Ritorna la lista in ordine alfabetico dei group_Name dei gruppi del network
  list::List network::groups(const Network &net){
    list::List l=list::createEmpty();
    for (int i=0;i<26;i++){
        Group*g=net->elem[i].groupList;
        while (g!=emptyGroup){
            list::Elem s=g->name;
            list::addBack(s,l);
            g=g->nextG;
        }
    }
    return l;
  }
  
  // Ritorna la lista dei user_Login degli amici del membro con user_Login = usr_Log
  //  in ordine alfabetico 
  // Se non c'e membro con user_Login = usr_Log ritorna la lista vuota
  list::List network::friends(string usr_Log, const Network &net){
    list::List k=list::createEmpty();
    Person* p=IsThisAPerson(usr_Log,net);
    if (p==emptyPersonList) return k;
    Friend* cur=p->friends;
    while (cur!=emptyFriendList) {
        list::Elem s=cur->ThisFriend->username;
        list::addBack(s,k);
        cur=cur->nextF;
    }
    return k;
  }

  // Ritorna la lista dei nomi dei gruppi di cui il membro usr_Log
  //   e' membro (in ordine alfabetico)
  // (NB: un membro e' anche membro di un gruppo di cui e' il creatore)
  // Se in net non c'e' membro usr_Log ritorna la lista vuota
  list::List network::memberOf(string usr_Log, const Network &net){
    list::List k=list::createEmpty();
    Person* p=IsThisAPerson(usr_Log,net);
    if (p==emptyPersonList) return k;
    GroupPart* g=p->group;
    while (g!=emptyGP) {
        list::Elem s=g->group->name;
        list::addBack(s,k);
        g=g->nextGP;
    }
    return k;
  }

  // Ritorna la lista dei nomi dei gruppi di cui il membro usr_Log
  //  e' creatore in ordine alfabetico 
  // Se non c'e' membro usr_Log ritorna la lista vuota
  list::List network::creatorOf(string usr_Log, const Network &net){
    list::List k=list::createEmpty();
    Person* p=IsThisAPerson(usr_Log,net);
    if (p==emptyPersonList) return k;
    GroupPart* g=p->group;
    while (g!=emptyGP) {
        if (g->group->creator==usr_Log){
        list::Elem s=g->group->name;
        list::addBack(s,k);
        }
        g=g->nextGP;
    }
    return k;
  }
  // Il membro usr_Log diventa amico con tutti i membri con i
  //   quali condivide un gruppo
  // Ritorna true se c'e un membro con user_Login = usr_Log
  // Altrimenti ritorna false
  bool network::makeMoreFriends(string usr_Log, Network &net){
    return false;
  }