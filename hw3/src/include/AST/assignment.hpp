#ifndef __AST_ASSIGNMENT_NODE_H
#define __AST_ASSIGNMENT_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>
#include <vector>

class AssignmentNode : public AstNode {
  public:
    AssignmentNode(const uint32_t line, const uint32_t col,
                   AstNode *const var_ref,
                   AstNode *const exp
                   /* TODO: variable reference, expression */);
    ~AssignmentNode() = default;

    AstNode *var_ref;
    AstNode *exp;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: variable reference, expression
};

#endif
