#ifndef AST_EXPRESSION_NODE_H
#define AST_EXPRESSION_NODE_H

#include "AST/ast.hpp"
#include "AST/PType.hpp"

class ExpressionNode : public AstNode {
  public:
    ~ExpressionNode() = default;
    ExpressionNode(const uint32_t line, const uint32_t col)
        : AstNode{line, col} {}

  PTypeSharedPtr node_type = nullptr;
  void settype(std::string type){
    if(type == "integer") node_type = std::make_shared<PType>(PType::PrimitiveTypeEnum::kIntegerType);
    else if(type == "real") node_type = std::make_shared<PType>(PType::PrimitiveTypeEnum::kRealType);
    else if(type == "boolean") node_type = std::make_shared<PType>(PType::PrimitiveTypeEnum::kBoolType);
    else if(type == "string") node_type = std::make_shared<PType>(PType::PrimitiveTypeEnum::kStringType);
    else if(type == "void") node_type = std::make_shared<PType>(PType::PrimitiveTypeEnum::kVoidType);
    else node_type = nullptr;


    //fprintf(stderr,"setting type:%s\n",node_type->getPTypeCString());
  }
  protected:
    // for carrying type of result of an expression
    // TODO: for next assignment
};

#endif
