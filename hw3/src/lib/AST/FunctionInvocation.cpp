#include "AST/FunctionInvocation.hpp"

// TODO
FunctionInvocationNode::FunctionInvocationNode(const uint32_t line,
                                               const uint32_t col,
                                               std::string func_name,
                                               std::vector<ExpressionNode*> *const exp_list)
    : ExpressionNode{line, col}, func_name{func_name}, exp_list{exp_list} {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionInvocationNode::print() {}

void FunctionInvocationNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (exp_list != nullptr){
        for (auto &exp : *exp_list) {
            exp->accept(p_visitor);
        }
    }
}
