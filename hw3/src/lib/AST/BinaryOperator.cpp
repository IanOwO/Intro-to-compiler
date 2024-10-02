#include "AST/BinaryOperator.hpp"

// TODO
BinaryOperatorNode::BinaryOperatorNode(const uint32_t line, const uint32_t col,
                                       std::string op,
                                       ExpressionNode* first_node,
                                       ExpressionNode* second_node)
    : ExpressionNode{line, col}, op{op}, first_node{first_node}, second_node{second_node} {}

// TODO: You may use code snippets in AstDumper.cpp
void BinaryOperatorNode::print() {}

void BinaryOperatorNode::visitChildNodes(AstNodeVisitor &p_visitor) {
    // TODO
    if (first_node != nullptr) {
        first_node->accept(p_visitor);
    }
    if (second_node != nullptr) {
        second_node->accept(p_visitor);
    }
}
