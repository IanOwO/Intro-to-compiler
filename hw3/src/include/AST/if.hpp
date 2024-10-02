#ifndef __AST_IF_NODE_H
#define __AST_IF_NODE_H

#include "AST/ast.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>
#include <vector>

class IfNode : public AstNode {
  public:
    IfNode(const uint32_t line, const uint32_t col,
           AstNode *const exp,
           CompoundStatementNode *const statement_if,
           CompoundStatementNode *const statement_else
           /* TODO: expression, compound statement, compound statement */);
    ~IfNode() = default;

    AstNode *exp;
    CompoundStatementNode *statement_if;
    CompoundStatementNode *statement_else;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: expression, compound statement, compound statement
};

#endif
