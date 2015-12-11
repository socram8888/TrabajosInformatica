import java_cup.runtime.*;
import java.io.*;

%%
%class LexicalAnalyzerMIPS
%unicode
%cup
%line
%column
	 
%{
int commdepth = 0;

private Symbol symbol(int type) {
   return new Symbol(type, yyline, yycolumn);
}
private Symbol symbol(int type, Object value) {
   return new Symbol(type, yyline, yycolumn, value);
}
%}

VarName = [A-Za-z_]{1,8}
Integer = 0|[1-9][0-9]*
Blank = [\r\n\t ]

%%
"/*"        { commdepth++; }
"*/"        { if (commdepth > 0) commdepth--; }

"leer"      { if (commdepth == 0) return symbol(sym.LEER); }
"mostrar"   { if (commdepth == 0) return symbol(sym.MOSTRAR); }
"<-"        { if (commdepth == 0) return symbol(sym.ASSIGN); }
"while"     { if (commdepth == 0) return symbol(sym.WHILE); }
"if"        { if (commdepth == 0) return symbol(sym.IF); }

"{"         { if (commdepth == 0) return symbol(sym.BROPEN); }
"}"         { if (commdepth == 0) return symbol(sym.BRCLOSE); }

"("         { if (commdepth == 0) return symbol(sym.PAROPEN); }
")"         { if (commdepth == 0) return symbol(sym.PARCLOSE); }

"*"         { if (commdepth == 0) return symbol(sym.MUL); }
"/"         { if (commdepth == 0) return symbol(sym.DIV); }
"%"         { if (commdepth == 0) return symbol(sym.MOD); }

"+"         { if (commdepth == 0) return symbol(sym.ADD); }
"-"         { if (commdepth == 0) return symbol(sym.SUB); }

"=="        { if (commdepth == 0) return symbol(sym.EQUALS); }
">="        { if (commdepth == 0) return symbol(sym.GREATER_EQUALS); }
"<="        { if (commdepth == 0) return symbol(sym.LESSER_EQUALS); }
">"        { if (commdepth == 0) return symbol(sym.GREATER); }
"<"        { if (commdepth == 0) return symbol(sym.LESSER); }

";"         { if (commdepth == 0) return symbol(sym.TERM); }

{VarName}   { if (commdepth == 0) return symbol(sym.VAR, yytext()); }
{Integer}   { if (commdepth == 0) return symbol(sym.INT, Integer.parseInt(yytext())); }

{Blank}     {}

.			{ throw new RuntimeException("Invalid syntax"); }
