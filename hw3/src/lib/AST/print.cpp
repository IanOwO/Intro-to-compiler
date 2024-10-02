#include "AST/print.hpp"

// TODO
PrintNode::PrintNode(const uint32_t line, const uint32_t col,
                     AstNode *const exp_node)
    : AstNode{line, col}, exp_node{exp_node} {}

// TODO: You may use code snippets in AstDumper.cpp
void PrintNode::print() {}

void PrintNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (exp_node != nullptr) {
        exp_node->accept(p_visitor);
    }
}
