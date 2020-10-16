//
//  main.cpp
//  test_cuckoo
//
//  Created by Udit Jaitly on 04/10/20.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#define MAXN 1000 // table size
int num_hash=3; // number of hash functions
int num_of_flows=1000;//number of flows
int cuckoo_step=2; //cuckoo steps limit

using namespace std;
int hash_table[MAXN];
vector<int> randoms;
int count=0;
int avail=0;
int c=0;

//Initialize the hash table
void initialize(int hash_table[]){
    for(int i=0;i!=MAXN;i++){
        hash_table[i]=INT_MIN;
    }
}

//Calculate random values to be used by hash function
void calc_randoms(int num_hash){
    for(int i=0;i<num_hash;i++){
        srand(i);
        randoms.push_back(rand());
    }
}

//Hash Function
int calculate_hash(int i, int element){
    return (element ^ randoms[i])%MAXN;
}



//Insert flow values in hash table
void insert(int flow_value, int count, int r){
        
    
    bool insert_success=false;
    vector<int> pos;
    int temp;
    
    for(int i=0;i<num_hash;i++){
        int position=calculate_hash(i, flow_value);
        pos.push_back(position);
        // Check if the flow value already exists in the table
        if(hash_table[position]==flow_value && count<1){
            return;
        }
    }
    
    
    //Checks if the available places in hash table are empty, if yes, insert flow val
    for(int i=0;i!=pos.size();i++){
        if(hash_table[pos[i]]==INT_MIN){
            hash_table[pos[i]]=flow_value;
            insert_success=true;
            avail=1;
            return;
        }
    }
    
    //If above insertion fails, replace the element which can be moved within the cokoo step limit
    if(insert_success==false){

        avail=0;
        while(r<num_hash){
            temp=hash_table[pos[r]];
            if((count+1)<cuckoo_step){
                insert(temp, count+1, r);
                if(avail==1){
                    hash_table[pos[r]]=flow_value;
                    break;
                }
            }
            r++;
        }        
    }
}
//Calculate flows
void countFlow(int hash_table[]){
    for(int i=0;i<num_of_flows;i++){
        if(hash_table[i]!=INT_MIN){
            c++;
        }
    }
}


//Prints the hash-table
void print(int hash_table[]){
    for(int i=0;i<num_of_flows;i++){
        if(hash_table[i]!=INT_MIN){
            cout<<hash_table[i]<<" ";
        }
        else{
            cout<<0<<" ";
        }
    }
}

int main(int argc, const char * argv[])
{
    initialize(hash_table);
    randoms.clear();
    calc_randoms(num_hash);
    for(int i=0;i<num_of_flows;i++){
        srand(i);
        insert(rand(),0,0);
    }
    countFlow(hash_table);
    cout<<"\nNumber of Flows In Table="<<c<<"\n";
    print(hash_table);

    return 0;
}
