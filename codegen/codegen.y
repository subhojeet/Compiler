%{
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
//map <string,int> varmap;

map<string, map< string, int > >varmap_func;
map<string, int>paranum;

map<string, map< string, int > >::iterator vit;
map<string, int>::iterator pit;
vector<string> cur_function;

//int lookup(char *);
int var_indx(char *);
int yylex(void);
#define YYSTYPE char *
void yyerror (char const *s) {
   		//fprintf (stderr, "%s\n", s);
 }
FILE *temp;
extern char *yytext;
int labelcount=0;
int res_str_count=0;

string cur_func;
int para_num;
int local_num;

string genLabel();
string genres_str();

%}



%start lines
%token	NUM ID EQ FUNCBEGIN FUNCEND PARAMSNUM RETURN PUSHARGS V0 STR_LIT
%token BINARY_OPERATORS
%token	PLUS	MINUS	TIMES	DIVIDE	
%token SMALLER SMALLEREQ GREATER GREATEREQ EQEQ 
%token IF GOTO
%token LABEL PARAM CALL COMMA LEFTSQPAR RIGSQPAR
%token STAR ANDP  UNARY_OPS PUSH
%token OUTSTRING INSTRING OUTINT ININT OUTFLOAT  INFLOAT
%%

lines:   lines line /* do nothing */ 
		| line
			;

line: 		binary  
			| unary 
			| copy 
			| conditional_jump 
			| unconditional_jump 
			| function_call 
			| indexed_copy
			| address_pointer_assignment 
			| label1
			| fun_begin
			| para_num
			| fun_end
			| return_stmt
			| pushargs
			| save_to_v0
			| load_from_v0
			| outint
			| inint
			| outfloat
			| infloat
			| outstring
			| instring	
			;



inint
	:	ININT identifier 	{
		int k=var_indx($2);
		k+=3;
		fprintf(temp, "li $v0 5\n" );
		fprintf(temp, "syscall\n" );
		fprintf(temp,"sw $v0 %d($t0)\n",4*k );
	}
	;
infloat
	:	INFLOAT identifier
	;
instring
	:	INSTRING identifier
	;

outint
	:	OUTINT identifiernum {
			int k=var_indx($2);
			k+=3;
			fprintf(temp, "li $v0 1\n" );
			if(k<=2){
				fprintf(temp,"li $a0 %s\n",$2);
			}else{
				fprintf(temp,"lw $a0 %d($t0)\n",4*k );
			}
			fprintf(temp, "syscall\n" );
	}
	;
outfloat
	:	OUTFLOAT identifiernum
	;
outstring
	:	OUTSTRING  STR_LIT {

		fprintf(temp, ".data\n");
		cout << $2;
		string newvar=genres_str();
		fprintf(temp, "%s: .asciiz %s\n",&newvar[0],yytext );
		fprintf(temp, ".text\n" );
		fprintf(temp, "li $v0 4\n" );
		fprintf(temp, "la $a0 %s\n",&newvar[0] );
		fprintf(temp, "syscall\n" );
	}
	;

str_l : STR_LIT{
	cout << "3892ur\n";  
	$$=strdup(yytext);
	cout << "3\n";
	}
	;
fun_begin:	label FUNCBEGIN {
				cout << "1\n";
				fprintf(temp,"%s\n",$1);
				string s($1);
				int l=s.length();
				string s1 = s.substr(0,l-1);
				cur_func=s1;
				cur_function.push_back(s1);
				cout << "2\n";
			}
			;

save_to_v0:	V0 EQ identifiernum {
			int k=var_indx($3);
			k+=3;
			if(k<=2){
				fprintf(temp,"li $a0 %s\n",$3);
			}else{
				fprintf(temp,"lw $a0 %d($t0)\n",4*k );
			}
			fprintf(temp, "move $v0 $a0\n" );
		}
		;

load_from_v0:	identifier EQ V0 {
			int k=var_indx($1);
			k+=3;
			fprintf(temp,"sw $v0 %d($t0)\n",4*k );
			fprintf(temp,"sw $v0 8($t0)\n" );
			/*fprintf(temp,"move $a0 $v0\n" );
			fprintf(temp,"li  $v0 1\n" );
			fprintf(temp,"syscall\n" );*/
		}
		;
fun_end:	FUNCEND num {
				cout << "funcend\n";
				fprintf(temp,"lw $ra 4($t0)\n");
		        int k = local_num + 4;
		        fprintf(temp,"addiu $sp $sp %d\n",4*k );
		        fprintf(temp,"jr $ra\n");
		        cur_function.pop_back();
			}
			;

para_num:	PARAMSNUM num {
				para_num = atoi($2);
				pit=paranum.find(cur_function.back());
				if(pit!=paranum.end()){
					local_num = pit->second;
				}
				int k = (local_num - para_num) + 3;
				fprintf(temp,"addiu $sp $sp %d\n",-4*k );
				fprintf(temp,"move $t0 $sp\n");
				fprintf(temp,"sw $t0 0($sp)\n");
				fprintf(temp,"sw $ra 4($t0)\n");
				fprintf(temp,"li $a0 0\n");
				fprintf(temp,"sw $a0 8($t0)\n");
				fprintf(temp,"addiu $sp $sp %d\n",-4 );
			}
			;
 
return_stmt:	RETURN {
					        fprintf(temp,"lw $ra 4($t0)\n");
					        int k = local_num + 4;
					        fprintf(temp,"addiu $sp $sp %d\n",4*k );
					        fprintf(temp,"jr $ra\n");
				}
				;

binary: 	identifier EQ identifiernum binary_ops identifiernum {
						
						if(strcmp($4,"+")==0)
						{

							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							fprintf(temp,"add $a0 $a0 $t1\n");
							//k=lookup($1);
							k=var_indx($1);
							k+=3;
							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}else if(strcmp($4,"-")==0){
							cout<<"MINUS"<<endl;
							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							fprintf(temp,"sub $a0 $t1 $a0\n");
							//k=lookup($1);
							k=var_indx($1);
							k+=3;
							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}else if(strcmp($4,"*")==0){
							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							fprintf(temp,"mul $a0 $a0 $t1\n");
							//k=lookup($1);
							k=var_indx($1);
							k+=3;
							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}else if(strcmp($4,"/")==0){
							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							fprintf(temp,"div $t1 $a0\n");
							fprintf(temp,"mflo	$a0\n");
							
							//k=lookup($1);
							k=var_indx($1);
							k+=3;

							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}else if(strcmp($4,"%")==0){
							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							fprintf(temp,"div $t1 $a0\n");
							fprintf(temp,"mfhi	$a0\n");
							
							//k=lookup($1);
							k=var_indx($1);
							k+=3;

							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}else if(strcmp($4,"<")==0){
							
							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							fprintf(temp,"sub $a0 $a0 $t1\n");

							string l1 = genLabel();
							string l2 = genLabel();

							cout<<"l1 "<<l1<<endl;
							cout<<"l2 "<<l2<<endl;

							fprintf(temp, "bgtz $a0 %s\n", l1.c_str() );
							fprintf(temp, "li $a0 0\n" );
							fprintf(temp, "b %s\n",l2.c_str() );
							fprintf(temp, "%s:",l1.c_str() );
							fprintf(temp, "li $a0 1\n" );
							fprintf(temp, "%s:",l2.c_str() );
							//k=lookup($1);
							k=var_indx($1);
							k+=3;
							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}else if(strcmp($4,">")==0){
							
							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							fprintf(temp,"sub $a0 $t1 $a0\n");

							string l1 = genLabel();
							string l2 = genLabel();

							cout<<"l1 "<<l1<<endl;
							cout<<"l2 "<<l2<<endl;

							fprintf(temp, "bgtz $a0 %s\n", l1.c_str() );
							fprintf(temp, "li $a0 0\n" );
							fprintf(temp, "b %s\n",l2.c_str() );
							fprintf(temp, "%s:",l1.c_str() );
							fprintf(temp, "li $a0 1\n" );
							fprintf(temp, "%s:",l2.c_str() );
							//k=lookup($1);
							k=var_indx($1);
							k+=3;
							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}else if(strcmp($4,"==")==0){
							
							//int k=lookup($3);
							int k=var_indx($3);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$3);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}

							//pushing into stack first arg
							fprintf(temp,"sw $a0 0($sp)\n");
							fprintf(temp,"addiu $sp $sp -4\n");


							//k=lookup($5);
							k=var_indx($5);
							k+=3;
							if(k<=2)
							{
								fprintf(temp,"li $a0 %s\n",$5);
							}
							else
							{
								fprintf(temp,"lw $a0 %d($t0)\n",4*k );
							}
							fprintf(temp,"lw $t1 4($sp)\n");
							fprintf(temp,"addiu $sp $sp 4\n");
							

							string l1 = genLabel();
							string l2 = genLabel();

							cout<<"l1 "<<l1<<endl;
							cout<<"l2 "<<l2<<endl;

							fprintf(temp, "beq $a0 $t1 %s\n", l1.c_str() );
							fprintf(temp, "li $a0 0\n" );
							fprintf(temp, "b %s\n",l2.c_str() );
							fprintf(temp, "%s:",l1.c_str() );
							fprintf(temp, "li $a0 1\n" );
							fprintf(temp, "%s:",l2.c_str() );
							//k=lookup($1);
							k=var_indx($1);
					 		k+=3;
							fprintf(temp,"sw $a0 %d($t0)\n",4*k );
									
						}
					}
					;
			
identifiernum : identifier {$$ = $1;}
				| num {$$ = $1;}
				;

binary_ops: BINARY_OPERATORS { $$ = strdup(yytext); }	

identifier: ID { $$ = strdup(yytext); }

num: 		NUM {$$ = strdup(yytext);}

label : LABEL {
	cout << "3\n";
	$$ = strdup(yytext);
	cout << "4\n";
	}
	;

unary: 		identifier EQ UNARY_OPS identifier {}

copy: 		identifier EQ identifier {
										//int k = lookup($3);
										int k=var_indx($3);
					 					k+=3;
					 					if(k>2){
											fprintf(temp,"lw $a0 %d($t0)\n",4*k);
										}
										k=var_indx($1);
					 					k+=3;
										//k = lookup($1);
										if(k>2){
											fprintf(temp,"sw $a0 %d($t0)\n",4*k);
										}
									}
			| identifier EQ num 	{
										//int k = lookup($1);
										int k=var_indx($1);
					 					k+=3;
					 					if(k>2){
											fprintf(temp,"li $a0 %s\n",$3);
											fprintf(temp,"sw $a0 %d($t0)\n",4*k);
										}
									}
label1: label
		{
			fprintf(temp,"%s\n",$1);
		}
		;
conditional_jump : IF identifier GOTO label
					 {
					 	//remove : from label:
					 	int l=strlen($4);
					 	$4[l-1]=0;

					 	cout<<"yes1"<<endl;
					 	//int k=lookup($2);
					 	int k=var_indx($2);
					 	k+=3;
					 	fprintf(temp,"lw $a0 %d($t0)\n",4*k);
				   	 	fprintf(temp,"li $t1 0\n");
				   	 	fprintf(temp,"bne $a0 $t1 %s\n",$4);
											
					 }
				   | IF num GOTO label 
				   	 {
				   	 	//remove : from label:
				   	 	int l=strlen($4);
					 	$4[l-1]=0;
				   	 	cout<<"yes2"<<endl;
				   	 	fprintf(temp,"li $a0 %s\n",$1);
				   	 	fprintf(temp,"li $t1 0\n");
				   	 	fprintf(temp,"bne $a0 $t1 %s\n",$4);
				   	 }
				   	 ;

unconditional_jump : GOTO label
					 {
					 	//remove : from label:
					 	
					 	int l=strlen($2);
					 	$2[l-1]=0;
					 	cout<<"yes3"<<endl;
					 	fprintf(temp,"b %s\n",$2);
					 }
					 ;

/*parameters : PUSH identifier 
			| PUSH num {cout<<"yes6"<<endl;}*/

//function_call : CALL LABEL COMMA num {cout<<"yes7"<<endl;}
function_call: CALL identifier {
								fprintf(temp,"jal %s\n",$2);
								fprintf(temp,"lw $t0 4($sp)\n");
								cout<<"jal "<< $2 <<endl;
								}
			  ;

pushargs:	PUSHARGS identifier 	{
				int k=var_indx($2);
				k+=3;
				fprintf(temp,"lw $a0 %d($t0)\n",4*k);
				fprintf(temp,"addiu $sp $sp -4\n");
				fprintf(temp,"sw $a0 0($sp)\n");
			}
			| PUSHARGS num 	{
				fprintf(temp,"li $a0 %s\n",$2);
				fprintf(temp,"addiu $sp $sp -4\n");
				fprintf(temp,"sw $a0 0($sp)\n");
			}
			;


indexed_copy : 	identifier EQ identifier LEFTSQPAR num RIGSQPAR 
				| identifier EQ identifier LEFTSQPAR identifier RIGSQPAR {cout<<"yes8"<<endl;}

address_pointer_assignment : 	STAR identifier EQ identifier 
								| identifier EQ STAR identifier | identifier EQ ANDP identifier |ANDP identifier EQ identifier | STAR identifier EQ num
								{cout<<"yes9"<<endl;}
%%
/*int lookup(char * a)
{
	string x(a);
	if(varmap.find(x)!=varmap.end())return varmap[x];
	else return -1;
}*/

int var_indx(char *a)
{
	string x(a);
	string fun=cur_function.back();
	vit = varmap_func.find(fun);
	if(vit!=varmap_func.end()){
		pit=(vit->second).find(x);
		if(pit!=(vit->second).end()){
			return ((local_num-1) - pit->second);
		}else{
			return -1;
		}
	}
	return -1;
}

string genLabel(){
	string l = "_lb";
	stringstream ss;
	ss<<labelcount;
	labelcount++;
	cout<<labelcount<<endl;
	
	return l+ss.str();
}
string genres_str(){
	string l = "res_str";
	stringstream ss;
	ss<<res_str_count;
	res_str_count++;
	//cout<<labelcount<<endl;
	
	return l+ss.str();
}
int main (void) {
	//printf("yes\n");
	char a[1000];
	//temp=fopen("mid.txt","r");
	int k=1;

	ifstream in;
	size_t found;
	in.open("../tmpvar.txt");
	string line;
	string cur_func="";
	while(getline(in, line)){
		found = line.find(":");
		if(found!=string::npos){
			string label = line.substr(0, found);
			string numstr = line.substr(found+1);
			int num = atoi(numstr.c_str());
			cur_func=label;
			paranum.insert(pair<string, int>(cur_func, num));
			map<string, int>tmp;
			varmap_func.insert(pair<string, map< string, int > >(cur_func, tmp));
		}else{
			found = line.find("=");
			if(found!=string::npos){
				string variable = line.substr(0, found);
				string indxstr = line.substr(found+1);
				int idx = atoi(indxstr.c_str());
				map<string, map< string, int > >::iterator it;
				it = varmap_func.find(cur_func);
				if(it!=varmap_func.end()){
					(it->second).insert(pair<string, int>(variable, idx));
				}
			}
		}
	}

	/*while(fscanf(temp,"%s",a)!=EOF)
	{
		string b(a);
		//cout<<a<<endl;
		//fscanf(temp,"%d",&k);
		if(varmap.find(b)==varmap.end()){varmap[b]=k++;}
	}*/
	//fclose(temp);
	//printf("yes\n");
	temp=fopen("out.s","w");
	fprintf(temp,".text\n");
	/*fprintf(temp,"main:\n");
	fprintf(temp,"move $t0 $sp\n");
	fprintf(temp,"addiu $sp $sp %d\n",-4*k );*/
	cur_function.push_back("global");
	yyparse ();
	//fprintf(temp,"jr $ra\n" );
	fclose(temp);
	return 0;
}


int yyerror (char *s) {fprintf (stderr, "error at %s\n", yytext);}
