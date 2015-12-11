%{
#include "CalcScanner.h"
#include <iostream>
using namespace std;
extern int nlines; //counting the name of lines
extern int ncol;
%}

%option nodefault yyclass="FlexScanner" noyywrap c++
DIGITO [0-9]
LETRA [a-zA-Z]
%%

"//".*$   { ncol += yyleng; /* do nothing */ }

{DIGITO}+ { ncol += yyleng; yylval->numeric = atoi(yytext);   
            return Calc::BisonParser::token::TKN_NUMINTEGER;}

{DIGITO}+("."{DIGITO}+)? { ncol += yyleng; yylval->numeric = atof(yytext); 
            return Calc::BisonParser::token::TKN_NUMREAL;}

"true"    { ncol += yyleng;  return Calc::BisonParser::token::TKN_TRUE;}
"false"   { ncol += yyleng;  return Calc::BisonParser::token::TKN_FALSE;}

"("       { ncol += yyleng;  return Calc::BisonParser::token::TKN_PA;}
")"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_PC;}
";"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_PTOCOMA;}
"="       { ncol += yyleng;  return Calc::BisonParser::token::TKN_ASSIGN;}

"sin"	  { ncol += yyleng;  return Calc::BisonParser::token::TKN_SIN;}
"cos"	  { ncol += yyleng;  return Calc::BisonParser::token::TKN_COS;}
"sqrt"	  { ncol += yyleng;  return Calc::BisonParser::token::TKN_SQRT;}
"^"	  { ncol += yyleng;  return Calc::BisonParser::token::TKN_POW;}

"*"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_MULT;}
"/"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_DIV;}
"+"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_MAS;}
"-"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_MENOS;}

"=="      { ncol += yyleng;  return Calc::BisonParser::token::TKN_EQUAL;}
"!="      { ncol += yyleng;  return Calc::BisonParser::token::TKN_NE;}
">="      { ncol += yyleng;  return Calc::BisonParser::token::TKN_GE;}
"<="      { ncol += yyleng;  return Calc::BisonParser::token::TKN_LE;}
">"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_GT;}
"<"       { ncol += yyleng;  return Calc::BisonParser::token::TKN_LT;}

"and"     { ncol += yyleng;  return Calc::BisonParser::token::TKN_AND;}
"or"      { ncol += yyleng;  return Calc::BisonParser::token::TKN_OR;}
"not"     { ncol += yyleng;  return Calc::BisonParser::token::TKN_NOT;}

"begin"   { ncol += yyleng;  return Calc::BisonParser::token::TKN_BEGIN;}
"end"     { ncol += yyleng;  return Calc::BisonParser::token::TKN_END;}

"bool"    { ncol += yyleng;  return Calc::BisonParser::token::TKN_BOOL;}
"integer" { ncol += yyleng;  return Calc::BisonParser::token::TKN_INT;}
"int"     { ncol += yyleng;  return Calc::BisonParser::token::TKN_INT;}
"double"  { ncol += yyleng;  return Calc::BisonParser::token::TKN_DBL;}
"const"  { ncol += yyleng;  return Calc::BisonParser::token::TKN_CONST;}

"write"   { ncol += yyleng;  return Calc::BisonParser::token::TKN_WRITE;}

{LETRA}({LETRA}|{DIGITO})* { ncol += yyleng; strcpy(yylval->chain,yytext);
	    return Calc::BisonParser::token::TKN_ID;}
[\r \t]   { ncol += yyleng; /* do nothing */ }
"\n"      { nlines++; 
	    ncol = 0;}
.         {  cout << "Line #" << nlines << " Column #" << ncol << " Lexical Error:" << endl;
             cout << "Char" << yytext << "does not match any token" << endl; }
