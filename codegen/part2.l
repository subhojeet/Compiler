
L			[a-zA-Z_]

%{
#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<iostream>
#include "codegen.tab.h"


using namespace std;
%}
%%
[i][f] {return(IF);}
[g][o][t][o] {return(GOTO);}
"v0"		{return(V0);}
"funcend :" 	{return(FUNCEND);}
"funcbegin" 	{return(FUNCBEGIN);}
"return"    {return(RETURN);}
"pushArgs"	{return(PUSHARGS);}
"call"		{return(CALL);}
"ParamsNum:"	{return(PARAMSNUM);}
"outint"	{return(OUTINT);}
"inint"		{return(ININT);}
"outfloat"	{return(OUTFLOAT);}
"infloat"		{return(INFLOAT);}
"outstr"	{return(OUTSTRING);}
"instr"		{return(INSTRING);}

[a-zA-z]+[a-zA-z0-9]* {return(ID);}


"==" {return(BINARY_OPERATORS);};
[-+*/<>%] {cout<<"binary"<<endl; return(BINARY_OPERATORS);}
[0-9]+ {return(NUM);}
[=] {return(EQ);}
[&] {return(ANDP);}
[a-zA-z]+[a-zA-z0-9]*[:] {return(LABEL);}
L?\"(\\.|[^\\"])*\"	{  return(STR_LIT); }
(.|\n)
%%
int yywrap()
{
	return 1;
}