#ifndef __AST_CONSTANT_VALUE_NODE_H
#define __AST_CONSTANT_VALUE_NODE_H

#include "AST/expression.hpp"

#include "visitor/AstNodeVisitor.hpp"

class ConstantValueNode : public ExpressionNode {
  public:
    ConstantValueNode(const uint32_t line, const uint32_t col,
                      const struct literal_data ld
                      /* TODO: constant value */);
    ~ConstantValueNode() = default;

    void print() override;

    enum LITERAL type_data;
    int int_data;
    float float_data;
    const char* string_data;

    const char* getdata(enum LITERAL type_data) {
      switch (type_data)
      {
      case INT:
        return (char*)std::to_string(int_data).c_str();
        break;
      case FLOAT:
        // char* ch;
        // sprintf(ch,"%f",float_data);
        // return ch;
        return (char*)std::to_string(float_data).c_str();
        break;
      case STRING_:
        return string_data;
        break;
      case TRUE_:
        return string_data;
        break;
      case FALSE_:
        return string_data;
        break;
      default:
        break;
      }
      return nullptr;
    }

    char* getdatatype(enum LITERAL type_data) {
      switch (type_data)
      {
      case INT:
        return (char*)"integer";
        break;
      case FLOAT:
        return (char*)"real";
        break;
      case STRING_:
        return (char*)"string";
        break;
      case TRUE_:
        return (char*)"boolean";
        break;
      case FALSE_:
        return (char*)"boolean";
        break;
      default:
        break;
      }
      return nullptr;
    }

    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }

  private:
    // TODO: constant value
};

#endif
