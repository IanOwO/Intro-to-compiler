#include "AST/ConstantValue.hpp"

// TODO
ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col,
                                     const struct literal_data ld)
    : ExpressionNode{line, col} {
        type_data = ld.en;
        int_data = ld.int_data;
        float_data = ld.float_data;
        string_data = ld.string_data;
    }

// TODO: You may use code snippets in AstDumper.cpp
void ConstantValueNode::print() {}
