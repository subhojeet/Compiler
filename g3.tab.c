/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 4 "g3.y" /* yacc.c:339  */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <fstream>

using namespace std;

extern  "C" char* yytext;			// To show erroneous pattern
extern void eat_to_newline(int);
bool eof=false;

char str[200];
//string sem_err= " ";
int row=1, col=1, errcount = 0;		// To keep track of row and column NUMBER



// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int yywrap();
int yyerror(const char *s);
extern int line_no;
extern int col_no;
bool caught=false;
void semantic_error(string );



typedef enum NodeType{
		_EPSILON, _CONSTANT, _VARIABLE, _OPERATION, _CONDITION, _ASSIGN, _WHILE, _IF, _ELSE, _INCLUDE, _INCLUDE_STR, _STATEMENT,
		 _FUNCTION,_ARGLIST, _ARG, _VAR, _FTYPE, _DTYPE, _IDLIST, _STATEMENTS, _FOR, _OUT, _IN, _CASE, _OTHER, _DOWHILE, _SWITCH,
		_FUNCTIONDEC, _DEC, _DEC_VAR, _DECVAR_EQ, _DEC_ARR, _ARG_CONS, _ARG_ID, _PARAMETERS, _PARA_DEC, _PARA_DEC_LIST, _EXPR,
		_FACTOR_ID, _FACTOR_CONS, _IFELSE, _RETURN_STATEMENT, _RETURNEXP_STATEMENT, _BREAK_STATEMENT, _CONTINUE_STATEMENT,
		_ELIF, _ERROR ,FUNC_CALL, _ARG_FUNC_CALL, _SEMI_COMMA, _COLON, _MAIN, _COMPOUND_STMNT, _EXPR_EXPR_OP, _EXPR_MICRO_OP, _EXPR_BRACKET,
		_EXPR_MICROVAL, _EXPR_UNARY, _IF_ELSEIF_ELSE, _ELIF_LIST, _ELIF_PART, _IF_ELSEIF, _EXPR_MICRO_ASS_OP, _FUNCTION_DEF, _FUNCTION_DEF_VOID,
		_FUNCTION_DEF_PARAM, _FUNCTION_DEF_PARAM_VOID, _MAIN_PARAM, _GET_INT, _GET_STRING, _GET_FLOAT, _PRINT_STRING, _PRINT_FLOAT, _PRINT_INT,
		_CONSTANT_NUMP, _CONSTANT_FLOATP, _ID_BOOLEAN_OP

}N_type;

typedef enum DataType{
		_INT, _BOOL, _FLOAT, _VOID, _CHAR, _STRING, _UNKNOWN, _EXP_INT, _EXP_BOOL, _EXP_FLOAT, _EXP_CHAR, _EXP_STRING
}D_type;

int scope=0, main_pres=1, syntactic_err=0, semantic_err=0,scope_code=0;
int var_line_no=0;
string threecode="";

struct symtb{
	int scope;
	string value;
	string id;
	DataType d_type;
};

struct cgenEntry{
	int scope;
	string value;
	DataType d_type;	
};

vector< map < string, struct symtb > > symbolTable;
vector< map < string, struct cgenEntry> > cgenTable;

struct functb{
	DataType r_type;
	vector<DataType>params;
	string func_name;
	map<string, int> var_list;
};


map<string, int> tmp_vars;
map<string, struct cgenEntry> global_var;


vector<DataType> return_v;
vector<DataType> arg_v;
map<string, struct functb > functionTable;
vector<DataType>pv;
map<string, struct functb>::iterator mit;
map<string, struct functb>::iterator mit1;

struct AST {
	//int child_no;
	//struct AST** children;
	//char value[100];
	//char code[500];
	vector<struct AST*> v;
	N_type n_type;
	D_type d_type;
	string value;
	string code;
};


void add_in_tmp_var(string s){
	map<string, int>::iterator it;
	it = tmp_vars.find(s);
	if(it==tmp_vars.end()){
		tmp_vars.insert(pair<string, int>(s, var_line_no));
		var_line_no++;
	}
}

void add_global_to_tmp_vars(string s)
{
	map<string, int>::iterator it;
	map<string, struct cgenEntry>::iterator it1;
	string x,a;
	int scop;
	int sz = tmp_vars.size();
	for(it1=global_var.begin(); it1!=global_var.end(); ++it1){
		x=it1->first;
		scop = (it1->second).scope;
		stringstream ss;
		ss << scop;
		a=x+ss.str();
		it=tmp_vars.find(a);
		if(it==tmp_vars.end()){
			tmp_vars.insert(pair<string, int>(a, sz));
			sz++;
		}
	}
} 


/****************************************Function Table*******************************/
/*************************************************************************************/
void check_args(string s){
	mit=functionTable.find(s);
	if(mit!=functionTable.end()){
		vector<DataType>::iterator pit1;
		vector<DataType>::iterator pit2;
		vector<DataType> tmp;
		tmp=(mit->second).params;
		if(arg_v.size()!=tmp.size()){
			semantic_err=1;
			cout << s << ": number of function parameters not matching" << endl;
		}else{
			for(pit1=arg_v.begin(),pit2=tmp.begin();pit1!=arg_v.end() && pit2!=tmp.end(); ++pit1,++pit2){
				if(*pit1!=*pit2){
					semantic_err=1;
					cout << s << ": function call argument type not matching" << endl;
					break;
				}
			}
		}
	}else{
		semantic_err=1;
		cout << s << " function not defined" << endl;
	}
}

DataType find_return_type(string s){
	mit=functionTable.find(s);
	if(mit!=functionTable.end()){
		return (mit->second).r_type;
	}else{
		semantic_err=1;
		return _VOID;
	}
}

void check_returning(DataType d, string s){
	vector<DataType>::iterator rit;
	if(return_v.size()<=0 && d!=_VOID){
		semantic_err=1;
		cout << "In function :" << s << " expecting return\n";
	}
	for(rit=return_v.begin();rit!=return_v.end();++rit){
		if(*rit!=d){
			semantic_err=1;
			cout << "In function :" << s << " return type is not matching with what you are returning\n";
		}
	}
	return_v.clear();
}

void check_validity_function(string s, DataType d){
	mit=functionTable.find(s);
	if(mit!=functionTable.end()){
		if((mit->second).r_type!=d){
			semantic_err=1;
			cout << s << ": function return typr not matching" << endl;	
		}
	}else{
		semantic_err=1;
		cout << s << ": function not defined" << endl;
	}
}

void check_validity_function_p(string s, DataType d){
	mit=functionTable.find(s);
	if(mit!=functionTable.end()){
		if((mit->second).r_type!=d){
			semantic_err=1;
			cout << s << ": function return type not matching" << endl;	
		}
		vector<DataType>::iterator pit1;
		vector<DataType>::iterator pit2;
		vector<DataType> tmp;
		tmp=(mit->second).params;
		if(pv.size()!=tmp.size()){
			semantic_err=1;
			cout << s << ": function parameters not matching" << endl;
		}else{
			for(pit1=pv.begin(),pit2=tmp.begin();pit1!=pv.end() && pit2!=tmp.end(); ++pit1,++pit2){
				if(*pit1!=*pit2){
					semantic_err=1;
					cout << s << ": function parameters not matching" << endl;
					break;
				}
			}
		}
	}else{
		semantic_err=1;
		cout << s << " function not defined" << endl;
	}
}


void add_var_list(string s){
	add_global_to_tmp_vars(s);
	mit = functionTable.find(s);
	if(mit!=functionTable.end()){
		//cout << "yahan aya\n";
		(mit->second).var_list = tmp_vars;
	}else{
		cout << "nahi mila\n";
	}
}

void add_entry_functb(DataType d, string s){
	struct functb tb;
	tb.func_name = s;
	tb.r_type = d;
	functionTable.insert(pair<string, struct functb>(s, tb));
}

void set_params(string s){
	mit=functionTable.find(s);
	if(mit!=functionTable.end()){
		(mit->second).params = pv;
	}
}

void fill_params(struct AST* node){
	vector<struct AST*>::iterator it1;
	if(node->n_type==_DTYPE){
		pv.push_back(node->d_type);
	}else{
		for(it1=(node->v).begin();it1!=(node->v).end();it1++){
			fill_params(*it1);
		}
	}
}

bool is_in_map(string s){
	mit=functionTable.find(s);
	if(mit!=functionTable.end()){
		return true;
	}
	return false;
}

/***************************************************************************/
/***************************************************************************/

void create_dot_graph(struct AST*, string);

string find_dty(DataType d){
	switch(d){
		case _INT: return "int";
		case _FLOAT: return "float";
		case _BOOL: return "bool";
		case _CHAR: return "char";
		case _STRING: return "string";
		default: return "unknown";
	}
}

DataType expc_datatype(DataType d){
	switch(d){
		case _INT: return _EXP_INT;
		case _FLOAT: return _EXP_FLOAT;
		case _BOOL: return _EXP_BOOL;
		case _CHAR: return _EXP_CHAR;
		case _STRING: return _EXP_STRING;
		default: return _VOID;
	}
}

int find_scope(string s){
	int sz = symbolTable.size();
	int ans = sz-1;
	map<string, struct symtb>::iterator it;
	vector< map < string, struct symtb > >::reverse_iterator it1;
	for(it1=symbolTable.rbegin();it1!=symbolTable.rend();++it1){
		it=it1->find(s);
		if(it!=it1->end()){
			return ans;
		}
		ans--;
	}
	return ans;
}

int in_current_scope(string s){
	
	map<string, struct symtb>::iterator it;
	it=symbolTable.back().find(s);
	if(it!=symbolTable.back().end()){
		return 1;
	}else{
		return 0;
	}
}

void rec_set_type(DataType d, struct AST* node){
	vector<struct AST*>::iterator it1;
	if(node->n_type==_DEC){
		for(it1=(node->v).begin();it1!=(node->v).end();it1++){
			rec_set_type(d, *it1);
		}
	}else if(node->n_type==_DEC_VAR || node->n_type==_DECVAR_EQ || node->n_type==_DEC_ARR){
		if(node->n_type==_DECVAR_EQ){
			if(node->d_type==_EXP_INT && (d!=_INT && d!=_FLOAT)){
				semantic_err=1;semantic_error(" Invalid assignment to variable");
				//printf("Invalid assignment to variable\n");
			}else if(node->d_type==_EXP_FLOAT && (d!=_FLOAT )){
				semantic_err=1;semantic_error("Invalid assignment to variable ");
				//printf("Invalid assignment to variable\n");
			}else if(node->d_type==_EXP_BOOL && d!=_BOOL){
				semantic_err=1;semantic_error("Invalid assignment to variable ");
				//printf("Invalid assignment to variable\n");
			}else if(node->d_type==_EXP_CHAR && d!=_CHAR){
				semantic_err=1;semantic_error("Invalid assignment to variable ");
				//printf("Invalid assignment to variable\n");
			}else if(node->d_type==_EXP_STRING && d!=_STRING){
				semantic_err=1;semantic_error("Invalid assignment to variable ");
				//printf("Invalid assignment to variable\n");
			}
		}
		map<string, struct symtb>::iterator it;
		it = symbolTable.back().find(node->value);
		if(it!=symbolTable.back().end()){
			(it->second).d_type = d;
		}
	}
	return;
}

void add_to_symtb(DataType d,int scp,string id, string val1){
	int sz=symbolTable.size();
	//cout << "Size "<< sz << endl;
	struct symtb tb;
	tb.scope=scp;
	tb.id=id;
	tb.value=val1;
	tb.d_type=d;
	symbolTable.back().insert(pair<string, struct symtb>(id,tb));
	/*if(sz>scope){
		symbolTable[scope].insert(pair<string, struct symtb>(id,tb));
	}else{
		map<string, struct symtb> mm;
		mm.insert(pair<string, struct symtb>(id,tb));
		symbolTable.push_back(mm);
	}*/
}

void set_type(DataType d,string id){
	if(in_current_scope(id)==1){
		//printf("Redeclaration of variable %s\n",s);
		//cout << "Redefination of variable " << id << endl;
		stringstream ss;
		ss<<"Redefination of variable "<<  id;
		string err_msg = ss.str();
		semantic_err=1;semantic_error(err_msg);
	}else{
		add_to_symtb(d,scope, id, "");
	}
}

struct AST* newopnode(string val){
	//cout << "cr3" << endl;
	struct AST* a;
	a = new struct AST[1];
	a->code = "";
	a->value = val;
	a->n_type = _OPERATION;
	a->d_type = _VOID;
	//cout << a << endl;
	return a;
}

struct AST* newnode(DataType d, NodeType n, string code){
	//cout << "cr2" << endl;
	struct AST* a;
	a = new struct AST[1];
	a->code = code;
	a->value = "";
	a->n_type = n;
	a->d_type = d;
	//cout << a << endl;
	return a;
}

struct AST* newnode(DataType d, NodeType n, string code, string val){
	struct AST* a;
	a = new struct AST[1];
	//cout << "cr1" << endl;
	a->code = code;
	a->value = val;
	a->n_type = n;
	a->d_type = d;
	//cout << a << endl;
	return a;
}

struct AST* newnode(){
	struct AST* a;
	a = new struct AST[1];
	//cout << "cr" << endl;
	a->code = "";
	a->value = "";
	a->n_type = _STATEMENTS;
	a->d_type = _VOID;
	//cout << a << endl;
	return a;
}

DataType find_type_id(string s){
	DataType d=_UNKNOWN;
	map<string, struct symtb>::iterator it;
	it=symbolTable.back().find(s);
	if(it!=symbolTable.back().end()){
		d=(it->second).d_type;
	}else{
		int scp;
		scp=find_scope(s);
		if(scp<0){
			//cout << "variable not  defined " << s << endl;
			
			stringstream ss;
			ss<<"variable not  defined  "<<  s;
			string err_msg = ss.str();
			semantic_err=1;semantic_error(err_msg);
		}else{
			it=symbolTable[scp].find(s);
			if(it!=symbolTable[scp].end()){
				d=(it->second).d_type;
			}
		}
	}
	return d;
}


bool logical(string op){
	if(op=="||" || op=="&&")
		return true;
	return false;
}

bool realational(string op){
	if(op=="<" || op==">"  || op==">=" || op=="<=" )
		return true;
	return false;
}

bool eqeqop(string op){
	if( op=="==" || op=="!=")
		return true;
	return false;
}


bool assignment(string op){
	if(op=="=" || op=="+="  || op=="-=" || op=="*=" || op=="/=" || op=="%=" || op=="|=" || op=="&=" || op=="^=")
		return true;
	return false;	
}

bool bit_logical(string op){
	if(op=="^" || op=="|"  || op=="&")
		return true;
	return false;	
}

bool binary(string op){
	if(op=="+" || op=="*"  || op=="-" || op=="/" || op=="%")
		return true;
	return false;
}

void check_validity(string op, DataType d1, DataType d2, DataType *d){
	if(d1!=d2 || (d1==_VOID || d2==_VOID) || (d1==_UNKNOWN || d2==_UNKNOWN)){
		stringstream ss;
		ss<<"type mismatch for "<<  op;
		string err_msg = ss.str();
		semantic_err=1;semantic_error(err_msg);
		//printf("type mismatch for %s\n",op);
		//cout << "type mismatch for " << op << endl;
	}
	if(logical(op) && (d1!=_BOOL || d2!=_BOOL)){
		stringstream ss;
		ss<<"type mismatch for " << op << " must be bool";
		string err_msg = ss.str();
		semantic_err=1;semantic_error(err_msg);
		//printf("type mismatch for %s\n , must be bool",op);
		//cout << "type mismatch for " << op << " must be bool" << endl;	
	}
	if(realational(op) && ((d1==_BOOL || d2== _BOOL))){
		stringstream ss;
		ss<<"type mismatch for " << op << " must be int,float,string,char" ;
		string err_msg = ss.str();
		semantic_err=1;semantic_error(err_msg);
		//printf("type mismatch for %s\n , must be int,float,string or char",op);
		//cout << "type mismatch for " << op << " must be int,float,string,char" << endl;	
	}
	if(logical(op)){
		*d=_BOOL;
	}else if(realational(op)){
		*d=_BOOL;
	}else if(assignment(op)){
		*d=_VOID;
	}else if(bit_logical(op)){
		*d=d1;
	}else if(binary(op)){
		*d=d1;
	}
}

struct AST* root;


#line 615 "g3.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "g3.tab.h".  */
#ifndef YY_YY_G3_TAB_H_INCLUDED
# define YY_YY_G3_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    DECIMAL = 259,
    BOOLEAN = 260,
    STR_LIT = 261,
    ID = 262,
    CHAR_LIT = 263,
    INT = 264,
    FLOAT = 265,
    CHAR = 266,
    BOOL = 267,
    VOID = 268,
    STRING = 269,
    ADD_ASS = 270,
    SUB_ASS = 271,
    MUL_ASS = 272,
    DIV_ASS = 273,
    MOD_ASS = 274,
    AND_ASS = 275,
    XOR_ASS = 276,
    OR_ASS = 277,
    BREAK = 278,
    CONTINUE = 279,
    RETURN = 280,
    FOR = 281,
    WHILE = 282,
    IF = 283,
    ELSE = 284,
    DO = 285,
    ELIF = 286,
    LESS_OP = 287,
    GREAT_OP = 288,
    LESS_EQ_OP = 289,
    GREAT_EQ_OP = 290,
    EQEQ_OP = 291,
    NOTEQ_OP = 292,
    AND_OP = 293,
    OR_OP = 294,
    MAIN = 295,
    IN = 296,
    OUT = 297,
    INCLUDE = 298,
    EXIT = 299,
    GETFLOAT = 300,
    GETINT = 301,
    GETSTRING = 302,
    PRINTSTR = 303,
    PRINTFLOAT = 304,
    PRINTINT = 305,
    CASE = 306,
    OTHERWISE = 307,
    SWITCH = 308,
    ERROR = 309,
    INCR = 310,
    DECR = 311,
    TYPEDEF = 312,
    RES_STR = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 554 "g3.y" /* yacc.c:355  */

	struct AST* node;
	int int_val;
	float float_val;
	bool bool_val;
	char* string_val;
	char char_val;

#line 723 "g3.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_G3_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 752 "g3.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   833

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  198
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  332

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,     2,    65,     2,    64,    73,     2,
      69,    67,    62,    60,    72,    61,    66,    63,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    78,    68,
       2,    59,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,    75,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,    74,    80,    77,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   608,   608,   619,   626,   633,   640,   652,   660,   669,
     677,   684,   691,   698,   710,   717,   725,   733,   750,   762,
     774,   781,   792,   800,   804,   819,   838,   855,   868,   884,
     896,   912,   930,   935,   953,   966,   989,  1004,  1023,  1036,
    1054,  1065,  1072,  1097,  1115,  1134,  1149,  1170,  1175,  1180,
    1208,  1217,  1226,  1236,  1252,  1266,  1280,  1301,  1325,  1333,
    1336,  1357,  1363,  1383,  1388,  1393,  1398,  1413,  1418,  1426,
    1431,  1436,  1441,  1446,  1453,  1458,  1463,  1468,  1473,  1478,
    1483,  1488,  1493,  1500,  1505,  1510,  1515,  1520,  1525,  1533,
    1538,  1543,  1551,  1556,  1564,  1571,  1581,  1587,  1593,  1599,
    1605,  1611,  1617,  1623,  1632,  1646,  1654,  1669,  1677,  1685,
    1693,  1709,  1725,  1741,  1755,  1769,  1786,  1809,  1826,  1849,
    1864,  1887,  1897,  1923,  1948,  1974,  1981,  2000,  2007,  2021,
    2029,  2033,  2049,  2054,  2063,  2092,  2097,  2105,  2135,  2143,
    2153,  2161,  2171,  2187,  2218,  2237,  2255,  2271,  2286,  2308,
    2315,  2321,  2339,  2349,  2354,  2364,  2375,  2381,  2391,  2406,
    2421,  2438,  2452,  2466,  2480,  2497,  2506,  2514,  2526,  2545,
    2561,  2570,  2575,  2587,  2593,  2599,  2606,  2618,  2624,  2641,
    2655,  2667,  2676,  2684,  2700,  2710,  2719,  2737,  2747,  2760,
    2777,  2786,  2807,  2814,  2822,  2837,  2852,  2871,  2901
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "DECIMAL", "BOOLEAN",
  "STR_LIT", "ID", "CHAR_LIT", "INT", "FLOAT", "CHAR", "BOOL", "VOID",
  "STRING", "ADD_ASS", "SUB_ASS", "MUL_ASS", "DIV_ASS", "MOD_ASS",
  "AND_ASS", "XOR_ASS", "OR_ASS", "BREAK", "CONTINUE", "RETURN", "FOR",
  "WHILE", "IF", "ELSE", "DO", "ELIF", "LESS_OP", "GREAT_OP", "LESS_EQ_OP",
  "GREAT_EQ_OP", "EQEQ_OP", "NOTEQ_OP", "AND_OP", "OR_OP", "MAIN", "IN",
  "OUT", "INCLUDE", "EXIT", "GETFLOAT", "GETINT", "GETSTRING", "PRINTSTR",
  "PRINTFLOAT", "PRINTINT", "CASE", "OTHERWISE", "SWITCH", "ERROR", "INCR",
  "DECR", "TYPEDEF", "RES_STR", "'='", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'#'", "'.'", "')'", "';'", "'('", "'['", "']'", "','", "'&'", "'|'",
  "'^'", "'!'", "'~'", "':'", "'{'", "'}'", "$accept", "Start_sym",
  "Start1", "Start2", "data_type", "include_dec", "string", "main_func",
  "func_dec", "semi_comma", "param", "func_def", "micro_val", "expr",
  "arg_list", "arg", "operators", "logical_op", "binary_op",
  "assignment_op", "relational_op", "bit_logical_op", "unary_op",
  "stmnt_list", "stmnt", "io_stmnt", "arg_print_int", "arg_print_float",
  "arg_printstr", "arg_get_str", "arg_get_int", "arg_get_float",
  "labeled_stmnt", "otwise_stmnt", "colon", "func_compound_stmnt",
  "compound_stmnt", "_LOB", "_ROB", "_LCB", "_RCB", "condition_stmnt",
  "elif_list", "elseifpart", "switch_stmnt", "switch_stmnt_list",
  "switch_stmnt_list1", "loop_stmnt", "expr_stmnt_list",
  "expr_stmnt_list_cond", "expr_stmnt", "jump_stmnt", "exit_stmnt",
  "constant", "param_list", "ext_dec", "dec", "ID_init_list", "dec_init", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,    61,
      43,    45,    42,    47,    37,    35,    46,    41,    59,    40,
      91,    93,    44,    38,   124,    94,    33,   126,    58,   123,
     125
};
# endif

#define YYPACT_NINF -123

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-123)))

#define YYTABLE_NINF -187

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -123,    47,   195,   -42,  -123,  -123,   102,  -123,  -123,  -123,
      28,  -123,    23,  -123,  -123,  -123,  -123,    20,  -123,    45,
       4,    60,     2,   141,    19,  -123,  -123,    16,  -123,  -123,
     288,   310,  -123,   390,   418,  -123,   148,   119,   468,  -123,
    -123,   131,  -123,   138,  -123,  -123,  -123,     2,   156,   118,
     120,    52,     2,   145,    18,     2,   154,  -123,  -123,  -123,
    -123,   132,  -123,    18,    18,    49,    61,    63,    64,    10,
      66,    68,    70,    71,    74,    75,    78,    79,  -123,   148,
    -123,  -123,  -123,  -123,    77,   725,    18,   148,   260,  -123,
    -123,  -123,   418,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,   127,   157,    52,     2,   162,    18,   -26,  -123,
      -8,  -123,  -123,     2,   204,  -123,     2,    18,  -123,  -123,
    -123,  -123,     2,   183,    98,  -123,  -123,  -123,    18,  -123,
     165,  -123,   148,  -123,   148,  -123,   206,  -123,   164,  -123,
     231,  -123,   233,  -123,   239,  -123,   104,  -123,    32,  -123,
      24,  -123,   148,    33,  -123,    25,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,   148,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,   175,  -123,  -123,   148,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,   340,  -123,  -123,  -123,  -123,     2,    18,
    -123,  -123,   240,  -123,   241,  -123,  -123,  -123,   181,  -123,
    -123,    40,  -123,  -123,  -123,   184,  -123,  -123,  -123,    41,
     187,   191,   190,    18,  -123,   193,  -123,   209,  -123,   214,
    -123,  -123,   224,  -123,  -123,   225,  -123,  -123,   226,   227,
    -123,   758,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,   262,  -123,  -123,  -123,  -123,   327,  -123,   148,   632,
      11,   217,   148,  -123,   235,   244,  -123,   246,   247,   248,
     222,   148,   662,  -123,  -123,  -123,  -123,  -123,    59,  -123,
    -123,   133,   250,  -123,  -123,  -123,  -123,  -123,   573,  -123,
    -123,  -123,   148,   165,   217,    81,   168,  -123,   255,   274,
    -123,  -123,  -123,   238,   496,  -123,    56,  -123,  -123,   148,
     217,   256,  -123,  -123,  -123,    14,  -123,    17,  -123,  -123,
     217,   259,  -123,  -123,  -123,  -123,   258,   650,  -123,   217,
     650,  -123
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,     6,     1,   189,     9,    10,    12,    11,
       0,    13,     0,     2,     4,     3,     5,     0,     7,     0,
       0,     0,   188,   195,     0,   192,    17,     0,    24,   138,
       0,     0,    25,     0,     0,    39,     0,     0,     0,   194,
     187,     0,    18,     0,    14,   186,     9,     0,     0,     0,
      34,    31,   139,     0,     0,     0,     0,   179,   180,   183,
     182,    41,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   171,     0,
      92,    93,   140,   141,     0,    47,     0,     0,     0,    94,
     102,    96,     0,   132,    98,    99,    97,   100,   103,    40,
     101,   197,     0,     0,    30,   139,     0,     0,   195,   193,
       0,    20,   184,     0,     0,    38,   139,     0,    33,    32,
      29,    22,     0,     0,     0,   173,   174,   175,     0,   164,
       0,   162,     0,   147,     0,   163,     0,   178,     0,   114,
       0,   113,     0,   115,     0,   112,     0,   110,     0,   111,
       0,   148,     0,     0,   191,     0,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      67,    68,     0,    74,    69,    70,    71,    72,    73,    89,
      90,    91,     0,    65,    63,     0,    64,    66,   172,    49,
     134,    95,   133,     0,   135,   198,   196,    36,   139,     0,
      27,    16,     0,    19,     0,    37,    28,    21,     0,    62,
      42,     0,    59,    61,    46,     0,   176,   167,   166,     0,
       0,     0,     0,     0,   124,     0,   123,     0,   122,     0,
     121,   120,     0,   119,   118,     0,   117,   116,     0,     0,
      53,    48,   190,    56,    54,    50,    51,   137,   136,    35,
      26,     0,   185,    45,    60,    43,     0,    44,     0,     0,
       0,     0,     0,   177,     0,     0,   107,     0,     0,     0,
       0,     0,     0,    15,    58,   165,   170,   169,     0,   161,
     158,   142,     0,   108,   109,   104,   106,   105,     0,    57,
      55,    52,     0,     0,     0,     0,   145,   150,     0,     0,
     154,   153,   157,     0,   129,   168,     0,   143,   151,     0,
       0,     0,   149,   159,   126,     0,   146,     0,   155,   156,
       0,     0,   144,   131,   130,   125,   131,     0,   160,     0,
     127,   152
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,  -123,  -123,     7,  -123,  -123,  -123,  -123,   -58,
     199,  -123,  -123,   -36,  -123,    86,   112,  -123,  -123,  -123,
    -123,  -123,  -123,   -88,   -85,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,  -123,    39,   -39,   -67,   137,   -21,  -123,
     -78,  -123,  -123,    31,    53,  -123,  -123,  -123,    65,  -123,
    -123,  -123,  -123,  -122,  -123,  -123,  -123,   275,   319
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    84,    18,    44,    13,    14,   120,
      49,    15,    85,    86,   211,   212,   182,   183,   184,   185,
     186,   187,    87,    88,    89,    90,   238,   235,   232,   229,
     227,   225,   301,   318,   325,    35,    91,    30,    54,    92,
      93,    94,   296,   297,   302,   303,   304,    95,   219,   278,
      96,    97,    98,    99,    50,    16,   100,    24,    25
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     101,   213,   136,   191,   193,   125,   126,   127,   111,    12,
     192,   135,   279,   115,   194,   323,   121,   107,   326,   118,
      39,    26,    42,    17,    22,   201,    39,   236,   188,   128,
      23,   237,   117,    36,   240,    20,   233,    48,    48,   234,
      48,   254,   118,   153,    37,    48,    28,     4,    43,   200,
     118,   189,    57,    58,    59,    60,    61,    62,   202,   206,
     118,    32,   129,    27,   131,   133,   197,   137,    21,   139,
     216,   141,   143,    29,   203,   145,   147,   205,   154,   149,
     151,    34,   308,   207,   108,   199,   119,    40,   215,    82,
      82,    41,   324,   242,   218,   324,   220,    41,   221,   214,
     241,    57,    58,    59,    60,    61,    62,   255,   191,   119,
     230,   231,   256,   258,    29,   248,   239,   119,    79,  -186,
     102,   204,   103,   320,  -186,    80,    81,   119,   258,    29,
     130,   292,   132,   134,   213,   138,   243,   140,   108,   142,
     144,   250,    19,   146,   148,   110,   245,   150,   152,   246,
     309,    57,    58,    59,    60,    61,    62,    31,    33,   249,
      38,   259,   294,   112,   295,   263,   217,    79,    57,    58,
      59,    60,    61,    62,    80,    81,   244,   315,    57,    58,
      59,    60,    61,    62,   208,   113,    57,    58,    59,    60,
     209,    62,   114,   280,   281,   -23,     5,   310,   195,   311,
      36,   123,   124,   300,     6,     7,     8,     9,    10,    11,
      29,    37,   116,    46,     7,     8,     9,    79,    11,   300,
     293,   122,   275,   277,    80,    81,   282,   307,   196,   198,
      53,   223,    56,   222,    79,   289,   291,   106,   224,   330,
     226,    80,    81,   322,    79,   191,   228,   251,   252,   253,
     210,    80,    81,   328,   260,   257,   305,   218,   261,   262,
     264,   190,   331,    57,    58,    59,    60,    61,    62,    46,
       7,     8,     9,   321,    11,   314,   265,    57,    58,    59,
      60,   266,    62,    63,    64,    65,    66,    67,    68,    45,
      69,   267,   268,   269,   270,   273,    82,    46,     7,     8,
       9,   288,    11,   283,    70,    71,    72,    73,    74,    75,
      76,    51,   284,    77,   285,   286,   287,   298,   316,    46,
       7,     8,     9,   313,    11,   309,   329,   312,    78,    79,
      57,    58,    59,    60,   209,    62,    80,    81,  -128,    82,
      83,   247,   274,    57,    58,    59,    60,    61,    62,    46,
       7,     8,     9,   272,    11,    47,   327,   319,   306,   155,
     109,     0,     0,    63,    64,    65,    66,    67,    68,     0,
      69,     0,     0,     0,     0,     0,     0,    52,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    45,     0,    77,     0,     0,     0,     0,     0,    46,
       7,     8,     9,     0,    11,     0,     0,     0,    78,    79,
       0,     0,     0,     0,     0,     0,    80,    81,     0,    82,
      83,    57,    58,    59,    60,    61,    62,    46,     7,     8,
       9,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    64,    65,    66,    67,    68,     0,    69,     0,
       0,     0,     0,     0,     0,     0,     0,    55,     0,     0,
       0,     0,    70,    71,    72,    73,    74,    75,    76,   104,
       0,    77,     0,     0,     0,     0,     0,    46,     7,     8,
       9,     0,    11,     0,     0,     0,    78,    79,     0,     0,
       0,     0,     0,     0,    80,    81,     0,    82,    83,    57,
      58,    59,    60,    61,    62,    46,     7,     8,     9,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,    63,
      64,    65,    66,    67,    68,     0,    69,     0,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,     0,     0,
      70,    71,    72,    73,    74,    75,    76,   299,   317,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    78,    79,     0,     0,     0,     0,
       0,     0,    80,    81,     0,    82,    57,    58,    59,    60,
      61,    62,    46,     7,     8,     9,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,    65,    66,
      67,    68,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,    71,    72,
      73,    74,    75,    76,   299,     0,    77,     0,     0,     0,
       0,     0,     0,   276,     0,    57,    58,    59,    60,    61,
      62,    78,    79,     0,     0,     0,     0,     0,     0,    80,
      81,     0,    82,    57,    58,    59,    60,    61,    62,    46,
       7,     8,     9,   290,    11,    57,    58,    59,    60,    61,
      62,     0,     0,    63,    64,    65,    66,    67,    68,     0,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    79,     0,    77,     0,     0,     0,     0,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,    78,    79,
       0,     0,     0,     0,     0,     0,    80,    81,     0,    82,
       0,    79,     0,     0,     0,     0,     0,     0,    80,    81,
     156,   157,   158,   159,   160,   161,   162,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   164,   165,   166,
     167,   168,   169,   170,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   172,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     164,   165,   166,   167,   168,   169,   170,   171,   179,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   271,     0,     0,     0,     0,     0,   174,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,   179,   180,   181
};

static const yytype_int16 yycheck[] =
{
      36,   123,    69,    88,    92,    63,    64,    65,    47,     2,
      88,     1,     1,    52,    92,     1,    55,    38,     1,     1,
       1,     1,     6,    65,     1,    33,     1,     3,    86,    65,
       7,     7,    53,    59,     1,     7,     4,    30,    31,     7,
      33,     1,     1,    79,    70,    38,     1,     0,    32,   107,
       1,    87,     3,     4,     5,     6,     7,     8,    66,   117,
       1,     1,     1,    43,     1,     1,   105,     1,    40,     1,
     128,     1,     1,    69,   113,     1,     1,   116,     1,     1,
       1,    79,     1,   122,     7,   106,    68,    68,   124,    79,
      79,    72,    78,    68,   130,    78,   132,    72,   134,     1,
      67,     3,     4,     5,     6,     7,     8,    67,   193,    68,
       6,     7,    72,    72,    69,   193,   152,    68,    69,    67,
       1,   114,     3,    67,    72,    76,    77,    68,    72,    69,
      69,    72,    69,    69,   256,    69,   172,    69,     7,    69,
      69,   199,    40,    69,    69,     7,   182,    69,    69,   185,
      69,     3,     4,     5,     6,     7,     8,    20,    21,   198,
      23,   219,    29,     7,    31,   223,     1,    69,     3,     4,
       5,     6,     7,     8,    76,    77,     1,   299,     3,     4,
       5,     6,     7,     8,     1,    67,     3,     4,     5,     6,
       7,     8,    72,   260,   261,     0,     1,    29,    71,    31,
      59,    69,    70,   288,     9,    10,    11,    12,    13,    14,
      69,    70,    67,     9,    10,    11,    12,    69,    14,   304,
     278,    67,   258,   259,    76,    77,   262,   294,    71,    67,
      31,    67,    33,    27,    69,   271,   272,    38,     7,   327,
       7,    76,    77,   310,    69,   330,     7,     7,     7,    68,
      67,    76,    77,   320,    67,    71,   292,   293,    67,    69,
      67,     1,   329,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   309,    14,     1,    67,     3,     4,     5,
       6,    67,     8,    23,    24,    25,    26,    27,    28,     1,
      30,    67,    67,    67,    67,    33,    79,     9,    10,    11,
      12,    79,    14,    68,    44,    45,    46,    47,    48,    49,
      50,     1,    68,    53,    68,    68,    68,    67,    80,     9,
      10,    11,    12,    68,    14,    69,    67,   296,    68,    69,
       3,     4,     5,     6,     7,     8,    76,    77,    80,    79,
      80,     1,   256,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   241,    14,    67,   317,   304,   293,    84,
      41,    -1,    -1,    23,    24,    25,    26,    27,    28,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,     1,    -1,    53,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    -1,    14,    -1,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    79,
      80,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,     1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    -1,    14,    -1,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    -1,    79,    80,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    -1,    79,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,     7,
       8,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    -1,    79,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     1,    14,     3,     4,     5,     6,     7,
       8,    -1,    -1,    23,    24,    25,    26,    27,    28,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    69,    -1,    53,    -1,    -1,    -1,    -1,    76,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    79,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      32,    33,    34,    35,    36,    37,    38,    39,    73,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,    83,    84,     0,     1,     9,    10,    11,    12,
      13,    14,    85,    88,    89,    92,   136,    65,    86,    40,
       7,    40,     1,     7,   138,   139,     1,    43,     1,    69,
     118,   118,     1,   118,    79,   116,    59,    70,   118,     1,
      68,    72,     6,    32,    87,     1,     9,    67,    85,    91,
     135,     1,    67,    91,   119,    67,    91,     3,     4,     5,
       6,     7,     8,    23,    24,    25,    26,    27,    28,    30,
      44,    45,    46,    47,    48,    49,    50,    53,    68,    69,
      76,    77,    79,    80,    85,    93,    94,   103,   104,   105,
     106,   117,   120,   121,   122,   128,   131,   132,   133,   134,
     137,    94,     1,     3,     1,    67,    91,   119,     7,   139,
       7,   116,     7,    67,    72,   116,    67,   119,     1,    68,
      90,   116,    67,    69,    70,    90,    90,    90,    94,     1,
      69,     1,    69,     1,    69,     1,   117,     1,    69,     1,
      69,     1,    69,     1,    69,     1,    69,     1,    69,     1,
      69,     1,    69,    94,     1,   138,    15,    16,    17,    18,
      19,    20,    21,    22,    32,    33,    34,    35,    36,    37,
      38,    39,    54,    59,    60,    61,    62,    63,    64,    73,
      74,    75,    97,    98,    99,   100,   101,   102,    90,    94,
       1,   105,   121,   104,   121,    71,    71,   116,    67,   119,
      90,    33,    66,   116,    85,   116,    90,   116,     1,     7,
      67,    95,    96,   134,     1,    94,    90,     1,    94,   129,
      94,    94,    27,    67,     7,   112,     7,   111,     7,   110,
       6,     7,   109,     4,     7,   108,     3,     7,   107,    94,
       1,    67,    68,    94,     1,    94,    94,     1,   121,   116,
      90,     7,     7,    68,     1,    67,    72,    71,    72,    90,
      67,    67,    69,    90,    67,    67,    67,    67,    67,    67,
      67,    54,    97,    33,    96,    94,     1,    94,   130,     1,
     117,   117,    94,    68,    68,    68,    68,    68,    79,    94,
       1,    94,    72,    90,    29,    31,   123,   124,    67,    51,
     105,   113,   125,   126,   127,    94,   129,   117,     1,    69,
      29,    31,   124,    68,     1,   134,    80,    52,   114,   125,
      67,    94,   117,     1,    78,   115,     1,   115,   117,    67,
     104,   117
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    84,    84,    85,
      85,    85,    85,    85,    86,    86,    86,    86,    87,    88,
      88,    88,    88,    88,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    92,    92,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    98,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   101,   101,   101,   101,   101,   101,   102,
     102,   102,   103,   103,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   111,   112,   113,   113,   114,   114,   114,
     115,   115,   116,   116,   116,   117,   117,   117,   118,   119,
     120,   121,   122,   122,   122,   122,   122,   122,   122,   123,
     123,   123,   124,   125,   125,   126,   127,   127,   128,   128,
     128,   128,   128,   128,   128,   129,   129,   129,   130,   130,
     130,   131,   131,   132,   132,   132,   132,   133,   133,   134,
     134,   134,   134,   134,   135,   135,   135,   136,   136,   136,
     137,   137,   138,   138,   138,   139,   139,   139,   139
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     1,     2,     0,     1,
       1,     1,     1,     1,     3,     7,     5,     2,     1,     6,
       5,     6,     5,     0,     3,     3,     6,     5,     6,     5,
       4,     4,     1,     1,     1,     6,     5,     6,     5,     3,
       1,     1,     3,     4,     4,     4,     3,     1,     3,     2,
       3,     3,     5,     3,     3,     5,     3,     5,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     5,     5,     4,     5,     5,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     3,     2,     0,
       1,     1,     2,     3,     3,     2,     3,     3,     1,     1,
       1,     1,     5,     7,     8,     6,     7,     2,     2,     2,
       1,     2,     5,     1,     1,     2,     2,     1,     5,     7,
       9,     5,     2,     2,     2,     3,     1,     1,     3,     1,
       1,     1,     2,     2,     2,     2,     3,     4,     2,     1,
       1,     1,     1,     1,     2,     4,     1,     3,     2,     1,
       3,     2,     1,     3,     2,     1,     4,     3,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 608 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Start";
			root = nnode;
			(yyval.node) = nnode;
		}
#line 2286 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 619 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Start1";
			(yyval.node) = nnode;
		}
#line 2298 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 626 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Start1";
			(yyval.node) = nnode;
		}
#line 2310 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 633 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Start1";
			(yyval.node) = nnode;
		}
#line 2322 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 640 "g3.y" /* yacc.c:1646  */
    {
			/*cout << "2" << endl;
			struct AST* nnode=newnode();
			cout << nnode << endl;
			(nnode->v).push_back($1);
			$$->code = "Start1";
			$$ = nnode;*/
			(yyval.node)=(yyvsp[0].node);
		}
#line 2336 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 652 "g3.y" /* yacc.c:1646  */
    {
			//cout << "3" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Start2";
			(yyval.node) = nnode;
		}
#line 2349 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 660 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_EPSILON;
			nnode->code="EPSILON";
			(yyval.node) = nnode;
		}
#line 2360 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 669 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_INT;
			nnode->code="INT_data_type";
			(yyval.node)=nnode;

		}
#line 2373 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 677 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_FLOAT;
			nnode->code="FLOAT_data_type";
			(yyval.node)=nnode;	
		}
#line 2385 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 684 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_BOOL;
			nnode->code="BOOL_data_type";
			(yyval.node)=nnode;
		}
#line 2397 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 691 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_CHAR;
			nnode->code="CHAR_data_type";
			(yyval.node)=nnode;
		}
#line 2409 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 698 "g3.y" /* yacc.c:1646  */
    {

			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_STRING;
			nnode->code="STRING_data_type";
			(yyval.node)=nnode;
		}
#line 2422 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 710 "g3.y" /* yacc.c:1646  */
    { 
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_INCLUDE_STR;
			nnode->code="INCLUDE";
			(yyval.node)=nnode;
		}
#line 2434 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 717 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			string s1((yyvsp[-3].string_val));
			string s2((yyvsp[-1].string_val));
			nnode->n_type=_INCLUDE;
			nnode->code="INCLUDE<" + s1 + "." + s2 + ">";
			(yyval.node)=nnode;
		}
#line 2447 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 725 "g3.y" /* yacc.c:1646  */
    {
			//cout << "4" << endl;
			struct AST* nnode=newnode();
			string s1((yyvsp[-1].string_val));
			nnode->n_type=_INCLUDE;
			nnode->code="INCLUDE<" + s1 + ">";
			(yyval.node)=nnode;
		}
#line 2460 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 733 "g3.y" /* yacc.c:1646  */
    {
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							//printing the error message in header declaration
							/*caught=true;
							sprintf (str, "in header declaration");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							eat_to_newline(1);
							
							yyclearin;yyerrok;
					   	}
#line 2479 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 750 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			string val((yyvsp[0].string_val));
			nnode->n_type=_CONSTANT;
			nnode->d_type=_STRING;
			nnode->value=val;
			nnode->code="String_constant";
			(yyval.node) = nnode;
		}
#line 2493 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 762 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_INT, _MAIN_PARAM, "MAIN", "main");
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;

			add_entry_functb(_INT, "main");
			pv.clear();
			fill_params((yyvsp[-2].node));
			set_params("main");
			check_returning(_INT, "main");
		}
#line 2510 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 774 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_INT, _MAIN, "MAIN","main");
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
			add_entry_functb(_INT, "main");
			check_returning(_INT, "main");
		}
#line 2522 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 781 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID, _MAIN_PARAM, "MAIN", "main");
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
			add_entry_functb(_VOID, "main");
			pv.clear();
			fill_params((yyvsp[-2].node));
			set_params("main");
			check_returning(_VOID, "main");
		}
#line 2538 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 792 "g3.y" /* yacc.c:1646  */
    {
			//cout << "5" << endl;
			struct AST* nnode=newnode(_VOID, _MAIN, "MAIN", "main");
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
			add_entry_functb(_VOID, "main");
			check_returning(_VOID, "main");
		}
#line 2551 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 800 "g3.y" /* yacc.c:1646  */
    {
			main_pres=0;
			(yyval.node) = newnode(_VOID,_ERROR,"NO_MAIN","");
		}
#line 2560 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 804 "g3.y" /* yacc.c:1646  */
    {
							
							//printing the error message in header declaration
							/*caught=true;
							sprintf (str, "in main function");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(2);
							
							yyclearin;yyerrok;
					   	}
#line 2580 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 819 "g3.y" /* yacc.c:1646  */
    {
							
							//printing the error message in header declaration
							/*caught=true;
							sprintf (str, "in main function");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(3);
							
							yyclearin;yyerrok;
					   	}
#line 2600 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 838 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-4].string_val));
			DataType d=(yyvsp[-5].node)->d_type;
			struct AST* nnode=newnode(d, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			(nnode->v).push_back((yyvsp[-2].node));
			(yyval.node) = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(d, s);
				pv.clear();
				fill_params((yyvsp[-2].node));
				set_params(s);
			}
		}
#line 2622 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 855 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-3].string_val));
			DataType d=(yyvsp[-4].node)->d_type;
			struct AST* nnode=newnode(d, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			(yyval.node) = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(d, s);
			}
		}
#line 2640 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 868 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-4].string_val));
			struct AST* nnode=newnode(_VOID, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			(nnode->v).push_back((yyvsp[-2].node));
			(yyval.node) = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(_VOID, s);
				pv.clear();
				fill_params((yyvsp[-2].node));
				set_params(s);
			}
		}
#line 2661 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 884 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-3].string_val));
			struct AST* nnode=newnode(_VOID, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			(yyval.node) = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(_VOID, s);
			}
		}
#line 2678 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 896 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in function declaration");

							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(4);
							
							yyclearin;yyerrok;
			   	}
#line 2698 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 912 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in function declaration");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(5);
							
							yyclearin;yyerrok;
			   	}
#line 2717 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 930 "g3.y" /* yacc.c:1646  */
    {

					(yyval.node) = newnode(_VOID,_SEMI_COMMA,"SEMI_COMMA","");

		}
#line 2727 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 935 "g3.y" /* yacc.c:1646  */
    {
							
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							/*caught=true;
							sprintf (str, "Missing ';' ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/


							yyerrok;
							
							
			   	}
#line 2748 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 953 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter param" << endl;
			/*map<string, struct symtb> mm;
			symbolTable.push_back(mm);*/
			//cout << "Size in param " << symbolTable.size() << endl;
			struct AST* nnode=newnode(_VOID, _PARAMETERS, "PARAMETERS", "");
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 2762 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 966 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-4].string_val));
			//cout << "funcdef" << endl;
			DataType d = (yyvsp[-5].node)->d_type;
			//cout << "funcdef2" << endl;
			struct AST* nnode=newnode(d, _FUNCTION_DEF_PARAM, s+"_FUNCTION", s);
			(nnode->v).push_back((yyvsp[-5].node));
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			//check if already defined
			if(is_in_map(s)){
				pv.clear();
				fill_params((yyvsp[-2].node));
				check_validity_function_p(s,d);
			}else{
				add_entry_functb(d, s);
				pv.clear();
				fill_params((yyvsp[-2].node));
				set_params(s);
			}
			check_returning(d, s);
			(yyval.node) = nnode;
		}
#line 2790 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 989 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-3].string_val));
			DataType d = (yyvsp[-4].node)->d_type;
			struct AST* nnode=newnode(d, _FUNCTION_DEF, s+"_FUNCTION", s);
			(nnode->v).push_back((yyvsp[-4].node));
			(nnode->v).push_back((yyvsp[0].node));
			//check if already defined
			if(is_in_map(s)){
				check_validity_function(s,d);
			}else{
				add_entry_functb(d, s);
			}
			check_returning(d, s);
			(yyval.node) = nnode;
		}
#line 2810 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1004 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-4].string_val));
			struct AST* nnode=newnode(_VOID, _FUNCTION_DEF_PARAM_VOID, s+"_FUNCTION", s);
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			//check if already defined
			if(is_in_map(s)){
				pv.clear();
				fill_params((yyvsp[-2].node));
				check_validity_function_p(s,_VOID);
			}else{
				add_entry_functb(_VOID, s);
				pv.clear();
				fill_params((yyvsp[-2].node));
				set_params(s);
			}
			check_returning(_VOID, s);
			(yyval.node) = nnode;
		}
#line 2834 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1023 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-3].string_val));
			struct AST* nnode=newnode(_VOID, _FUNCTION_DEF_VOID, s+"_FUNCTION", s);
			(nnode->v).push_back((yyvsp[0].node));
			//check if already defined
			if(is_in_map(s)){
				check_validity_function(s,_VOID);
			}else{
				add_entry_functb(_VOID, s);
			}
			check_returning(_VOID, s);
			(yyval.node) = nnode;
		}
#line 2852 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1036 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, "in function definition");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							yyerrok;
							
							
			   	}
#line 2871 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1054 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter here" << endl;
			//cout << "enter here1" << endl;
			//cout << $1->value << endl;
			//cout << "enter here2" << endl;
			struct AST* nnode=newnode((yyvsp[0].node)->d_type, _FACTOR_CONS, "Constant_factor "+ (yyvsp[0].node)->value, (yyvsp[0].node)->value);
			//cout << "now here" << endl;
			(nnode->v).push_back((yyvsp[0].node));

			(yyval.node)=nnode;
		}
#line 2887 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1065 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			struct AST* nnode=newnode(_VOID, _FACTOR_ID, "Id_factor "+s, s);
			DataType d=find_type_id(s);
			nnode->d_type=d;
			(yyval.node)=nnode;
		}
#line 2899 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1072 "g3.y" /* yacc.c:1646  */
    {

			string s((yyvsp[-2].string_val));
			struct AST* nnode=newnode(_VOID, FUNC_CALL, s + "()", s);
			nnode->d_type=_UNKNOWN;
			
			if(!is_in_map(s)){
				semantic_err=1;
				cout << s << " function is not defined\n";
			}else{
				map<string, struct functb>::iterator mp1;
				mp1=functionTable.find(s);
				if(mp1!=functionTable.end()){
					if((mp1->second).params.size()!=0){
						semantic_err=1;
						cout << s << " given argument expecting none\n";
					}
				}
				DataType d=find_return_type(s);
				nnode->d_type=d;
			}
			arg_v.clear();
			(yyval.node)=nnode;

		}
#line 2929 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1097 "g3.y" /* yacc.c:1646  */
    {

			string s((yyvsp[-3].string_val));
			struct AST* nnode=newnode(_VOID, _ARG_FUNC_CALL, s + "()", s);
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->d_type=_UNKNOWN;
			
			if(!is_in_map(s)){
				semantic_err=1;
				cout << s << " function is not defined\n";
			}else{
				check_args(s);
				DataType d=find_return_type(s);
				nnode->d_type=d;
			}
			arg_v.clear();
			(yyval.node)=nnode;
		}
#line 2952 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1115 "g3.y" /* yacc.c:1646  */
    {

			if((yyvsp[-1].node)->d_type!=_INT)
			{
				//printf("Expression in array index must be int\n");
				stringstream ss;
				ss<<"Expression in array index must be int " ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
				
			}
			string s((yyvsp[-3].string_val));

			struct AST* nnode=newnode(_VOID, _FACTOR_ID, s + "[" + (yyvsp[-1].node)->value + "]", s);
			DataType d=find_type_id(s);
			nnode->d_type=d;
			(nnode->v).push_back((yyvsp[-1].node));
			(yyval.node)=nnode;
		}
#line 2976 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1134 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, "in expression1 ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(6);
							
							yyclearin;yyerrok;
			   	}
#line 2995 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1149 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, "in expression ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(7);
							
							yyclearin;yyerrok;
							//cout<<"ho gaya"<<yytext<<endl;
			   	}
#line 3015 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1170 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode((yyvsp[0].node)->d_type, _EXPR_MICROVAL, "EXPR_microval", (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3025 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1175 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode((yyvsp[-1].node)->d_type, _EXPR_BRACKET, "EXPR_expr", "("+(yyvsp[-1].node)->value+")");
			(nnode->v).push_back((yyvsp[-1].node));
			(yyval.node)=nnode;
		}
#line 3035 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1180 "g3.y" /* yacc.c:1646  */
    {
			DataType d=(yyvsp[0].node)->d_type;

			if((yyvsp[-1].node)->value=="~"){
				if(!(d==_INT || d==_FLOAT) ){
					stringstream ss;
					ss<<"type mismatch for ~" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
					
					//printf("type mismatch for ~\n");
					
				}
			}else if((yyvsp[-1].node)->value=="!"){
				if(!(d==_BOOL) ){
					stringstream ss;
					ss<<"type mismatch for !" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
					//printf("type mismatch for !\n");
					//cout << "type mismatch for !" << endl;
				}
			}
			struct AST* nnode=newnode((yyvsp[0].node)->d_type, _EXPR_UNARY, "EXPR_OP_"+(yyvsp[-1].node)->value, (yyvsp[-1].node)->value+" "+(yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3068 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1208 "g3.y" /* yacc.c:1646  */
    {
			DataType d=_VOID;
			check_validity((yyvsp[-1].node)->value, (yyvsp[-2].node)->d_type, (yyvsp[0].node)->d_type,&d);
			struct AST* nnode=newnode(d, _EXPR_MICRO_OP, "EXPR_OP_"+(yyvsp[-1].node)->value, (yyvsp[-2].node)->value + " " + (yyvsp[-1].node)->value + " " + (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3082 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1217 "g3.y" /* yacc.c:1646  */
    {
			DataType d=_VOID;
			check_validity((yyvsp[-1].node)->value, (yyvsp[-2].node)->d_type, (yyvsp[0].node)->d_type,&d);
			struct AST* nnode=newnode(d, _EXPR_MICRO_ASS_OP, "EXPR_OP_"+(yyvsp[-1].node)->value, (yyvsp[-2].node)->value + " " + (yyvsp[-1].node)->value + " " + (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3096 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1226 "g3.y" /* yacc.c:1646  */
    {
			DataType d=_VOID;
			check_validity((yyvsp[-1].node)->value, (yyvsp[-3].node)->d_type, (yyvsp[0].node)->d_type,&d);
			struct AST* nnode=newnode(d, _EXPR_EXPR_OP, "EXPR_OP_"+(yyvsp[-1].node)->value,"("+(yyvsp[-3].node)->value + ") " + (yyvsp[-1].node)->value + " " + (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[-3].node));
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3110 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1236 "g3.y" /* yacc.c:1646  */
    {

								/*caught=true;
							sprintf (str, "in expression ");
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
								 
								fprintf(stderr, "\n");									   
							caught=false;*/
								(yyval.node) = newnode(_VOID,_ERROR,"error","");
								eat_to_newline(8);
								
								yyclearin;yyerrok;
			}
#line 3129 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1252 "g3.y" /* yacc.c:1646  */
    {

								/*caught=true;
							sprintf (str, "in expression ");
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
								 
								fprintf(stderr, "\n");									   
							caught=false;*/
								(yyval.node) = newnode(_VOID,_ERROR,"error","");
								eat_to_newline(9);
								
								yyclearin;yyerrok;
			}
#line 3148 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1266 "g3.y" /* yacc.c:1646  */
    {

								/*caught=true;
							sprintf (str, "in expression 2");
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
								 
								fprintf(stderr, "\n");									   
							caught=false;*/
								(yyval.node) = newnode(_VOID,_ERROR,"error","");
								eat_to_newline(10);
								
								
			}
#line 3167 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1280 "g3.y" /* yacc.c:1646  */
    {

								caught=true;
								/*errcount++;
								syntactic_err=1;
							
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d syntax error, unexpected %s, expecting operator before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,yytext,yytext);
								 
								fprintf(stderr, "\n");
																	   */
								(yyval.node) = newnode(_VOID,_ERROR,"error","");
								sprintf(str,"%d.%d - %d.%d syntax error, unexpected token, expecting operator in the expression ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column);
								yyerror(str);
								caught=false;
								eat_to_newline(11);
								
								
								
								
			}
#line 3193 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1301 "g3.y" /* yacc.c:1646  */
    {
								
								caught=true;
								/*errcount++;
								syntactic_err=1;
							
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d syntax error, unexpected %s, expecting operator before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,yytext,yytext);
								 
								fprintf(stderr, "\n");									   */
								(yyval.node) = newnode(_VOID,_ERROR,"error","");
								sprintf(str,"%d.%d - %d.%d syntax error, unexpected token, expecting operator in the expression  ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column);
								yyerror(str);
								caught=false;
								eat_to_newline(12);
								yyclearin;yyerrok;
								
								
			}
#line 3217 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1325 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_ARGLIST;
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="ARG_LIST";			
			(yyval.node)=nnode;
		}
#line 3230 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1333 "g3.y" /* yacc.c:1646  */
    {
			(yyval.node)=(yyvsp[0].node);
		}
#line 3238 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1336 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, "in parameter list");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(13);
							
							yyclearin;yyerrok;
			   	}
#line 3257 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1357 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID, _ARG_CONS, "Arg : "+ (yyvsp[0].node)->value, (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
			arg_v.push_back((yyvsp[0].node)->d_type);
		}
#line 3268 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1363 "g3.y" /* yacc.c:1646  */
    {  //add type of this in symbol table
			string s((yyvsp[0].string_val));
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _ARG_ID, "Arg : " + s, s);
			(yyval.node) = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			arg_v.push_back(d1);
		}
#line 3289 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1383 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3299 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1388 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3309 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1393 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3319 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1398 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", (yyvsp[0].node)->value);
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
		}
#line 3329 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1413 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("&&");
			nnode->code="&&";
			(yyval.node)=nnode;
		}
#line 3339 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1418 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("||");
			nnode->code="||";
			(yyval.node)=nnode;
		}
#line 3349 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1426 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("+");
			nnode->code="+";
			(yyval.node)=nnode;
		}
#line 3359 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1431 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("-");
			nnode->code="-";
			(yyval.node)=nnode;
		}
#line 3369 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1436 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("*");
			nnode->code="-";
			(yyval.node)=nnode;
		}
#line 3379 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1441 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("/");
			nnode->code="/";
			(yyval.node)=nnode;
		}
#line 3389 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1446 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("%");
			nnode->code="%";
			(yyval.node)=nnode;
		}
#line 3399 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1453 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("=");
			nnode->code="=";
			(yyval.node)=nnode;
		}
#line 3409 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1458 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("+=");
			nnode->code="+=";
			(yyval.node)=nnode;
		}
#line 3419 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1463 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("-=");
			nnode->code="-=";
			(yyval.node)=nnode;
		}
#line 3429 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1468 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("*=");
			nnode->code="*=";
			(yyval.node)=nnode;
		}
#line 3439 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1473 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("/=");
			nnode->code="/=";
			(yyval.node)=nnode;
		}
#line 3449 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1478 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("%=");
			nnode->code="%=";
			(yyval.node)=nnode;
		}
#line 3459 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1483 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("&=");
			nnode->code="&=";
			(yyval.node)=nnode;
		}
#line 3469 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1488 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("^=");
			nnode->code="^=";
			(yyval.node)=nnode;
		}
#line 3479 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1493 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("|=");
			nnode->code="|=";
			(yyval.node)=nnode;
		}
#line 3489 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1500 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("<");
			nnode->code="<";
			(yyval.node)=nnode;
		}
#line 3499 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1505 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode(">");
			nnode->code=">";
			(yyval.node)=nnode;
		}
#line 3509 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1510 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("<=");
			nnode->code="<=";
			(yyval.node)=nnode;
		}
#line 3519 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1515 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode(">=");
			nnode->code=">=";
			(yyval.node)=nnode;
		}
#line 3529 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1520 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("==");
			nnode->code="==";
			(yyval.node)=nnode;
		}
#line 3539 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1525 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("!=");
			nnode->code="!=";
			(yyval.node)=nnode;
		}
#line 3549 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1533 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("&");
			nnode->code="&";
			(yyval.node)=nnode;
		}
#line 3559 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1538 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("|");
			nnode->code="|";
			(yyval.node)=nnode;
		}
#line 3569 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1543 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("^");
			nnode->code="^";
			(yyval.node)=nnode;
		}
#line 3579 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1551 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("!");
			nnode->code="!";
			(yyval.node)=nnode;
		}
#line 3589 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1556 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newopnode("~");
			nnode->code="~";
			(yyval.node)=nnode;
		}
#line 3599 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1564 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter stmntlist" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_List";
			(yyval.node) = nnode;
		}
#line 3611 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1571 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_List";
			(yyval.node) = nnode;
		}
#line 3623 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1581 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3634 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1587 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3645 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1593 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3656 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1599 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3667 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1605 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3678 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1611 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3689 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1617 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3700 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1623 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="Statement_Types";
			(yyval.node) = nnode;
		}
#line 3711 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1632 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			nnode->n_type=_PRINT_STRING;
			nnode->code="PRINTSTR";
			(yyval.node)=nnode;
		}
#line 3723 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1646 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			//(nnode->v).push_back($3);
			(nnode->v).push_back((yyvsp[-2].node));
			nnode->n_type=_PRINT_INT;
			nnode->code="PRINTINT";
			(yyval.node)=nnode;
		}
#line 3736 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1654 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			nnode->n_type=_PRINT_FLOAT;
			nnode->code="PRINTFLOAT";
			(yyval.node)=nnode;
		}
#line 3748 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1669 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			//(nnode->v).push_back($5);
			nnode->n_type=_GET_STRING;
			nnode->code="GETSTRING";
			(yyval.node)=nnode;
		}
#line 3761 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1677 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			//(nnode->v).push_back($5);
			nnode->n_type=_GET_FLOAT;
			nnode->code="GETFLOAT";
			(yyval.node)=nnode;
		}
#line 3774 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1685 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			//(nnode->v).push_back($5);
			nnode->n_type=_GET_INT;
			nnode->code="GETINT";
			(yyval.node)=nnode;
		}
#line 3787 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1693 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration


							/*caught=true;
							sprintf (str, "in out()function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(14);
							
							yyclearin;yyerrok;
			   	}
#line 3808 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1709 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration


							/*caught=true;
							sprintf (str, "in out()function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(14);
							
							yyclearin;yyerrok;
			   	}
#line 3829 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1725 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration


							/*caught=true;
							sprintf (str, "in out()function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(14);
							
							yyclearin;yyerrok;
			   	}
#line 3850 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1741 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in in() function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(15);
							
							yyclearin;yyerrok;
			   	}
#line 3869 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1755 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in in() function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(15);
							
							yyclearin;yyerrok;
			   	}
#line 3888 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1769 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in in() function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(15);
							
							yyclearin;yyerrok;
			   	}
#line 3907 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1786 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _FACTOR_ID, "Arg : " + s, s);
			(yyval.node) = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			if(d1 != _INT)
			{
					stringstream ss;
					ss<<"Argument to printInt() must be Integer" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);

			}
		}
#line 3935 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1809 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter constant number" << endl;
			struct AST* nnode=newnode();
			nnode->d_type=_INT;
			nnode->n_type=_CONSTANT_NUMP;
			int a=(yyvsp[0].int_val);
			stringstream ss;
			ss << a;
			string val = ss.str();
			//cout << "value_:_" << val << endl;
			nnode->code = val;
			nnode->value = val;
			(yyval.node)=nnode;
		}
#line 3954 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1826 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _FACTOR_ID, "Arg : " + s, s);
			(yyval.node) = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			if(d1 != _FLOAT)
			{
					stringstream ss;
					ss<<"Argument to printFloat() must be Float" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);

			}
		}
#line 3982 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1849 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->d_type=_FLOAT;
			nnode->n_type=_CONSTANT_FLOATP;
			double a=(yyvsp[0].float_val);
			stringstream ss;
			ss << a;
			string val = ss.str();
			nnode->code = val;
			nnode->value = val;
			(yyval.node)=nnode;
		}
#line 3999 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1864 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _ARG_ID, "Arg : " + s, s);
			(yyval.node) = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			if(d1 != _STRING)
			{
					stringstream ss;
					ss<<"Argument to printString() must be STRING" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);

			}
		}
#line 4027 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1887 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->d_type=_STRING;
			nnode->n_type=_CONSTANT;
			nnode->code = (yyvsp[0].string_val);
			nnode->value = (yyvsp[0].string_val);
			(yyval.node)=nnode;
		}
#line 4040 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1897 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _FACTOR_ID, "Arg : " + s, s);
			(yyval.node) = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			if(d1 != _STRING)
			{
					stringstream ss;
					ss<<"Argument to getString() must be string" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);

			}
		}
#line 4068 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1923 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _FACTOR_ID, "Arg : " + s, s);
			(yyval.node) = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			if(d1 != _INT)
			{
					stringstream ss;
					ss<<"Argument to getInt() must be Integer" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);

			}
		}
#line 4096 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1948 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _FACTOR_ID, "Arg : " + s, s);
			(yyval.node) = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			if(d1 != _FLOAT)
			{
					stringstream ss;
					ss<<"Argument to getFloat must be Float" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);

			}
		}
#line 4124 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1974 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->n_type=_CASE;
			nnode->code="CASE_:";
			(yyval.node)=nnode;
		}
#line 4136 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1981 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in case statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(16);
							
							yyclearin;yyerrok;
			   	}
#line 4155 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 2000 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_CASE;
			nnode->code="OTHERWISE_:";
			(yyval.node)=nnode;
		}
#line 4167 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 2007 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in otwise statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(17);
							
							yyclearin;yyerrok;
			   	}
#line 4186 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 2021 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID,_CASE,"No_OTHERWISE","");
			(yyval.node)=nnode;
		}
#line 4195 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 2029 "g3.y" /* yacc.c:1646  */
    {

			(yyval.node) = newnode(_VOID,_COLON,"COLON","");
		}
#line 4204 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 2033 "g3.y" /* yacc.c:1646  */
    {
							/*caught=true;
							sprintf (str, "Missing ':' ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							yyerrok;
							
							
			   	}
#line 4222 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 2049 "g3.y" /* yacc.c:1646  */
    {
			cout << "23" << endl;
			struct AST* nnode=newnode();
			(yyval.node) = nnode;
		}
#line 4232 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 2054 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter func comp_stmnt" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->n_type=_COMPOUND_STMNT;
			nnode->code="Compound_statements";
			(yyval.node) = nnode;
			//cout << "exit func comp_stmnt" << endl;
		}
#line 4246 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 2063 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, " ");
							eat_to_newline(18);
							if(eof==true)
							{
								if(yylloc.first_line)
							    	fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str," the end of file");
							}
							else 
							{
								if(yylloc.first_line)
							    	fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							


							}
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							yyclearin;yyerrok;
							
							
			   	}
#line 4276 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 2092 "g3.y" /* yacc.c:1646  */
    {
			//cout << "7" << endl;
			struct AST* nnode=newnode();
			(yyval.node) = nnode;
		}
#line 4286 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 2097 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter comp_stmnt" << endl;
			struct AST* nnode = newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->code="Compound_statements";
			nnode->n_type=_COMPOUND_STMNT;
			(yyval.node) = nnode;
		}
#line 4299 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 2105 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, " ");
							eat_to_newline(19);
							if(eof==true)
							{
								if(yylloc.first_line)
							    	fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str," the end of file");
							}
							else 
							{
								if(yylloc.first_line)
							    	fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							


							}
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							
							yyclearin;yyerrok;
							
							
			   	}
#line 4330 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 2135 "g3.y" /* yacc.c:1646  */
    {
			map<string, struct symtb> mm;
			symbolTable.push_back(mm);
			scope++;
		}
#line 4340 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 2143 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter '}'" << endl;
			if(symbolTable.size()>0){
				symbolTable.pop_back();
			}
			scope--;
		}
#line 4352 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 2153 "g3.y" /* yacc.c:1646  */
    {
			map<string, struct symtb> mm;
			symbolTable.push_back(mm);
			scope++;
		}
#line 4362 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 2161 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter '}'" << endl;
			if(symbolTable.size()>0){
				symbolTable.pop_back();
			}
			scope--;
		}
#line 4374 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 2171 "g3.y" /* yacc.c:1646  */
    {
			/*expr type must be bool*/
			if((yyvsp[-2].node)->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_IF;
			nnode->code="IF";
			(yyval.node)=nnode;
		}
#line 4395 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 2187 "g3.y" /* yacc.c:1646  */
    {
			/*expr type must be bool*/
			if((yyvsp[-4].node)->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-4].node));
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_IFELSE;
			nnode->code="IF_ELSE";
			(yyval.node)=nnode;
		}
#line 4417 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 2218 "g3.y" /* yacc.c:1646  */
    {
			/*expr type must be bool*/
			if((yyvsp[-5].node)->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-5].node));
			(nnode->v).push_back((yyvsp[-3].node));
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_IF_ELSEIF_ELSE;
			nnode->code="IF_ELIF-ELSE";
			(yyval.node)=nnode;
		}
#line 4440 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 2237 "g3.y" /* yacc.c:1646  */
    {
			/*expr type must be bool*/
			if((yyvsp[-3].node)->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-3].node));
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_IF_ELSEIF;
			nnode->code="IF_ELIF";
			(yyval.node)=nnode;
		}
#line 4462 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 2255 "g3.y" /* yacc.c:1646  */
    {
			/*expr type must be int, float, char, string*/
			if(!((yyvsp[-4].node)->d_type==_FLOAT || (yyvsp[-4].node)->d_type==_INT || (yyvsp[-4].node)->d_type==_CHAR || (yyvsp[-4].node)->d_type==_STRING)){
				//printf("Expression in switch must be one of int,float,char,string type\n");
				stringstream ss;
				ss<<"Expression in switch must be one of int,float,char,string type" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-4].node));
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->n_type=_SWITCH;
			nnode->code="SWITCH_CASE";
			(yyval.node)=nnode;
		}
#line 4483 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 2271 "g3.y" /* yacc.c:1646  */
    {

							/*caught=true;
							sprintf (str, "in if statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(20);
							
							yyclearin;yyerrok;		
			}
#line 4502 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 2286 "g3.y" /* yacc.c:1646  */
    {



							/*caught=true;
							sprintf (str, "in switch statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(21);
							
							yyclearin;yyerrok;		
			
		}
#line 4524 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 2308 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID, _ELIF_LIST, "ELIF_LIST", "");
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			//(nnode->v).push_back($6);
			(yyval.node) = nnode;
		}
#line 4536 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 2315 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID, _ELIF, "ELIF", "");
			(nnode->v).push_back((yyvsp[0].node));
			//(nnode->v).push_back($5);
			(yyval.node) = nnode;
		}
#line 4547 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 2321 "g3.y" /* yacc.c:1646  */
    {

							/*caught=true;
							sprintf (str, "in if statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(22);
							
							yyclearin;yyerrok;		
			}
#line 4566 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 2339 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID, _ELIF_PART, "ELIF_LIST", "");
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			//(nnode->v).push_back($6);
			(yyval.node) = nnode;
		}
#line 4578 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 2349 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_LABELED_STATEMENT","");
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
		}
#line 4588 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 2354 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_STATEMENT_STMNT","");
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
		}
#line 4598 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 2364 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->code="SWITCH_LABELED_STATEMENT";
			(yyval.node) = nnode;
		}
#line 4610 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 2375 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_STATEMENT_LIST","");
			(nnode->v).push_back((yyvsp[-1].node));
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
		}
#line 4621 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 2382 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_STATEMENT","");
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node) = nnode;
		}
#line 4631 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 2391 "g3.y" /* yacc.c:1646  */
    {
			if((yyvsp[-2].node)->d_type!=_BOOL){
				//printf("Expression in while must be bool\n");
				stringstream ss;
				ss<<"Expression in while must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_WHILE;
			nnode->code="WHILE";
			(yyval.node)=nnode;
		}
#line 4651 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 2406 "g3.y" /* yacc.c:1646  */
    {
			if((yyvsp[-2].node)->d_type!=_BOOL){
				//printf("Expression in while must be bool\n");
				stringstream ss;
				ss<<"Expression in while must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-5].node));
			(nnode->v).push_back((yyvsp[-2].node));
			nnode->n_type=_DOWHILE;
			nnode->code="DO_WHILE";
			(yyval.node)=nnode;
		}
#line 4671 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 2421 "g3.y" /* yacc.c:1646  */
    {

			
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-6].node));
			(nnode->v).push_back((yyvsp[-4].node));
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_FOR;
			nnode->code="FOR";
			(yyval.node)=nnode;




		}
#line 4692 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 2438 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, "in while body");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(23);
							
							yyclearin;yyerrok;
			   	}
#line 4711 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 2452 "g3.y" /* yacc.c:1646  */
    {
							
							/*caught=true;
							sprintf (str, "in while loop");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(24);
							
							yyclearin;yyerrok;
			   	}
#line 4730 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 2466 "g3.y" /* yacc.c:1646  */
    {
							/*caught=true;
							sprintf (str, "in do-while loop");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(25);
							
							yyclearin;yyerrok;

		}
#line 4749 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 2480 "g3.y" /* yacc.c:1646  */
    {

							/*caught=true;
							sprintf (str, "in for loop");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(26);
							
							yyclearin;yyerrok;		
			}
#line 4768 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 2497 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_EXPR;
			nnode->code="Expression__list";
			(yyval.node) = nnode;
			//cout << "exit expr_stmnt" << endl;
		}
#line 4782 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 2506 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_EXPR;
			nnode->code="Expression";
			(yyval.node) = nnode;
			//cout << "exit expr_stmnt" << endl;
		}
#line 4795 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 2514 "g3.y" /* yacc.c:1646  */
    {

					(yyval.node) = newnode(_VOID,_ERROR,"error","");
					eat_to_newline(40);
					yyclearin;yyerror;
		}
#line 4806 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 2526 "g3.y" /* yacc.c:1646  */
    {

			if((yyvsp[0].node)->d_type!=_BOOL){
				//printf("Conditional Expression in for must be bool\n");
				stringstream ss;
				ss<<"Conditional Expression in for must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}

			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_EXPR;
			nnode->code="cond_Expression_list";
			(yyval.node) = nnode;
			
		}
#line 4829 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 2545 "g3.y" /* yacc.c:1646  */
    {
			if((yyvsp[0].node)->d_type!=_BOOL){
				//printf("Conditional Expression in for must be bool\n");
				stringstream ss;
				ss<<"Conditional Expression in for must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_EXPR;
			nnode->code="Expression";
			(yyval.node) = nnode;
			
		}
#line 4849 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 2561 "g3.y" /* yacc.c:1646  */
    {

					(yyval.node) = newnode(_VOID,_ERROR,"error","");
					eat_to_newline(40);
					yyclearin;yyerror;
		}
#line 4860 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 2570 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_STATEMENT;
			(yyval.node) = nnode;
		}
#line 4870 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 2575 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter expr_stmnt" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->n_type=_STATEMENT;
			nnode->code="Expression_statement";
			(yyval.node) = nnode;
			//cout << "exit expr_stmnt" << endl;
		}
#line 4884 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 2587 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_BREAK_STATEMENT;
			nnode->code="BREAK";
			(yyval.node) = nnode;
		}
#line 4895 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 2593 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_CONTINUE_STATEMENT;
			nnode->code="CONTINUE";
			(yyval.node) = nnode;
		}
#line 4906 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 2599 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_RETURN_STATEMENT;
			nnode->code="RETURN";
			(yyval.node) = nnode;
			return_v.push_back(_VOID);
		}
#line 4918 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 2606 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->n_type=_RETURNEXP_STATEMENT;
			nnode->d_type=(yyvsp[-1].node)->d_type;
			nnode->code="RETURN_Expression";
			(yyval.node) = nnode;
			return_v.push_back((yyvsp[-1].node)->d_type);
		}
#line 4932 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 2618 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->n_type=_STATEMENT;
			nnode->code="Exit";
			(yyval.node) = nnode;
		}
#line 4943 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 2624 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in exit statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(27);
							
							yyclearin;yyerrok;
			   	}
#line 4962 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 2641 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter constant number" << endl;
			struct AST* nnode=newnode();
			nnode->d_type=_INT;
			nnode->n_type=_CONSTANT;
			int a=(yyvsp[0].int_val);
			stringstream ss;
			ss << a;
			string val = ss.str();
			//cout << "value_:_" << val << endl;
			nnode->code = val;
			nnode->value = val;
			(yyval.node)=nnode;
		}
#line 4981 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 2655 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->d_type=_FLOAT;
			nnode->n_type=_CONSTANT;
			double a=(yyvsp[0].float_val);
			stringstream ss;
			ss << a;
			string val = ss.str();
			nnode->code = val;
			nnode->value = val;
			(yyval.node)=nnode;
		}
#line 4998 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 2667 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->d_type=_CHAR;
			nnode->n_type=_CONSTANT;
			string val(1,(yyvsp[0].char_val));
			nnode->code = val;
			nnode->value = val;
			(yyval.node)=nnode;
		}
#line 5012 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 2676 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->d_type=_STRING;
			nnode->n_type=_CONSTANT;
			nnode->code = (yyvsp[0].string_val);
			nnode->value = (yyvsp[0].string_val);
			(yyval.node)=nnode;
		}
#line 5025 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 2684 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode=newnode();
			nnode->d_type=_BOOL;
			nnode->n_type=_CONSTANT;
			if((yyvsp[0].bool_val)==true){
				nnode->code = "True";
				nnode->value = "True";
			}else if((yyvsp[0].bool_val)==false){
				nnode->code = "False";
				nnode->value = "False";
			}
			(yyval.node)=nnode;
		}
#line 5043 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 2700 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter paramlist single" << endl;
			string s((yyvsp[0].string_val));
			struct AST* nnode = newnode(_VOID, _PARA_DEC, "PARAMETER_DECLARATION", s);
			(nnode->v).push_back((yyvsp[-1].node));
			(yyval.node)=nnode;
			//cout << "call set_type" << endl;
			set_type((yyvsp[-1].node)->d_type, s);
			//cout << "return set_type" << endl;
		}
#line 5058 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 2710 "g3.y" /* yacc.c:1646  */
    {
			//cout << "enter paramlist double" << endl;
			string s((yyvsp[0].string_val));
			struct AST* nnode = newnode(_VOID, _PARA_DEC_LIST, "PARAMETER_DECLARATION_LIST", s);
			(nnode->v).push_back((yyvsp[-3].node));
			(nnode->v).push_back((yyvsp[-1].node));
			(yyval.node)=nnode;
			set_type((yyvsp[-1].node)->d_type, s);
		}
#line 5072 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 2719 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in parameter list");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(28);
							
							yyclearin;yyerrok;
			   	}
#line 5091 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 2737 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->n_type=_DEC;
			nnode->code	= "DECLARATION";
			(yyval.node)=nnode;
			rec_set_type((yyvsp[-2].node)->d_type, (yyvsp[-1].node));
		}
#line 5105 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 2747 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in  declaration
							
							/*sprintf (str, "in  declaration ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(29);
							
							yyclearin;yyerrok;
			   	}
#line 5123 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 2760 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in  declaration
							/*sprintf (str, "in  declaration " );
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(30);
							
							yyclearin;yyerrok;
			   	}
#line 5140 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 2777 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[-1].node));
			nnode->n_type=_DEC;
			nnode->code	= "DECLARATION";
			(yyval.node)=nnode;
			rec_set_type((yyvsp[-2].node)->d_type, (yyvsp[-1].node));
		}
#line 5154 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 2786 "g3.y" /* yacc.c:1646  */
    {
							//printing the error message in  declaration
							
							/*sprintf (str, "in  declaration ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(31);
							
							yyclearin;yyerrok;
			   	}
#line 5172 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 2807 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode();
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_DEC;
			nnode->code="DECLARATIONS_LIST";
			(yyval.node)=nnode;
		}
#line 5184 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 2814 "g3.y" /* yacc.c:1646  */
    {
			struct AST* nnode = newnode();
			(nnode->v).push_back((yyvsp[-2].node));
			(nnode->v).push_back((yyvsp[0].node));
			nnode->n_type=_DEC;
			nnode->code="DECLARATIONS_LIST";
			(yyval.node)=nnode;
		}
#line 5197 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 2822 "g3.y" /* yacc.c:1646  */
    {
							
							//printing the error message in variable declaration
							/*sprintf (str, "in declaration");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							(yyval.node) = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(32);
							yyclearin;yyerrok;
			   	}
#line 5214 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 2837 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[0].string_val));
			struct AST* nnode=newnode(_VOID,_DEC_VAR,s,s);
			(yyval.node)=nnode;
			int i=in_current_scope(s);
			if(i==1){
				//cout << "Redefination of variable " << s << endl;
				stringstream ss;
				ss<<"Redefination of variable "<< s ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}else{
				add_to_symtb(_UNKNOWN,scope,s,"");
			}
		}
#line 5234 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 2852 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-3].string_val));
			int a=(yyvsp[-1].int_val);
			stringstream ss;
			ss << a;
			string val = ss.str();
			struct AST* nnode=newnode(_VOID,_DEC_ARR,s+"["+val+"]",s);
			(yyval.node)=nnode;
			int i=in_current_scope(s);
			if(i==1){
				//cout << "Redefination of variable " << s << endl;
				stringstream ss;
				ss<<"Redefination of variable " << s ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}else{
				add_to_symtb(_UNKNOWN,scope,s,"");
			}
		}
#line 5258 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 2871 "g3.y" /* yacc.c:1646  */
    {
			string s((yyvsp[-2].string_val));
			if((yyvsp[0].node)->d_type==_VOID || (yyvsp[0].node)->d_type==_UNKNOWN){
				//********************************************************************************************************
				//********************************************************************************************************
				//************************yahan id=expr wala problem hai*********************************
				//********************************************************************************************************
				//********************************************************************************************************
				//********************************************************************************************************
				//printf("ID=expr, expr must not be void");
				/*stringstream ss;
				ss<<"ID=expr, expr must not be void" ;
				string err_msg = ss.str();
				semantic_error(err_msg);*/
			}
			DataType d=expc_datatype((yyvsp[0].node)->d_type);
			struct AST* nnode=newnode(d,_DECVAR_EQ,s+":=",s);
			(nnode->v).push_back((yyvsp[0].node));
			(yyval.node)=nnode;
			int i=in_current_scope(s);
			if(i==1){
				//cout << "Redefination of variable " << s << endl;
				stringstream ss;
				ss<<"Redefination of variable " << s ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}else{
				add_to_symtb(_UNKNOWN,scope,s,"");
			}
		}
#line 5293 "g3.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 2901 "g3.y" /* yacc.c:1646  */
    {
									//printing the error message in array initializer declaration
									/*caught=true;
							sprintf (str, " Error in array index ");
									if(yylloc.first_line)
									    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
									 
									fprintf(stderr, "\n");									   
							caught=false;*/
									(yyval.node) = newnode(_VOID,_ERROR,"error","");
									eat_to_newline(33);
									//cout <<"yahn aaya"<<endl;
									yyclearin;yyerrok;
			   					}
#line 5312 "g3.tab.c" /* yacc.c:1646  */
    break;


#line 5316 "g3.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2922 "g3.y" /* yacc.c:1906  */


//dot_code+="\t" + val1 +  node->code  + " -> " + val2 + (*it)->code + ";\n";

int node_no=1;
string dot_code="digraph G {\n";

void create_dot_graph(struct AST* node, string lab){
	vector<struct AST*>::iterator it;
	

	int c_num=1;
	if(node!=NULL){
		for(it=(node->v).begin();it!=(node->v).end();++it){
			stringstream s22;
			s22 << c_num;
			string val22=s22.str(); //val22 has c_num
			dot_code+="\t" + std::string("\"") + lab + std::string("\n") + node->code + std::string("\"") +  " -> " + std::string("\"") + lab + "." + val22 + std::string("\n") + (*it)->code + std::string("\"") + ";\n";
			node_no+=1;
			create_dot_graph(*it,lab + "." + val22 );
			c_num++;
		}
	}
	return;
}

/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
string cgen(struct AST* n);
string elifgen(struct AST* n, string nextLabel);
//vector<map<string, string> cgenTable;
//map<string, string>cgenm;
//cgenTable.push_back(cgenm);

static int label=0;
int num_para=0;

string getNewReg()
{
	static int count=0;
	stringstream ss;
	ss<<++count;
	
	return string("r"+ss.str());
}

string genNewLabel()
{
	
	stringstream ss;
	ss<<++label;
	return string("label"+ss.str()+":");
}

string get_cur_label(){
	stringstream ss;
	ss<<label;
	return string("label"+ss.str()+":");
}


string eliflistgen(struct AST* n, string finalLabel)
{
		if(n->n_type==_ELIF_LIST)
		{
			//string newelifLabel=genNewLabel();
			//cout<<eliflabel<<endl;
			eliflistgen(n->v[0],finalLabel);
			//string newLabel2=genNewLabel();
			elifgen(n->v[1],finalLabel);
		}
		else if(n->n_type==_ELIF)
		{
			elifgen(n->v[0],finalLabel);
		} 

	return "";
}

void global_vars()
{
	map<string, struct cgenEntry>::iterator it1;
	for(it1=global_var.begin(); it1!=global_var.end(); ++it1){
		if((it1->second).value==""){
			cout << it1->first << (it1->second).scope << " = 0" << endl; 
		}else{
			cout << it1->first << (it1->second).scope << " = " << (it1->second).value << endl;
		}
	}
}

string elifgen(struct AST* n, string finalLabel)
{
		cout<<get_cur_label()<<endl;
		string r1=cgen(n->v[0]);
		string trueLabel = genNewLabel();
		
		
		cout<<"if "<<r1<<" goto "<<trueLabel<<endl;
		cout<<"goto "<<genNewLabel()<<endl;
		cout<<trueLabel<<endl;
		cgen((n->v)[1]);
		cout<< "goto "<<finalLabel<<endl;
		return "";
}

string cgen(struct AST* n)
{
	if(n==NULL) 
	{
		return "";
	}
	else if(n->n_type == _MAIN )
	{
		tmp_vars.clear();
		num_para=0;
		var_line_no=0;
		string s="main";
		cout<<s<<": funcbegin"<<endl;
		cout << "ParamsNum: " << num_para << endl;
		global_vars();
		cgen(n->v[0]);
		cout<<"funcend : " << tmp_vars.size() <<endl;
		add_var_list(s);
		tmp_vars.clear();
		var_line_no=0;
		return "";

	}
	else if(n->n_type==_MAIN_PARAM)
	{
		tmp_vars.clear();
		num_para=0;
		var_line_no=0;
		string s="main";
		cout<<s<<": funcbegin"<<endl;
		cgen(n->v[0]);
		cout << "ParamsNum: " << num_para << endl;
		global_vars();
		cgen(n->v[1]);
		cout<<"funcend : " << tmp_vars.size() <<endl;
		add_var_list(s);
		tmp_vars.clear();
		var_line_no=0;
		return "";
	}
	else if(n->n_type == _FUNCTION){

	    string funcLabel=genNewLabel();
		cout<<funcLabel<<endl;
		cgen(n->v[0]);
		return "";

	}
	else if(n->n_type == _COMPOUND_STMNT)
	{
		map<string, struct cgenEntry> tmp;
		scope_code++;
		cgenTable.push_back(tmp);
		if((n->v).size()==1) cgen((n->v)[0]);
		cgenTable.pop_back();
		scope_code--;
		return "";
	}
	else if(n->n_type == _DEC_VAR)
	{
		/*vector<map<string, struct cgenEntry> >::iterator tmp;
		tmp=cgenTable.back();*/
		struct cgenEntry a;
		a.scope = scope_code;
		a.value = "";
		if(scope_code==0){
			global_var.insert(pair<string, struct cgenEntry>(n->value, a));
		}else{
			cgenTable.back().insert(pair<string, struct cgenEntry>(n->value, a));	
		}
		return "";
	}
	else if(n->n_type == _DECVAR_EQ)
	{
		string R1=cgen(n->v[0]);
		string R2=n->value;
		cout << R2<<scope_code << " = " << R1 << endl;
		/*vector< map < string, struct cgenEntry> >::iterator tmp;
		tmp=cgenTable.back();*/
		struct cgenEntry a;
		a.scope = scope_code;
		a.value = R1;
		if(scope_code==0){
			global_var.insert(pair<string, struct cgenEntry>(n->value, a));
		}else{
			cgenTable.back().insert(pair<string, struct cgenEntry>(n->value, a));	
		}
		return "";
	}
	else if(n->n_type == _IF)
	{
		string r1=cgen((n->v)[0]);
		string trueLabel = genNewLabel();
		//string falseLabel = genNewLabel();
		string nextLabel = genNewLabel();
		cout<<"if "<<r1<<" goto "<<trueLabel<<endl;
		//cout<<"goto "<<falseLabel<<endl;
		cout<<trueLabel<<endl;
		cgen((n->v)[1]);
		cout<< "goto "<<nextLabel<<endl;
		//string newReg=getNewReg();
		//cout<<falseLabel<<endl; 
		cout<< nextLabel<<endl;
		return "";
	}
	else if(n->n_type == _IFELSE)
	{
		string r1=cgen((n->v)[0]);
		string trueLabel = genNewLabel();
		string falseLabel = genNewLabel();
		string nextLabel = genNewLabel();
		cout<<"if "<<r1<<" goto "<<trueLabel<<endl;
		cout<<"goto "<<falseLabel<<endl;
		cout<<trueLabel<<endl;
		cgen((n->v)[1]);
		cout<< "goto "<<nextLabel<<endl;
		//string newReg=getNewReg();
		cout<<falseLabel<<endl; 
		cgen(n->v[2]);
		cout<< nextLabel<<endl;
		return "";
	}
	else if(n->n_type == _IF_ELSEIF_ELSE)
	{
		string r1=cgen((n->v)[0]);
		string trueLabel = genNewLabel();
		//string falseLabel = genNewLabel();
		string finalLabel = genNewLabel();
		string eliflabel = genNewLabel();
		cout<<"if "<<r1<<" goto "<<trueLabel<<endl;
		cout<<"goto "<<eliflabel<<endl;
		cout<<trueLabel<<endl;
		cgen((n->v)[1]);
		cout<< "goto "<<finalLabel<<endl;
		eliflistgen(n->v[2],finalLabel);
		
		//cout<<falseLabel<<endl; 
		cout<<get_cur_label()<<endl;
		cgen(n->v[3]);
		cout<< finalLabel<<endl;
		return "";
	}
	else if(n->n_type == _IF_ELSEIF)
	{
		string r1=cgen((n->v)[0]);
		string trueLabel = genNewLabel();
		//string falseLabel = genNewLabel();
		string finalLabel = genNewLabel();
		string eliflabel = genNewLabel();
		cout<<"if "<<r1<<" goto "<<trueLabel<<endl;
		cout<<"goto "<<eliflabel<<endl;
		cout<<trueLabel<<endl;
		cgen((n->v)[1]);
		cout<< "goto "<<finalLabel<<endl;
		eliflistgen(n->v[2],finalLabel);
		
		//cout<<falseLabel<<endl; 
		cout<<get_cur_label()<<endl;
		
		cout<< finalLabel<<endl;
		return "";
	}
	else if(n->n_type == _WHILE)
	{
		string entryLabel = genNewLabel();
		cout<<entryLabel<<endl;
		string r1=cgen((n->v)[0]);
		string bodyLabel = genNewLabel();
		string exitLabel = genNewLabel();
		cout<<"if "<<r1<<" goto "<<bodyLabel<<endl;
		cout<<"goto "<<exitLabel<<endl;
		cout<<bodyLabel<<endl;
		cgen((n->v)[1]);
		cout<<"goto "<<entryLabel<<endl;
		cout<<exitLabel<<endl;
		return "";
	}
	else if(n->n_type == _DOWHILE)
	{
		
		string bodyLabel = genNewLabel();
		
		cout<<bodyLabel<<endl;
		cgen((n->v)[0]);
		/*string entryLabel = genNewLabel();
		cout<<entryLabel<<endl;*/
		string r1=cgen((n->v)[1]);
		string exitLabel = genNewLabel();
		cout<<"if "<<r1<<" goto "<<bodyLabel<<endl;
		cout<<"goto "<<exitLabel<<endl;

		cout<<exitLabel<<endl;
		return "";
	}
	else if(n->n_type == _FACTOR_ID)
	{
		string s = n->value;
		int scope_count=0;
		map<string, struct cgenEntry>::iterator it;
		vector< map < string, struct cgenEntry > >::reverse_iterator it1;
		for(it1=cgenTable.rbegin();it1!=cgenTable.rend();++it1){
			it=it1->find(s);
			if(it!=it1->end()){
				scope_count = (it->second).scope;
				break;
			}
		}
		stringstream ss;
		ss<<scope_count;
		add_in_tmp_var(n->value+ss.str());
		return n->value+ss.str();
	}
	else if(n->n_type == _FACTOR_CONS)
	{
		string reg1=getNewReg();
		string reg2=getNewReg();
		if(n->value=="True")
		{
			cout<<reg1 << " = 0"<<endl;
			cout<<reg2<<" = "<<reg1<<" == 0"<<endl;
			add_in_tmp_var(reg1);
			add_in_tmp_var(reg2);
			return reg2;
		}
		else if(n->value=="False")
		{
			cout<<reg1 << " = 1"<<endl;
			cout<<reg2<<" = "<<reg1<<" == 0"<<endl;

			add_in_tmp_var(reg1);
			add_in_tmp_var(reg2);
			return reg2;
		}
		else
			return n->value;
	}
	else if(n->n_type==FUNC_CALL)
	{
		string s=n->value;
		cout << "call " << s << endl;
		string newReg = getNewReg();
		add_in_tmp_var(newReg);
		cout << newReg << " = v0" << endl;
		return newReg;

	}
	else if(n->n_type==_ARG_FUNC_CALL)
	{
		string s=n->value;
		cgen(n->v[0]);
		cout << "call " << s << endl;
		string newReg = getNewReg();
		add_in_tmp_var(newReg);
		cout << newReg << " = v0" << endl;
		return newReg;
	}
	else if(n->n_type==_ARG_CONS)
	{
		cout << "pushArgs " << n->value << endl;
		return "";
	}
	else if(n->n_type==_ARG_ID)
	{
		string s = n->value;
		int scope_count=0;
		map<string, struct cgenEntry>::iterator it;
		vector< map < string, struct cgenEntry > >::reverse_iterator it1;
		for(it1=cgenTable.rbegin();it1!=cgenTable.rend();++it1){
			it=it1->find(s);
			if(it!=it1->end()){
				scope_count = (it->second).scope;
				break;
			}
		}
		stringstream ss;
		ss<<scope_count;
		add_in_tmp_var(n->value+ss.str());
		cout << "pushArgs " << n->value+ss.str() << endl;
		return "";
	}
	else if(n->n_type == _EXPR_MICROVAL)
	{
		
		return cgen(n->v[0]);

		
	}
	else if (n->n_type == _EXPR_BRACKET)
	{
		if((n->v[0])->n_type==_EXPR_MICROVAL){
			cout << cgen(n->v[0]) << endl;
			return "";
		}else{
			return cgen(n->v[0]);

		}
		

	}
	else if(n->n_type == _EXPR_MICRO_OP)
	{
		string r1=cgen(n->v[0]);
		string op=n->v[1]->value;
		string r2=cgen(n->v[2]);
		string newReg=getNewReg();
		if(op=="=")
			cout<<r1<<" "<<op<<" "<<r2<<endl;
		else
			cout<<newReg<<" = "<<r1<<" "<<op<<" "<<r2<<endl;
		add_in_tmp_var(newReg);
		return newReg;

	}
	else if(n->n_type == _EXPR_EXPR_OP)
	{
		string r1=cgen(n->v[0]);
		string op=n->v[1]->value;
		string r2=cgen(n->v[2]);
		string newReg=getNewReg();
		if(op=="=")
			cout<<r1<<" "<<op<<" "<<r2<<endl;
		else
			cout<<newReg<<" = "<<r1<<" "<<op<<" "<<r2<<endl;
		add_in_tmp_var(newReg);
		return newReg;

	}
	else if(n->n_type == _EXPR_MICRO_ASS_OP)
	{
		string r1=cgen(n->v[0]);
		string op=n->v[1]->value;
		string r2=cgen(n->v[2]);
		cout<<r1<<" "<<op<<" "<<r2<<endl;
		return "";
	}
	else if(n->n_type == _EXPR_UNARY)
	{
		string r1=cgen(n->v[1]);
		
		string op=n->v[0]->value;
		string newReg=getNewReg();
		if(op=="~")
		{
			cout<<newReg<<" = 0 - "<<r1<<endl;
		}
		else if(op=="!")
		{
			cout<<newReg<<" = !"<<r1<<endl;
		}
		add_in_tmp_var(newReg);
		return newReg;
	}
	else if(n->n_type == _FUNCTION_DEF)
	{
		string s=n->value;
		num_para=0;
		tmp_vars.clear();
		var_line_no=0;
		cout<<s<<": funcbegin"<<endl;
		//cout<<"funcbegin "<<endl;
		cout << "ParamsNum: " << num_para << endl;
		global_vars();
		cgen(n->v[1]);
		
		cout<<"funcend : " << tmp_vars.size() <<endl;
		add_var_list(s);
		tmp_vars.clear();
		var_line_no=0;
	}

	else if(n->n_type==_FUNCTION_DEF_VOID)
	{
		string s=n->value;
		num_para=0;
		tmp_vars.clear();
		var_line_no=0;
		cout<<s<<": funcbegin"<<endl;
		//cout<<"funcbegin "<<endl;
		cout << "ParamsNum: " << num_para << endl;
		global_vars();
		cgen(n->v[0]);
		
		cout<<"funcend : " << tmp_vars.size() <<endl;
		add_var_list(s);
		tmp_vars.clear();
		var_line_no=0;
	}
	else if(n->n_type==_FUNCTION_DEF_PARAM)
	{
		string s=n->value;
		num_para=0;
		tmp_vars.clear();
		var_line_no=0;
		cout<<s<<": funcbegin"<<endl;
		//cout<<"funcbegin "<<endl;
		cgen(n->v[1]);
		cout << "ParamsNum: " << num_para << endl;
		global_vars();
		cgen(n->v[2]);
		
		cout<<"funcend : " << tmp_vars.size() <<endl;
		add_var_list(s);
		tmp_vars.clear();
		var_line_no=0;
	}else if(n->n_type==_FUNCTION_DEF_PARAM_VOID)
	{
		string s=n->value;
		num_para=0;
		tmp_vars.clear();
		var_line_no=0;
		cout<<s<<": funcbegin"<<endl;
		//cout<<"funcbegin "<<endl;
		cgen(n->v[0]);
		cout << "ParamsNum: " << num_para << endl;
		global_vars();
		cgen(n->v[1]);
		
		cout<<"funcend : " << tmp_vars.size() <<endl;
		add_var_list(s);
		tmp_vars.clear();
		var_line_no=0;
	}
	else if(n->n_type==_PARA_DEC)
	{
		struct cgenEntry a;
		a.scope = scope_code+1;
		cgenTable.back().insert(pair<string, struct cgenEntry>(n->value, a));
		stringstream ss;
		ss << scope_code+1;
		add_in_tmp_var(n->value+ss.str());
		num_para++;
		return "";
	}
	else if(n->n_type==_PARA_DEC_LIST)
	{
		cgen(n->v[0]);
		struct cgenEntry a;
		a.scope = scope_code+1;
		cgenTable.back().insert(pair<string, struct cgenEntry>(n->value, a));
		stringstream ss;
		ss << scope_code+1;
		add_in_tmp_var(n->value+ss.str());
		num_para++;
		return "";
	}
	else if(n->n_type==_RETURN_STATEMENT)
	{	
		cout << "v0 = 0" << endl;
		cout << "return" << endl;
		return "";
	}
	else if(n->n_type==_RETURNEXP_STATEMENT)
	{
		string R1=cgen(n->v[0]);
		cout << "v0 = " << R1 << endl;
		cout << "return" << endl;
		return "";
	}
	else if(n->n_type==_CONSTANT_NUMP)
	{
		return n->value;
	}
	else if(n->n_type==_CONSTANT_FLOATP)
	{
		return n->value;
	}
	else if(n->n_type==_PRINT_STRING)
	{
		cout << "outstr " << (n->v[0])->value << endl;
		return "";
	}
	else if(n->n_type==_PRINT_INT)
	{
		string r1 = cgen(n->v[0]);
		cout << "outint " << r1 << endl;
		return "";
	}
	else if(n->n_type==_PRINT_FLOAT)
	{
		string r1 = cgen(n->v[0]);
		cout << "outfloat " << r1 << endl;
		return "";
	}
	else if(n->n_type==_GET_STRING)
	{
		string r1 = cgen(n->v[0]);
		cout << "instr " << r1 << endl;
		return "";
	}
	else if(n->n_type==_GET_INT)
	{
		string r1 = cgen(n->v[0]);
		cout << "inint " << r1 << endl;
		return "";
	}
	else if(n->n_type==_GET_FLOAT)
	{
		string r1 = cgen(n->v[0]);
		cout << "infloat " << r1 << endl;
		return "";
	}
	else
	{
		
		for (int i = 0; i < (n->v).size(); ++i)
		{
			cgen((n->v)[i]);
		}
		return "";
	}
}
/****************************************************************************************************************/
/****************************************************************************************************************/
/****************************************************************************************************************/






main ()
{
	//**************************************************************************
	
	FILE *myfile = fopen("input.txt", "r");
	
	
	
	yyin = myfile;
	//cout << "in main" << endl;
	map<string, struct symtb> mm;
	symbolTable.push_back(mm);
	//cout << "size initially " << symbolTable.size() << endl;
	cout << "doing parse" << endl;
	do {
		yyparse();
	} while (!feof(yyin));
	//****************************************************************************
   	//yyparse();			// Start parsing
	if(errcount)			// If error occured
                printf("\n Result: %d syntax errors. Input rejected \n",errcount);
   	
	printf("\n");
	
	if(semantic_err)
		printf("Your code has semantic errors\n");

	cout << "Root Address: " << root << endl;
	

	if(!(semantic_err==1 || syntactic_err==1)){
		create_dot_graph(root, "1");
		
		dot_code+="}";
		ofstream out("sample.dot");
		out<<dot_code;
		out.close();

		cout<<"Generating the Syntax tree.\n";

		system("dot -Tpng sample.dot  > sample.png");
		cout<<"Syntax tree generated.\n";
	}

	map<string, struct cgenEntry>cgenm;
	cgenTable.push_back(cgenm);

	cgen(root);

	FILE *ftmp;
	ftmp = fopen("tmpvar.txt","w");
	map<string, int>::iterator fit;
	int sz;
	for(mit=functionTable.begin();mit!=functionTable.end();++mit){
		sz=(mit->second).var_list.size();
		fprintf(ftmp, "\n%s:%d\n", (mit->first).c_str(), sz);
		for(fit=(mit->second).var_list.begin(); fit!=(mit->second).var_list.end(); ++fit ){
			fprintf(ftmp, "%s=%d\n", (fit->first).c_str(), fit->second);
		}
	}
}


void semantic_error(string sem_err)
{

	
	fprintf(stderr, "Line no - %d :semantic error, %s",yylloc.first_line,&sem_err[0]);
	fprintf(stderr, "\n");


}


int yyerror(const char *s)
{
	errcount++;
	syntactic_err=1;
		if(caught)
		{
			fprintf(stderr, "%s", s);	
			fprintf(stderr, "\n");
		}
		else{
		sprintf(str," ");
		//fprintf(stderr, "%d.%d - %d.%d : %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,s,yytext);
		fprintf(stderr, "%d.%d - %d.%d : %s  ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,s);
		fprintf(stderr, "\n");
		}
	if(eof)
		exit(1);
	
					
	
}






				//********************************************************************************************************
				//********************************************************************************************************
				//************************ array reference of a variable ,function wala sara rehta hai type checking******
				//********************************************************************************************************
				//********************************************************************************************************
				//********************************************************************************************************
