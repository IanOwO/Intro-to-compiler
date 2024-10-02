#include "AST/function.hpp"

// TODO
FunctionNode::FunctionNode(const uint32_t line, const uint32_t col,
                           const char *const func_name,
                           const std::string type_name,
                           CompoundStatementNode *const compound_body,
                           std::vector<AstNode*>* var_list)
    : AstNode{line, col}, func_name{func_name}, type_name{type_name}, compound_body{compound_body}, var_list{var_list} {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionNode::print() {}

void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (var_list != nullptr){
        for (auto &decl : *var_list) {
            decl->accept(p_visitor);
        }
    }
    if (compound_body != nullptr){
        compound_body->accept(p_visitor);
    }
}
