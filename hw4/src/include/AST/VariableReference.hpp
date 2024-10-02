#ifndef AST_VARIABLE_REFERENCE_NODE_H
#define AST_VARIABLE_REFERENCE_NODE_H

#include "AST/expression.hpp"
#include "visitor/AstNodeVisitor.hpp"

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

class VariableReferenceNode final : public ExpressionNode {
  public:
    using ExprNodes = std::vector<std::unique_ptr<ExpressionNode>>;

  public:
    std::string m_name;
    ExprNodes m_indices;

  public:
    ~VariableReferenceNode() = default;

    // normal reference
    VariableReferenceNode(const uint32_t line, const uint32_t col,
                          const char *const p_name)
        : ExpressionNode{line, col}, m_name(p_name){}

    // array reference
    VariableReferenceNode(const uint32_t line, const uint32_t col,
                          const char *const p_name, ExprNodes &p_indices)
        : ExpressionNode{line, col}, m_name(p_name),
          m_indices(std::move(p_indices)){}

    const char *getNameCString() const { return m_name.c_str(); }

    void accept(AstNodeVisitor &p_visitor) override { p_visitor.visit(*this); }
    void visitChildNodes(AstNodeVisitor &p_visitor) override;

    void dim_modify(std::string str){
      std::vector<uint64_t> new_dimension;
      //fprintf(stderr,"type to set:%s\n",str.c_str());
      for(int i = 0;i < str.length();i++){
        if(str[i] == '['){
          int j = i + 1;
          while(str[j] != ']') j++;
          new_dimension.emplace_back(std::stoi(str.substr(i + 1,j - i - 1)));
          i = j;
        }
      }
      // for(int i = 0;i < new_dimension.size();i++){
      //   fprintf(stderr,"output dimention:%lu\n",new_dimension[i]);
      // }
      for(int i = 0;i < m_indices.size();i++) new_dimension.erase(new_dimension.begin());
      node_type->m_dimensions = std::move(new_dimension);
      // for(int i = 0;i < node_type->m_dimensions.size();i++){
      //   fprintf(stderr,"output dimention:%lu\n",node_type->m_dimensions[i]);
      // }
    }
};

#endif
