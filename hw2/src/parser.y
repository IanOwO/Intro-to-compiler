%{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern int32_t line_num;    /* declared in scanner.l */
extern char current_line[]; /* declared in scanner.l */
extern FILE *yyin;          /* declared by lex */
extern char *yytext;        /* declared by lex */

extern int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%token KWID

%token KWCOMMA KWSEMICOLON KWCOLON KWL_PAREN KWR_PAREN KWL_BRACKET KWR_BRACKET
%token KWVAR KWARR KWOF KWBOOL KWINT KWREAL KWSTR KWTRUE KWFALSE KWDEF KWRETURN KWBEGIN KWEND KWWHILE KWDO KWIF KWTHEN KWELSE KWFOR KWTO KWPRINT KWREAD
%token KWSCIENTIFIC KWFLOAT KWOCTAL KWDECIMAL	/* number */
%token KWSTRING

%left KWADD KWSUB KWMUL KWDIV KWMOD KWLT KWLE KWNE KWGE KWGT KWEQ KWAND KWOR /* operation, may modify */
%right KWASSIGN KWNOT

%%

program: KWID KWSEMICOLON zero_more_var_const_declare zero_more_func_declare_or_def compound_statement KWEND
	;

zero_more_func_declare_or_def: func_declare_or_def zero_more_func_declare_or_def
	|
	;

func_declare_or_def: KWID KWL_PAREN argument KWR_PAREN KWCOLON scalar_type KWSEMICOLON
	| KWID KWL_PAREN argument KWR_PAREN KWSEMICOLON
	| KWID KWL_PAREN argument KWR_PAREN KWCOLON scalar_type compound_statement KWEND
	| KWID KWL_PAREN argument KWR_PAREN compound_statement KWEND
	;

zero_more_var_const_declare: var_const_declare zero_more_var_const_declare
	| 
	;

var_const_declare: KWVAR id_list KWCOLON scalar_type KWSEMICOLON
	| KWVAR id_list KWCOLON dimention scalar_type KWSEMICOLON	/* DECIMAL need modify, contain 0 */
	| KWVAR id_list KWCOLON literal_const KWSEMICOLON
	;

dimention: KWARR KWDECIMAL KWOF dimention
	| 
	;

id_list: id_list KWCOMMA KWID
	| KWID
	;

scalar_type: KWBOOL
	| KWINT
	| KWREAL
	| KWSTR
	;

argument: id_list KWCOLON scalar_type argument
	| 
	;

literal_const: KWDECIMAL
	| KWFLOAT
	| KWSTRING
	| KWSCIENTIFIC
	| KWTRUE
	| KWFALSE
	;

var_reference: KWID zero_more_bracket
	;

zero_more_bracket: KWL_BRACKET expression KWR_BRACKET zero_more_bracket
	| 
	;

compound_statement: KWBEGIN zero_more_var_const_declare zero_more_statement KWEND;

statement: var_reference KWASSIGN expression KWSEMICOLON
	| KWPRINT expression KWSEMICOLON
	| KWREAD var_reference KWSEMICOLON
	| KWIF expression KWTHEN compound_statement KWELSE compound_statement KWEND KWIF
	| KWIF expression KWTHEN compound_statement KWEND KWIF
	| KWWHILE expression KWDO compound_statement KWEND KWDO
	| KWFOR KWID KWASSIGN KWDECIMAL KWTO KWDECIMAL KWDO compound_statement KWEND KWDO
	| KWRETURN expression KWSEMICOLON
	| KWID KWL_PAREN comma_expression KWR_PAREN KWSEMICOLON
	| KWID KWL_PAREN KWR_PAREN KWSEMICOLON
	;

zero_more_statement: statement zero_more_statement
	| compound_statement zero_more_statement
	|
	;

comma_expression: comma_expression KWCOMMA expression
	| expression
	;

expression: KWID KWL_PAREN comma_expression KWR_PAREN
	| KWID KWL_PAREN KWR_PAREN
	| KWSUB expression 
	| expression KWMUL expression
	| expression KWDIV expression
	| expression KWMOD expression
	| expression KWADD expression
	| expression KWSUB expression
	| expression KWNE expression
	| expression KWLE expression
	| expression KWLT expression
	| expression KWGE expression
	| expression KWGT expression
	| expression KWEQ expression
	| expression KWAND expression
	| expression KWOR expression
	| KWNOT expression
	| KWL_PAREN expression KWR_PAREN
	| literal_const
	| var_reference
	;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, current_line, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen() failed");
        exit(-1);
    }

    yyparse();

    fclose(yyin);
    yylex_destroy();

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
