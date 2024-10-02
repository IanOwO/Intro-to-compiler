#ifndef AST_AST_NODE_H
#define AST_AST_NODE_H

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>


class AstNodeVisitor;

struct Location {
    uint32_t line;
    uint32_t col;

    ~Location() = default;
    Location(const uint32_t line, const uint32_t col) : line(line), col(col) {}
};

// ================ new add start ===================
enum LITERAL{
    INT,FLOAT,STRING_,TRUE_,FALSE_
};

struct literal_data{
    enum LITERAL en;
    int int_data;
    float float_data;
    const char* string_data;
};
// ================ new add end ===================


class AstNode {
  protected:
    Location location;

  public:
    virtual ~AstNode() = 0;
    AstNode(const uint32_t line, const uint32_t col);

    const Location &getLocation() const;

    virtual void print() = 0;
    
    virtual void accept(AstNodeVisitor &p_visitor) = 0;
    virtual void visitChildNodes(AstNodeVisitor &p_visitor){};
};

#endif
