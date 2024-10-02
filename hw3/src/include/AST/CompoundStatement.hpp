#ifndef __AST_COMPOUND_STATEMENT_NODE_H
#define __AST_COMPOUND_STATEMENT_NODE_H

#include "AST/ast.hpp"

#include "visitor/AstNodeVisitor.hpp"
#include <memory>
#include <vector>
#include "AST/decl.hpp"
class CompoundStatementNode : public AstNode {
  public:
    CompoundStatementNode(const uint32_t line, const uint32_t col,
                          std::vector<AstNode*> *const decl_list,
                          std::vector<AstNode*> *const statement_list
                          /* TODO: declarations, statements */);
    ~CompoundStatementNode() = default;

    void print() override;

    std::vector<AstNode*> *decl_list;
    std::vector<AstNode*> *statement_list;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: declarations, statements
};

#endif
