#include "AST/assignment.hpp"

// TODO
AssignmentNode::AssignmentNode(const uint32_t line, const uint32_t col,
                               AstNode *const var_ref,
                               AstNode *const exp)
    : AstNode{line, col}, var_ref{var_ref}, exp{exp} {}

// TODO: You may use code snippets in AstDumper.cpp
void AssignmentNode::print() {}

void AssignmentNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (var_ref != nullptr) var_ref->accept(p_visitor);
    if (exp != nullptr) exp->accept(p_visitor);
}
