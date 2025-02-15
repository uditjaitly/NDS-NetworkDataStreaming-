//
//  main.cpp
//  counterSketch
//
//  Created by Udit Jaitly on 23/10/20.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <math.h>
using namespace std;
#define MAXN 3000;
vector<string> ipAddresses;
vector<float> size;
vector<long> ipToNumbers;
vector<int> randomNums;
vector<vector<int>> counters(3,vector<int>(3000,0));
vector<float> errors;


struct ds{
    string flowId;
    long estSize;
    long trueSize;
    
};
vector<ds> info;

float total;
int hashNums=3;
float totalError=0;
float avgError;
bool neg;

void generateRandoms(){
    for(int i =0; i<hashNums;i++){
 
        randomNums.push_back(rand());
    }
}

void estimate(){
    for(int i=0;i<ipAddresses.size();i++){
        vector<long> hashVals;
        float error;
        for(int j=0;j<hashNums;j++){
            int val= (abs(ipToNumbers[i])^abs(randomNums[j]))%MAXN;
            hashVals.push_back(counters[j][val]);
            long long int test=abs(ipToNumbers[i])^abs(randomNums[j]);
            string binary = std::bitset<32>(test).to_string();
            if(binary[1]=='0'){
                hashVals[j]=abs(hashVals[j]);
            }
        }
        sort(hashVals.begin(),hashVals.end());
        info.push_back(ds());
        info[i].flowId=ipAddresses[i];
        info[i].estSize=hashVals[1];
        info[i].trueSize=size[i];
        
        error=abs(hashVals[1]-size[i]);
        errors.push_back(error);
        totalError=totalError+error;
    }
}

bool compareByEstSize(const ds &a, const ds &b)
{
    return a.estSize > b.estSize;
}



void record(){
    for(int i=0;i<ipToNumbers.size();i++){
        vector<int> hashVals;
        for(int j=0;j<hashNums;j++){
            if((ipToNumbers[i]^randomNums[j])<0){
                neg=true;
            }
            else{
                neg=false;
            }
            long long int test=abs(ipToNumbers[i])^abs(randomNums[j]);
            string binary = std::bitset<32>(test).to_string();
            //cout<<"Binary="<<binary<<"\n";
            int val= (abs(ipToNumbers[i])^abs(randomNums[j]))%MAXN;
            hashVals.push_back(val);
            if(binary[1]=='1' ){
                counters[j][val]=counters[j][val]+size[i];
                
            }
            else{
                counters[j][val]=counters[j][val]-size[i];
            }
        }
    }
}



void readInput(){
    ifstream inputFile;
    inputFile.open("project3input.txt");
    string word;
    
    int k=0;
    if(inputFile.is_open()){
        while (inputFile >> word) {
            k++;
            if(k>1 && k%2==0){
                ipAddresses.push_back(word);
            }
            else if(k>1){
                size.push_back(stoi(word));
            }
            else if(k==0){
                total=stoi(word);
            }
        }
    }
}


void convertAddresses(vector<string> ipAddresses){
    long curr=0;
    string token;
    for(int i=0;i<ipAddresses.size();i++){
        vector<int> tempNums;
        while ((curr = ipAddresses[i].find(".")) != std::string::npos) {
            token = ipAddresses[i].substr(0, curr);
            //std::cout << token << std::endl;
            tempNums.push_back(stoi(token));

            ipAddresses[i].erase(0, curr + 1);
        }
        tempNums.push_back(stoi(ipAddresses[i]));
        int temp = 0;
        temp = ((tempNums[0]*255 + tempNums[1])*255 + tempNums[2])*255 + tempNums[3]+10000000000;
        //cout<<temp<<"\n";
        //cout<<tempNums[3]<<"\n";

        ipToNumbers.push_back(temp);
    }
}


int main(int argc, const char * argv[]) {
    readInput();
    convertAddresses(ipAddresses);
    generateRandoms();
    record();
    estimate();
    avgError=totalError/10000;
    
    cout<<"Average Error="<<avgError<<"\n";
    sort(info.begin(), info.end(), compareByEstSize);
    for(int i=0;i<100;i++){
        cout<<"FlowId="<<info[i].flowId<<" EstimatedSize="<<info[i].estSize<<" "<<"TrueSize="<<info[i].trueSize<<"\n";
    }
    //cout<<ipAddresses[0];
    return 0;
}
