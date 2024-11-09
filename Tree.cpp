#include <bits/stdc++.h>
#include "BTree.hpp"
#include "SegmentTree.cpp"
#include "BST.cpp"
using namespace std;

int main() {
    
    BST dbNames;//POPULATE THIS USING THE DATA FROM CSV FILE

    SegmentTree* segTree1;
    SegmentTree* segTree2;
    BTree btree(4);
    while(true){
    cout<<"1.CREATE\n2.READ/UPDATE/DELETE\n";
    int crud_choice; cin>>crud_choice;
    //Acc to choice, create or read a csv file

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


    vector<string> attributes(4);
    cout<<"Enter Attribute Names:"<<endl;
    for(int i=0; i<4; i++){
        cin>>attributes[i];
    }
    
    //Enter these names in top of the file


    int aggregateAttribute; cin>>aggregateAttribute;
    vector<int> segmentData1;
    vector<float> segmentData2;
    //Input of data
    while(true){
        
        int key; string name; int attribute1; float attribute2;
        cin>>key>>name>>attribute1>>attribute2;
        btree.insert(key,name,attribute1, attribute2); 
        segmentData1.push_back(attribute1); 
        segmentData2.push_back(attribute2); 
        
        int choice; cout<<"Enter 1 to add more, 0 to exit: "; cin>>choice;
        if(choice==0){
            cout<<"Data Insersion Complete\n";
            break;
        }
    }
    segTree1=new SegmentTree(segmentData1);
    segTree2=new SegmentTree(segmentData2);
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
        //BTree btree(4);

        vector<string> attributes;  //PUT NAMES OF ATTEIBUTES IN THIS. IT'LL BE HELPFUL IN PRINTING
        vector<int> segmentdata1;
        vector<float>segmentdata2;
        //POPULATE THIS VECTOR ALSO
        segTree1=new SegmentTree(segmentdata1);
        segTree2=new SegmentTree(segmentdata2);

        //NOW IMPLEMENT ALL THE QUERIES. ASK USER FOR QUERIES AND CHOICE TILL HE WANTS.



        //Clean BTree and SegmentTrees. NO DATA FLUSHING REQUIRED AS DATA IS SAME.
    

    //UPDATE
    //if(crud_choice==3){
        // string dbname;
        // cin>>dbname;

        // if(!dbNames.search(dbname)){
        //     cout<<"No such Database exists"<<endl;
        //     return 0;
        // }
        
        //FETCH THE CSV FILE OF THE DATABASE AND POPULATE THE BTree

        //QUERIES
        cout<<"MENU:\n1.SELECT\t2.UPDATE\t3.DELETE"<<endl;
        int choice;cin>>choice;
        //SELECT
        if(choice==1){
            cout<<"1.*\n2.NAME, "<<attributes[0]<<"\n3.NAME, "<<attributes[1]<<"4. AGGREGATE"<<endl;
            int read_choice;cin>>read_choice;
            if(read_choice==1){
                btree.printAllRecords();
            }
            if(read_choice==2){
                // Will do this
            }
            if(read_choice==3){
                // Will do this
            }
            if(read_choice==4){
                cout<<"1.SUM\t2.COUNT\t3.MIN\t4.MAX\n";
                cout<<"1. "<<attributes[0]<<"\t 2. "<<attributes[1]<<endl;
                int aggregateType, attributeNo;cin>>aggregateType>>attributeNo;
                //Sum
                if(aggregateType==1){
                    if(attributeNo==1){
                        //segTree1->sumAll()
                    }
                    else if(attributeNo==2){
                        //segTree2->sumAll();
                    }
                    else{
                        cout<<"invalid input"<<endl;
                    }
                }
                //Count
                if(aggregateType==2){
                    if(attributeNo==1){
                        //segTree1->countAll()
                    }
                    else if(attributeNo==2){
                        //segTree2->countAll();
                    }
                    else{
                        cout<<"invalid input"<<endl;
                    }
                }

                //Min
                if(aggregateType==1){
                    if(attributeNo==1){
                        //segTree1->minAll()
                    }
                    else if(attributeNo==2){
                        //segTree2->minAll();
                    }
                    else{
                        cout<<"invalid input"<<endl;
                    }
                }
                //Max
                if(aggregateType==1){
                    if(attributeNo==1){
                        //segTree1->maxAll()
                    }
                    else if(attributeNo==2){
                        //segTree2->maxAll();
                    }
                    else{
                        cout<<"invalid input"<<endl;
                    }
                }

            }
            else{
                cout<<"invalid input"<<endl;
            }
        }
        else if(choice==2){
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
            //segTree1->update(value);
            cout<<"Updated Successfully"<<endl;
        }
        
        else if(choice==3){
            cout<<"ENTER KEY NUMBER OF DATA YOU WANT TO DELETE: ";
            int key; cin>>key;
            BTreeNode* node=btree.search(key);
            if(!node){
                cout<<"NO SUCH NODE PRESENT"<<endl;
                return 0;
            }
            node->remove(key);
            
            cout<<"Deleted Successfully"<<endl;
        }

        // while (true)
        // {
        //     //cout<<"1.NAME \n2."<<attributes[2]<<endl;
        //     cout<<"Enter attribute you want to change: ";
        //     int updateno; cin>>updateno;
        //     cout<<"ENTER KEY NUMBER OF DATA YOU WANT TO UPDATE: ";
        //     int key; cin>>key;
        //     cout<<"ENTER THE NEW VALUE: ";
        //     int value; cin>>value;
        //     BTreeNode* node=btree.search(key);
        //     if(!node){
        //         cout<<"NO SUCH NODE PRESENT"<<endl;
        //         return 0;
        //     }
        //     node->ages[key]=value;

        //     cout<<"DO YOU WANT TO UPDATE MORE? 1. YES 0. NO: ";
        //     int choice; cin>>choice;
        //     if(choice==0){
        //         break;
        //     }
        // }
    

    //if(crud_choice==4){
        // string dbname;
        // cin>>dbname;

        // if(!dbNames.search(dbname)){
        //     cout<<"No such Database exists"<<endl;
        //     return 0;
        // }

    //     BTree btree(4);
    //     vector<int> segmentdata;
    //     vector<string> attribute; //PUT NAMES OF ATTRIBUTES IN THIS. IT'LL BE HELPFUL IN PRINTING
    //     //POPULATE THIS VECTOR ALSO
    //     SegmentTree* segTree=new SegmentTree(segmentdata);

    //     while (true)
    //     {
    //         cout<<"1.NAME \n2."<<attribute[2]<<endl;
    //         cout<<"ENTER KEY NUMBER OF DATA YOU WANT TO DELETE: ";
    //         int key; cin>>key;
    //         BTreeNode* node=btree.search(key);
    //         if(!node){
    //             cout<<"NO SUCH NODE PRESENT"<<endl;
    //             return 0;
    //         }
    //         node->remove(key);

    //         cout<<"DO YOU WANT TO DELETE MORE? 1. YES 0. NO: ";
    //         int choice; cin>>choice;
    //         if(choice==0){
    //             break;
    //         }
    //     }
    
    // }
    }
    cout<<"Want to query more?Enter 1 to continue, 0 to exit"<<endl;
    int contChoice;cout<<"Enter your choice: "; cin>>contChoice;
    if(contChoice==0) break;
    }
    //ALL QUERIES DONE! EXIT PROGRAM
    //FLUSH DATA IN CSV

    delete segTree1;
    delete segTree2;
    
    return 0;
}
