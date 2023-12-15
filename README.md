# Shared Memory Cpp to Python  

## Dependencies  
System V IPC  
> Python : `pip install sysv_ipc`  

Google Protocol Buffer C++ and Python Extension  
> C++ : Build from Ofiicial github repository source.  
> Python : `pip install protobuf`  

## Usage  
1. Change directory om terminal. `cmake .`  
2. `make` and `./run`  
3. Execute test.py 

## Description  
Implementation of inter-process communication by using System V based shared memory.  

C++ : Create shared memory and write the data.   
Python : Read shared memory and get the data.  
Google Protocol Buffer : Serialize and Deserialize mesh data to binary string for using shared memory.  
