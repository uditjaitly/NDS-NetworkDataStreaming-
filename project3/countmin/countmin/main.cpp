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
vector<int> size;
vector<long> ipToNumbers;
vector<int> randomNums;
vector<vector<int>> counters(3,vector<int>(3000,0));
vector<int> errors;
long total;
int hashNums=3;
long totalError=0;
void generateRandoms(){
    for(int i =0; i<hashNums;i++){
        randomNums.push_back(rand());
    }
}

void estimate(){
    for(int i=0;i<ipAddresses.size();i++){
        vector<int> hashVals;
        int min=99999999;
        int error;
        for(int j=0;j<hashNums;j++){
            int val= (ipToNumbers[i]^randomNums[j])%MAXN;
            hashVals.push_back(val);
            if(min>counters[j][val]){
                min=counters[j][val];
            }
        }
        error=(min-size[i])/min;
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
        cout<<temp<<"\n";
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
    cout<<"HERE";
    //cout<<ipAddresses[0];
    return 0;
}
