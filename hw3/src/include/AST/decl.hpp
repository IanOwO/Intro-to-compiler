#ifndef __AST_DECL_NODE_H
#define __AST_DECL_NODE_H

#include "AST/ast.hpp"

#include "visitor/AstNodeVisitor.hpp"
#include "AST/variable.hpp"
#include <vector>


class DeclNode : public AstNode {
  public:
    // variable declaration
    DeclNode(const uint32_t line, const uint32_t col,
             std::vector<AstNode*> *const var_body,
             std::vector<std::string> *const id_body,
             std::string const type_body
            //  AstNode *const var_body
             /* TODO: identifiers, type */);

    // constant variable declaration
    //DeclNode(const uint32_t, const uint32_t col
    //         /* TODO: identifiers, constant */);

    ~DeclNode() = default;

    void print() override;

    std::vector<AstNode*> *var_body;
    std::vector<std::string> * id_body;
    std::string type_body;
    // AstNode *var_body;
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

  private:
    // TODO: variables
};

#endif
