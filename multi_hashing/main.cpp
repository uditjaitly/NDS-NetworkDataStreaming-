//
//  main.cpp
//  multi_hashing
//
//  Created by Udit Jaitly on 04/10/20.
//

#include <iostream>
#include <vector>
#define MAXN 1000
using namespace std;
int c=0;
int hash_num=3;
vector<int> randoms;
int hash_table[MAXN];

void initialize(int hash_table[]){
    for(int i=0;i<MAXN;i++){
        hash_table[i]=INT_MIN;
    }
}
void calc_random(int hash_num){
    for(int i=0;i<hash_num;i++){
        randoms.push_back(rand());
    }
}
int calc_hash(int element, int i){
    return (randoms[i]^element)%MAXN;
}

void insert(int flow_value, int hash_table[]){
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

void print(int hash_table[]){
    for(int i=0;i<MAXN;i++){
        //cout<<hash_table[i]<<" ";
        if(hash_table[i]!=INT_MIN){
            c++;
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    initialize(hash_table);
    calc_random(hash_num);
    
    for(int i=0;i<MAXN;i++){
        insert(rand(), hash_table);
    }
    std::cout << "Hello, World!\n";
    print(hash_table);
    cout<<"TOTAL ENTRIES="<<c;
    return 0;
}
