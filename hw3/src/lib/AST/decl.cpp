#include "AST/decl.hpp"
#include <vector>

// TODO
DeclNode::DeclNode(const uint32_t line, const uint32_t col,
                   std::vector<AstNode*> *const var_body,
                   std::vector<std::string> *const id_body,
                   std::string const type_body)
                //    AstNode *const var_body)
    : AstNode{line, col}, var_body{var_body}, id_body{id_body}, type_body{type_body} {}

// TODO
//DeclNode::DeclNode(const uint32_t line, const uint32_t col)
//    : AstNode{line, col} {}

// TODO: You may use code snippets in AstDumper.cpp
void DeclNode::print() {}

void DeclNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (var_body != nullptr){
        for (auto &var_ : *var_body) {
            // printf("decl accept\n");
            // printf("var body size:%lu\n",var_body->size());
            var_->accept(p_visitor);
        }
    }
    // if (!var_body.empty()){
    //     for (long unsigned int i = 0;i < var_body.size();i++) {
    //         // printf("decl accept\n");
    //         // printf("var body size:%lu\n",var_body->size());
    //         var_body[i]->accept(p_visitor);
    //     }
    // }
    // var_body->accept(p_visitor);
}
