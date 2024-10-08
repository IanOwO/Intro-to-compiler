#ifndef __AST_RETURN_NODE_H
#define __AST_RETURN_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>

class ReturnNode : public AstNode {
  public:
    ReturnNode(const uint32_t line, const uint32_t col,
               AstNode *const exp
               /* TODO: expression */);
    ~ReturnNode() = default;

    AstNode *exp;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: expression
};

#endif
