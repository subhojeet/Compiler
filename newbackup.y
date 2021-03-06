//note that our grammar has right associative behavior . so to have left associativity we need to use braces.

%{

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
		_EXPR_MICROVAL, _EXPR_UNARY, _IF_ELSEIF_ELSE, _ELIF_LIST, _ELIF_PART, _IF_ELSEIF, _EXPR_MICRO_ASS_OP

}N_type;

typedef enum DataType{
		_INT, _BOOL, _FLOAT, _VOID, _CHAR, _STRING, _UNKNOWN, _EXP_INT, _EXP_BOOL, _EXP_FLOAT, _EXP_CHAR, _EXP_STRING
}D_type;

int scope=0, main_pres=1, syntactic_err=0, semantic_err=0,scope_code=0;

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
};

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
	if(op=="<" || op==">"  || op==">=" || op=="<=" || op=="==" || op=="!=")
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
	if(realational(op) && (d1==_BOOL || d2== _BOOL )){
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

%}

%union
{
	struct AST* node;
	int int_val;
	float float_val;
	bool bool_val;
	char* string_val;
	char char_val;
}

%define parse.error verbose
%locations

%type <node> expr expr_stmnt data_type include_dec func_dec func_def main_func micro_val arg arg_list compound_stmnt 
			stmnt_list stmnt jump_stmnt condition_stmnt loop_stmnt exit_stmnt io_stmnt labeled_stmnt 
			operators binary_op logical_op bit_logical_op assignment_op relational_op Start1 Start2 
			Start_sym string unary_op param_list dec dec_init ID_init_list constant param func_compound_stmnt ext_dec 
			otwise_stmnt switch_stmnt switch_stmnt_list1 switch_stmnt_list elif_list expr_stmnt_list expr_stmnt_list_cond semi_comma colon
			elseifpart


%token <int_val> NUMBER
%token <float_val> DECIMAL
%token <bool_val> BOOLEAN
%token <string_val> STR_LIT
%token <string_val> ID
%token <char_val> CHAR_LIT

%token INT FLOAT CHAR BOOL VOID

%token 	 ADD_ASS SUB_ASS MUL_ASS DIV_ASS MOD_ASS AND_ASS XOR_ASS OR_ASS 
%token BREAK CONTINUE RETURN
%token FOR WHILE IF ELSE DO ELIF
%token LESS_OP GREAT_OP LESS_EQ_OP GREAT_EQ_OP EQEQ_OP NOTEQ_OP AND_OP OR_OP
%token MAIN IN OUT INCLUDE   EXIT
%token CASE OTHERWISE SWITCH
%token ERROR INCR DECR TYPEDEF

%right '=' ADD_ASS SUB_ASS MUL_ASS DIV_ASS MOD_ASS AND_ASS XOR_ASS OR_ASS 
%left LESS_OP GREAT_OP LESS_EQ_OP GREAT_EQ_OP 
%left EQEQ_OP NOTEQ_OP
%left AND_OP OR_OP
%left '+' '-' 
%left '*' '/' '%'




%expect 0

%start Start_sym

%%
Start_sym
		:	Start1 main_func	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->code="Start";
			root = nnode;
			$$ = nnode;
		}
		;

Start1
		:	Start1 func_def		{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->code="Start1";
			$$ = nnode;
		}
		|	Start1 func_dec		{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->code="Start1";
			$$ = nnode;
		}
		|	Start1 ext_dec 			{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->code="Start1";
			$$ = nnode;
		}
		|	Start2		{
			/*cout << "2" << endl;
			struct AST* nnode=newnode();
			cout << nnode << endl;
			(nnode->v).push_back($1);
			$$->code = "Start1";
			$$ = nnode;*/
			$$=$1;
		}
		;

Start2
		:	Start2 include_dec	{
			//cout << "3" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->code="Start2";
			$$ = nnode;
		}
		|	{
			struct AST* nnode=newnode();
			nnode->n_type=_EPSILON;
			nnode->code="EPSILON";
			$$ = nnode;
		}
		;

data_type
		:	INT 	{
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_INT;
			nnode->code="INT_data_type";
			$$=nnode;

		}
		|	FLOAT 	{
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_FLOAT;
			nnode->code="FLOAT_data_type";
			$$=nnode;	
		}
		|	BOOL 	{
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_BOOL;
			nnode->code="BOOL_data_type";
			$$=nnode;
		}
		|	CHAR 	{
			struct AST* nnode=newnode();
			nnode->n_type=_DTYPE;
			nnode->d_type=_CHAR;
			nnode->code="CHAR_data_type";
			$$=nnode;
		}
		
		;

include_dec
		:	'#' INCLUDE string 	{ 
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			nnode->n_type=_INCLUDE_STR;
			nnode->code="INCLUDE";
			$$=nnode;
		}
		|	'#' INCLUDE LESS_OP ID '.' ID GREAT_OP 	{
			struct AST* nnode=newnode();
			string s1($4);
			string s2($6);
			nnode->n_type=_INCLUDE;
			nnode->code="INCLUDE<" + s1 + "." + s2 + ">";
			$$=nnode;
		}
		|	'#' INCLUDE LESS_OP ID GREAT_OP {
			//cout << "4" << endl;
			struct AST* nnode=newnode();
			string s1($4);
			nnode->n_type=_INCLUDE;
			nnode->code="INCLUDE<" + s1 + ">";
			$$=nnode;
		}
		|	'#' error 	{
							$$ = newnode(_VOID,_ERROR,"error","");
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
		;
	
string
		:	STR_LIT		{
			struct AST* nnode=newnode();
			string val($1);
			nnode->n_type=_CONSTANT;
			nnode->d_type=_STRING;
			nnode->value=val;
			nnode->code="String_constant";
			$$ = nnode;
		}
		;

main_func
		:	INT MAIN _LOB param ')' func_compound_stmnt 	{
			struct AST* nnode=newnode(_INT, _MAIN, "MAIN", "MAIN");
			(nnode->v).push_back($4);
			(nnode->v).push_back($6);
			$$ = nnode;

			add_entry_functb(_INT, "main");
			pv.clear();
			fill_params($4);
			set_params("main");
			check_returning(_INT, "main");
		}
		|	INT MAIN _LOB ')' func_compound_stmnt 	{
			struct AST* nnode=newnode(_INT, _MAIN, "MAIN","MAIN");
			(nnode->v).push_back($5);
			$$ = nnode;
			add_entry_functb(_INT, "main");
			check_returning(_INT, "main");
		}
		|	VOID MAIN _LOB param ')' func_compound_stmnt 	{
			struct AST* nnode=newnode(_VOID, _MAIN, "MAIN", "MAIN");
			(nnode->v).push_back($4);
			(nnode->v).push_back($6);
			$$ = nnode;
			add_entry_functb(_VOID, "main");
			pv.clear();
			fill_params($4);
			set_params("main");
			check_returning(_VOID, "main");
		}
		|	VOID MAIN _LOB ')' func_compound_stmnt 	{
			//cout << "5" << endl;
			struct AST* nnode=newnode(_VOID, _MAIN, "MAIN", "MAIN");
			(nnode->v).push_back($5);
			$$ = nnode;
			add_entry_functb(_VOID, "main");
			check_returning(_VOID, "main");
		}
		|	{
			main_pres=0;
			$$ = newnode(_VOID,_ERROR,"NO_MAIN","");
		}
		|	INT MAIN error{
							
							//printing the error message in header declaration
							/*caught=true;
							sprintf (str, "in main function");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(2);
							
							yyclearin;yyerrok;
					   	}
		|	VOID MAIN error{
							
							//printing the error message in header declaration
							/*caught=true;
							sprintf (str, "in main function");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(3);
							
							yyclearin;yyerrok;
					   	}
		
		;

func_dec
		:	data_type ID _LOB param _ROB semi_comma 	{
			string s($2);
			DataType d=$1->d_type;
			struct AST* nnode=newnode(d, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			(nnode->v).push_back($4);
			$$ = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(d, s);
				pv.clear();
				fill_params($4);
				set_params(s);
			}
		}
		|	data_type ID _LOB _ROB semi_comma 	{
			string s($2);
			DataType d=$1->d_type;
			struct AST* nnode=newnode(d, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			$$ = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(d, s);
			}
		}
		|	VOID ID _LOB param _ROB semi_comma 	{
			string s($2);
			struct AST* nnode=newnode(_VOID, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			(nnode->v).push_back($4);
			$$ = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(_VOID, s);
				pv.clear();
				fill_params($4);
				set_params(s);
			}
		}
		|	VOID ID _LOB _ROB semi_comma 	{
			string s($2);
			struct AST* nnode=newnode(_VOID, _FUNCTIONDEC, s+"_FUNCTION_DEC", s+"_FUNCTION_DEC");
			$$ = nnode;
			//check if already defined
			if(is_in_map(s)){
				semantic_err=1;
				cout << "Redefination of function :" + s << endl;
			}else{
				add_entry_functb(_VOID, s);
			}
		}
		|	data_type ID _LOB error {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in function declaration");

							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(4);
							
							yyclearin;yyerrok;
			   	}

		|	VOID ID _LOB error  {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in function declaration");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(5);
							
							yyclearin;yyerrok;
			   	}
		
		;

semi_comma
		:	';' {

					$$ = newnode(_VOID,_SEMI_COMMA,"SEMI_COMMA","");

		}
		|	error {
							
							$$ = newnode(_VOID,_ERROR,"error","");
							/*caught=true;
							sprintf (str, "Missing ';' ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/


							yyerrok;
							
							
			   	}
		;
param
		:	param_list 	{
			//cout << "enter param" << endl;
			/*map<string, struct symtb> mm;
			symbolTable.push_back(mm);*/
			//cout << "Size in param " << symbolTable.size() << endl;
			struct AST* nnode=newnode(_VOID, _PARAMETERS, "PARAMETERS", "");
			(nnode->v).push_back($1);
			$$=nnode;
		}
		;

		
func_def
		:	data_type ID _LOB param ')' func_compound_stmnt	{
			string s($2);
			//cout << "funcdef" << endl;
			DataType d = $1->d_type;
			//cout << "funcdef2" << endl;
			struct AST* nnode=newnode(d, _FUNCTION, s+"_FUNCTION", s+"_FUNCTION");
			(nnode->v).push_back($1);
			(nnode->v).push_back($4);
			(nnode->v).push_back($6);
			//check if already defined
			if(is_in_map(s)){
				pv.clear();
				fill_params($4);
				check_validity_function_p(s,d);
			}else{
				add_entry_functb(d, s);
				pv.clear();
				fill_params($4);
				set_params(s);
			}
			check_returning(d, s);
			$$ = nnode;
		}
		|	data_type ID _LOB ')' func_compound_stmnt		{
			string s($2);
			DataType d = $1->d_type;
			struct AST* nnode=newnode(d, _FUNCTION, s+"_FUNCTION", s+"_FUNCTION");
			(nnode->v).push_back($1);
			(nnode->v).push_back($5);
			//check if already defined
			if(is_in_map(s)){
				check_validity_function(s,d);
			}else{
				add_entry_functb(d, s);
			}
			check_returning(d, s);
			$$ = nnode;
		}
		|	VOID ID _LOB param ')' func_compound_stmnt 	{
			string s($2);
			struct AST* nnode=newnode(_VOID, _FUNCTION, s+"_FUNCTION", s+"_FUNCTION");
			(nnode->v).push_back($4);
			(nnode->v).push_back($6);
			//check if already defined
			if(is_in_map(s)){
				pv.clear();
				fill_params($4);
				check_validity_function_p(s,_VOID);
			}else{
				add_entry_functb(_VOID, s);
				pv.clear();
				fill_params($4);
				set_params(s);
			}
			check_returning(_VOID, s);
			$$ = nnode;
		}
		|	VOID ID _LOB ')' func_compound_stmnt 	{
			string s($2);
			struct AST* nnode=newnode(_VOID, _FUNCTION, s+"_FUNCTION", s+"_FUNCTION");
			(nnode->v).push_back($5);
			//check if already defined
			if(is_in_map(s)){
				check_validity_function(s,_VOID);
			}else{
				add_entry_functb(_VOID, s);
			}
			check_returning(_VOID, s);
			$$ = nnode;
		}
		| 	data_type error func_compound_stmnt {
							
							/*caught=true;
							sprintf (str, "in function definition");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							yyerrok;
							
							
			   	}
		;
		

micro_val
		:	constant 	{
			//cout << "enter here" << endl;
			//cout << "enter here1" << endl;
			//cout << $1->value << endl;
			//cout << "enter here2" << endl;
			struct AST* nnode=newnode($1->d_type, _FACTOR_CONS, "Constant_factor "+ $1->value, $1->value);
			//cout << "now here" << endl;
			(nnode->v).push_back($1);

			$$=nnode;
		}
		|	ID 	{
			string s($1);
			struct AST* nnode=newnode(_VOID, _FACTOR_ID, "Id_factor "+s, s);
			DataType d=find_type_id(s);
			nnode->d_type=d;
			$$=nnode;
		}
		|	ID '(' ')' {

			string s($1);
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
			$$=nnode;

		}
		|	ID '(' arg_list ')' {

			string s($1);
			struct AST* nnode=newnode(_VOID, _ARG_FUNC_CALL, s + "()", s);
			(nnode->v).push_back($3);
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
			$$=nnode;
		}
		|	ID '[' expr ']'  {

			if($3->d_type!=_INT)
			{
				//printf("Expression in array index must be int\n");
				stringstream ss;
				ss<<"Expression in array index must be int " ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
				
			}
			string s($1);

			struct AST* nnode=newnode(_VOID, _FACTOR_ID, s + "[" + $3->value + "]", s);
			DataType d=find_type_id(s);
			nnode->d_type=d;
			(nnode->v).push_back($3);
			$$=nnode;
		}
		|	ID '(' error ';' {
							
							/*caught=true;
							sprintf (str, "in expression1 ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(6);
							
							yyclearin;yyerrok;
			   	}

		|	ID '[' error  {
							
							/*caught=true;
							sprintf (str, "in expression ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(7);
							
							yyclearin;yyerrok;
							//cout<<"ho gaya"<<yytext<<endl;
			   	}

		;

		

expr
		:	micro_val 	{
			struct AST* nnode=newnode($1->d_type, _EXPR_MICROVAL, "EXPR_microval", $1->value);
			(nnode->v).push_back($1);
			$$=nnode;
		}
		|	'(' expr ')' 	{
			struct AST* nnode=newnode($2->d_type, _EXPR_BRACKET, "EXPR_expr", "("+$2->value+")");
			(nnode->v).push_back($2);
			$$=nnode;
		}
		|	unary_op expr 	{
			DataType d=$2->d_type;

			if($1->value=="~"){
				if(!(d==_INT || d==_FLOAT) ){
					stringstream ss;
					ss<<"type mismatch for ~" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
					
					//printf("type mismatch for ~\n");
					
				}
			}else if($1->value=="!"){
				if(!(d==_BOOL) ){
					stringstream ss;
					ss<<"type mismatch for !" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
					//printf("type mismatch for !\n");
					//cout << "type mismatch for !" << endl;
				}
			}
			struct AST* nnode=newnode($2->d_type, _EXPR_UNARY, "EXPR_OP_"+$1->value, $1->value+" "+$2->value);
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			$$=nnode;
		}
		|	micro_val operators expr 	{
			DataType d=_VOID;
			check_validity($2->value, $1->d_type, $3->d_type,&d);
			struct AST* nnode=newnode(d, _EXPR_MICRO_OP, "EXPR_OP_"+$2->value, $1->value + " " + $2->value + " " + $3->value);
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			(nnode->v).push_back($3);
			$$=nnode;
		}
		|	micro_val assignment_op expr 	{
			DataType d=_VOID;
			check_validity($2->value, $1->d_type, $3->d_type,&d);
			struct AST* nnode=newnode(d, _EXPR_MICRO_ASS_OP, "EXPR_OP_"+$2->value, $1->value + " " + $2->value + " " + $3->value);
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			(nnode->v).push_back($3);
			$$=nnode;
		}
		|	'(' expr ')' operators expr 	{
			DataType d=_VOID;
			check_validity($4->value, $2->d_type, $5->d_type,&d);
			struct AST* nnode=newnode(d, _EXPR_EXPR_OP, "EXPR_OP_"+$4->value,"("+$2->value + ") " + $4->value + " " + $5->value);
			(nnode->v).push_back($2);
			(nnode->v).push_back($4);
			(nnode->v).push_back($5);
			$$=nnode;
		}
		|	'(' expr error {

								/*caught=true;
							sprintf (str, "in expression ");
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
								 
								fprintf(stderr, "\n");									   
							caught=false;*/
								$$ = newnode(_VOID,_ERROR,"error","");
								eat_to_newline(8);
								
								yyclearin;yyerrok;
			}


		|	micro_val operators error {

								/*caught=true;
							sprintf (str, "in expression ");
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
								 
								fprintf(stderr, "\n");									   
							caught=false;*/
								$$ = newnode(_VOID,_ERROR,"error","");
								eat_to_newline(9);
								
								yyclearin;yyerrok;
			}
		|	'(' expr ')' operators error {

								/*caught=true;
							sprintf (str, "in expression 2");
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
								 
								fprintf(stderr, "\n");									   
							caught=false;*/
								$$ = newnode(_VOID,_ERROR,"error","");
								eat_to_newline(10);
								
								
			}
		|	micro_val ERROR expr{

								caught=true;
								/*errcount++;
								syntactic_err=1;
							
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d syntax error, unexpected %s, expecting operator before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,yytext,yytext);
								 
								fprintf(stderr, "\n");
																	   */
								$$ = newnode(_VOID,_ERROR,"error","");
								sprintf(str,"%d.%d - %d.%d syntax error, unexpected token, expecting operator in the expression ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column);
								yyerror(str);
								caught=false;
								eat_to_newline(11);
								
								
								
								
			}
		|	'(' expr ')' ERROR expr {
								
								caught=true;
								/*errcount++;
								syntactic_err=1;
							
								if(yylloc.first_line)
								    fprintf(stderr, "%d.%d - %d.%d syntax error, unexpected %s, expecting operator before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,yytext,yytext);
								 
								fprintf(stderr, "\n");									   */
								$$ = newnode(_VOID,_ERROR,"error","");
								sprintf(str,"%d.%d - %d.%d syntax error, unexpected token, expecting operator in the expression  ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column);
								yyerror(str);
								caught=false;
								eat_to_newline(12);
								yyclearin;yyerrok;
								
								
			}
			

		;

arg_list
		:	arg_list ',' arg 	{
			struct AST* nnode=newnode();
			nnode->n_type=_ARGLIST;
			(nnode->v).push_back($1);
			(nnode->v).push_back($3);
			nnode->code="ARG_LIST";			
			$$=nnode;
		}
		|	arg 	{
			$$=$1;
		}
		|	arg_list error {
							
							/*caught=true;
							sprintf (str, "in parameter list");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(13);
							
							yyclearin;yyerrok;
			   	}

		
		
		;
		;

arg
		:	constant 	{
			struct AST* nnode=newnode(_VOID, _ARG_CONS, "Arg : "+ $1->value, "");
			(nnode->v).push_back($1);
			$$ = nnode;
			arg_v.push_back($1->d_type);
		}
		|	ID 	{  //add type of this in symbol table
			string s($1);
			int scp = find_scope(s);
			if(scp<0){
					stringstream ss;
					ss<<"no variable " <<  s << " defined in scope" ;
					string err_msg = ss.str();
					semantic_err=1;semantic_error(err_msg);
				//cout << "no variable " <<  s << " defined in scope" << endl;
			}
			struct AST* nnode=newnode(_VOID, _ARG_ID, "Arg : " + s, s);
			$$ = nnode;
			DataType d1=_UNKNOWN;
			d1=find_type_id(s);
			arg_v.push_back(d1);
		}
		;

		
operators
		:	binary_op 	{
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", $1->value);
			(nnode->v).push_back($1);
			$$=nnode;
		}
		|	relational_op 	{
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", $1->value);
			(nnode->v).push_back($1);
			$$=nnode;
		}
		|	logical_op 	{
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", $1->value);
			(nnode->v).push_back($1);
			$$=nnode;
		}
		|	bit_logical_op 	{
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", $1->value);
			(nnode->v).push_back($1);
			$$=nnode;
		}
		/*|	assignment_op 	{
			struct AST* nnode = newnode(_VOID, _OPERATION, "Operator", $1->value);
			(nnode->v).push_back($1);
			$$=nnode;
		}*/
		;


		
logical_op
		:	AND_OP 	{
			struct AST* nnode=newopnode("&&");
			nnode->code="&&";
			$$=nnode;
		}
		|	OR_OP 	{
			struct AST* nnode=newopnode("||");
			nnode->code="||";
			$$=nnode;
		}
		;
		
binary_op
		:	'+' 	{
			struct AST* nnode=newopnode("+");
			nnode->code="+";
			$$=nnode;
		}
		| 	'-' 	{
			struct AST* nnode=newopnode("-");
			nnode->code="-";
			$$=nnode;
		}
		|	'*' 	{
			struct AST* nnode=newopnode("*");
			nnode->code="-";
			$$=nnode;
		}
		|	'/' 	{
			struct AST* nnode=newopnode("/");
			nnode->code="/";
			$$=nnode;
		}
		|	'%' 	{
			struct AST* nnode=newopnode("%");
			nnode->code="%";
			$$=nnode;
		}
		;
assignment_op
		:	'=' 	{
			struct AST* nnode=newopnode("=");
			nnode->code="=";
			$$=nnode;
		}
		|	ADD_ASS 	{
			struct AST* nnode=newopnode("+=");
			nnode->code="+=";
			$$=nnode;
		}
		|	SUB_ASS 	{
			struct AST* nnode=newopnode("-=");
			nnode->code="-=";
			$$=nnode;
		}
		|	MUL_ASS 	{
			struct AST* nnode=newopnode("*=");
			nnode->code="*=";
			$$=nnode;
		}
		|	DIV_ASS 	{
			struct AST* nnode=newopnode("/=");
			nnode->code="/=";
			$$=nnode;
		}
		|	MOD_ASS 	{
			struct AST* nnode=newopnode("%=");
			nnode->code="%=";
			$$=nnode;
		}
		|	AND_ASS 	{
			struct AST* nnode=newopnode("&=");
			nnode->code="&=";
			$$=nnode;
		}
		|	XOR_ASS 	{
			struct AST* nnode=newopnode("^=");
			nnode->code="^=";
			$$=nnode;
		}
		|	OR_ASS 	{
			struct AST* nnode=newopnode("|=");
			nnode->code="|=";
			$$=nnode;
		}
		;
relational_op
		:	LESS_OP 	{
			struct AST* nnode=newopnode("<");
			nnode->code="<";
			$$=nnode;
		}
		|	GREAT_OP 	{
			struct AST* nnode=newopnode(">");
			nnode->code=">";
			$$=nnode;
		}
		|	LESS_EQ_OP	{
			struct AST* nnode=newopnode("<=");
			nnode->code="<=";
			$$=nnode;
		}
		|	GREAT_EQ_OP {
			struct AST* nnode=newopnode(">=");
			nnode->code=">=";
			$$=nnode;
		}
		|	EQEQ_OP 	{
			struct AST* nnode=newopnode("==");
			nnode->code="==";
			$$=nnode;
		}
		|	NOTEQ_OP 	{
			struct AST* nnode=newopnode("!=");
			nnode->code="!=";
			$$=nnode;
		}
		;

bit_logical_op
		:	'&' 	{
			struct AST* nnode=newopnode("&");
			nnode->code="&";
			$$=nnode;
		}
		|	'|' 	{
			struct AST* nnode=newopnode("|");
			nnode->code="|";
			$$=nnode;
		}
		|	'^' 	{
			struct AST* nnode=newopnode("^");
			nnode->code="^";
			$$=nnode;
		}
		;

unary_op
		:	'!' 	{
			struct AST* nnode=newopnode("!");
			nnode->code="!";
			$$=nnode;
		}
		|	'~' 	{
			struct AST* nnode=newopnode("~");
			nnode->code="~";
			$$=nnode;
		}
		;
		
stmnt_list
		:	 stmnt 	{
			//cout << "enter stmntlist" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_List";
			$$ = nnode;
		}
		|	 stmnt_list stmnt 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->code="Statement_List";
			$$ = nnode;
		}
		;		

stmnt
		: 	compound_stmnt 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		| 	expr_stmnt 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		| 	condition_stmnt 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		| 	loop_stmnt 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		| 	jump_stmnt 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		|	dec 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		|	io_stmnt 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		|	exit_stmnt {
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->code="Statement_Types";
			$$ = nnode;
		}
		;
		
io_stmnt
		:	OUT '(' string ')' ';' 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			nnode->n_type=_OUT;
			nnode->code="OUT";
			$$=nnode;
		}
		|	OUT '(' string ',' arg_list ')' ';' 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			nnode->n_type=_OUT;
			nnode->code="OUT";
			$$=nnode;
		}
		|	IN '(' string ',' arg_list ')' ';' 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			nnode->n_type=_IN;
			nnode->code="IN";
			$$=nnode;
		}
		|	OUT  error {
							//printing the error message in func declaration


							/*caught=true;
							sprintf (str, "in out()function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(14);
							
							yyclearin;yyerrok;
			   	}
		|	IN  error {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in in() function call");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(15);
							
							yyclearin;yyerrok;
			   	}

		;
		;
		
labeled_stmnt
		:	CASE constant colon  	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($2);
			nnode->n_type=_CASE;
			nnode->code="CASE_:";
			$$=nnode;
		}
		|	CASE error {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in case statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(16);
							
							yyclearin;yyerrok;
			   	}

		
		;

otwise_stmnt
		:	OTHERWISE colon	 stmnt_list	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			nnode->n_type=_CASE;
			nnode->code="OTHERWISE_:";
			$$=nnode;
		}
		|	OTHERWISE error  {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in otwise statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(17);
							
							yyclearin;yyerrok;
			   	}
		| {
			struct AST* nnode=newnode(_VOID,_CASE,"No_OTHERWISE","");
			$$=nnode;
		}
		
		;

colon
		:	':' {

			$$ = newnode(_VOID,_COLON,"COLON","");
		}
		|	error {
							/*caught=true;
							sprintf (str, "Missing ':' ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							yyerrok;
							
							
			   	}
		;

func_compound_stmnt
		:	'{' _RCB 	{
			cout << "23" << endl;
			struct AST* nnode=newnode();
			$$ = nnode;
		}
		|	'{' stmnt_list _RCB 	{
			//cout << "enter func comp_stmnt" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back($2);
			nnode->n_type=_COMPOUND_STMNT;
			nnode->code="Compound_statements";
			$$ = nnode;
			//cout << "exit func comp_stmnt" << endl;
		}
		|	'{' stmnt_list error {
							
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
							$$ = newnode(_VOID,_ERROR,"error","");
							yyclearin;yyerrok;
							
							
			   	}

		;
		
compound_stmnt
		:	_LCB _RCB 	{
			//cout << "7" << endl;
			struct AST* nnode=newnode();
			$$ = nnode;
		}
		| 	_LCB stmnt_list _RCB 	{
			//cout << "enter comp_stmnt" << endl;
			struct AST* nnode = newnode();
			(nnode->v).push_back($2);
			nnode->code="Compound_statements";
			nnode->n_type=_COMPOUND_STMNT;
			$$ = nnode;
		}
		|	_LCB stmnt_list error {
							
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
							$$ = newnode(_VOID,_ERROR,"error","");
							
							yyclearin;yyerrok;
							
							
			   	}

		;	

_LOB
		:	'(' 	{
			map<string, struct symtb> mm;
			symbolTable.push_back(mm);
			scope++;
		}
		;

_ROB
		:	')' 	{
			//cout << "enter '}'" << endl;
			if(symbolTable.size()>0){
				symbolTable.pop_back();
			}
			scope--;
		}
		;

_LCB
		:	'{' 	{
			map<string, struct symtb> mm;
			symbolTable.push_back(mm);
			scope++;
		}
		;

_RCB
		:	'}' 	{
			//cout << "enter '}'" << endl;
			if(symbolTable.size()>0){
				symbolTable.pop_back();
			}
			scope--;
		}
		;

condition_stmnt
		:	IF '(' expr ')' compound_stmnt 	{
			/*expr type must be bool*/
			if($3->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			nnode->n_type=_IF;
			nnode->code="IF";
			$$=nnode;
		}
		|	IF '(' expr ')' compound_stmnt ELSE compound_stmnt 	{
			/*expr type must be bool*/
			if($3->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			(nnode->v).push_back($7);
			nnode->n_type=_IFELSE;
			nnode->code="IF_ELSE";
			$$=nnode;
		}
		/*|	SWITCH '(' expr ')' compound_stmnt 	{
			//expr type must be int, float, char, string
			if(!($3->d_type==_FLOAT || $3->d_type==_INT || $3->d_type==_CHAR || $3->d_type==_STRING)){
				printf("Expression in switch must be one of int,float,char,string type\n");
				semantic_err=1;semantic_error(" ");
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			nnode->n_type=_SWITCH;
			nnode->code="SWITCH_CASE";
			$$=nnode;
		}*/
		/***********/
		|	IF '(' expr ')' compound_stmnt elif_list ELSE compound_stmnt {
			/*expr type must be bool*/
			if($3->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			(nnode->v).push_back($6);
			(nnode->v).push_back($8);
			nnode->n_type=_IF_ELSEIF_ELSE;
			nnode->code="IF_ELIF-ELSE";
			$$=nnode;
		}

		|	IF '(' expr ')' compound_stmnt elif_list 	{
			/*expr type must be bool*/
			if($3->d_type!=_BOOL){
				//printf("Expression in if must be bool\n");
				stringstream ss;
				ss<<"Expression in if must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			(nnode->v).push_back($6);
			nnode->n_type=_IF_ELSEIF;
			nnode->code="IF_ELIF";
			$$=nnode;
		}

		|	SWITCH '(' expr ')'  '{' switch_stmnt_list '}' {
			/*expr type must be int, float, char, string*/
			if(!($3->d_type==_FLOAT || $3->d_type==_INT || $3->d_type==_CHAR || $3->d_type==_STRING)){
				//printf("Expression in switch must be one of int,float,char,string type\n");
				stringstream ss;
				ss<<"Expression in switch must be one of int,float,char,string type" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($6);
			nnode->n_type=_SWITCH;
			nnode->code="SWITCH_CASE";
			$$=nnode;
		}
		|	IF error {

							/*caught=true;
							sprintf (str, "in if statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(20);
							
							yyclearin;yyerrok;		
			}

		|	SWITCH error{



							/*caught=true;
							sprintf (str, "in switch statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(21);
							
							yyclearin;yyerrok;		
			
		}

		;


elif_list
		:	elif_list elseifpart {
			struct AST* nnode=newnode(_VOID, _ELIF_LIST, "ELIF_LIST", "");
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			//(nnode->v).push_back($6);
			$$ = nnode;
		}
		|	elseifpart {
			struct AST* nnode=newnode(_VOID, _ELIF, "ELIF", "");
			(nnode->v).push_back($1);
			//(nnode->v).push_back($5);
			$$ = nnode;
		}
		|	ELIF error {

							/*caught=true;
							sprintf (str, "in if statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(22);
							
							yyclearin;yyerrok;		
			}
		;


elseifpart
		:	ELIF '(' expr ')' compound_stmnt{
			struct AST* nnode=newnode(_VOID, _ELIF_PART, "ELIF_LIST", "");
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			//(nnode->v).push_back($6);
			$$ = nnode;
		}
		;

switch_stmnt
		:	labeled_stmnt 	{
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_LABELED_STATEMENT","");
			(nnode->v).push_back($1);
			$$ = nnode;
		}
		|	stmnt 	{
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_STATEMENT_STMNT","");
			(nnode->v).push_back($1);
			$$ = nnode;
		}
		;



switch_stmnt_list
		:	switch_stmnt_list1 otwise_stmnt {
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->code="SWITCH_LABELED_STATEMENT";
			$$ = nnode;
		}
		;

switch_stmnt_list1

		:	switch_stmnt_list1 switch_stmnt {
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_STATEMENT_LIST","");
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			$$ = nnode;
		}
		|	switch_stmnt
		{
			struct AST* nnode=newnode(_VOID,_SWITCH,"SWITCH_STATEMENT","");
			(nnode->v).push_back($1);
			$$ = nnode;
		}
		;

		
loop_stmnt
		:	WHILE '(' expr ')' compound_stmnt 	{
			if($3->d_type!=_BOOL){
				//printf("Expression in while must be bool\n");
				stringstream ss;
				ss<<"Expression in while must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			nnode->n_type=_WHILE;
			nnode->code="WHILE";
			$$=nnode;
		}
		| 	DO compound_stmnt WHILE '(' expr ')' ';' 	{
			if($5->d_type!=_BOOL){
				//printf("Expression in while must be bool\n");
				stringstream ss;
				ss<<"Expression in while must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($2);
			(nnode->v).push_back($5);
			nnode->n_type=_DOWHILE;
			nnode->code="DO_WHILE";
			$$=nnode;
		}
		| 	FOR '(' expr_stmnt_list semi_comma expr_stmnt_list_cond semi_comma expr_stmnt_list ')' compound_stmnt		/**some grammar mistake check**/ {

			
			struct AST* nnode=newnode();
			(nnode->v).push_back($3);
			(nnode->v).push_back($5);
			(nnode->v).push_back($7);
			(nnode->v).push_back($9);
			nnode->n_type=_FOR;
			nnode->code="FOR";
			$$=nnode;




		}
	
		|	WHILE '(' expr ')' error {
							
							/*caught=true;
							sprintf (str, "in while body");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(23);
							
							yyclearin;yyerrok;
			   	}
		|	WHILE error {
							
							/*caught=true;
							sprintf (str, "in while loop");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(24);
							
							yyclearin;yyerrok;
			   	}
		| DO error {
							/*caught=true;
							sprintf (str, "in do-while loop");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(25);
							
							yyclearin;yyerrok;

		}
		|	FOR error {

							/*caught=true;
							sprintf (str, "in for loop");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(26);
							
							yyclearin;yyerrok;		
			}
			
		;
expr_stmnt_list
		:	expr_stmnt_list ',' expr {
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($3);
			nnode->n_type=_EXPR;
			nnode->code="Expression__list";
			$$ = nnode;
			//cout << "exit expr_stmnt" << endl;
		}
		|	expr  {
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->n_type=_EXPR;
			nnode->code="Expression";
			$$ = nnode;
			//cout << "exit expr_stmnt" << endl;
		}
		|	error {

					$$ = newnode(_VOID,_ERROR,"error","");
					eat_to_newline(40);
					yyclearin;yyerror;
		}
		;
/************************************************************************************************************************************************/
/*****************************************yahan pe dekh liyo as kuch gadbad ho sakta hai*****set_type($3->d_type, s);***************DataType d=expc_datatype($3->d_type);********************/
/************************************************************************************************************************************************/
/************************************************************************************************************************************************/
expr_stmnt_list_cond
		:	expr_stmnt_list_cond ',' expr {

			if($3->d_type!=_BOOL){
				//printf("Conditional Expression in for must be bool\n");
				stringstream ss;
				ss<<"Conditional Expression in for must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}

			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($3);
			nnode->n_type=_EXPR;
			nnode->code="cond_Expression_list";
			$$ = nnode;
			
		}

		|	expr {
			if($1->d_type!=_BOOL){
				//printf("Conditional Expression in for must be bool\n");
				stringstream ss;
				ss<<"Conditional Expression in for must be bool" ;
				string err_msg = ss.str();
				semantic_err=1;semantic_error(err_msg);
			}
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->n_type=_EXPR;
			nnode->code="Expression";
			$$ = nnode;
			
		}
		
		| error {

					$$ = newnode(_VOID,_ERROR,"error","");
					eat_to_newline(40);
					yyclearin;yyerror;
		}
		;

expr_stmnt
		:	';'	{
			struct AST* nnode=newnode();
			nnode->n_type=_STATEMENT;
			$$ = nnode;
		}
		|	expr semi_comma 	{
			//cout << "enter expr_stmnt" << endl;
			struct AST* nnode=newnode();
			(nnode->v).push_back($1);
			nnode->n_type=_STATEMENT;
			nnode->code="Expression_statement";
			$$ = nnode;
			//cout << "exit expr_stmnt" << endl;
		}
		;

jump_stmnt
		:	BREAK semi_comma 	{
			struct AST* nnode=newnode();
			nnode->n_type=_BREAK_STATEMENT;
			nnode->code="BREAK";
			$$ = nnode;
		}
		|	CONTINUE semi_comma 	{
			struct AST* nnode=newnode();
			nnode->n_type=_CONTINUE_STATEMENT;
			nnode->code="CONTINUE";
			$$ = nnode;
		}
		|	RETURN semi_comma 	{
			struct AST* nnode=newnode();
			nnode->n_type=_RETURN_STATEMENT;
			nnode->code="RETURN";
			$$ = nnode;
			return_v.push_back(_VOID);
		}
		|	RETURN	expr semi_comma 	{
			struct AST* nnode=newnode();
			(nnode->v).push_back($2);
			nnode->n_type=_RETURNEXP_STATEMENT;
			nnode->d_type=$2->d_type;
			nnode->code="RETURN_Expression";
			$$ = nnode;
			return_v.push_back($2->d_type);
		}
		;
		
exit_stmnt
		:	EXIT '(' ')' semi_comma 	{
			struct AST* nnode=newnode();
			nnode->n_type=_STATEMENT;
			nnode->code="Exit";
			$$ = nnode;
		}
		|	EXIT error  {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in exit statement");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(27);
							
							yyclearin;yyerrok;
			   	}
		;
		
constant
		:	NUMBER 	{
			//cout << "enter constant number" << endl;
			struct AST* nnode=newnode();
			nnode->d_type=_INT;
			nnode->n_type=_CONSTANT;
			int a=$1;
			stringstream ss;
			ss << a;
			string val = ss.str();
			//cout << "value_:_" << val << endl;
			nnode->code = val;
			nnode->value = val;
			$$=nnode;
		}
		|	DECIMAL 	{
			struct AST* nnode=newnode();
			nnode->d_type=_FLOAT;
			nnode->n_type=_CONSTANT;
			double a=$1;
			stringstream ss;
			ss << a;
			string val = ss.str();
			nnode->code = val;
			nnode->value = val;
			$$=nnode;
		}
		|	CHAR_LIT 	{
			struct AST* nnode=newnode();
			nnode->d_type=_CHAR;
			nnode->n_type=_CONSTANT;
			string val(1,$1);
			nnode->code = val;
			nnode->value = val;
			$$=nnode;
		}
		|	STR_LIT 	{
			struct AST* nnode=newnode();
			nnode->d_type=_STRING;
			nnode->n_type=_CONSTANT;
			nnode->code = $1;
			nnode->value = $1;
			$$=nnode;
		}
		|	BOOLEAN 	{
			struct AST* nnode=newnode();
			nnode->d_type=_BOOL;
			nnode->n_type=_CONSTANT;
			if($1==true){
				nnode->code = "True";
				nnode->value = "True";
			}else if($1==false){
				nnode->code = "False";
				nnode->value = "False";
			}
			$$=nnode;
		}
		;		

param_list
		:	data_type ID 	{
			//cout << "enter paramlist single" << endl;
			string s($2);
			struct AST* nnode = newnode(_VOID, _PARA_DEC, "PARAMETER_DECLARATION", s);
			(nnode->v).push_back($1);
			$$=nnode;
			//cout << "call set_type" << endl;
			set_type($1->d_type, s);
			//cout << "return set_type" << endl;
		}
		|	param_list ',' data_type ID 	{
			//cout << "enter paramlist double" << endl;
			string s($4);
			struct AST* nnode = newnode(_VOID, _PARA_DEC_LIST, "PARAMETER_DECLARATION_LIST", s);
			(nnode->v).push_back($1);
			(nnode->v).push_back($3);
			$$=nnode;
			set_type($3->d_type, s);
		}
		|	error  {
							//printing the error message in func declaration
							/*caught=true;
							sprintf (str, "in parameter list");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");									   
							caught=false;*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(28);
							
							yyclearin;yyerrok;
			   	}
		
		;

ext_dec
		:	data_type  ID_init_list ';' 	{
			struct AST* nnode = newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->n_type=_DEC;
			nnode->code	= "DECLARATION";
			$$=nnode;
			rec_set_type($1->d_type, $2);
		}

		|	data_type error {
							//printing the error message in  declaration
							
							/*sprintf (str, "in  declaration ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(29);
							
							yyclearin;yyerrok;
			   	}
		|	error {
							//printing the error message in  declaration
							/*sprintf (str, "in  declaration " );
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(30);
							
							yyclearin;yyerrok;
			   	}

	
		;


dec		:	data_type  ID_init_list ';' {
			struct AST* nnode = newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($2);
			nnode->n_type=_DEC;
			nnode->code	= "DECLARATION";
			$$=nnode;
			rec_set_type($1->d_type, $2);
		}
		|	data_type error {
							//printing the error message in  declaration
							
							/*sprintf (str, "in  declaration ");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(31);
							
							yyclearin;yyerrok;
			   	}

	
		;
	
//*******************************************************************************************************************

		
ID_init_list
		:	dec_init 	{
			struct AST* nnode = newnode();
			(nnode->v).push_back($1);
			nnode->n_type=_DEC;
			nnode->code="DECLARATIONS_LIST";
			$$=nnode;
		}
		|	ID_init_list ',' dec_init 	{
			struct AST* nnode = newnode();
			(nnode->v).push_back($1);
			(nnode->v).push_back($3);
			nnode->n_type=_DEC;
			nnode->code="DECLARATIONS_LIST";
			$$=nnode;
		}
		|	ID_init_list error 	{
							
							//printing the error message in variable declaration
							/*sprintf (str, "in declaration");
							if(yylloc.first_line)
							    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
							 
							fprintf(stderr, "\n");*/
							$$ = newnode(_VOID,_ERROR,"error","");
							eat_to_newline(32);
							yyclearin;yyerrok;
			   	}
		;
	
dec_init
		:	ID 	{
			string s($1);
			struct AST* nnode=newnode(_VOID,_DEC_VAR,s,s);
			$$=nnode;
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
		|	ID '[' NUMBER ']' 	{
			string s($1);
			int a=$3;
			stringstream ss;
			ss << a;
			string val = ss.str();
			struct AST* nnode=newnode(_VOID,_DEC_ARR,s+"["+val+"]",s);
			$$=nnode;
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
		|	ID '=' expr 	{
			string s($1);
			if($3->d_type==_VOID || $3->d_type==_UNKNOWN){
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
			DataType d=expc_datatype($3->d_type);
			struct AST* nnode=newnode(d,_DECVAR_EQ,s+":=",s);
			(nnode->v).push_back($3);
			$$=nnode;
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
		|	ID '[' error ']'	{
									//printing the error message in array initializer declaration
									/*caught=true;
							sprintf (str, " Error in array index ");
									if(yylloc.first_line)
									    fprintf(stderr, "%d.%d - %d.%d error: %s before %s ", yylloc.first_line, yylloc.first_column,yylloc.last_line, yylloc.last_column,str,yytext);
									 
									fprintf(stderr, "\n");									   
							caught=false;*/
									$$ = newnode(_VOID,_ERROR,"error","");
									eat_to_newline(33);
									//cout <<"yahn aaya"<<endl;
									yyclearin;yyerrok;
			   					}
		
		;

		
		


%%

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

	    cout<<"main:"<<endl;
		cgen(n->v[0]);
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
		cgenTable.back().insert(pair<string, struct cgenEntry>(n->value, a));
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
		cgenTable.back().insert(pair<string, struct cgenEntry>(R2, a));
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
		int scope_count;
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

		return n->value+ss.str();
	}
	else if(n->n_type == _FACTOR_CONS)
	{
		return n->value;
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
		return newReg;
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
