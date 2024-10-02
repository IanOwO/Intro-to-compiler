#ifndef __AST_WHILE_NODE_H
#define __AST_WHILE_NODE_H

#include "AST/ast.hpp"
#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>
#include <vector>
class WhileNode : public AstNode {
  public:
    WhileNode(const uint32_t line, const uint32_t col,
              AstNode *const exp,
              CompoundStatementNode *const statement_while
              /* TODO: expression, compound statement */);
    ~WhileNode() = default;

    AstNode *exp;
    CompoundStatementNode *statement_while;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: expression, compound statement
};

#endif
