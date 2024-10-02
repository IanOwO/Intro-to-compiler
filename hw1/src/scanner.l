%{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LIST_SOURCE                 appendToCurrentLine(yytext)
#define LIST_TOKEN(name)            do { LIST_SOURCE; if(opt_tok) printf("<%s>\n", name); } while(0)
#define LIST_LITERAL(name, literal) do { LIST_SOURCE; if(opt_tok) printf("<%s: %s>\n", name, literal); } while(0)
#define MAX_LINE_LENG               512

uint32_t line_num = 1;
static char current_line[MAX_LINE_LENG];

static uint32_t opt_src = 1;
static uint32_t opt_tok = 1;
static char *current_line_ptr = current_line;

static char str_[MAX_LINE_LENG];
static char *str_ptr = str_;

static void appendToCurrentLine(const char *yytext_ptr);
static void str_copy(const char *yytext_ptr, const int quote);

%}

delimeter ","|";"|":"|"("|")"|"["|"]"

op_one_char [-+*//=<>]
op_two_char ":="|">="|"<="|"<>"
op_reserved mod|and|or|not

rw_declare var|def
rw_type array|of|boolean|integer|real|string
rw_value true|false
rw_flow_control while|do|if|then|else|for|to
rw_block begin|end
rw_statememt print|read|return

identifier [a-zA-Z][a-zA-Z0-9]*
octal 0[0-7]+
nonzero_decimal [1-9][0-9]*
decimal {nonzero_decimal}|"0"
nonzero_float ({nonzero_decimal}\.[0-9]*[1-9])|({nonzero_decimal}\.[0-9])|"0."[0-9]*[1-9]
float {nonzero_float}|"0.0"
scientific ({nonzero_decimal}|{nonzero_float})(E|e)[-+]?{decimal}

word \"([^\"]+)\"

%Start COMMENT_BLOCK COMMENT_LINE PSEUDOCOMMENT IN_STRING
%%
	/*pseudicomment*/
<INITIAL>"//&S+"/"\n" {LIST_SOURCE; opt_src = 1;}
<INITIAL>"//&S+" {LIST_SOURCE; opt_src = 1; BEGIN COMMENT_LINE;}
<INITIAL>"//&S-"/"\n" { LIST_SOURCE; opt_src = 0;}
<INITIAL>"//&S-" { LIST_SOURCE; opt_src = 0; BEGIN COMMENT_LINE;}
<INITIAL>"//&T+"/"\n" {LIST_SOURCE; opt_tok = 1;}
<INITIAL>"//&T+" {LIST_SOURCE; opt_tok = 1; BEGIN COMMENT_LINE;}
<INITIAL>"//&T-"/"\n" { LIST_SOURCE; opt_tok = 0; }
<INITIAL>"//&T-" { LIST_SOURCE; opt_tok = 0; BEGIN COMMENT_LINE;}
	/*C-style comment*/
<COMMENT_BLOCK>"*/" { LIST_SOURCE; BEGIN INITIAL; }
<INITIAL>"/*" { LIST_SOURCE; BEGIN COMMENT_BLOCK; }
<COMMENT_BLOCK>. LIST_SOURCE;
	/*C++-style comment*/
<COMMENT_LINE>./"\n" { LIST_SOURCE; BEGIN INITIAL;}
<INITIAL>"//"/[^&] { LIST_SOURCE; BEGIN COMMENT_LINE; }
<COMMENT_LINE>. LIST_SOURCE;
	/*string*/
<INITIAL>\"\"/[^"] { LIST_SOURCE; if(opt_tok) printf("<string: >\n"); }
<INITIAL>\" { LIST_SOURCE; str_[0] = '\0'; str_ptr = str_; BEGIN IN_STRING;}
<IN_STRING>\"\" { LIST_SOURCE; str_copy("\"",1);}
<IN_STRING>\" { LIST_SOURCE;
	if(opt_tok) printf("<string: %s>\n", str_); BEGIN INITIAL;}
<IN_STRING>. { LIST_SOURCE; str_copy(yytext,0);}
	/*space&tab*/
<INITIAL>" "|"\t" { LIST_SOURCE; }
	/*delimeters*/
<INITIAL>{delimeter} { LIST_TOKEN(yytext); }
	/*two char operators*/
<INITIAL>{op_two_char} { 
	LIST_SOURCE;
	if(opt_tok) printf("<%c%c>\n",yytext[0],yytext[1]); yyless(2); }
	/*one char operators*/
<INITIAL>{op_one_char} { 
	LIST_SOURCE; 
	if(opt_tok) printf("<%c>\n",yytext[0]); yyless(1); }
	/*reserved operators*/
<INITIAL>{op_reserved} { LIST_TOKEN(yytext); }
	/*reserved words*/
<INITIAL>{rw_declare} |
<INITIAL>{rw_type} |
<INITIAL>{rw_value} |
<INITIAL>{rw_flow_control} |
<INITIAL>{rw_block} |
<INITIAL>{rw_statememt} { 
	LIST_SOURCE;
	if(opt_tok) printf("<KW%s>\n",yytext); }
	/*constant*/
<INITIAL>{scientific} { LIST_LITERAL("scientific", yytext); }
<INITIAL>{float} { LIST_LITERAL("float", yytext); }
<INITIAL>{octal} { LIST_LITERAL("oct_integer", yytext); }
<INITIAL>{decimal} { LIST_LITERAL("integer", yytext); }
	/*identifier*/
<INITIAL>{identifier} { LIST_LITERAL("id", yytext); }

\n {
    if (opt_src) {
        printf("%d: %s\n", line_num, current_line);
    }
    ++line_num;
    current_line[0] = '\0';
    current_line_ptr = current_line;
	str_[0] = '\0';
	str_ptr = str_;
}

    /* Catch the character which is not accepted by rules above */
<INITIAL>. {
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

static void str_copy(const char *yytext_ptr, const int quote) {
	while (*yytext_ptr != '"' && *yytext_ptr) {
        	*str_ptr = *yytext_ptr;
        	++str_ptr;
        	++yytext_ptr;
	}
	if (quote) {
		*str_ptr = *yytext_ptr;
        	++str_ptr;
        	++yytext_ptr;
	}
	*str_ptr = '\0';
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stderr, "Open file error\n");
        exit(-1);
    }

    yylex();

    fclose(yyin);
    /* Free resources used by the scanner; otherwise, unused data structures
    will persist throughout the successive compiler phases. */
    yylex_destroy();

    return 0;
}
