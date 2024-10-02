#ifndef __AST_FUNCTION_NODE_H
#define __AST_FUNCTION_NODE_H

#include "AST/ast.hpp"

#include "visitor/AstNodeVisitor.hpp"
#include <vector>
#include "AST/CompoundStatement.hpp"

class FunctionNode : public AstNode {
  public:
    FunctionNode(const uint32_t line, const uint32_t col,
                 const char *const func_name,
                 const std::string type_name,
                 CompoundStatementNode *const compound_body,
                 std::vector<AstNode*>* var_list
                 /* TODO: name, declarations, return type,
                  *       compound statement (optional) */);
    ~FunctionNode() = default;

    void print() override;

    const char *const func_name;
    const std::string type_name;
    CompoundStatementNode* compound_body;
    std::vector<AstNode*>* var_list;

    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: name, declarations, return type, compound statement
};

#endif
