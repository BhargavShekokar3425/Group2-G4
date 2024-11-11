#include <bits/stdc++.h>
#include <iostream>
//#include "BTree.cpp"
#include "segtree.cpp"
//#include "BST.cpp"
#include "csvAaryan.hpp"

using namespace std;

int main() {

    SegmentTree<int> segTree1;
    SegmentTree<float> segTree2;
    BTree btree(4);
    string fname;
    while(true){
    std::cout<<"1.CREATE\n2.READ/UPDATE/DELETE\n";
    int crud_choice; std::cin>>crud_choice;
    //Acc to choice, create or read a csv file

    //CREATE
    if(crud_choice==1){
        std::cout<<"Enter Name of Database: ";
    string dbname; std::cin>>dbname;
    string filename=dbname+".csv";
    
    CSVHandler check(filename,btree);
    if(check.filexistchk(filename)==true){
        std::cout<<"DB Already Exists!! Use a new name"<<endl;
        continue;
    }



    vector<string> attributes(4);
    std::cout<<"Enter Attribute Names:"<<endl;
    for(int i=0; i<4; i++){
        std::cin>>attributes[i];
    }
    
    //Enter these names in top of the file


    //int aggregateAttribute; std::cin>>aggregateAttribute;
    vector<int> segmentData1;
    vector<float> segmentData2;
    //Input of data
    cout<<"Enter Data according to arrtibute format(ID NAME AGE SALARY)"<<endl;
    while(true){
        
        int key; string name; int attribute1; float attribute2;
        std::cin>>key>>name>>attribute1>>attribute2;
        btree.insert(key,name,attribute1, attribute2); 
        segmentData1.push_back(attribute1); 
        segmentData2.push_back(attribute2); 
        
        int choice; std::cout<<"Enter 1 to add more, 0 to exit: "; std::cin>>choice;
        if(choice==0){
            std::cout<<"Data Insersion Complete\n";
            break;
        }
    }
    segTree1.construct(segmentData1);
    segTree2.construct(segmentData2);
    
    CSVHandler c(filename, btree);
    c.saveCSV();
    c.exportBTreeToCPP();
    fname=filename;
    }

    //CREATE DONE IN MEMORY. FLUSH THE DATA TO CSV FILES

    //READ
    if(crud_choice==2){
        std::cout<<"Enter Name of Database: ";
        string dbname;
        std::cin>>dbname;
        string filename=dbname+".csv";
        CSVHandler check(filename,btree);
        if(check.filexistchk(filename)==false){
            std::cout<<"DB Doesn't Exists!! Use an existing db"<<endl;
            continue;
        }
        if(btree.isTreeEmpty()==true){
            CSVHandler c(filename, btree);
            c.loadCSV();
        }
        if(btree.isTreeEmpty()==true){
            std::cout<<"Empty hai"<<endl;
        }
        btree.printAllRecords();
        std::cout<<"TESTING DONEEE"<<endl;
        
        //FETCH THE CSV FILE OF THE DATABASE AND POPULATE THE BTree
        //BTree btree(4);

        vector<string> attributes(4);  //PUT NAMES OF ATTEIBUTES IN THIS. IT'LL BE HELPFUL IN PRINTING
        vector<int> segmentdata1;
        vector<float>segmentdata2;
        segmentdata1=btree.root->ages;
        segmentdata2=btree.root->salaries;
        //POPULATE THIS VECTOR ALSO
        segTree1.construct(segmentdata1);
        segTree2.construct(segmentdata2);

        //NOW IMPLEMENT ALL THE QUERIES. ASK USER FOR QUERIES AND CHOICE TILL HE WANTS.



        //Clean BTree and SegmentTrees. NO DATA FLUSHING REQUIRED AS DATA IS SAME.
    

    
        std::cout<<"MENU:\n1.SELECT\t2.UPDATE\t3.DELETE"<<endl;
        int choice;std::cin>>choice;
        //SELECT
        if(choice==1){
            std::cout<<"1.*\t2. * WHERE AGE"<<"\t3. * WHERE SALARY"<<"\t4. AGGREGATE"<<endl;
            int read_choice;std::cin>>read_choice;
            if(read_choice==1){
                btree.printAllRecords();
            }
            if(read_choice==2){
                // Will do this
                // For Name and age
                //i will ask for the range of all records, age (upper limit, lower limit), greater than age condition, less than age condition
                //call to B tree fucntion for name and age

                std::cout << "For Name and Age columns what do you want your conditions to be:" << endl;
                std::cout << "1. Greater than" << endl;
                std::cout << "2. Less than" << endl;
                std::cout << "3. Range" << endl;
                std::cout << "4. Equal" << endl;

                int read_choice2;
                std::cin >> read_choice2;

                // 0 represents attribute[0] i.e. Age
                if (read_choice2 == 1) {
                    btree.printGreater(0);
                }
                if (read_choice2 == 2) {
                    btree.printLess(0);
                }
                if (read_choice2 == 3) {
                    btree.printRange(0);
                }
                if(read_choice2 == 4){
                    btree.printEqual(0);
                }
            }
            if(read_choice==3){
                // Will do this right
                std::cout << "For Name and Salary columns what do you want your conditions to be:" << endl;
                std::cout << "1. Greater than" << endl;
                
                std::cout << "2. Less than" << endl;
                std::cout << "3. Range" << endl;
                std::cout << "4. Equal" << endl;

                int read_choice2;
                std::cin >> read_choice2;

                // 1 represents attribute[1] i.e. Salary
                if (read_choice2 == 1) {
                    btree.printGreater(1);
                }
                if (read_choice2 == 2) {
                    btree.printLess(1);
                }
                if (read_choice2 == 3) {
                    btree.printRange(1);
                }
                if(read_choice2 == 4){
                    btree.printEqual(1);
                }
            }
            if(read_choice==4){
                std::cout<<"1.SUM\t2.COUNT\t3.MAX\t4.MIN\n";
                std::cout<<"1. AGE"<<"\t 2. SALARY"<<endl;
                int aggregateType, attributeNo;std::cin>>aggregateType>>attributeNo;
                //Sum
                if(aggregateType==1 && attributeNo==1){
                    //if(attributeNo==1){
                        //segTree1->sumAll()
                        //int sum;
                        //sum = segTree1.sumWithConditions(segTree1.root, 0, segmentdata1.size()-1, 0, segmentdata1.size()-1);
                        std::cout<<"Sum of Age: "<<segTree1.rangeSum(0,segmentdata1.size()-1)<<endl;
                    }
                    else if(aggregateType==1 && attributeNo==2){
                        //segTree2->sumAll();
                        // float sum;
                        // sum = segTree2.sumSalary(segTree1.root, 0, segmentdata1.size()-1, 0, segmentdata1.size()-1);
                        std::cout<<"Sum of salary: "<<segTree2.rangeSum(0, segmentdata2.size()-1)<<endl;
                    }
                    // else{
                    //     std::cout<<"invalid input1"<<endl;
                    // }
                
                //Count
                if(aggregateType==2 && attributeNo==1){
                    //if(attributeNo==1){
                        //segTree1->countAll()
                        // int count;
                        // count=segTree1.countAge(segTree1.root, 0, segmentdata1.size()-1, 0, segmentdata1.size()-1);
                        std::cout<<"Count of Age: "<<segTree1.rangeCount(0, segmentdata1.size()-1)<<endl;
                }
                    else if(aggregateType==2 && attributeNo==2){
                        //segTree2->countAll();
                        // float count;
                        // count=segTree2.countAge(segTree2.root, 0, segmentdata2.size()-1, 0, segmentdata2.size()-1);
                        std::cout<<"Count of salary: "<<segTree2.rangeCount(0,segmentdata2.size()-1);
                    }
                    // else{
                    //     std::cout<<"invalid input2"<<endl;
                    // }
                

                //Max
                if(aggregateType==3 && attributeNo==1){
                    //if(attributeNo==1){
                        //segTree1->minAll()
                        // int maxage;
                        // maxage=segTree1.maxAge(segTree1.root, 0, segmentdata1.size()-1, 0, segmentdata1.size()-1);
                        std::cout<<"Max Age: "<<segTree1.rangeMax(0, segmentdata1.size()-1);
                    }
                    else if(aggregateType==3 && attributeNo==2){
                        //segTree2->minAll();
                        // float maxsalary;
                        // maxsalary=segTree2.maxSalary(segTree2.root, 0, segmentdata2.size()-1, 0, segmentdata2.size()-1);
                        std::cout<<"Max Salary: "<<segTree2.rangeMax(0, segmentdata2.size()-1);
                    }
                    // else{
                    //     std::cout<<"invalid input3"<<endl;
                    // }
                
                //Min
                if(aggregateType==4 && attributeNo==1){
                    //if(attributeNo==1){
                        //segTree1->maxAll()
                        // int minage;
                        // minage=segTree1.minAge(segTree1.root, 0, segmentdata1.size()-1, 0, segmentdata1.size()-1);
                        std::cout<<"Min Age: "<<segTree1.rangeMin(0, segmentdata1.size()-1);
                    }
                    else if(aggregateType==4 && attributeNo==2){
                        //segTree2->maxAll();
                        // float minsalary;
                        // minsalary=segTree2.minSalary(segTree2.root, 0, segmentdata2.size()-1, 0, segmentdata2.size()-1);
                        std::cout<<"Min Salary: "<<segTree2.rangeMin(0, segmentdata2.size()-1);
                    }
                    // else{
                    //     std::cout<<"invalid input4"<<endl;
                    // }
                

            }
            // else{
            //     std::cout<<"invalid input5"<<endl;
            // }
        }
        else if(choice==2){
            //UPDATE OPERATION

            std::cout <<"Do you want to perform 1:-Point update operation\t2:-New entry"<<endl;
            int type_of_update;
            std::cin >> type_of_update;
            if(type_of_update==1){
                //point update operation
                cout << " Enter the attribute you want to change: \n 1:Age \t2:Salary" << endl;
                int updateno;
                std::cin >> updateno;
                if(updateno==1){
                    std::cout << " Enter the key number of data you want to update: " << endl;
                    int key;
                    std::cin >> key;
                    std::cout << " Do you want to perform 1:- Increment operation\t2:-Decrement operation\t3:-Set operation "<<endl;
                    int choice_update;
                    std::cin >> choice_update;
                    if(choice_update==1){
                        //increment operation
                        std::cout << " Enter the add value: " << endl;
                        int add_value;
                        std::cin >> add_value;
                        //update_add_age
                        //call segment tree with parameters(add_value, key,(age or salary))
                        //segTree1.point_add_age(add_value, key);
                        btree.updateAddAge(key,add_value);
                        //std::cout<<"Updated Successfully"<<endl;
                    }
                    else if(choice_update==2){
                        //decrement operation
                        std::cout << " Enter the subtract value: " << endl;
                        int sub_value;
                        std::cin >> sub_value;
                        //update_sub_age
                        //call segment tree with parameters(sub_value, key,(age or salary))
                        btree.updateAddAge(key,(-1*sub_value));
                        std::cout<<"Updated Successfully"<<endl;
                    }
                    else if(choice_update==3){
                        //set operation
                        std::cout << " Enter the new value: " << endl;
                        int new_value;
                        std::cin >> new_value;
                        //update_set_age
                        //call segment tree with parameters(new_value, key,(age or salary))
                        btree.updateAge(key, new_value);
                        std::cout<<"Updated Successfully"<<endl;
                    }
                    else{
                        std::cout << "invalid input6"<<endl;    
                    }
                }
                else if(updateno==2){
                    //salary update operation
                    std::cout << " Enter the key number of data you want to update: " << endl;
                    int key;
                    std::cin >> key;
                    std::cout << " Do you want to perform 1:- Increment operation\t2:-Decrement operation\t3:-Set operation "<<endl;
                    int choice_update;
                    std::cin >> choice_update;
                    if(choice_update==1){
                        //increment operation
                        std::cout << " Enter the add value: " << endl;
                        float add_value;
                        std::cin >> add_value;
                        //update_add_salary
                        //call segment tree with parameters(add_value, key,(age or salary))
                        btree.updateAddSalary(key, add_value);
                        //std::cout<<"Updated Successfully"<<endl;
                    }
                    else if(choice_update==2){
                        //decrement operation
                        std::cout << " Enter the subtract value: " << endl;
                        float sub_value;
                        std::cin >> sub_value;
                        //update_sub_salary
                        //call segment tree with parameters(sub_value, key,(age or salary))
                        //segTree2.point_sub_salary(sub_value, key);
                        btree.updateAddSalary(key, -1*sub_value);
                        //std::cout<<"Updated Successfully"<<endl;
                    }
                    else if(choice_update==3){
                        //set operation
                        std::cout << " Enter the new value: " << endl;
                        float new_value;
                        std::cin >> new_value;
                        //update_set_salary
                        btree.updateSalary(key, new_value);
                        //std::cout<<"Updated Successfully"<<endl;
                        //call segment tree with parameters(new_value, key,(age or salary))
                    }
                    else{
                        std::cout << "invalid input7"<<endl;    
                    }
                }
            }
            if(type_of_update==2){
                //new key, name, age, sal
                //update btree
                //update segtree
                cout<<"Enter ID NAME AGE SALARY"<<endl;
                int key; string name; int attribute1; float attribute2;
                std::cin>>key>>name>>attribute1>>attribute2;
                btree.insert(key,name,attribute1, attribute2);
                cout<<"Updated Successfully"<<endl;
            }
            // if(type_of_update==3){
            //     //range update operation
            //     cout << " Enter the attribute you want to change: \n 1:Age \t2:Salary" << endl;
            //     int updateno;
            //     std::cin >> updateno;
            //     if(updateno==1){
            //         //range update operation age
            //         std::cout << " Enter the range of key numbers of data you want to update (low high): " << endl;
            //         int low_key,high_key;
            //         std::cin >> low_key >> high_key;
            //         std::cout << " Do you want to perform 1:- Increment operation\t2:-Decrement operation\t3:-Set operation "<<endl;
            //         int choice_update;
            //         std::cin >> choice_update;
            //         if(choice_update==1){
            //             //increment operation
            //             std::cout << " Enter the add value: " << endl;
            //             int add_value;
            //             std::cin >> add_value;
            //             //range_update_add_age
            //             //call segment tree with parameters(add_value, key range(low,high),(age or salary))
            //             segTree1.range_add_age(segTree1.root, low_key, high_key, 0, segmentdata1.size()-1, add_value);
            //             std::cout<<"Updated Successfully"<<endl;
            //         }
            //         else if(choice_update==2){
            //             //decrement operation
            //             std::cout << " Enter the subtract value: " << endl;
            //             int sub_value;
            //             std::cin >> sub_value;
            //             //range_update_sub_age
            //             //call segment tree with parameters(sub_value, key range(low,high),(age or salary))
            //             segTree1.range_sub_age(segTree1.root, low_key, high_key, 0, segmentdata1.size()-1, sub_value);
            //             std::cout<<"Updated Successfully"<<endl;
            //         }
            //         else if(choice_update==3){
            //             //set operation
            //             std::cout << " Enter the new value: " << endl;
            //             int new_value;
            //             std::cin >> new_value;
            //             //range_update_set_age
            //             //call segment tree with parameters(new_value, key range(low,high),(age or salary))
            //             segTree1.range_set_age(segTree1.root, low_key, high_key, 0, segmentdata1.size()-1, new_value);
            //             std::cout<<"Updated Successfully"<<endl;
            //         }
            //         else{
            //             std::cout << "invalid input"<<endl;    
            //         }
            //     }
            //     else if(updateno==2){
            //         //range update operation salary
            //         std::cout << " Enter the range of key number of data you want to update (low high): " << endl;
            //         int low_key,high_key;
            //         std::cin >> low_key >> high_key;
            //         std::cout << " Do you want to perform 1:- Increment operation\t2:-Decrement operation\t3:-Set operation "<<endl;
            //         int choice_update;
            //         std::cin >> choice_update;
            //         if(choice_update==1){
            //             //increment operation
            //             std::cout << " Enter the add value: " << endl;
            //             float add_value;
            //             std::cin >> add_value;
            //             //range_update_add_salary
            //             //call segment tree with parameters(add_value, key range(low,high),(age or salary))
            //             segTree2.range_add_salary(segTree2.root, low_key, high_key, 0, segmentdata2.size()-1, add_value);
            //             std::cout<<"Updated Successfully"<<endl;

            //         }
            //         else if(choice_update==2){
            //             //decrement operation
            //             std::cout << " Enter the subtract value: " << endl;
            //             float sub_value;
            //             std::cin >> sub_value;
            //             //range_update_sub_salary
            //             //call segment tree with parameters(sub_value, key range(low,high),(age or salary))
            //             segTree2.range_sub_salary(segTree2.root, low_key, high_key, 0, segmentdata2.size()-1, sub_value);
            //             std::cout<<"Updated Successfully"<<endl;
            //         }
            //         else if(choice_update==3){
            //             //set operation
            //             std::cout << " Enter the new value: " << endl;
            //             float new_value;
            //             std::cin >> new_value;
            //             //range_update_set_salary
            //             //call segment tree with parameters(new_value, key range(low,high),(age or salary))
            //             segTree2.range_set_salary(segTree2.root, low_key, high_key, 0, segmentdata2.size()-1, new_value);
            //             std::cout<<"Updated Successfully"<<endl;
            //         }
                    // else{
                    //     std::std::cout << "invalid input"<<endl;    
                    // }
            
        }

            
            
        
        
        else if(choice==3){
            std::cout<<"ENTER KEY NUMBER OF DATA YOU WANT TO DELETE: ";
            int key; std::cin>>key;
            BTreeNode* node=btree.search(key);
            if(!node){
                std::cout<<"NO SUCH NODE PRESENT"<<endl;
                return 0;
            }
            node->remove(key);
            
            std::cout<<"Deleted Successfully"<<endl;
        }
        fname=filename;
    }
        
    
    cout<<"Want to query more?Enter 1 to continue, 0 to exit"<<endl;
    int contChoice=1;
    std::cout<<"Enter your choice: "; 
    std::cin>>contChoice;
    if(contChoice==0){
        CSVHandler csvflush(fname, btree);
        csvflush.saveCSV();
        csvflush.exportBTreeToCPP();
        break;
    }
    }
    
    return 0;
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