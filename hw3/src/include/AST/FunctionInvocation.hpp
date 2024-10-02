#ifndef __AST_FUNCTION_INVOCATION_NODE_H
#define __AST_FUNCTION_INVOCATION_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>
#include <vector>

class FunctionInvocationNode : public ExpressionNode {
  public:
    FunctionInvocationNode(const uint32_t line, const uint32_t col,
                           std::string func_name,
                           std::vector<ExpressionNode*> *const exp_list
                           /* TODO: function name, expressions */);
    ~FunctionInvocationNode() = default;

    const char *getNameCString() const;
    std::string func_name;
    std::vector<ExpressionNode*>* exp_list;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: function name, expressions
};

#endif
