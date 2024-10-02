#include "AST/read.hpp"

// TODO
ReadNode::ReadNode(const uint32_t line, const uint32_t col,
                   AstNode *const var_ref)
    : AstNode{line, col}, var_ref{var_ref} {}

// TODO: You may use code snippets in AstDumper.cpp
void ReadNode::print() {}

void ReadNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (var_ref != nullptr) var_ref->accept(p_visitor);
}
