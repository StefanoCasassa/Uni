// TO DO, vedi indicazioni in network.h

#include "network.h"
#include <iostream>
using namespace network;
struct Person;
struct Group;
struct Friend;
struct Partecipant;

const int N=26; //number of bucket;

typedef Group* GroupP; 
const GroupP emptyGroup = nullptr;

typedef Friend* FriendP;
const FriendP emptyFriendList = nullptr;

typedef Person* PersonP;
const PersonP emptyPersonList = nullptr;

typedef Partecipant* PartecipantP;
const PartecipantP emptyPartecipantList = nullptr;

struct Friend { //sotto lista di ogni persona
    PersonP ThisFriend = emptyPersonList; 
    FriendP nextF = emptyFriendList;
};
struct Person { //lista 2 del bucket
    string username;
    FriendP friends = emptyFriendList;
    PersonP nextP = emptyPersonList;
};
struct Partecipant {//sotto lista di ogni gruppo
    PersonP ThisPerson = emptyPersonList;
    PartecipantP nextPart = emptyPartecipantList;
};
struct Group {//lista 1 del bucket
    string name;
    string creator;
    PartecipantP partecipant = emptyPartecipantList;
    GroupP nextG = emptyGroup;
};
struct Elem{ //bucket
    GroupP groupList = emptyGroup;
    PersonP personList = emptyPersonList;
};
struct network::st_Network {//Tabella di hash
    int size;
    Elem* elem = nullptr;
};

    Network network::createEmptyNetwork(){//Create the array 
        Network k=new st_Network;
        k->size=N;
        k->elem=new Elem[N];
        for (int i=0;i<k->size;i++){
            k->elem[i].groupList=emptyGroup;
            k->elem[i].personList=emptyPersonList;
        }
        return k;
    }

    int hash1(string usr){ //Se il nome inizia con una lettera dell'alfabeto va nel bucket apposito, in caso contrario va in 0;
        int z,k;
        if (usr[0]>='a' && usr[0]<='z') {
            k = usr[0]-97;
            return k;
        }
        if (usr[0]>='A' &&  usr[0]<='Z') {
            z = usr[0]-65;
            return z;
        }
        return 0;
    } 
  
    bool network::isEmpty(const Network& net){//se tutti i bucket sono vuoti
        for (int i=0;i<net->size;i++){
            if (net->elem[i].groupList!=emptyGroup) return false;
            if (net->elem[i].personList!=emptyPersonList) return false;
        }
        return true;
    }

   
    bool isUser_LogOk(string usr) { //controllo se il nome è Ok
        if (usr=="") return false;
        for (long unsigned int i=0;i<usr.length();i++){
            if (usr[i]<'a' || usr[i]>'z') {
                if (usr[i]<'A' || usr[i]>'Z') return false;
            }
        }
    return true;
    }

    Person* IsThisAPerson(string usr,const Network &net){ //cerco se esiste la Persona
   
        if (!isUser_LogOk(usr)) return emptyPersonList;
        int i=hash1(usr);
        PersonP p=net->elem[i].personList;
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

    //La addMember tiene conto che la lista delle persone in ogni bucket è ordinata;
    bool network::addMember(string usr_Log, Network &net) { 

        if (!isUser_LogOk(usr_Log)) return false; //controlli vari
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p!=emptyPersonList) return false;

        PersonP aux=new Person;
        aux->friends=emptyFriendList;
        aux->username=usr_Log;
        if (net->elem[hash1(usr_Log)].personList==emptyPersonList) {//insert in caso il bucket sia vuoto
            aux->nextP=emptyPersonList;
            net->elem[hash1(usr_Log)].personList=aux;
            return true;
        }

        PersonP cur=net->elem[hash1(usr_Log)].personList;
        PersonP prev=emptyPersonList;
        while (cur!=emptyPersonList){
            if (cur->username>usr_Log){
                
                if (prev==emptyPersonList){//insert in testa
                    aux->nextP=net->elem[hash1(usr_Log)].personList;
                    net->elem[hash1(usr_Log)].personList=aux;
                    return true;
                }
                else {//insert generale
                    prev->nextP=aux;
                    aux->nextP=cur;
                    return true;
                }
            }
            prev=cur;
            cur=cur->nextP;
        }
        prev->nextP=aux; //insert in coda
        aux->nextP=emptyPersonList;
        return true;
    
    }


    bool network::areFriends(string usr_Log1, string usr_Log2, const Network &net){ //controllo se sono già amici
  
        PersonP a=IsThisAPerson(usr_Log1,net);
        if (a==emptyPersonList) return false; 

            FriendP fa = a->friends;
            bool found=false;
            while (!found && fa!=emptyFriendList){
                if (fa->ThisFriend->username==usr_Log2) found=true;
                if (fa->ThisFriend->username>usr_Log2) return false;
                fa=fa->nextF;
            }
        if (!found) return false;
        return true;
    }


    void becomeFriendsAux(Person* p,Person* c){
        FriendP aux=new Friend;
        aux->ThisFriend=c;

        bool done=false;
        FriendP cur=p->friends;
        FriendP prev=emptyFriendList;
        if (p->friends==emptyFriendList) {//insert in caso di bucket vuoto
            p->friends=aux;
            aux->nextF=emptyFriendList;
            done=true;
        }
        else {
            while (cur!=emptyFriendList) {

                if (cur->ThisFriend->username>c->username) {
                    done=true;
                    if (prev==emptyFriendList) {//in testa
                        aux->nextF=p->friends;
                        p->friends=aux;
                        break;
                    }
                    else {//caso generale
                        prev->nextF=aux;
                        aux->nextF=cur;
                        break;
                    }
                
                }
                prev=cur;
                cur=cur->nextF;
            }
            if (!done && cur==emptyFriendList) {//in coda
                prev->nextF=aux;
                aux->nextF=emptyFriendList;
            }
        }
    }

    //la becomeFriends tiene conto che le liste amici sono ordinate
    bool network::becomeFriends(string usr_Log1, string usr_Log2, Network &net){ 
  
        PersonP p=IsThisAPerson(usr_Log1,net);
        if (p==emptyPersonList) return false; 

        PersonP c=IsThisAPerson(usr_Log2,net);
        if (c==emptyPersonList) return false;

        if (areFriends(usr_Log1,usr_Log2,net)) return true;

        becomeFriendsAux(p,c);
        becomeFriendsAux(c,p);

        return true;
    }

 
     Group* DoesThisGroupExist(string name,const Network &net){ //controllo se il gruppo con nome name esiste
        int i=hash1(name);
        GroupP g=net->elem[i].groupList;
        while (g!=emptyGroup) {
            if (g->name==name) {
                return g;
            }
            if (g->name>name) return emptyGroup;
            g=g->nextG;
        }
        return emptyGroup;
    }


    //la join considera il fatto che la lista dei partecipanti al gruppo è ordinata
    bool network::joinGroup(string usr_Log, string g_Name, Network &net) { 

        GroupP g=DoesThisGroupExist(g_Name,net);
        if (g==emptyGroup) return false;
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return false;

        PartecipantP Part=new Partecipant;
        Part->ThisPerson=p;
        if (g->partecipant==emptyPartecipantList){//insert in caso sia vuota
            g->partecipant=Part;
            Part->nextPart=emptyPartecipantList;
            return true;
        }
        PartecipantP cur=g->partecipant;
        PartecipantP prev=emptyPartecipantList;
        while (cur!=emptyPartecipantList){
            if (cur->ThisPerson->username>usr_Log){//in caso sia fatta in testa
                if (prev==emptyPartecipantList){
                    g->partecipant=Part;
                    Part->nextPart=cur;
                    return true;
                }
                else {//caso generale
                    prev->nextPart=Part;
                    Part->nextPart=cur;
                    return true;
                }
            }
            prev=cur;
            cur=cur->nextPart;
        }
        //insert in coda
        prev->nextPart=Part;
        Part->nextPart=emptyPartecipantList;
        return true;

    
    }

    //la create inserisci i gruppi ordinati per nome
    bool network::createGroup(string usr_Log, string g_Name, Network &net) {
    
        if (DoesThisGroupExist(g_Name,net)!=emptyGroup) return false;
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return false; 

        GroupP aux=new Group;
        aux->creator=usr_Log;
        aux->name=g_Name;
    
    
        if (net->elem[hash1(g_Name)].groupList==emptyGroup){//in caso il bucket ia vuoto;
            net->elem[hash1(g_Name)].groupList=aux;
            aux->nextG=emptyGroup;
        }
        else {
            GroupP cur=net->elem[hash1(g_Name)].groupList;
            GroupP prev=emptyGroup;
            while (cur!=emptyGroup){
                if (cur->name>g_Name){
                    if (prev==emptyGroup){//in caso vada inserito come primo elemento del bucket
                        aux->nextG=net->elem[hash1(g_Name)].groupList;
                        net->elem[hash1(g_Name)].groupList=aux;
                        break;
                    }
                    else {//caso generale
                        prev->nextG=aux;
                        aux->nextG=cur;
                    }
                }
                prev=cur;
                cur=cur->nextG;
            }
            if (cur==emptyGroup){//insert in coda
                prev->nextG=aux;
                aux->nextG=cur;
            }
        }
        
        FriendP f=p->friends;
        while (f!=emptyFriendList){//aggiungo gli amici del creatore al nuovo gruppo come partecipanti
            joinGroup(f->ThisFriend->username,g_Name,net);
            f=f->nextF;
        }
        return true;


    }

    bool network::deleteGroup(string g_Name, Network &net){ 
        
        GroupP z=DoesThisGroupExist(g_Name,net);
        if (z==emptyGroup) return false;

        PartecipantP Pa=z->partecipant;
        PartecipantP aux;
        while (Pa!=emptyPartecipantList){//svuto la lista partecipanti
            aux=Pa;
            Pa=Pa->nextPart;
            delete aux;
        }
        z->partecipant=emptyPartecipantList;
        
        GroupP cur=net->elem[hash1(g_Name)].groupList;
        GroupP prev=emptyGroup;
        while (cur!=emptyGroup){//elimino il gruppo nella lista gruppo
            if (cur->name==g_Name){
                if (prev==emptyGroup){
                    net->elem[hash1(g_Name)].groupList=net->elem[hash1(g_Name)].groupList->nextG;
                    delete cur;
                    return true;
                }
                else {
                    prev->nextG=cur->nextG;
                    delete cur;
                    return true;
                }
            }
            prev=cur;
            cur=cur->nextG;
        }
        return true;
    }
  
    bool network::leaveFriendship(string usr_Log1, string usr_Log2, Network &net){
        PersonP p=IsThisAPerson(usr_Log1,net);
        if (p==emptyPersonList) return false;
        PersonP b=IsThisAPerson(usr_Log2,net);
        if (b==emptyPersonList) return false;

        
        FriendP cur=p->friends;
        FriendP prev=emptyFriendList;
        while (cur!=emptyFriendList){//elimino usr_Log2 dalla lista amici di usr_Log1
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
        while (cur!=emptyFriendList){//viceversa
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

    bool network::deleteMember(string usr_Log, Network &net){

        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return false;

        GroupP g = emptyGroup;
        for (int i=0;i<N;i++){//Gestisto i gruppi a cui usr_Log partecipa o è creatore
            g=net->elem[i].groupList;
            while (g!=emptyGroup){
                if (g->creator==usr_Log) {
                    deleteGroup(g->name,net);
                }
                else {
                    PartecipantP pa=g->partecipant;
                    while (pa!=emptyPartecipantList){
                        if (pa->ThisPerson->username==usr_Log) {
                            leaveGroup(pa->ThisPerson->username,g->name,net);
                            break;
                        }
                        pa=pa->nextPart;
                    }
                }
                g=g->nextG;
            }
        }

        FriendP f=p->friends;
        while (f!=emptyFriendList) {//Elimino gli elementi della lista amici
            string s=f->ThisFriend->username;
            f=f->nextF;
            leaveFriendship(usr_Log,s,net);
        }
        p->friends=emptyFriendList;

        //cerco la persona nei bucket per eliminarla dalla lista persone
        PersonP cur=net->elem[hash1(usr_Log)].personList;
        PersonP prev=emptyPersonList;
        while (cur!=emptyPersonList){
            if (cur->username==usr_Log){
                if (prev==emptyPersonList){
                    net->elem[hash1(usr_Log)].personList=net->elem[hash1(usr_Log)].personList->nextP;
                    delete cur;
                    return true;
                }
                else{
                    prev->nextP=cur->nextP;
                    delete cur;
                    return true;
                }

            }
            prev=cur;
            cur=cur->nextP;
        }
        
        return true;
    }



  
    bool network::leaveGroup(string usr_Log, string g_Name, Network &net){

        GroupP g=DoesThisGroupExist(g_Name,net);
        if (g==emptyGroup) return false;
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return false;

        if (g->creator==usr_Log) {//in caso sia il creatore chiamo la delete
            deleteGroup(g_Name,net);
            return true;
        }


        PartecipantP cur=g->partecipant;
        PartecipantP prev=emptyPartecipantList;
        while (cur!=emptyPartecipantList){//caso generale cerco il partecipante nel gruppo
            if (cur->ThisPerson->username==usr_Log) {
                if (prev==emptyPartecipantList){
                    g->partecipant=g->partecipant->nextPart;
                    delete cur;
                    return true;
                }
                else {
                    prev->nextPart=cur->nextPart;
                    delete cur;
                    return true;
                }
            }
            prev=cur;
            cur=cur->nextPart;
        }

        return true;
    }

  
    list::List network::members(const Network &net){
        list::List l=list::createEmpty();
        for (int i=0;i<N;i++){
            PersonP p=net->elem[i].personList;
            while (p!=emptyPersonList){
                list::Elem s=p->username;
                list::addBack(s,l);
                p=p->nextP;
            }
        }
        return l;
    }

  
    list::List network::groups(const Network &net){
        list::List l=list::createEmpty();
        for (int i=0;i<N;i++){
            GroupP g=net->elem[i].groupList;
            while (g!=emptyGroup){
                list::Elem s=g->name;
                list::addBack(s,l);
                g=g->nextG;
            }
        }
        return l;
    }
  
  
    list::List network::friends(string usr_Log, const Network &net){
        list::List k=list::createEmpty();
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return k;
        FriendP cur=p->friends;
        while (cur!=emptyFriendList) {
            list::Elem s=cur->ThisFriend->username;
            list::addBack(s,k);
            cur=cur->nextF;
        }
        return k;
    }

    //controllo in tutti i gruppi tutti i partecipanti per vedere se usr_log è membro
    list::List network::memberOf(string usr_Log, const Network &net){
        list::List k=list::createEmpty();
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return k;
        
        GroupP g =emptyGroup;
        for (int i=0;i<N;i++){
            g=net->elem[i].groupList;
            while (g!=emptyGroup){
                if (g->creator==usr_Log) {
                    list::Elem s=g->name;
                    list::addBack(s,k);   
                }
                else {
                    PartecipantP pa=g->partecipant;
                    while (pa!=emptyPartecipantList){
                        if (pa->ThisPerson->username==usr_Log) {
                            list::Elem s=g->name;
                            list::addBack(s,k); ;
                            break;
                        }
                        pa=pa->nextPart;
                    }
                }
                g=g->nextG;
            }
        }
        return k;
    }

  
    list::List network::creatorOf(string usr_Log, const Network &net){
        list::List k=list::createEmpty();
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return k;
        GroupP g =emptyGroup;
        for (int i=0;i<N;i++){
            g=net->elem[i].groupList;
            while (g!=emptyGroup){
                if (g->creator==usr_Log) {
                    list::Elem s=g->name;
                    list::addBack(s,k);   
                }
                g=g->nextG;
            }
        }
        return k;
    }
 
    bool network::makeMoreFriends(string usr_Log, Network &net){
        PersonP p=IsThisAPerson(usr_Log,net);
        if (p==emptyPersonList) return false;
        
        GroupP g =emptyGroup;
        for (int i=0;i<N;i++){
            g=net->elem[i].groupList;
            while (g!=emptyGroup){
                if (g->creator==usr_Log) {
                    PartecipantP pb=g->partecipant;
                    while (pb!=emptyPartecipantList) {
                        becomeFriends(usr_Log,pb->ThisPerson->username,net);
                        pb=pb->nextPart;
                    }  
                }
                else {
                    PartecipantP pa=g->partecipant;
                    bool k=false;
                    while (pa!=emptyPartecipantList){
                        if (pa->ThisPerson->username==usr_Log) {
                            k=true;
                            break;
                        }
                        pa=pa->nextPart;
                    }
                    PartecipantP pc=g->partecipant;
                    while (k && pc!=emptyPartecipantList) {
                        if (usr_Log!=pc->ThisPerson->username)
                        becomeFriends(usr_Log,pc->ThisPerson->username,net);
                        pc=pc->nextPart;
                    }
                }
                g=g->nextG;
            }
        }
        return true;
    }