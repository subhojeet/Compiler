/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
#line 554 "g3.y" /* yacc.c:1909  */

	struct AST* node;
	int int_val;
	float float_val;
	bool bool_val;
	char* string_val;
	char char_val;

#line 122 "g3.tab.h" /* yacc.c:1909  */
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
