#include "AST/UnaryOperator.hpp"

// TODO
UnaryOperatorNode::UnaryOperatorNode(const uint32_t line, const uint32_t col,
                                     std::string op,
                                     ExpressionNode* first_node)
    : ExpressionNode{line, col}, op{op}, first_node{first_node} {}

// TODO: You may use code snippets in AstDumper.cpp
void UnaryOperatorNode::print() {}

void UnaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (first_node != nullptr) {
        first_node->accept(p_visitor);
    }
}
