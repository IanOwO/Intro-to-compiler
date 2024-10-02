#include "AST/program.hpp"

// TODO
ProgramNode::ProgramNode(const uint32_t line, const uint32_t col,
                         const char *const p_name,
                         std::vector<AstNode*> *const decl_body,
                         std::vector<AstNode*> *const func_body,
                         CompoundStatementNode *const p_body)
    : AstNode{line, col}, name{p_name}, decl_body{decl_body}, func_body{func_body}, m_body{p_body} {}

// visitor pattern version: const char *ProgramNode::getNameCString() const { return name.c_str(); }

void ProgramNode::print() {
    // TODO
    // outputIndentationSpace();

    std::printf("program <line: %u, col: %u> %s %s\n",
                location.line, location.col,
                name.c_str(), "void");

    // TODO
    // incrementIndentation();
    // visitChildNodes();
    // decrementIndentation();
}


void ProgramNode::visitChildNodes(AstNodeVisitor &p_visitor) { // visitor pattern version
    /* TODO
     *
     * for (auto &decl : var_decls) {
     *     decl->accept(p_visitor);
     * }
     *
     * // functions
     *
     * body->accept(p_visitor);
     */
    
    if (decl_body != nullptr){
        for (auto &decl : *decl_body) {
            decl->accept(p_visitor);
        }
    }
    if (func_body != nullptr){
        for (auto &func : *func_body) {
            func->accept(p_visitor);
        }
    }
    m_body->accept(p_visitor);
}
