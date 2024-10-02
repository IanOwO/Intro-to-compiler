#include "AST/VariableReference.hpp"

// TODO
VariableReferenceNode::VariableReferenceNode(const uint32_t line,
                                             const uint32_t col,
                                             std::string var_name,
                                             std::vector<ExpressionNode*> *const exp_list)
    : ExpressionNode{line, col}, var_name{var_name}, exp_list{exp_list} {}

// TODO
// VariableReferenceNode::VariableReferenceNode(const uint32_t line,
//                                              const uint32_t col)
//     : ExpressionNode{line, col} {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableReferenceNode::print() {}

void VariableReferenceNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (exp_list != nullptr){
        for (auto &exp : *exp_list) {
            exp->accept(p_visitor);
        }
    }
}
