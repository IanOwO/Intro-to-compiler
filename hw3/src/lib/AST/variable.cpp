#include "AST/variable.hpp"


// TODO
VariableNode::VariableNode(const uint32_t line, const uint32_t col,
                           const char *const var_name,
                           std::string type_name,
                           AstNode *const const_value)
    : AstNode{line, col}, var_name{var_name}, type_name{type_name}, const_value{const_value} {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableNode::print() {}

void VariableNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (const_value != nullptr){
        const_value->accept(p_visitor);
    }
}
