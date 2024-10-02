#ifndef __AST_UNARY_OPERATOR_NODE_H
#define __AST_UNARY_OPERATOR_NODE_H

#include "AST/expression.hpp"

#include <memory>
#include <visitor/AstNodeVisitor.hpp>

class UnaryOperatorNode : public ExpressionNode {
  public:
    UnaryOperatorNode(const uint32_t line, const uint32_t col,
                      std::string op,
                      ExpressionNode* first_node
                      /* TODO: operator, expression */);
    ~UnaryOperatorNode() = default;

    std::string op;
    ExpressionNode* first_node;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: operator, expression
};

#endif
