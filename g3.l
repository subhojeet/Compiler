DIGIT		[0-9]
HEX			[a-fA-F0-9]	
LETTER		[a-zA-Z_]
stringLit			\"([^\"]|\\.)*\"
charLit			\'([^\']|\\.)?\'

E 			[Ee][+-]?{DIGIT}+
FS 			(f|F|l|L)
IS 			(u|U|l|L)*


%{

#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()

#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
	
#include "g3.tab.h"



extern int row, col;			// To keep track of row and column number
extern bool eof;
static void calc();
void comment();
extern YYLTYPE yylloc;

//int yyleng;			// To keep track of colomn NUMBER
//char* yytext;			// To show erroneous pattern
void eat_to_newline(void);

int yyparse();


int line_no = 1;
int col_no = 1;
void pre_update();
void post_update();

	


%}


%x COMMENTS COMMENT


%%

"//"						{ col_no += yyleng; BEGIN(COMMENT); 						}
<COMMENT>\n 				{ line_no++; col_no = 1; /*printf("COMMENT ");*/BEGIN(INITIAL); }
<COMMENT>.					{ col_no++;													}

"/*"						{ col_no += yyleng; BEGIN(COMMENTS); 						}
<COMMENTS>"*/"				{ col_no += yyleng; /*printf("COMMENT ");*/ BEGIN(INITIAL); 	}
<COMMENTS>\n				{ line_no++; col_no = 1; 									}
<COMMENTS>.					{ col_no++;													}

"include"	{	pre_update(); col_no += yyleng; calc();post_update();/*printf("INCLUDE\n");*/ return(INCLUDE);			}
"break"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("BREAK\n");*/ return(BREAK);			}
"bool"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("BOOL\n");*/ return(BOOL);			}
"case"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("CASE\n");*/ return(CASE);			}
"char"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("CHAR\n");*/ return(CHAR);			}
"continue"	{	pre_update(); col_no += yyleng; calc();post_update();/*printf("CONTINUE\n");*/ return(CONTINUE);		}
"otwise"	{	pre_update(); col_no += yyleng; calc();post_update();/*printf("OTHERWISE\n");*/ return(OTHERWISE);		}
"do"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("DO\n");*/ return(DO);				}
"elif"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("ELIF\n");*/ return(ELIF);			}
"else"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("ELSE\n");*/ return(ELSE);			}
"exit"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("EXIT\n");*/ return(EXIT);			}
"true"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("TRUE\n");*/ yylval.bool_val=true; return(BOOLEAN);			}
"false"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("FALSE\n");*/ yylval.bool_val=false;return(BOOLEAN);			}
"float"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("FLOAT\n");*/ return(FLOAT);			}
"for"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("FOR\n");*/ return(FOR);				}
"if"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("IF\n");*/ return(IF);				}
"int"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("INT\n");*/ return(INT);				}
"return"	{	pre_update(); col_no += yyleng; calc();post_update();/*printf("RETURN\n");*/ return(RETURN);			}
"switch"	{	pre_update(); col_no += yyleng; calc();post_update();/*printf("SWITCH\n");*/ return(SWITCH);			}
"typedef"	{	pre_update(); col_no += yyleng; calc();post_update();/*printf("TYPEDEF\n");*/ return(TYPEDEF);			}
"void"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("VOID\n");*/ return(VOID);			}
"while"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("WHILE\n");*/ return(WHILE);			}
"main"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("MAIN\n");*/ return(MAIN);			}
"getInt"     {   pre_update(); col_no += yyleng; calc();post_update();/*printf("IN\n");*/ return(GETINT);           }
"getString"       {   pre_update(); col_no += yyleng; calc();post_update();/*printf("OUT\n");*/ return(GETSTRING);  }
"getFloat"     {   pre_update(); col_no += yyleng; calc();post_update();/*printf("IN\n");*/ return(GETFLOAT);         }
"printString"       {   pre_update(); col_no += yyleng; calc();post_update();/*printf("OUT\n");*/ return(PRINTSTR); }
"printInt"     {   pre_update(); col_no += yyleng; calc();post_update();/*printf("IN\n");*/ return(PRINTINT);       }
"printFloat"       {   pre_update(); col_no += yyleng; calc();post_update();/*printf("OUT\n");*/ return(PRINTFLOAT);}

"res_str"       {   pre_update(); col_no += yyleng; calc();post_update();/*printf("RESSTR\n");*/ return(RES_STR);}

"#"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("HASH\n");*/ return('#');				}
"+="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("ADD_ASS\n");*/ return(ADD_ASS);	/*assignment operators*/		}
"-="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("SUB_ASS\n");*/ return(SUB_ASS);			}
"*="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("MUL_ASS\n");*/ return(MUL_ASS);			}
"/="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("DIV_ASS\n");*/ return(DIV_ASS);			}
"%="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("MOD_ASS\n");*/ return(MOD_ASS);			}
"&="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("AND_ASS\n");*/ return(AND_ASS);			}
"^="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("XOR_ASS\n");*/ return(XOR_ASS);			}
"|="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("OR_ASS\n");*/ return(OR_ASS);			}

"++"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("INCR\n");*/ return(INCR);			}
"--"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("DECR\n");*/ return(DECR);			}

"<="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("LESS_EQ_OP\n");*/ return(LESS_EQ_OP);		}
">="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("GREAT_EQ_OP\n");*/ return(GREAT_EQ_OP);		}
"=="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("EQEQ_OP\n");*/ return(EQEQ_OP);			}
"<"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("LESS_OP\n");*/ return(LESS_OP);			}
">"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("GREAT_OP\n");*/ return(GREAT_OP);		}
"!="		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("NOTEQ_OP\n");*/ return(NOTEQ_OP);		}

"&&"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("AND_OP\n");*/ return(AND_OP);			}
"||"		{	pre_update(); col_no += yyleng; calc();post_update();/*printf("OR_OP\n");*/ return(OR_OP);			}

";"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("SEMI_COMMA\n");*/ return(';');		}
","			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("COMMA\n");*/ return(',');			}

"{"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("LCB\n");*/ return('{');				}
"}"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("RCB\n");*/ return('}');				}
"("			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("LOB\n");*/ return('(');				}
")"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("ROB\n");*/ return(')');				}
"["			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("LSB\n");*/ return('[');				}
"]"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("RSB\n");*/ return(']');				}
":"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("COLON\n");*/ return(':');			}
"="			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("EQUAL\n");*/ return('=');			}

"."			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("DOT\n");*/ return('.');				}

"&"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("BAND\n");*/ return('&');			}
"|"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("BOR\n");*/ return('|');				}
"^"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("BXOR\n");*/ return('^');			}
"!"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("NOT\n");*/ return('!');				}
"~"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("NEG\n");*/ return('~');				}
"+"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("PLUS\n");*/ return('+');			}
"-"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("MINUS\n");*/ return('-');			}
"*"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("MUL\n");*/ return('*');				}
"/"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("DIV\n");*/ return('/');				}
"%"			{	pre_update(); col_no += yyleng; calc();post_update();/*printf("MOD\n");*/ return('%');				}



[\n]		{ 	line_no++; col_no = 1; calc();																				}
[ \t]		{	col_no+=yyleng; 																							}
{LETTER}({LETTER}|{DIGIT})* 	{	pre_update(); col_no += yyleng; calc();post_update();  yylval.string_val = strdup(yytext);/*printf("ID\n");*/ return(ID);				}

0[xX]{HEX}+{IS}? 				{	pre_update(); col_no += yyleng; calc();post_update();/*printf("NUMBER\n");*/ return(NUMBER);			}
0{DIGIT}+{IS}? 					{	pre_update(); col_no += yyleng; calc();post_update();/*printf("NUMBER\n");*/ return(NUMBER);			}
{DIGIT}+{IS}? 					{	pre_update(); col_no += yyleng; calc();post_update();yylval.int_val = atoi(strdup(yytext));/*printf("NUMBER\n");*/ return(NUMBER);			}
{DIGIT}+{E}{FS}? 				{	pre_update(); col_no += yyleng; calc();post_update();yylval.int_val = atoi(strdup(yytext));/*printf("NUMBER\n");*/ return(NUMBER);			}
{DIGIT}*"."{DIGIT}+({E})?{FS}?	{	pre_update(); col_no += yyleng; calc();post_update();yylval.float_val = atof(strdup(yytext));/*printf("NUMBER\n");*/ return(DECIMAL);			}
{DIGIT}+"."{DIGIT}*({E})?{FS}? 	{	pre_update(); col_no += yyleng; calc();post_update();yylval.float_val = atof(strdup(yytext));/*printf("NUMBER\n");*/ return(DECIMAL);			}
{charLit}						{	pre_update(); col_no += yyleng; calc();post_update(); yylval.char_val = yytext[1];/*printf("CHAR_LIT\n");*/ return(CHAR_LIT);		}
{stringLit}						{	pre_update(); col_no += yyleng; calc();post_update();yylval.string_val = strdup(yytext); /*printf("STR_LIT\n");*/ return(STR_LIT);		}


.								{	/*printf("ERROR\n");*/ pre_update(); col_no += yyleng; calc();post_update();return(ERROR);/*Ignore everything else*/	}


%%

int yywrap()
{
	printf("\n"); return(1);
}

void calc()
{
	int i;
	for(i=0; yytext[i] != '\0';i++)
	{
		if(yytext[i] == '\n')
		{
			col=0;
			row++;
		}
		else if(yytext[i] =='\t')
		{
			col+=8-(col%8);
		}		
		else
		{
			col++;
		}
	}

}


void eat_to_newline(int call)
{
    

	//cout<<"called at no "<< call<<endl;
	
    int c;
    bool brk=false;

    while ((c = yyinput()) != 0  && c != '\n' && c!=10 )
    {

    	//cout<<"char read is "<<c<<endl;
    	
        if(c==EOF )
        {
            brk=true;
            eof=true;
            break;
        }
    	if(c==';')
    	{
    		brk=true;
    		unput(c);
    		break;
    	}	
    	if(c=='{')
    	{
    		brk=true;
    		unput(c);
    		break;
    	}
    	if(c=='}')
    	{
    		brk=true;
    		unput(c);
    		break;
    	}
        if(c==')')
        {

            brk=true;
            break;
        
        }
        if(c==']')
        {

            brk=true;
            break;
        
        }
    
    }
    
    
    if(!brk)
    {
    	
    	line_no++;
    	col_no=1;
	}


	 //cout<<"done till "<<c<<endl;
}


void post_update()
{
	yylloc.last_line = line_no;
	yylloc.last_column  = col_no;
}

void pre_update()
{
	yylloc.first_line = line_no;
	yylloc.first_column = col_no;
}

