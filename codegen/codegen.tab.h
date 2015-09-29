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

#ifndef YY_YY_CODEGEN_TAB_H_INCLUDED
# define YY_YY_CODEGEN_TAB_H_INCLUDED
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
    NUM = 258,
    ID = 259,
    EQ = 260,
    FUNCBEGIN = 261,
    FUNCEND = 262,
    PARAMSNUM = 263,
    RETURN = 264,
    PUSHARGS = 265,
    V0 = 266,
    STR_LIT = 267,
    BINARY_OPERATORS = 268,
    PLUS = 269,
    MINUS = 270,
    TIMES = 271,
    DIVIDE = 272,
    SMALLER = 273,
    SMALLEREQ = 274,
    GREATER = 275,
    GREATEREQ = 276,
    EQEQ = 277,
    IF = 278,
    GOTO = 279,
    LABEL = 280,
    PARAM = 281,
    CALL = 282,
    COMMA = 283,
    LEFTSQPAR = 284,
    RIGSQPAR = 285,
    STAR = 286,
    ANDP = 287,
    UNARY_OPS = 288,
    PUSH = 289,
    OUTSTRING = 290,
    INSTRING = 291,
    OUTINT = 292,
    ININT = 293,
    OUTFLOAT = 294,
    INFLOAT = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CODEGEN_TAB_H_INCLUDED  */
