#include "AST/while.hpp"

// TODO
WhileNode::WhileNode(const uint32_t line, const uint32_t col,
                     AstNode *const exp,
                     CompoundStatementNode *const statement_while)
    : AstNode{line, col}, exp{exp}, statement_while{statement_while} {}

// TODO: You may use code snippets in AstDumper.cpp
void WhileNode::print() {}

void WhileNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (exp != nullptr) exp->accept(p_visitor);
    if (statement_while != nullptr) statement_while->accept(p_visitor);
}
