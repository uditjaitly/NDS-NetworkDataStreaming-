//
//  main.cpp
//  bloom_filter
//
//  Created by Udit Jaitly on 16/10/20.
//

#include <iostream>
#include <vector>
#include <set>
#define MAXN 10000
using namespace std;
vector<int> bloomFilter;
vector<int> randomNums;
vector<int> elementsA;
vector<int> elementsB;
int numHashes=7;
int matchCount=0;
int numElements=1000;
int c=0;



void initFilter(){
    for(int i=0;i<MAXN;i++){
        bloomFilter.push_back(0);
    }
}


void calcRandoms(){
    for(int i=0;i<numHashes;i++){
        randomNums.push_back(rand());
    }
}



void insert(vector<int> elements){
    for(int i=0;i<elements.size();i++){
        vector<int> hashValues;

        for(int j=0;j<numHashes;j++){
           
            hashValues.push_back((randomNums[j]^elements[i])%MAXN);
            if(bloomFilter[hashValues[j]]==0){
                bloomFilter[hashValues[j]]=1;
                c++;
            }
        }
    }
   
    
    
}

void query(vector<int> elements){
   
    
    for(int i=0;i<elements.size();i++){
        int count=0;
        vector<int> hashValues;
        for(int j=0;j<numHashes;j++){
            hashValues.push_back((randomNums[j]^elements[i])%MAXN);
            if(bloomFilter[hashValues[j]]==1){
                count++;
            }
        }
        
        if (count==numHashes){
            matchCount++;
        }
    }
    
    
    
    
    
    
}


vector<int> generateNums(int x){
    
    vector<int> elements;
    set<int> trackElements;
    srand(x);
    for(int i=0;i<numElements;i++){
        int x=rand();
        
        while(trackElements.find(x)!=trackElements.end()){
            x=rand();
       }
        elements.push_back(x);
        trackElements.insert(x);
    }
    return elements;
}












int main(int argc, const char * argv[]) {
    // insert code here...
    initFilter();
    calcRandoms();
    elementsA=generateNums(1);
    insert(elementsA);
    query(elementsA);
    cout<<"Lookup for A Elements="<<matchCount<<"\n";
    elementsB=generateNums(2);
    matchCount=0;
    query(elementsB);
    //cout<<"Number of 1's in Bloom"<<c<<"\n";
    cout<<"Lookup for B Elements="<<matchCount;
    
    return 0;
}
