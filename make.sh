#!/bin/bash
clear
g++ -std=c++17 -Wall -Wextra -Werror main.cpp bit_operations.cpp file_operations.cpp box.cpp fraction.cpp -o app
./app
