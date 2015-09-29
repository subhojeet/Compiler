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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    ID = 259,
    EQ = 260,
    FUNCBEGIN = 261,
    FUNCEND = 262,
    PARAMSNUM = 263,
    RETURN = 264,
    PUSHARGS = 265,
    BINARY_OPERATORS = 266,
    PLUS = 267,
    MINUS = 268,
    TIMES = 269,
    DIVIDE = 270,
    SMALLER = 271,
    SMALLEREQ = 272,
    GREATER = 273,
    GREATEREQ = 274,
    EQEQ = 275,
    IF = 276,
    GOTO = 277,
    LABEL = 278,
    PARAM = 279,
    CALL = 280,
    COMMA = 281,
    LEFTSQPAR = 282,
    RIGSQPAR = 283,
    STAR = 284,
    ANDP = 285,
    UNARY_OPS = 286,
    PUSH = 287
  };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define EQ 260
#define FUNCBEGIN 261
#define FUNCEND 262
#define PARAMSNUM 263
#define RETURN 264
#define PUSHARGS 265
#define BINARY_OPERATORS 266
#define PLUS 267
#define MINUS 268
#define TIMES 269
#define DIVIDE 270
#define SMALLER 271
#define SMALLEREQ 272
#define GREATER 273
#define GREATEREQ 274
#define EQEQ 275
#define IF 276
#define GOTO 277
#define LABEL 278
#define PARAM 279
#define CALL 280
#define COMMA 281
#define LEFTSQPAR 282
#define RIGSQPAR 283
#define STAR 284
#define ANDP 285
#define UNARY_OPS 286
#define PUSH 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
