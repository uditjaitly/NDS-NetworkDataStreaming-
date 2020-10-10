#include <iostream>
#include <vector>
#define MAXN 1000  //table size
int hash_num=4;   // number of hash functions
int number_of_flows=1000; // number of flows

using namespace std;
int c=0;
vector<int> randoms;
int hash_table[MAXN];
int segment_interval=MAXN/4;


// Initialize the hash table
void initialize(int hash_table[]){
    for(int i=0;i<MAXN;i++){
        hash_table[i]=INT_MIN;
    }
}

//Calculate random values to be used by hash function
void calc_random(int hash_num){
    for(int i=0;i<hash_num;i++){
        srand(i+3947);
        randoms.push_back(rand());
    }
}

//Hash Function
int calc_hash(int element, int i){
    return (randoms[i]^element)%segment_interval;
}


//Insert flow values in hash table
void insert(int flow_value, int hash_table[]){
    vector<int> pos;
    for(int i=0;i<hash_num;i++){
        int position=calc_hash(flow_value, i) + (segment_interval*i);
        pos.push_back(position);
        // Check if the flow value already exists in the table
        if(hash_table[position]==flow_value){
            return;
        }
    }
    //Checks if the available places in hash table are empty, if yes, insert flow val
    for(int i=0;i<hash_num;i++){
        if(hash_table[pos[i]]==INT_MIN){
            hash_table[pos[i]]=flow_value;
            return;
        }
    }
    
}
//Calculate flows
void countFlow(int hash_table[]){
    for(int i=0;i<number_of_flows;i++){
        if(hash_table[i]!=INT_MIN){
            c++;
        }
    }
}


//Prints the hash-table
void print(int hash_table[]){
    for(int i=0;i<MAXN;i++){
        if(hash_table[i]!=INT_MIN){
            cout<<hash_table[i]<<" ";
        }
        else{
            cout<<0<<" ";
        }
    }
}

int main(int argc, const char * argv[]) {
    initialize(hash_table);
    calc_random(hash_num);
    for(int i=0;i<number_of_flows;i++){
        srand(i);
        insert(rand(), hash_table);
    }
    countFlow(hash_table);
    cout<<"\nNumber of Flows In Table="<<c<<"\n";
    print(hash_table);

    return 0;
}
