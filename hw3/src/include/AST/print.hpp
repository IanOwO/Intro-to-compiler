#ifndef __AST_PRINT_NODE_H
#define __AST_PRINT_NODE_H

#include "AST/ast.hpp"

#include "visitor/AstNodeVisitor.hpp"
#include <memory>
#include <vector>

class PrintNode : public AstNode {
  public:
    PrintNode(const uint32_t line, const uint32_t col,
              AstNode *const exp_node
              /* TODO: expression */);
    ~PrintNode() = default;

    AstNode* exp_node;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: expression
};

#endif
