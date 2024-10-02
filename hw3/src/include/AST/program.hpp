#ifndef AST_PROGRAM_NODE_H
#define AST_PROGRAM_NODE_H

#include "AST/ast.hpp"

#include <string>

#include "AST/CompoundStatement.hpp"
#include "visitor/AstNodeVisitor.hpp"
#include <memory>

#include <vector>

#include "AST/decl.hpp"
// #include "AST/variable.hpp"

class ProgramNode final : public AstNode {
  private:
    std::string name;
    // TODO: return type, declarations, functions, compound statement

  public:
    ~ProgramNode() = default;
    ProgramNode(const uint32_t line, const uint32_t col,
                const char *const p_name,
                std::vector<AstNode*> *const decl_body,
                std::vector<AstNode*> *const func_body,
                CompoundStatementNode *const p_body
                /* TODO: return type, declarations, functions,
                 *       compound statement */);

    // visitor pattern version: const char *getNameCString() const;
    void print() override;

    std::vector<AstNode*> *decl_body;
    std::vector<AstNode*> *func_body;
    CompoundStatementNode *m_body;
    const char *getNameCString() const{ return name.c_str(); }
    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;
};

#endif
