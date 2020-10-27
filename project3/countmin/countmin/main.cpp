//
//  main.cpp
//  countmin
//
//  Created by Udit Jaitly on 22/10/20.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 3000;
vector<string> ipAddresses;
vector<float> size;
vector<long> ipToNumbers;
vector<int> randomNums;
vector<vector<int>> counters(3,vector<int>(3000,0));
vector<float> errors;
float total;
int hashNums=3;
float totalError=0;
float avgError;
void generateRandoms(){
    for(int i =0; i<hashNums;i++){
        randomNums.push_back(rand());
    }
}
struct ds{
    string flowId;
    int estSize;
    int trueSize;
};
vector<ds> info;

bool compareByEstSize(const ds &a, const ds &b)
{
    return a.estSize > b.estSize;
}
void estimate(){
    for(int i=0;i<ipAddresses.size();i++){
        vector<int> hashVals;
        float min=99999999;
        float error;
        for(int j=0;j<hashNums;j++){
            int val= (ipToNumbers[i]^randomNums[j])%MAXN;
            hashVals.push_back(val);
            if(min>counters[j][val]){
                min=counters[j][val];
            }
        }
        info.push_back(ds());
        info[i].estSize=min;
        info[i].flowId=ipAddresses[i];
        info[i].trueSize=size[i];
        error=(min-size[i]);
        errors.push_back(error);
        totalError=totalError+error;
    }
}

void record(){
    for(int i=0;i<ipToNumbers.size();i++){
        vector<int> hashVals;
        for(int j=0;j<hashNums;j++){
            int val= (ipToNumbers[i]^randomNums[j])%MAXN;
            hashVals.push_back(val);
            counters[j][val]=counters[j][val]+size[i];
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
        unsigned int temp = 0;
        temp = ((tempNums[0]*255 + tempNums[1])*255 + tempNums[2])*255 + tempNums[3];
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
    sort(info.begin(),info.end(),compareByEstSize);
    for(int i=0;i<100;i++){
        cout<<"FlowId="<<info[i].flowId<<" EstimatedSize="<<info[i].estSize<<" "<<"TrueSize="<<info[i].trueSize<<"\n";
    }
    //cout<<ipAddresses[0];
    return 0;
}
