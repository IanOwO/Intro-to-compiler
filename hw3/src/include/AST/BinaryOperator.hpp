#ifndef __AST_BINARY_OPERATOR_NODE_H
#define __AST_BINARY_OPERATOR_NODE_H

#include "AST/expression.hpp"

#include <memory>
#include <visitor/AstNodeVisitor.hpp>

class BinaryOperatorNode : public ExpressionNode {
  public:
    BinaryOperatorNode(const uint32_t line, const uint32_t col,
                       std::string op,
                       ExpressionNode* first_node,
                       ExpressionNode* second_node
                       /* TODO: operator, expressions */);
    ~BinaryOperatorNode() = default;

    std::string op;
    ExpressionNode* first_node;
    ExpressionNode* second_node;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: operator, expressions
};

#endif
