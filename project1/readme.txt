Project 1

This project consists of implementations of the following in C++

1. Cuckoo Hashing
2. D-Left-Hashing
3. Multi-Hashing

The programs run using the inputs provided in the project description. The value for each input can be changed at the first few lines of main.cpp for each program:
1. The size of table can be changed by changing value of MAXN (Default val=1000)
2. The number of flow values can be changed by changing the value of variable ‘num_of_flows’. (Default val=1000)
3. The number of hash functions can be changed by changing the value of variable ‘num_hash’ (Default val=4 for D-Left Hashing) (Default val=3 for Cuckoo and Multi Hashing)
4. The cuckoo step limit can be changed by changing the value of variable ‘cuckoo_step’. (Default val =2)

The final number of flows in the table for each program will be the same every time we run the program. This is because I have used seeded randomisers when generating random numbers in my program.