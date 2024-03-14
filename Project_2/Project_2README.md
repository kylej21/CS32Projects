# Map class
This is a project made for UCLA CS32. This project is a self made implementation of a Map, using linkedLists under the hood. 

# Overview
This software utilizes linkedlists to implement a Map class with implementation of common member functions like insert, erase, size, etc. Later, in Homework_5, this class was updated to use templates, but in this version it maps whatever data types you put as KeyType and ValueType in the header file. It is by default mapping doubles to strings. There is also a brief test.cpp file, to prove some of the functions do work.

# How to use
Since this is a class, you can use it by writing include "oldMap.h" if the header and cpp file are in the directory with your code. When you compile, make sure to compile oldMap.cpp as well.
-- To run the test file with g++, write "g++ -o test test.cpp oldMap.cpp" -> then -> ./test 

