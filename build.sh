#!/bin/bash
g++ -Wall -g -O0 -c util.cpp
g++ -Wall -g -O0 -c ep1.cpp
g++ -Wall -g -O0 -c unit_test2.cpp
g++ util.o ep1.o unit_test2.o -o unit_test2 -lm
