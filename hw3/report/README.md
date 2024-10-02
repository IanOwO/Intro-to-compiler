# hw3 report

|||
|-:|:-|
|Name|Ian Lai|
|ID|110550168|

## How much time did you spend on this project

> e.g. 2 hours.

Around 3-4 days.

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way.
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here.

### Overview

In this report, I will explain how I done this project in two part, modification in scanner and parser. In the part of parser, I will explain it by nodes and the parameter in creating the specific node, and also the relation modification in parser (Return type : modification at %type and %union, Describe : modification at the rule definition part, related cpp and hpp). 

### Modification in scanner

I only modify the return type and value of the token INT\_LITERAL, REAL\_LITERAL and STRING\_LITERAL. For these, they need to return there value in yytext, so I use yylval.(return type defined in %union) with the help of several functions in std. 

### Modification in parser

**How visitor pattern works**

1. For all nodes, except ExpressionNode, I add accept and visitChildNodes function in their .cpp and .hpp. 

2. For the definition of visitChildNodes function, if the parameter of the function has pointers of AstNode or its inherit types and also the pointer is not nullptr, I call the pointer's accept with p_visitor to print the information. If the pointer is a vector of AstNode or its inherit types, then I will go through all the vector by for and auto.

3. Since I will check if the pointer is nullptr or not, I can pass nullptr if I don't need the Node for some special cases.

#### Program node

**1. Modify part : Program**

 - Return type : assign to variable root

 - Describe : I follow the instruction in hint.md, and add two more pointer parameters with a vector of AstNode* type to let ProgramNode have these child. I use vector here so that I can contain a list of nodes. 

#### Declaration node, Variable node

**1. Modify part : DeclarationList**

 - Return type : a pointer of a vector of AstNode pointers

 - Describe : return nullptr if epsilon, and then it will disable it

**2. Modify part : Declarations**

 - Return type : a pointer of a vector of AstNode pointers

 - Describe : new a pointer of a vector of AstNode pointers if is "Declaration" only, and if is "Declarations Declaration", set return to (the previous vector)$1 and push back a new coming "Declaration"

**3. Modify part : Declaration**

 - Return type : a pointer of DeclNode pointers

 - Describe : I create VarableNode here, with the line, col and name from "IdList" and the type from "Type" or "LiteralConstant", then push back to a vector of AstNode. At the same time, store the id name in a vector of string. Then new a DeclNode pointer with parameters(line, col, VarableNode list, id name list, type) and return.

**4. Modify part : IdList**

 - Return type : a pointer of a vector of struct id\_data(id name, line, col)

 - Describe : New a pointer of a vector if is "ID" only, if is "IdList COMMA ID", set return to $1(the previous vector) and push back a struct created by the information of the new coming "ID".

#### Constant value node

**1. Modify part : LiteralConstant**

 - Return type : a pointer of ConstantValueNode

 - Describe : 
	 1. Use a self-defined struct literal_data, with information of the data and data type, data type is enum type and data contain int, float and string.
	 2. The value of the struct differs. For "INT\_LITERAL" and "REAL\_LITERAL" case, I will multiple it by $1("NegOrNot"). For "StringAndBoolean", I will use the information in it and differ string, true or false and give the struct data.
	 3. Then new a pointer of a ConstantValueNode with parameters(ine, col, literal_dat)a, return it.
	 4. In constructor of ConstantValue, I will assign the data to specific type of variable. When we need to get the data, I call get data function and pass the enum data type in, then the function will return the correct value.

**2. Modify part : NegOrNot**

 - Return type : integer

 - Describe : if is neg, return -1, else return 1

**3. Modify part : StringAndBoolean**

 - Return type : a pointer of struct id_data(data, string or not, true or false)

 - Describe : None

#### Function node

**1. Modify part : FunctionList**

 - Return type : a pointer of a vector of AstNode pointers

 - Describe : return nullptr if epsilon, and then it will disable it

**2. Modify part : Functions**

 - Return type : a pointer of a vector of AstNode pointers

 - Describe : new a pointer of a vector of AstNode pointers if is "Function" only, and if is "Functions Function", set return to (the previous vector)$1 and push back a new coming "Function"

**3. Modify part : Function**

 - Return type : a pointer of FunctionNode

 - Describe : None

**4. Modify part : FunctionDeclaration**

 - Return type : a pointer of FunctionNode

 - Describe : 
	 1. I connect $6("ReturnType") with the arg's type get from $3("FormalArgList") as the function\_prototype by string addition.
	 2. I make $3("FormalArgList") from a vector of DeclNode to a a vector of AstNode.
	 3. new a FunctionNode with parameters(line, col, $1("FunctionName", char* type), function\_prototype, nullptr, a vector of DeclNode in AstNode type), return it.
	 
**5. Modify part : FunctionDefinition**

 - Return type : a pointer of FunctionNode

 - Describe : Same as "FunctionDeclaration" except the fifth parameter is not nullptr but is compound statement($5)

**6. Modify part : FormalArgList**

 - Return type : a pointer of a vector of DeclNode

 - Describe : None

**7. Modify part : FormalArgs**

 - Return type : a pointer of a vector of DeclNode

 - Describe : similar action as "Functions"

**8. Modify part : FormalArg**

 - Return type : a pointer of DeclNode

 - Describe : create a VariableNode for all id in IdList, and new a DeclNode for this type

**9. Modify part : ReturnType**

 - Return type : char*

 - Describe : "void" for epsilon, and the others are from "ScalarType"

**10. Modify part : ScalarType**

 - Return type : char*

 - Describe : return specific type

#### Compound statement node

**1. Modify part : CompoundStatement**

 - Return type : a pointer of CompoundStatementNode

 - Describe : new a CompoundStatementNode with parameter (line, col, a vector of DeclNode in AstNode type, a vector of AstNode which contain different statement)

**2. Modify part : StatementList and Statements**

 - Return type : a pointer of a vector of AstNode

 - Describe : same as other list

**3. Modify part : Statement**

 - Return type : a pointer of AstNode

 - Describe : will return different type of statement, may in different node type, but then will become AstNode type

#### Print node, Unary operator node, Binary operator node

**1. Modify part : Simple "PRINT Expression SEMICOLON"**

 - Return type : a pointer of AstNode

 - Describe : new a PrintNode with parameter (line, col, a pointer of ExpressionNode in AstNose type)

**2. Modify part : Expression**

 - Return type : a pointer of ExpressionNode

 - Describe : will return different type of expression, may in different node type, but then will become ExpressionNode type. 
	1. For "IntegerAndReal" and "StringAndBoolean", they will new a ConstantValueNode like previous. 
	2. For unary operation, I create UnaryOperatorNode with parameter(line, col, string type of operator, a pointer of Expression node).
	3. For binary operation, I create BinaryOperatorNode with parameter(line, col, string type of operator, a pointer of Expression node for first expression,a pointer of Expression node for second expression).

**3. Modify part : ExpressionList and Expressions**

 - Return type : a pointer of a vector of ExpressionNode

 - Describe : same as other list

#### Function invocation node

**1. Modify part : FunctionInvocation**

 - Return type : a pointer of ExpressionNode

 - Describe : return $1.

**2. Modify part : FunctionCall**

 - Return type : a pointer of ExpressionNode

 - Describe : new a ExpressionNode with parameter (line, col, function name, a pointer of a vector of ExpressionNode that store expression list)

#### Variable reference node

**1. Modify part : VariableReference**

 - Return type : a pointer of VariableReferenceNode

 - Describe : new a VariableReferenceNode with parameter (line, col, variable name, a pointer of a vector of ExpressionNode that store reference list)

**2. Modify part : ArrRefList and ArrRefs**

 - Return type : a pointer of a vector of ExpressionNode

 - Describe : same as other list

#### Assignment node

**1. Modify part : Simple "VariableReference ASSIGN Expression SEMICOLON"**

 - Return type : a pointer of AstNode

 - Describe : new a AssignmentNode with parameter (line, col, a pointer of VariableReferenceNode in AstNode type, a pointer of ExpressionNode in AstNode type)

#### Read node

**1. Modify part : Simple "READ VariableReference SEMICOLON"**

 - Return type : a pointer of AstNode

 - Describe : new a ReadNode with parameter (line, col, a pointer of VariableReferenceNode in AstNode type)

#### If node

**1. Modify part : Condition**

 - Return type : a pointer of IfNode

 - Describe : new a IfNode with parameter (line, col, a pointer of ExpressionNode in AstNode type, a pointer of CompoundStatementNode for compound statement, a pointer of CompoundStatementNode for else)

**2. Modify part : ElseOrNot**

 - Return type : a pointer of CompoundStatementNode

 - Describe : 
	1. return a pointer of CompoundStatementNode for else compound statement if is "ELSE CompoundStatement"
	2. return nullptr if is "Epsilon"

#### While node

**1. Modify part : While**

 - Return type : a pointer of WhileNode

 - Describe : new a WhileNode with parameter (line, col, a pointer of ExpressionNode in AstNode type, a pointer of CompoundStatementNode for compound statement)


#### For node

**1. Modify part : For**

 - Return type : a pointer of ForNode

 - Describe : 
	1. Do actions to create DeclNode and their related nodes. Same as "Declaration".
	2. Then create AssignmentNode and their related nodes.
	3. Create ConstantValueNode and their related parameters.
	4. new a WhileNode with parameter (line, col, 3 nodes above, a pointer of CompoundStatementNode)

#### Return node

**1. Modify part : Return**

 - Return type : a pointer of ReturnNode

 - Describe : new a ReturnNode with parameter (line, col, a pointer of ExpressionNode in AstNode type)

## What is the hardest you think in this project

> Not required, but bonus point may be given.

I think that the most hardest of this project is to look through all given files and understand them. I can say that the hint.md actually helps, but I still spend a lot of time working at the begining.

## Feedback to T.A.s

> Not required, but bonus point may be given.

For me, I didn't find any big problem in this project, except the challenge in finishing it.


