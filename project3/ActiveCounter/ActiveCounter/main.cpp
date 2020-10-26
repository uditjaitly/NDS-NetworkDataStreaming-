//
//  main.cpp
//  ActiveCounter
//
//  Created by Udit Jaitly on 26/10/20.
//

#include <iostream>


using namespace std;
  
long long int num=0;
long long int expo=0;
float probability;
int binaryToDecimal(long long int n)
{
    long long int num = n;
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    long long int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    }
 
    return dec_value;
}

long long int decimalToBinary(long long int N)
{
  
    // To store the binary number
    unsigned long long int binary = 0;
    int cnt = 0;
    while (N != 0) {
        int rem = N % 2;
        unsigned long long int c = pow(10, cnt);
        binary += rem * c;
        N /= 2;
  
        // Count used to store exponent value
        cnt++;
    }
  
    return binary;
}




long long int addOne(long long int r)
{
    int m = 1;
    // Flip all the set bits
    // until we find a 0
    while( r & m )
    {
        r = r ^ m;
        m <<= 1;
    }
    // flip the rightmost 0 bit
    r = r ^ m;
    r=decimalToBinary(r);
    return r;
}

int countDigit(long long int n)
{
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}


int main(int argc, const char * argv[]) {
    
    // insert code here...
    
    for(int i=0;i<1000000;i++){
        
        probability=(1/pow(2,binaryToDecimal(expo)));
        srand(i);
        int randNum=rand() % 100 ;
        if(randNum>=0 && randNum<(probability*100)){
            num=addOne(binaryToDecimal(num));
        }
        if(countDigit(num)>16){
            num=binaryToDecimal(num)>>1;
            num=decimalToBinary(num);
            expo=addOne(binaryToDecimal(expo));
        }
        
    }
    cout<<num<<"\n";
    cout<<expo;
    std::cout << "Hello, World!\n";
    return 0;
}
