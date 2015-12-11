#!/bin/bash -e
echo "Bison"
bison --warnings=none Calc.y
echo "Flex"
flex Calc.l
echo "G++"
g++ -Wall -o calc lex.yy.cc Calc.tab.c Main.cpp Symbol.cpp
