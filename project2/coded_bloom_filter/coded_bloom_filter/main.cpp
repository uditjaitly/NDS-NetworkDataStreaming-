//
//  main.cpp
//  coded_bloom_filter
//
//  Created by Udit Jaitly on 16/10/20.
//
#include <iostream>
#include <vector>
#include <set>
#define MAXN 30000
using namespace std;
//vector<int> bloomFilter;
vector<vector<int>> allBloomFilters(3,vector<int>(30000,0));
vector<int> randomNums;
vector<int> elementsA;
vector<int> elementsB;
vector<vector<int>> codes{{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
vector<vector<int>> sets;
int numHashes=7;
int numOfSets=7;
int matchCount=0;
int numElements=1000;
int c=0;
int numOfBloomFilters=3;
int falsePositive=0;


void initAllBloomFilters(){
    
    for(int i=0;i<numOfBloomFilters;i++){
        vector<int> bloomfilter;
        for(int j=0;i<MAXN;j++){
            bloomfilter.push_back(0);
        }
        allBloomFilters.push_back(bloomfilter);
    }
}


void calcRandoms(){
    for(int i=0;i<numHashes;i++){
        randomNums.push_back(rand());
    }
}



void insert(vector<int> set,int curr){
    for(int k=0;k<numOfBloomFilters;k++){
        if(codes[curr][k]==1){
            
       
            for(int i=0;i<set.size();i++){
                vector<int> hashValues;

                for(int j=0;j<numHashes;j++){
                   
                    hashValues.push_back((randomNums[j]^set[i])%MAXN);
                    if(allBloomFilters[k][hashValues[j]]==0){
                        allBloomFilters[k][hashValues[j]]=1;
                        c++;
                    }
                }
            }
        }
    }
}


void query(vector<int> set,int curr){
   
    for(int i=0;i<set.size();i++){
        vector<int> elementCode;
        int flag=0;
        for(int k=0;k<numOfBloomFilters;k++){
            int count=0;
            vector<int> hashValues;
            for(int j=0;j<numHashes;j++){
                hashValues.push_back((randomNums[j]^set[i])%MAXN);
                if(allBloomFilters[k][hashValues[j]]==1){
                    count++;
                }
            }
            
            if (count==numHashes){
                
                elementCode.push_back(1);
                
            }
            else{
                elementCode.push_back(0);
            }
            
        }
        for(int i=0 ; i< elementCode.size();i++){
            if(elementCode[i]!=codes[curr][i]){
                flag=1;
            }
            
        }
        if(flag==0){
            matchCount++;
        }
    }
    
    
    
    
    
    
}


void generateSets(){
    
    
    for(int j=0;j<numOfSets;j++){
        vector<int> elements;
        set<int> trackElements;
        srand(j);
        for(int i=0;i<numElements;i++){
            int x=rand();
            
            while(trackElements.find(x)!=trackElements.end()){
                x=rand();
           }
            elements.push_back(x);
            trackElements.insert(x);
        }
        sets.push_back(elements);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //initAllBloomFilters();
    calcRandoms();
    generateSets();
    
    for(int i = 0;i < numOfSets;i++){
        insert(sets[i],i);
    }
    for(int i = 0;i < numOfSets;i++){
        query(sets[i],i);
    }
    
    int totalCorrectLookups=matchCount;
    cout<<"Correct Lookups"<<totalCorrectLookups;
    
    return 0;
}

