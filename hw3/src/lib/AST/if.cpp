#include "AST/if.hpp"

// TODO
IfNode::IfNode(const uint32_t line, const uint32_t col,
               AstNode *const exp,
               CompoundStatementNode *const statement_if,
               CompoundStatementNode *const statement_else)
    : AstNode{line, col}, exp{exp}, statement_if{statement_if}, statement_else{statement_else} {}

// TODO: You may use code snippets in AstDumper.cpp
void IfNode::print() {}

void IfNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (exp != nullptr) exp->accept(p_visitor);
    if (statement_if != nullptr) statement_if->accept(p_visitor);
    if (statement_else != nullptr) statement_else->accept(p_visitor);
}
