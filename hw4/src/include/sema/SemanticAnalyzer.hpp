#ifndef SEMA_SEMANTIC_ANALYZER_H
#define SEMA_SEMANTIC_ANALYZER_H

#include "visitor/AstNodeVisitor.hpp"
#include "sema/symbolTable.hpp"
#include "memory"
#include <algorithm>
#include "string.h"
#include <sstream>
#include "AST/expression.hpp"

class SemanticAnalyzer final : public AstNodeVisitor {
    public:
    ~SemanticAnalyzer() = default;
    SemanticAnalyzer() = default;
    SemanticAnalyzer(char **src):src(src) {}

    SymbolManager manager;
    SymbolTable *global_table;
    SymbolTable *cur_table;
    SymbolEntry *entry_using;
    PTypeSharedPtr array_ptype_ptr;
    char **src;
    int level;
    int sematic_error = 0;
    int for_is_decl=0; // for node declaration, use in variable node analyzer
    int for_no_pop = 0; // variable node declaration, use to tell for not to pop
    int func_is_parameter=0; // for function parameter, use in variable node anaiyzer
    int func_is_compound = 0; // for function compound statement, use in compound statement
    std::vector<std::string> for_parameter; // for parameter, need to check

    int for_using = 0; // in for block
    int for_is_first = 0; // for lower bound flag
    int for_is_second = 0; // for upper bound flag
    const char* for_first; // for lower bound
    const char* for_second; // for upper bound

    int print_using = 0; // print node using
    std::string print_data; // print data from const value node
    int is_arr = 0; // mark that var is array variable and its dimension
    std::vector<std::string> array_dimention; // store array dimension and ckeck in variable reference node
    std::string array_type; // store the array type
    int arr_index_not_valid = 0; // check if array has valid index
    int read_using = 0; // read node using

    int binary_using = 0; // binary operation node using
    int binary_using_first = 0; // binary operation node using first node
    std::string binary_type_first;
    int binary_using_second = 0; // binary operation node using second node
    std::string binary_type_second;

    int unary_using = 0; // unary operation node using
    std::string unary_type;
    int unary_error = 0; // unary happen error ------ not used know
    int variable_ref_getting_var = 0; // variable reference node is getting variable
    int variable_ref_using = 0;

    int func_invocation_using = 0; // function invocation node usign
    std::vector<std::string> func_parameter;
    int func_current_par = 0; // index of func_parameter
    int func_para_num_err = 0; // parameter more

    int assignment_using = 0;


    bool redeclaration(uint32_t line, uint32_t col,std::string check_name);
    bool array_index_less_than_0(VariableNode &node);
    bool varable_ref(VariableReferenceNode &exp_node);
    bool function_ref(FunctionInvocationNode &exp_node);
    bool array_dim_over_def(uint32_t line,uint32_t col,std::string var_name);

    bool print_check_in_var_ref(u_int32_t line,u_int32_t col, std::string var_name); // check for some print rules
    bool read_check_in_var_ref(u_int32_t line,u_int32_t col, std::string var_name); // check for some print rules
    bool upper_lower_check(u_int32_t line,u_int32_t col);

    void visit(ProgramNode &p_program) override;
    void visit(DeclNode &p_decl) override;
    void visit(VariableNode &p_variable) override;
    void visit(ConstantValueNode &p_constant_value) override;
    void visit(FunctionNode &p_function) override;
    void visit(CompoundStatementNode &p_compound_statement) override;
    void visit(PrintNode &p_print) override;
    void visit(BinaryOperatorNode &p_bin_op) override;
    void visit(UnaryOperatorNode &p_un_op) override;
    void visit(FunctionInvocationNode &p_func_invocation) override;
    void visit(VariableReferenceNode &p_variable_ref) override;
    void visit(AssignmentNode &p_assignment) override;
    void visit(ReadNode &p_read) override;
    void visit(IfNode &p_if) override;
    void visit(WhileNode &p_while) override;
    void visit(ForNode &p_for) override;
    void visit(ReturnNode &p_return) override;
};

#endif
