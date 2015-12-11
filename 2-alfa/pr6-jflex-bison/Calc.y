%require "2.4.1"
%skeleton "lalr1.cc"
%defines
%define namespace "Calc"
%define parser_class_name "BisonParser"
%parse-param { Calc::FlexScanner &scanner}
%lex-param   { Calc::FlexScanner &scanner }


%code {
#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include "Symbol.h"

using namespace std;
extern map <string, symbol> Table;
int nlines = 1; //number of lines
int ncol = 0;

int assigns = 0;
int sums = 0;
int subs = 0;
int muls = 0;
int divs = 0;
}

%code requires {
// Forward-declare the Scanner class; the Parser needs to be assigned a 
// Scanner, but the Scanner can't be declared without the Parser
namespace Calc {
class FlexScanner; }
}

%code {
// Definiton for the yylex function
static int yylex(Calc::BisonParser::semantic_type * yylval, 
Calc::FlexScanner &scanner);
}

%union { //list of types that can be stored in the symbols of the grammar
char chain[16]; //maximum size for name of the IDs
double numeric;
}

// Axiom
%start Program  

// List of Terminal Symbols
%token  TKN_PA
%token  TKN_PC
%token  TKN_PTOCOMA

%token  TKN_MAS
%token  TKN_MENOS
%token  TKN_MULT
%token  TKN_DIV
%token 	TKN_SIN
%token 	TKN_COS
%token 	TKN_POW
%token 	TKN_SQRT

%token  TKN_ASSIGN

%token <chain> 		TKN_ID
%token <numeric> 	TKN_NUMINTEGER
%token <numeric> 	TKN_NUMREAL
%token <numeric> 	TKN_TRUE
%token <numeric> 	TKN_FALSE

%token 	TKN_EQUAL
%token 	TKN_NE
%token 	TKN_GT
%token 	TKN_LT
%token 	TKN_GE
%token 	TKN_LE

%token 	TKN_AND
%token 	TKN_OR
%token 	TKN_NOT

%token	TKN_BEGIN
%token  TKN_END
%token  TKN_INT
%token 	TKN_WRITE
%token 	TKN_BOOL
%token 	TKN_DBL
%token  TKN_CONST

//List of non-terminals

%type <numeric> Program
%type <numeric> DeclarationList
%type <numeric> DeclVars
%type <numeric> Type
%type <numeric> StmtList
%type <numeric> AssignStmt
%type <numeric> WriteStmt
%type <numeric> Constant
%type <numeric> E

//Defining precedence and associativy of operators

%nonassoc TKN_EQUAL TKN_NE TKN_LE TKN_GE TKN_LT TKN_GT

%left TKN_AND TKN_OR
%left TKN_NOT

%left TKN_MAS TKN_MENOS
%left TKN_MULT TKN_DIV
%left TKN_POW
%left TKN_SIN TKN_COS TKN_SQRT

%%
//Listing the productions
Program : DeclarationList TKN_BEGIN StmtList TKN_END
{
  //printing the Symbol Table when the list of sentences is finished
  map <string,symbol>::iterator i;
  cout << "SYMBOL TABLE" << endl;
  cout << "------------" << endl;
  cout << "NAME        VALUE" << endl;
  for (i=Table.begin();i!=Table.end();i++)
    cout  << (*i).first << "            " << (*i).second << endl; 
  cout << endl;
  cout << "STATISTICS" << endl;
  cout << "----------" << endl;
  cout << "Total assignments:     " << assigns << endl;
  cout << "Total additions:       " << sums << endl;
  cout << "Total substractions:   " << subs << endl;
  cout << "Total multiplications: " << muls << endl;
  cout << "Total divisions:       " << divs << endl;
};

DeclarationList : DeclVars DeclarationList | ;

DeclVars  : TKN_CONST Type TKN_ID TKN_ASSIGN Constant TKN_PTOCOMA {
  if (Table[$3].getType() != 0) {
    error(yylloc, "Variable already defined");
    YYABORT;
  }

  symbol s;
  s.putType($2);
  s.putValue($5);
  s.setConst(true);
  Table[$3] = s;
} |
Type TKN_ID TKN_PTOCOMA {
  if (Table[$2].getType() != 0) {
    error(yylloc, "Variable already defined");
    YYABORT;
  }

  symbol s;
  s.putType($1);
  Table[$2] = s;
};

Type : TKN_BOOL { $$ = 1; } | TKN_INT {$$ = 2;} | TKN_DBL { $$ = 3; };

StmtList : Stmt TKN_PTOCOMA  StmtList | ;

Stmt : AssignStmt | WriteStmt ;

AssignStmt :  TKN_ID  TKN_ASSIGN  E  { 
  symbol s;
  s = Table[$1];

  if (s.getType() == 0) {
    error(yylloc, "assignment to undefined variable");
    YYABORT;
  }

  if (!s.putValue($3)) {
    error(yylloc, "invalid type assigned to variable");
    YYABORT;
  }

  if (s.isConst()) {
    error(yylloc, "cannot assign variable to constant");
    YYABORT;
  }

  assigns++;
  Table[$1]=s;
} | TKN_ID  TKN_MAS TKN_ASSIGN  E  { 
  symbol s;
  s = Table[$1];

  if (s.getType() == 0) {
    error(yylloc, "assignment to undefined variable");
    YYABORT;
  }

  if (!s.putValue(s.getValue()+$4)) {
    error(yylloc, "invalid type assigned to variable");
    YYABORT;
  }

  if (s.isConst()) {
    error(yylloc, "cannot assign variable to constant");
    YYABORT;
  }

  sums++;
  assigns++;
  Table[$1]=s;
} | TKN_ID  TKN_MENOS TKN_ASSIGN  E  { 
  symbol s;
  s = Table[$1];

  if (s.getType() == 0) {
    error(yylloc, "assignment to undefined variable");
    YYABORT;
  }

  if (!s.putValue(s.getValue()-$4)) {
    error(yylloc, "invalid type assigned to variable");
    YYABORT;
  }

  if (s.isConst()) {
    error(yylloc, "cannot assign variable to constant");
    YYABORT;
  }
  
  subs++;
  assigns++;
  Table[$1]=s;
} | TKN_ID  TKN_MULT TKN_ASSIGN  E  { 
  symbol s;
  s = Table[$1];

  if (s.getType() == 0) {
    error(yylloc, "assignment to undefined variable");
    YYABORT;
  }

  if (!s.putValue(s.getValue()*$4)) {
    error(yylloc, "invalid type assigned to variable");
    YYABORT;
  }

  if (s.isConst()) {
    error(yylloc, "cannot assign variable to constant");
    YYABORT;
  }

  
  assigns++;
  muls++;
  Table[$1]=s;
} | TKN_ID  TKN_DIV TKN_ASSIGN  E  { 
  symbol s;
  s = Table[$1];

  if (s.getType() == 0) {
    error(yylloc, "assignment to undefined variable");
    YYABORT;
  }

  if (!s.putValue(s.getValue()/$4)) {
    error(yylloc, "invalid type assigned to variable");
    YYABORT;
  }

  if (s.isConst()) {
    error(yylloc, "cannot assign variable to constant");
    YYABORT;
  }

  
  assigns++;
  divs++;
  Table[$1]=s;
};

WriteStmt : TKN_WRITE TKN_ID {
  symbol s;
  s = Table[$2];

  if (s.getType() == 0) {
    error(yylloc, "write of undefined variable");
    YYABORT;
  }

  cout << "Valor de " << $2 << ": " << s << endl;
};

//Factors
E : Constant | 
TKN_ID { 
     symbol s = Table[$1];
     if (s.getType() == 0) {
       error(yylloc, "access to undefined variable");
       YYABORT;
     }
     $$=s.getValue();
};

// Constant
Constant : TKN_NUMREAL {$$ = $1;} | 
TKN_NUMINTEGER {$$ = $1;} | 
TKN_TRUE {$$=1;} | 
TKN_FALSE {$$=0;};

//Aritmetic operators
E: E TKN_MAS E {sums++; $$=$1+$3;}|
E TKN_MENOS E {subs++; $$=$1-$3;} |
E TKN_DIV E {divs++; $$=$1/$3;} |
E TKN_MULT E {muls++; $$=$1*$3;} |
TKN_PA E TKN_PC {$$=$2;}|
E TKN_POW E {$$=pow($1,$3);};

// Functions
E: TKN_SIN TKN_PA E TKN_PC {$$=sin($3);}|
TKN_COS TKN_PA E TKN_PC {$$=cos($3);}|
TKN_SQRT TKN_PA E TKN_PC {$$=sqrt($3);};


//Boolean operators
E : E TKN_AND E {
if ($1==1 && $3==1)
  $$=1;
else 
  $$=0;} |
E TKN_OR E { $$=$1||$3;} |
TKN_NOT E {$$=!$2;};

//Realtional Operators

E : E TKN_EQUAL E {
if ($1 == $3)
  $$=1;
else 
  $$=0;} |
E TKN_NE E {$$=$1!=$3;} |
E TKN_GT E {$$=$1>$3;} |
E TKN_LT E {$$=$1<$3;} |
E TKN_GE E {$$=$1>=$3;} |
E TKN_LE E {$$=$1<=$3;};

%% 
// Auxiliar Code

// Implementation of the error function
void Calc::BisonParser::error(const Calc::BisonParser::location_type &loc, 
const std::string &msg) {
std::cerr << "Line: " << nlines << " Column: " << ncol << " " << msg << "." << std::endl;
}

// Implementation of the Scanner 
#include "CalcScanner.h"
static int yylex(Calc::BisonParser::semantic_type * yylval, 
Calc::FlexScanner &scanner) {
  return scanner.yylex(yylval);
}
