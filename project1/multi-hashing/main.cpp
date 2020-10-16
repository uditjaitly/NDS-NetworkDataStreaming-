
#include <iostream>
#include <vector>
#define MAXN 1000  // Table size
int hash_num=3; //Number of Hash Functions
int num_of_flows=1000; //Number of Flows

using namespace std;
int c=0;
vector<int> randoms;
int hash_table[MAXN];
//Initialize the hash table
void initialize(int hash_table[]){
    for(int i=0;i<MAXN;i++){
        hash_table[i]=INT_MIN;
    }
}

//Calculate random values to be used by hash function
void calc_random(int hash_num){
    for(int i=0;i<hash_num;i++){
        srand(i);
        randoms.push_back(rand());
    }
}


//Hash Function
int calc_hash(int element, int i){
    return (randoms[i]^element)%MAXN;
}

//Insert flow values in hash table
void insert(int flow_value){
    vector<int> pos;
    for(int i=0;i<hash_num;i++){
        int position=calc_hash(flow_value, i);
        pos.push_back(position);
        if(hash_table[position]==flow_value){
            return;
        }
    }
    
    for(int i=0;i<hash_num;i++){
        //cout<<hash_table[pos[i]]<<" ";
        if(hash_table[pos[i]]==INT_MIN){
            hash_table[pos[i]]=flow_value;
            return;
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

int main(int argc, const char * argv[]) {
    // insert code here...
    initialize(hash_table);
    calc_random(hash_num);
    
    for(int i=0;i<num_of_flows;i++){
        srand(i);
        insert(rand());
    }
    countFlow(hash_table);
    cout<<"NUMBER OF FLOWS IN TABLE="<<c<<"\n";
    print(hash_table);
    return 0;
}
