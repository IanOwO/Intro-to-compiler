#include "AST/CompoundStatement.hpp"

// TODO
CompoundStatementNode::CompoundStatementNode(const uint32_t line,
                                             const uint32_t col,
                                             std::vector<AstNode*> *const decl_list,
                                             std::vector<AstNode*> *const statement_list)
    : AstNode{line, col}, decl_list{decl_list}, statement_list{statement_list} {}

// TODO: You may use code snippets in AstDumper.cpp
void CompoundStatementNode::print() {}

void CompoundStatementNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (decl_list != nullptr) {
        for (auto &decl : *decl_list) {
            decl->accept(p_visitor);
        }
    }
    if (statement_list != nullptr) {
        for (auto &statement : *statement_list) {
            statement->accept(p_visitor);
        }
    }
}
