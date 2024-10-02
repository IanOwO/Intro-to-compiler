#include "AST/return.hpp"

// TODO
ReturnNode::ReturnNode(const uint32_t line, const uint32_t col,
                       AstNode *const exp)
    : AstNode{line, col}, exp{exp} {}

// TODO: You may use code snippets in AstDumper.cpp
void ReturnNode::print() {}

void ReturnNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (exp != nullptr) exp->accept(p_visitor);
}
