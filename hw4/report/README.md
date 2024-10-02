# hw4 report

|||
|-:|:-|
|Name|Ian Lsi|
|ID|110550168|

## How much time did you spend on this project

> e.g. 2 hours.

5 full days

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way.
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here.

### Overview

In this report, I will explain how I done this project in two part, modification on parser & scanner in one part and the the modification on the AST. And also, since I didn't past all test case, so that some of the part may not be described.

### Modification in parser & scanner

I add a char pointer with two dimension to store the current line. To add the current line, I do it when I met newline in scanner. The variable "whichline" store the maximum of the char array size. And I store the current line by strdup() at the line\_num same as the given one.

In parser, I need to add a extern variable a the top, and then I pass the source code during I construct the SemanticAnalyzer.

### Modification in AST

In this part, I will explain it node by node. Most of them are modified in SemanticAnaylzer.cpp. If not, I will specify it.

Basically, I use flag to seperate different node, so that I can do different operation.

#### Symbol manager, Symbol table, Symbol entry, 

1. I create a new hpp and cpp file to store them

2. Class SymbolManager store the symbol table in stack

3. Class SymbolTable store the vector entry, and the function name (used to store the function name of this table, can use it to find the function's information in other table)

4. To add the entry, I have two add type, one pass the string of type, one pass the ptype of type. First is for function parameter, not using ptype but use other variable to store the information. The other is for constructing other kind of variable and usr ptype the get information.

#### Expression node, modify in expression.hpp

1. I add a PTypeSharedPtr in Expression, and when visiting child node, I will add the type of expression so that when we  do semantic analyze later, we can get the type and do comparison. 

2. The way we set the expression node's ptype is by calling the self-defined function by using the given type in string.

#### Program node

1. add table & symbol

2. visit child node

3. pop the table

#### Variable node

1. check redeclaration, a self-defined function that go through the current table and check if exist. Here, I check if is for declare, if redeclaration, I set a flag and used in for node to prevent other check.

2. check if the variable is array type and has 0 dimension or not

3. by seperate different type of declaration (for, function, or normal variable) and do different addSymbol

4. visit child node

#### Constant value node

1. if is for constant value, I seperate the first and the second, then do compare in for node

2. if is using the node, then don't set the expression node type, else set the ptype

3. if comes from variable node, the it means that we need to set its type to constant, and it will be the last entry in the current table

#### Function node

1. check redeclaration, a self-defined function that go through the current table and check if exist, if not, then add symbol to current table

2. create new symbol table and add it

3. set flag and visit parameter

4. if m\_body is not null, set flag and visit

5. pop the table

#### Compound statement node

1. add new table if is not function compound statement and pop at last

2. visit child node

#### Expression node's child node (PrintNode, BinaryOperatorNode, UnaryOperatorNode, FunctionInvocationNode, VariableReferenceNode, AssignmentNode, ReadNode, IfNode, WhileNode, ReturnNode)

1. visit child node

2. if its child node is nullptr, then return, which means do nothing

3. based on the child nodes type (store in node\_type, a PTypeSharedPtr) of each different node and the rule, do the Semantic Analyze, I will tell the special part and what I used in each node later

#### PrintNode

1. check used type is valid and is not array

#### BinaryOperatorNode and UnaryOperatorNode

1. when visiting child node, I set a flag to prevent modify to the type

2. apply different operation check, use the node\_type from operand

3. set the current node's type by the different rule, if error, then don't set type

#### FunctionInvocationNode

1. when visiting child node, I set a flag to prevent modify to the type

2. Go through global table and current table and check if there is definition. I write a function and based on its return value to know if there is definition.

3. inside the function, there are lots of flag to seperate different condition

4. apply different operation check, go through the table and get the function's entry, use it to get the defined parameter size and type, compare it with the current node's child node's ptype

5. set the current node's type by the defined type, if error, then don't set type

#### VariableReferenceNode

1. when visiting child node, I set a flag to prevent modify to the type

2. Go through global table and current table and check if there is definition. I write a function (similar to the function in FunctionInvocationNode but different) and based on its return value to know if there is definition.

3. inside the function, there are lots of flag to seperate different condition

4. apply different operation check, go through the table and get the function's entry, use it to get the defined array size and check if is an over array

5. if is not an over array, go through the vector of child node and check the index is integer

6. set the current node's type, explain it by example
 - defined : arr[2][2][3]
 - cur node : arr[2][2]
 - the type will be arr[3]

#### AssignmentNode

1. when visiting child node, I set a flag to prevent modify to the type

2. apply different operation check, use the node\_type from expression

3. Go through global table and current table and get the m_lvalue type

#### ReadNode

1. when visiting child node, I set a flag to prevent modify to the type

2. apply different operation check, use the node\_type from the child node

#### IfNode, WhileNode

1. apply different operation check, use the node\_type from the child node

#### ReturnNode

1. get the current table and check the function name, if nothing, which means that it should not return

2. search the global table and get the function return type

3. apply different operation check, use the node\_type from the child node, and the function defined return type

#### For node

1. add table

2. set two flag, one for using for, and one for definition of loop variable, then visit loop\_var\_decl node
 - if is loop variable definition, I will check if redefined and set a flag for\_no\_pop to tell me not to go through init and end condition

3. if no redeclaration, go through init and end condition node, each set a flag and store the value in specific variable

4. check if init is smaller or equal then then end condition, written in function and use return to know if error

5. visit m\_body

6. pop the table


## What is the hardest you think in this project

> Not required, but bonus point may be given.

I think that the most difficult part of this work is to know that you need to put a Ptype in expression node, so that you can get the Ptype after you visit. I didn't see this part in the guideline, so it confused me a lot.

## Feedback to T.A.s

> Not required, but bonus point may be given.

I think that the deadline of this homework is not friendly, since the final exam is so close. Maybe start the homework 2 earlier so that we will not crash everything together.
