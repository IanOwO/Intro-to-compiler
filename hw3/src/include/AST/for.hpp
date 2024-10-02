#ifndef __AST_FOR_NODE_H
#define __AST_FOR_NODE_H

#include "AST/ast.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>

#include "AST/decl.hpp"
#include "AST/assignment.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/CompoundStatement.hpp"

class ForNode : public AstNode {
  public:
    ForNode(const uint32_t line, const uint32_t col,
            DeclNode *const decl,
            AssignmentNode *const assign,
            ConstantValueNode *const const_val,
            CompoundStatementNode *const statement
            /* TODO: declaration, assignment, expression,
             *       compound statement */);
    ~ForNode() = default;

    DeclNode *decl;
    AssignmentNode *assign;
    ConstantValueNode *const_val;
    CompoundStatementNode *statement;
    void print() override;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: declaration, assignment, expression, compound statement
};

#endif
