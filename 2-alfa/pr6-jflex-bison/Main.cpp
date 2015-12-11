#include "CalcScanner.h"
#include "CalcParser.h"
#include "Symbol.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;


map <string, symbol> Table;

// Entry Point
int main(int argc, char * argv[]) {
symbol s;

  //declaring the Parser
  Calc::Parser parser;
  //starting the sintactic analysis
  parser.parse();
  
  

  return 0;
}

