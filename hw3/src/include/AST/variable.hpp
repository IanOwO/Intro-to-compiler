#ifndef __AST_VARIABLE_NODE_H
#define __AST_VARIABLE_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"

#include "AST/ConstantValue.hpp"

class VariableNode : public AstNode {
  public:
    VariableNode(const uint32_t line, const uint32_t col,
                 const char *const var_name,
                 std::string type_name,
                 AstNode *const const_value
                 /* TODO: variable name, type, constant value */);
    ~VariableNode() = default;

    void print() override;

    const char* const var_name;
    std::string type_name;
    AstNode* const_value;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

    

  private:
    // TODO: variable name, type, constant value
};

#endif
