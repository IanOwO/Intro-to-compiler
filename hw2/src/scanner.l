%option never-interactive
%option nounput
%option noinput

%{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define LIST_SOURCE                 appendToCurrentLine(yytext)
#define LIST_TOKEN(name)            do { LIST_SOURCE; if(opt_tok) printf("<%s>\n", name); } while(0)
#define LIST_LITERAL(name, literal) do { LIST_SOURCE; if(opt_tok) printf("<%s: %s>\n", name, literal); } while(0)
#define MAX_LINE_LENG               512

uint32_t line_num = 1;
char current_line[MAX_LINE_LENG];

static uint32_t opt_src = 1;
static uint32_t opt_tok = 1;
static char string_literal[MAX_LINE_LENG];
static char *current_line_ptr = current_line;

static void appendToCurrentLine(const char *yytext_ptr);

%}

integer 0|[1-9][0-9]*
float {integer}\.(0|[0-9]*[1-9])
nonzero_integer [1-9][0-9]*
    /* If the integral part is nonzero, then the fractional part can be either zero
    or not. However, if the integral part is zero, the fractional part cannot be zero. */
nonzero_float ({nonzero_integer}\.(0|[0-9]*[1-9]))|(0\.([0-9]*[1-9]))

    /* exclusive start condition */
%x CCOMMENT

%%
    /* Delimiter */
"," { LIST_TOKEN(","); return KWCOMMA;}
";" { LIST_TOKEN(";"); return KWSEMICOLON;}
":" { LIST_TOKEN(":"); return KWCOLON;}
"(" { LIST_TOKEN("("); return KWL_PAREN;}
")" { LIST_TOKEN(")"); return KWR_PAREN;}
"[" { LIST_TOKEN("["); return KWL_BRACKET;}
"]" { LIST_TOKEN("]"); return KWR_BRACKET;}

    /* Operator */
"+"   { LIST_TOKEN("+"); return KWADD;}
"-"   { LIST_TOKEN("-"); return KWSUB;}
"*"   { LIST_TOKEN("*"); return KWMUL;}
"/"   { LIST_TOKEN("/"); return KWDIV;}
"mod" { LIST_TOKEN("mod"); return KWMOD;}
":="  { LIST_TOKEN(":="); return KWASSIGN;}
"<"   { LIST_TOKEN("<"); return KWLT;}
"<="  { LIST_TOKEN("<="); return KWLE;}
"<>"  { LIST_TOKEN("<>"); return KWNE;}
">="  { LIST_TOKEN(">="); return KWGE;}
">"   { LIST_TOKEN(">"); return KWGT;}
"="   { LIST_TOKEN("="); return KWEQ;}
"and" { LIST_TOKEN("and"); return KWAND;}
"or"  { LIST_TOKEN("or"); return KWOR;}
"not" { LIST_TOKEN("not"); return KWNOT;}

    /* Reserved Word */
"var"     { LIST_TOKEN("KWvar"); return KWVAR;}
"array"   { LIST_TOKEN("KWarray"); return KWARR;}
"of"      { LIST_TOKEN("KWof"); return KWOF;}
"boolean" { LIST_TOKEN("KWboolean"); return KWBOOL;}
"integer" { LIST_TOKEN("KWinteger"); return KWINT;}
"real"    { LIST_TOKEN("KWreal"); return KWREAL;}
"string"  { LIST_TOKEN("KWstring"); return KWSTR;}

"true"    { LIST_TOKEN("KWtrue"); return KWTRUE;}
"false"   { LIST_TOKEN("KWfalse"); return KWFALSE;}

"def"     { LIST_TOKEN("KWdef"); return KWDEF;}
"return"  { LIST_TOKEN("KWreturn"); return KWRETURN;}

"begin"   { LIST_TOKEN("KWbegin"); return KWBEGIN;}
"end"     { LIST_TOKEN("KWend"); return KWEND;}

"while"   { LIST_TOKEN("KWwhile"); return KWWHILE;}
"do"      { LIST_TOKEN("KWdo"); return KWDO;}

"if"      { LIST_TOKEN("KWif"); return KWIF;}
"then"    { LIST_TOKEN("KWthen"); return KWTHEN;}
"else"    { LIST_TOKEN("KWelse"); return KWELSE;}

"for"     { LIST_TOKEN("KWfor"); return KWFOR;}
"to"      { LIST_TOKEN("KWto"); return KWTO;}

"print"   { LIST_TOKEN("KWprint"); return KWPRINT;}
"read"    { LIST_TOKEN("KWread"); return KWREAD;}

    /* Identifier */
[a-zA-Z][a-zA-Z0-9]* { LIST_LITERAL("id", yytext); return KWID;}

    /* Integer (decimal/octal) */
{integer} { LIST_LITERAL("integer", yytext); return KWDECIMAL;}
0[0-7]+   { LIST_LITERAL("oct_integer", yytext); return KWOCTAL;}

    /* Floating-Point */
{float} { LIST_LITERAL("float", yytext); return KWFLOAT;}

    /* Scientific Notation [Ee][+-]?[0-9]+ */
({nonzero_integer}|{nonzero_float})[Ee][+-]?({integer}) { LIST_LITERAL("scientific", yytext); return KWSCIENTIFIC;}

    /* String */
\"([^"\n]|\"\")*\" {
    char *yyt_ptr = yytext + 1;  // +1 for skipping the first double quote "
    char *str_ptr = string_literal;

    while (*yyt_ptr) {
        if (*yyt_ptr == '"') {
            // Handle the situation of two double quotes "" in string literal
            if (*(yyt_ptr + 1) == '"') {
                *str_ptr = *yyt_ptr;
                ++str_ptr;
                yyt_ptr += 2; // move to the next character of ""
            } else {
                ++yyt_ptr;
            }
        } else {  // normal character
            *str_ptr = *yyt_ptr;
            ++str_ptr;
            ++yyt_ptr;
        }
    }
    *str_ptr = '\0';
    LIST_LITERAL("string", string_literal);
	return KWSTRING;
}

    /* Whitespace */
[ \t]+ { LIST_SOURCE; }

    /* Pseudocomment */
"//&"[ST][+-].* {
    LIST_SOURCE;
    char option = yytext[3];
    switch (option) {
    case 'S':
        opt_src = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'T':
        opt_tok = (yytext[4] == '+') ? 1 : 0;
        break;
    }
}

    /* C++ Style Comment */
"//".* { LIST_SOURCE; }

    /* C Style Comment */
"/*"           { LIST_SOURCE; BEGIN(CCOMMENT); }
<CCOMMENT>"*/" { LIST_SOURCE; BEGIN(INITIAL); }
<CCOMMENT>.    { LIST_SOURCE; }

    /* Newline */
<INITIAL,CCOMMENT>\n {
    if (opt_src) {
        printf("%d: %s\n", line_num, current_line);
    }
    ++line_num;
    current_line[0] = '\0';
    current_line_ptr = current_line;
}

    /* Catch the character which is not accepted by all rules above */
. {
    printf("Error at line %d: bad character \"%s\"\n", line_num, yytext);
    exit(-1);
}

%%

static void appendToCurrentLine(const char *yytext_ptr) {
    while (*yytext_ptr) {
        *current_line_ptr = *yytext_ptr;
        ++current_line_ptr;
        ++yytext_ptr;
    }
    *current_line_ptr = '\0';
}
