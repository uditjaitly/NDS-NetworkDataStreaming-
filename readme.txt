{\rtf1\ansi\ansicpg1252\cocoartf2513
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww28600\viewh18000\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Project 1\
\
This project consists of implementations of the following in C++\
\
1. Cuckoo Hashing\
2. D-Left-Hashing\
3. Multi-Hashing\
\
The programs run using the inputs provided in the project description. The value for each input can be changed at the first few lines of main.cpp for each program:\
1. The size of table can be changed by changing value of MAXN (Default val=1000)\
2. The number of flow values can be changed by changing the value of variable \'91num_of_flows\'92. (Default val=1000)\
3. The number of hash functions can be changed by changing the value of variable \'91num_hash\'92 (Default val=4 for D-Left Hashing) (Default val=3 for Cuckoo and Multi Hashing)\
4. The cuckoo step limit can be changed by changing the value of variable \'91cuckoo_step\'92. (Default val =2)\
\
The final number of flows in the table for each program will be the same every time we run the program. This is because I have used seeded randomisers when generating random numbers in my program.}