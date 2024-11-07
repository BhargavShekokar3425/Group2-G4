#include <bits/stdc++.h>
#include "iostream"
#include "BTree.hpp"
#include "SegmentTree.hpp"
#include "BST.hpp"
using namespace std;

int main() {

    cout<<"1.CREATE\n2.READ\n3.UPDATE\n4.DELETE\n";
    int crud_choice; cin>>crud_choice;
    //Acc to choice, create or read a csv file

    BST dbNames;//POPULATE THIS USING THE DATA FROM CSV FILE

    //CREATE
    if(crud_choice==1){
    string dbname; cin>>dbname;
    //check if DB Exists
    if(dbNames.search(dbname)==true){
        cout<<"Database Already Exists\n";
        return 0;
    }

    //If DB is new, insert in the BST
    dbNames.insert(dbname);

    int deg; cin>>deg;  //No of attributes
    if(deg!=3 || deg!=4){
        cout<<"Input Size according to given constraints"<<endl;
        return 0;
    }
    BTree btree(deg); // BTree of degree entered by the user
    vector<string> attributes(deg);
    cout<<"Enter Attribute Names:"<<endl;
    for(int i=0; i<deg; i++){
        cin>>attributes[i];
    }
    //Enter these names in top of the file


    //Input Attribute Number for the Aggregate Query Operations
    int aggregateAttribute; cin>>aggregateAttribute;
    // for(int i=0; i<aggregateNo; i++){
    //     cin>>aggregateAttributes[i];
    // }
    vector<int> segmentData;
    //Input of data
    while(true){
        if(deg==3){
            int key; string name; int attribute1;
            cin>>key>>name>>attribute1;
            btree.insert(key,name,attribute1);
            segmentData.push_back(attribute1);   
        }
        if(deg==4){
            int key; string name; int attribute1; float attribute2;
            cin>>key>>name>>attribute1>>attribute2;
            btree.insert(key,name,attribute1, attribute2); 
            segmentData.push_back(attribute2);  
        }
        int choice; cout<<"Enter 1 to add more, 0 to exit: "; cin>>choice;
        if(choice==0){
            cout<<"Data Insersion Complete\n";
            break;
        }
    }
    SegmentTree* segTree=new SegmentTree(segmentData);
    }

    //CREATE DONE IN MEMORY. FLUSH THE DATA TO CSV FILES

    //READ
    if(crud_choice==2){
        string dbname;
        cin>>dbname;

        if(!dbNames.search(dbname)){
            cout<<"No such Database exists"<<endl;
            return 0;
        }
        
        //FETCH THE CSV FILE OF THE DATABASE AND POPULATE THE BTree
        int deg = 3; // or the appropriate degree
        BTree btree(deg);
        vector<string> attributes;  //PUT NAMES OF ATTEIBUTES IN THIS. IT'LL BE HELPFUL IN PRINTING
        vector<int> segmentdata;
        //POPULATE THIS VECTOR ALSO
        SegmentTree* segTree=new SegmentTree(segmentdata);

        //NOW IMPLEMENT ALL THE QUERIES. ASK USER FOR QUERIES AND CHOICE TILL HE WANTS.


        //Clean BTree and SegmentTrees. NO DATA FLUSHING REQUIRED AS DATA IS SAME.
    }

    //UPDATE
    if(crud_choice==3){
        string dbname;
        cin>>dbname;

        if(!dbNames.search(dbname)){
            cout<<"No such Database exists"<<endl;
            return 0;
        }
        
        //FETCH THE CSV FILE OF THE DATABASE AND POPULATE THE BTree
        BTree btree;
        vector<int> segmentdata;
        vector<string> attribute; //PUT NAMES OF ATTEIBUTES IN THIS. IT'LL BE HELPFUL IN PRINTING
        //POPULATE THIS VECTOR ALSO
        SegmentTree* segTree=new SegmentTree(segmentdata);

        while (true)
        {
            cout<<"1.NAME \n2."<<attribute[2]<<endl;
            cout<<"Enter attribute you want to change: ";
            int updateno; cin>>updateno;
            cout<<"ENTER KEY NUMBER OF DATA YOU WANT TO UPDATE: ";
            int key; cin>>key;
            cout<<"ENTER THE NEW VALUE: ";
            int value; cin>>value;
            BTreeNode* node=btree.search(key);
            if(!node){
                cout<<"NO SUCH NODE PRESENT"<<endl;
                return 0;
            }
            node->ages[key]=value;

            cout<<"DO YOU WANT TO UPDATE MORE? 1. YES 0. NO: ";
            int choice; cin>>choice;
            if(choice==0){
                break;
            }
        }
    }

    if(crud_choice==4){
        string dbname;
        cin>>dbname;

        if(!dbNames.search(dbname)){
            cout<<"No such Database exists"<<endl;
            return 0;
        }

        BTree btree;
        vector<int> segmentdata;
        vector<string> attribute; //PUT NAMES OF ATTRIBUTES IN THIS. IT'LL BE HELPFUL IN PRINTING
        //POPULATE THIS VECTOR ALSO
        SegmentTree* segTree=new SegmentTree(segmentdata);

        while (true)
        {
            cout<<"1.NAME \n2."<<attribute[2]<<endl;
            cout<<"Enter attribute you want to change: ";
            int updateno; cin>>updateno;
            cout<<"ENTER KEY NUMBER OF DATA YOU WANT TO DELETE: ";
            int key; cin>>key;
            BTreeNode* node=btree.search(key);
            if(!node){
                cout<<"NO SUCH NODE PRESENT"<<endl;
                return 0;
            }
            node->remove(key);

            cout<<"DO YOU WANT TO DELETE MORE? 1. YES 0. NO: ";
            int choice; cin>>choice;
            if(choice==0){
                break;
            }
        }
    }


    //delete segTree;
    return 0;
}
