#include "AST/for.hpp"

// TODO
ForNode::ForNode(const uint32_t line, const uint32_t col,
                 DeclNode *const decl,
                 AssignmentNode *const assign,
                 ConstantValueNode *const const_val,
                 CompoundStatementNode *const statement)
    : AstNode{line, col}, decl{decl}, assign{assign}, const_val{const_val}, statement{statement} {}

// TODO: You may use code snippets in AstDumper.cpp
void ForNode::print() {}

void ForNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (decl != nullptr) decl->accept(p_visitor);
    if (assign != nullptr) assign->accept(p_visitor);
    if (const_val != nullptr) const_val->accept(p_visitor);
    if (statement != nullptr) statement->accept(p_visitor);
}
