/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    KWID = 258,
    KWCOMMA = 259,
    KWSEMICOLON = 260,
    KWCOLON = 261,
    KWL_PAREN = 262,
    KWR_PAREN = 263,
    KWL_BRACKET = 264,
    KWR_BRACKET = 265,
    KWVAR = 266,
    KWARR = 267,
    KWOF = 268,
    KWBOOL = 269,
    KWINT = 270,
    KWREAL = 271,
    KWSTR = 272,
    KWTRUE = 273,
    KWFALSE = 274,
    KWDEF = 275,
    KWRETURN = 276,
    KWBEGIN = 277,
    KWEND = 278,
    KWWHILE = 279,
    KWDO = 280,
    KWIF = 281,
    KWTHEN = 282,
    KWELSE = 283,
    KWFOR = 284,
    KWTO = 285,
    KWPRINT = 286,
    KWREAD = 287,
    KWSCIENTIFIC = 288,
    KWFLOAT = 289,
    KWOCTAL = 290,
    KWDECIMAL = 291,
    KWSTRING = 292,
    KWADD = 293,
    KWSUB = 294,
    KWMUL = 295,
    KWDIV = 296,
    KWMOD = 297,
    KWLT = 298,
    KWLE = 299,
    KWNE = 300,
    KWGE = 301,
    KWGT = 302,
    KWEQ = 303,
    KWAND = 304,
    KWOR = 305,
    KWASSIGN = 306,
    KWNOT = 307
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

#endif /* !YY_YY_PARSER_H_INCLUDED  */
