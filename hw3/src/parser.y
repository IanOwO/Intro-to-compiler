%{
#include "AST/BinaryOperator.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/ast.hpp"
#include "AST/decl.hpp"
#include "AST/expression.hpp"
#include "AST/for.hpp"
#include "AST/function.hpp"
#include "AST/if.hpp"
#include "AST/print.hpp"
#include "AST/program.hpp"
#include "AST/read.hpp"
#include "AST/return.hpp"
#include "AST/variable.hpp"
#include "AST/while.hpp"
#include "AST/AstDumper.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>


#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

extern int32_t line_num;    /* declared in scanner.l */
extern char current_line[]; /* declared in scanner.l */
extern FILE *yyin;          /* declared by lex */
extern char *yytext;        /* declared by lex */

static AstNode *root;

struct id_data{
    const char* const name;
    uint32_t line;
    uint32_t column;
};

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%code requires {
    class AstNode;
	class ProgramNode;
    class CompoundStatementNode;
    class DeclNode;
    class VariableNode;
    struct id_data;
    struct formal_data;
    class ConstantValueNode;
    class FunctionNode;
	#include "AST/BinaryOperator.hpp"
	#include "AST/CompoundStatement.hpp"
	#include "AST/ConstantValue.hpp"
	#include "AST/FunctionInvocation.hpp"
	#include "AST/UnaryOperator.hpp"
	#include "AST/VariableReference.hpp"
	#include "AST/assignment.hpp"
	#include "AST/ast.hpp"
	#include "AST/decl.hpp"
	#include "AST/expression.hpp"
	#include "AST/for.hpp"
	#include "AST/function.hpp"
	#include "AST/if.hpp"
	#include "AST/print.hpp"
	#include "AST/program.hpp"
	#include "AST/read.hpp"
	#include "AST/return.hpp"
	#include "AST/variable.hpp"
	#include "AST/while.hpp"
	#include <cstdint>
	#include <cstdio>
	#include <cstdlib>
	#include <cstring>
    #include <vector>
}

    /* For yylval */
%union {
    /* basic semantic value */
    char *identifier;

    AstNode *node;
	ProgramNode *program_node;
    CompoundStatementNode *compound_stmt_ptr;
    DeclNode *decl_ptr;
    std::vector<AstNode*> *node_list_ptr;
    std::vector<struct id_data> *id_list_ptr;
    int int_lit;
    float real_lit;
    struct id_data* id_data_ptr;
    struct literal_data* literal_data_ptr;
    ConstantValueNode *const_val_ptr;
    FunctionNode *func_ptr;
    std::vector<DeclNode*> *decl_list_ptr;
    ExpressionNode* exp_ptr;
    std::vector<ExpressionNode*> *exp_list_ptr;
    VariableReferenceNode* var_ref_ptr;

    IfNode* if_ptr;
    WhileNode* while_ptr;
    ForNode* for_ptr;
    ReturnNode* return_ptr;
};

%type <identifier> ProgramName ID
%type <compound_stmt_ptr> CompoundStatement

%type <identifier> Type
%type <identifier> ScalarType
%type <identifier> ArrType
%type <identifier> ArrDecl
%type <decl_ptr> Declaration
%type <node_list_ptr> Declarations
%type <node_list_ptr> DeclarationList 
%type <id_list_ptr> IdList
%type <const_val_ptr> LiteralConstant
%type <int_lit> NegOrNot
%type <int_lit> INT_LITERAL
%type <real_lit> REAL_LITERAL
%type <identifier> STRING_LITERAL
%type <id_data_ptr> StringAndBoolean
%type <func_ptr> Function FunctionDeclaration FunctionDefinition
%type <node_list_ptr> Functions FunctionList
%type <identifier> FunctionName 
%type <identifier> ReturnType
%type <decl_ptr> FormalArg
%type <decl_list_ptr> FormalArgs FormalArgList
%type <node> Statement
%type <node_list_ptr> Statements StatementList
%type <node> Simple
%type <literal_data_ptr> IntegerAndReal
%type <exp_ptr> Expression FunctionInvocation FunctionCall
%type <exp_list_ptr> Expressions ExpressionList ArrRefs ArrRefList 
%type <var_ref_ptr> VariableReference

%type <if_ptr> Condition
%type <compound_stmt_ptr> ElseOrNot
%type <while_ptr> While
%type <for_ptr> For
%type <return_ptr> Return


    /* Follow the order in scanner.l */

    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token FALSE TRUE
%token PRINT READ

    /* Identifier */
%token ID

    /* Literal */
%token INT_LITERAL
%token REAL_LITERAL
%token STRING_LITERAL


%%

Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
        root = new ProgramNode(@1.first_line, @1.first_column,
                               $1, $3, $4, $5);
        free($1);
    }
;

ProgramName:
    ID
;

DeclarationList:
    Epsilon {
        $$ = nullptr;
    }
    |
    Declarations {
        $$ = $1;
    }
;

Declarations:
    Declaration {
        $$ = new std::vector<AstNode*>;
        $$->push_back($1);
    }
    |
    Declarations Declaration {
        $$ = $1;
        $$->push_back($2);
    }
;

FunctionList:
    Epsilon {
        $$ = nullptr;
    }
    |
    Functions {
        $$ = $1;
    }
;

Functions:
    Function {
        $$ = new std::vector<AstNode*>;
        $$->push_back($1);
    }
    |
    Functions Function {
        $$ = $1;
        $$->push_back($2);
    }
;

Function:
    FunctionDeclaration {
        $$ = $1;
    }
    |
    FunctionDefinition {
        $$ = $1;
    }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON {
        std::vector<AstNode*> *ast_node = new std::vector<AstNode*>;
        std::string arg_list;
        
        arg_list = $5;
        arg_list += " (";
        if ($3 != nullptr) {
            for (unsigned int i = 0;i < ($3)->size();i++){
                // variable node pushback
                ast_node->push_back(new DeclNode(($3)->at(i)->getLocation().line, ($3)->at(i)->getLocation().col, 
                                                ($3)->at(i)->var_body, ($3)->at(i)->id_body, ($3)->at(i)->type_body));
                // type & parameter add
                if (i > 0) {
                    arg_list += ", ";
                }
                for (unsigned int j = 0;j < ($3)->at(i)->id_body->size();j++){
                    if (j > 0) {
                        arg_list += ", ";
                    }
                    arg_list += $3->at(i)->type_body;
                }
            }
        }
        arg_list += ')';
        $$ = new FunctionNode(@1.first_line, @1.first_column, $1, arg_list, nullptr, ast_node);
    }
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END {
        std::vector<AstNode*> *ast_node = new std::vector<AstNode*>;
        std::string arg_list;
        // printf("name:%s,type:%s\n",$1,$5);
        arg_list = $5;
        arg_list += " (";
        if ($3 != nullptr) {
            for (unsigned int i = 0;i < ($3)->size();i++){
                // variable node pushback
                ast_node->push_back(new DeclNode(($3)->at(i)->getLocation().line, ($3)->at(i)->getLocation().col, 
                                                ($3)->at(i)->var_body, ($3)->at(i)->id_body, ($3)->at(i)->type_body));
                // type & parameter add
                if (i > 0) {
                    arg_list += ", ";
                }
                for (unsigned int j = 0;j < ($3)->at(i)->id_body->size();j++){
                    if (j > 0) {
                        arg_list += ", ";
                    }
                    arg_list += $3->at(i)->type_body;
                }
            }         
        }
        arg_list += ')';
        // printf("result:%s\n",arg_list.c_str());
        $$ = new FunctionNode(@1.first_line, @1.first_column, $1, arg_list, $6, ast_node);
    }
;

FunctionName:
    ID {
        $$ = $1;
    }
;

FormalArgList:
    Epsilon {
        $$ = nullptr;
    }
    |
    FormalArgs {
        $$ = $1;
    }
;

FormalArgs:
    FormalArg {
        $$ = new std::vector<DeclNode*>;
        $$->push_back($1);
    }
    |
    FormalArgs SEMICOLON FormalArg {
        $$ = $1;
        $$->push_back($3);
    }
;

FormalArg:
    IdList COLON Type {
        std::vector<AstNode*> *id_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        std::string var_type_string = $3;
        if ($1 != nullptr) {
            for (auto &var_node : *($1)) {
                id_node->push_back(new VariableNode(var_node.line, var_node.column, var_node.name, var_type_string, nullptr));
                id_string->push_back(var_node.name);
            }
        }
        else {
            id_node = nullptr;
        }

        $$ = new DeclNode(@1.first_line, @1.first_column, id_node, id_string, var_type_string);
    }
;

IdList:
    ID {
        // printf("parser to ID\n");
        $$ = new std::vector<struct id_data>;
        struct id_data cur_var = {$1, @1.first_line, @1.first_column};
        $$->push_back(cur_var);
        // printf("idnew:%s\n",$1);
    }
    |
    IdList COMMA ID {
        // printf("parser to ID_list\n");
        $$ = $1;
        // printf("in id list:%s, %u\n",$1->at(0)->name,$1->at(0)->column);
        struct id_data cur_var_new = {$3, @3.first_line, @3.first_column};
        $$->push_back(cur_var_new);
        // printf("in id list:%s, %u\n",$$->at(1)->name,$$->at(1)->column);
        // printf("idadd:%s\n",$3);
    }
;

ReturnType:
    COLON ScalarType {
        $$ = $2;
    }
    |
    Epsilon {
        $$ = (char*)"void";
    }
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON Type SEMICOLON {
        // for (unsigned int i = 0;i < $2->size();i++){
        //     printf("id list struct:%u,%u,%s\n",$2->at(i).line,$2->at(i).column,$2->at(i).name);
        // }

        std::vector<AstNode*> *id_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        std::string var_type_string = $4;
        if ($2 != nullptr) {
            for (auto &var_node : *($2)) {
                id_node->push_back(new VariableNode(var_node.line, var_node.column, var_node.name, var_type_string, nullptr));
                id_string->push_back(var_node.name);
            }
        }
        else {
            id_node = nullptr;
        }

        $$ = new DeclNode(@1.first_line, @1.first_column, id_node, id_string, var_type_string);
    }
    |
    VAR IdList COLON LiteralConstant SEMICOLON {
        // for (unsigned int i = 0;i < $2->size();i++){
        //     printf("id list struct:%u,%u,%s\n",$2->at(i).line,$2->at(i).column,$2->at(i).name);
        // }

        std::vector<AstNode*> *id_const_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        
        std::string var_type_string = $4->getdatatype($4->type_data);
        if ($2 != nullptr) {
            for (auto &id_list : *$2) {
                id_const_node->push_back(new VariableNode(id_list.line, id_list.column, id_list.name, var_type_string, $4));
                id_string->push_back(id_list.name);
            }
        }
        else {
            id_const_node = nullptr;
        }
        
        $$ = new DeclNode(@1.first_line, @1.first_column, id_const_node, id_string, var_type_string);
    }
;

Type:
    ScalarType {
        $$ = $1;
    }
    |
    ArrType {
        $$ = $1;
    }
;

ScalarType:
    INTEGER {
        $$ = (char*)"integer";
    }
    |
    REAL {
        $$ = (char*)"real";
    }
    |
    STRING {
        $$ = (char*)"string";
    }
    |
    BOOLEAN {
        $$ = (char*)"boolean";
    }
;

ArrType:
    ArrDecl ScalarType {
        std::string str = $2;
        str += $1;
        $$ = (char*)str.c_str();
    }
;

ArrDecl:
    ARRAY INT_LITERAL OF {
        std::string str = " [";
        str += std::to_string($2);
        str += ']';
        //printf("string:%s,int:%d",std::to_string(INT_LITERAL),);
        $$ = (char*)str.c_str();
    }
    |
    ArrDecl ARRAY INT_LITERAL OF {
        std::string str = $1;
        str += '[';
        str += std::to_string($3);
        str += ']';
        $$ = (char*)str.c_str();
    }
;

LiteralConstant:
    NegOrNot INT_LITERAL {
        // std::string str = $1;
        // str += std::to_string(INT_LITERAL);
        // $$ = (char*)str.c_str();
        struct literal_data ld = {INT, $1 * $2, 0.0, nullptr};
        if ($1 == 1) $$ = new ConstantValueNode(@2.first_line, @2.first_column, ld);
        else $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
    }
    |
    NegOrNot REAL_LITERAL {
        // std::string str = $1;
        // str += std::to_string(INT_LITERAL);
        // $$ = (char*)str.c_str();
        struct literal_data ld = {FLOAT, 0, $1 * $2, nullptr};
        if ($1 == 1) $$ = new ConstantValueNode(@2.first_line, @2.first_column, ld);
        else $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
    }
    |
    StringAndBoolean {
        if (($1)->line == 1) {
            struct literal_data ld = {STRING_, 0, 0.0, ($1)->name};
            $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
        }
        else {
            if (($1)->column == 1){
                struct literal_data ld = {TRUE_, 0, 0.0, ($1)->name};
                $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
            }
            else {
                struct literal_data ld = {FALSE_, 0, 0.0, ($1)->name};
                $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
            }
        }
    }
;

NegOrNot:
    Epsilon {
        $$ = 1;
    }
    |
    MINUS %prec UNARY_MINUS {
        $$ = -1;
    }
;

StringAndBoolean:
    STRING_LITERAL {
        struct id_data id_ = {$1,1,0};
        $$ = &id_;
    }
    |
    TRUE {
        struct id_data id_ = {"true",0,1};
        $$ = &id_;
    }
    |
    FALSE {
        struct id_data id_ = {"false",0,0};
        $$ = &id_;
    }
;

IntegerAndReal:
    INT_LITERAL {
        struct literal_data ld = {INT, $1, 0.0, nullptr};
        $$ = &ld;
    }
    |
    REAL_LITERAL {
        struct literal_data ld = {FLOAT, 0, $1, nullptr};
        $$ = &ld;
    }
;

    /*
       Statements
                  */

Statement:
    CompoundStatement {
        $$ = $1;
    }
    |
    Simple {
        $$ = $1;
    }
    |
    Condition {
        $$ = $1;
    }
    |
    While {
        $$ = $1;
    }
    |
    For {
        $$ = $1;
    }
    |
    Return {
        $$ = $1;
    }
    |
    FunctionCall {
        $$ = $1;
    }
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END {
        $$ = new CompoundStatementNode(@1.first_line, @1.first_column, $2, $3);
    }
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON {
        $$ = new AssignmentNode(@2.first_line, @2.first_column, (AstNode*)$1, (AstNode*)$3);
    }
    |
    PRINT Expression SEMICOLON {
        $$ = new PrintNode(@1.first_line, @1.first_column, (AstNode*)$2);
    }
    |
    READ VariableReference SEMICOLON {
        $$ = new ReadNode(@1.first_line, @1.first_column, (AstNode*)$2);
    }
;

VariableReference:
    ID ArrRefList {
        std::string var_name = $1;
        $$ = new VariableReferenceNode(@1.first_line, @1.first_column, var_name, $2);
    }
;

ArrRefList:
    Epsilon {
        $$ = nullptr;
    }
    |
    ArrRefs {
        $$ = $1;
    }
;

ArrRefs:
    L_BRACKET Expression R_BRACKET {
        $$ = new std::vector<ExpressionNode*>;
        $$->push_back($2);
    }
    |
    ArrRefs L_BRACKET Expression R_BRACKET {
        $$ = $1;
        $$->push_back($3);
    }
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot
    END IF {
        $$ = new IfNode(@1.first_line, @1.first_column, (AstNode*)$2, $4, $5);
    }
;

ElseOrNot:
    ELSE
    CompoundStatement {
        $$ = $2;
    }
    |
    Epsilon {
        $$ = nullptr;
    }
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO {
        $$ = new WhileNode(@1.first_line, @1.first_column, (AstNode*)$2, $4);
    }
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement
    END DO {
        // DeclNode part
        std::vector<AstNode*> *id_node = new std::vector<AstNode*>;
        std::vector<std::string> *id_string = new std::vector<std::string>;
        std::string var_name_string = $2;
        std::string var_type_string = "integer";
        if ($2 != nullptr) {
            id_node->push_back(new VariableNode(@2.first_line, @2.first_column, $2, var_type_string, nullptr));
            id_string->push_back(var_name_string);
        }
        else {
            id_node = nullptr;
        }
        DeclNode* decl_node_ptr = new DeclNode(@2.first_line, @2.first_column, id_node, id_string, var_type_string);

        // AssignmentNode part
        VariableReferenceNode* var_ref_node_ptr = new VariableReferenceNode(@2.first_line, @2.first_column, var_name_string, nullptr);
        struct literal_data ld_one = {INT, $4, 0.0, nullptr};
        ConstantValueNode* const_val_node_1 = new ConstantValueNode(@4.first_line, @4.first_column, ld_one);
        AssignmentNode* assign_node_ptr = new AssignmentNode(@3.first_line, @3.first_column, (AstNode*)var_ref_node_ptr, (AstNode*)const_val_node_1);

        // ConstantValueNode part
        struct literal_data ld_two = {INT, $6, 0.0, nullptr};
        ConstantValueNode* const_val_node_2 = new ConstantValueNode(@6.first_line, @6.first_column, ld_two);

        $$ = new ForNode(@1.first_line, @1.first_column, decl_node_ptr, assign_node_ptr, const_val_node_2, $8);
    }
;

Return:
    RETURN Expression SEMICOLON {
        $$ = new ReturnNode(@1.first_line, @1.first_column, $2);
    }
;

FunctionCall:
    FunctionInvocation SEMICOLON {
        $$ = $1;
    }
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS {
        std::string tmp_name = $1;
        $$ = new FunctionInvocationNode(@1.first_line, @1.first_column, tmp_name, $3);
    }
;

ExpressionList:
    Epsilon {
        $$ = nullptr;
    }
    |
    Expressions {
        $$ = $1;
    }
;

Expressions:
    Expression {
        $$ = new std::vector<ExpressionNode*>;
        $$->push_back($1);
    }
    |
    Expressions COMMA Expression {
        $$ = $1;
        $$->push_back($3);    
    }
;

StatementList:
    Epsilon {
        $$ = nullptr;
    }
    |
    Statements {
        $$ = $1;
    }
;

Statements:
    Statement {
        $$ = new std::vector<AstNode*>;
        $$->push_back($1);
    }
    |
    Statements Statement {
        $$ = $1;
        $$->push_back($2);    
    }
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS {
        $$ = $2;
    }
    |
    MINUS Expression %prec UNARY_MINUS {
        std::string op = "neg";
        $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, op, $2);
    }
    |
    Expression MULTIPLY Expression {
        std::string op = "*";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression DIVIDE Expression {
        std::string op = "/";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression MOD Expression {
        std::string op = "mod";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression PLUS Expression {
        std::string op = "+";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression MINUS Expression {
        std::string op = "-";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression LESS Expression {
        std::string op = "<";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression LESS_OR_EQUAL Expression {
        std::string op = "<=";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression GREATER Expression {
        std::string op = ">";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression GREATER_OR_EQUAL Expression {
        std::string op = ">=";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression EQUAL Expression {
        std::string op = "=";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression NOT_EQUAL Expression {
        std::string op = "<>";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    NOT Expression {
        std::string op = "not";
        $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, op, $2);
    }
    |
    Expression AND Expression {
        std::string op = "and";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    Expression OR Expression {
        std::string op = "or";
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, op, $1, $3);
    }
    |
    IntegerAndReal {
        // struct literal_data ld = {INT, $1 * $2, 0.0, nullptr};
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, *($1));
    }
    |
    StringAndBoolean {
        if (($1)->line == 1) {
            struct literal_data ld = {STRING_, 0, 0.0, ($1)->name};
            $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
        }
        else {
            if (($1)->column == 1){
                struct literal_data ld = {TRUE_, 0, 0.0, ($1)->name};
                $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
            }
            else {
                struct literal_data ld = {FALSE_, 0, 0.0, ($1)->name};
                $$ = new ConstantValueNode(@1.first_line, @1.first_column, ld);
            }
        }
    }
    |
    VariableReference {
        $$ = $1;
    }
    |
    FunctionInvocation {
        $$ = $1;
    }
;

    /*
       misc
            */
Epsilon:
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
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [--dump-ast]\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen() failed");
        exit(-1);
    }

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        AstDumper ast_dumper;
        root->accept(ast_dumper);
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
