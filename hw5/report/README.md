# hw5 report

|||
|-:|:-|
|Name|Ian Lai|
|ID|110550168|

## How much time did you spend on this project

> e.g. 2 hours.

3 days for code, but this homework is the only one and I can do it for a week

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way.
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here.

## Overview

In this report, I will explain how I done this project in two part, modification to the original code and how I implement the code generation. And also, since I didn't past all test case, so that some of the part may not be described.

### Modification to the original code

I modify the return type of lookup to a pointer of SymbolEntry instead of a constant pointer. The reason is that we need to store the offset in symbol entry, but if we get the entry from lookup, we cannot modify it.

#### Program node

1. Set the label to 1, label is a counter to count how many label is created.

2. visit DeclNode and FuncMode

3. print prologue, allocate space

4. set offset to -12 and visit CompoundStatementNode, before entering CompoundStatementNode I reset the offset variable, since the space I used in a new allocated one.

5. print epilogue, clear the memory

6. close the file, or the code will not be dumped

#### Variable node

1. determine declare global variable or local and output different code

2. If global, determine whether having constant value node and output different code

3. If local, save the offset in the symbol entry and seperate to function parameter and variable declare. For function parameter, store the value to register a(0-7) and t(0-6). For variable declare and having constant value, output the same code as assignment code.

#### Constant value node

1. determine declare global variable or local and output different code

2. If global, output .word

3. If local, put the constant value in stack. If the value is true, put 1, else if the value is false, put 0.

#### Function node

1. output prologue and allocate the memory, set the offset counter to -12, parameter counter to 0.

    - offset : to get the defined variable's offset from the bottom of the stack

    - parameter counter : count the parameter number, so that I can know which register need to be used and whether it is over 8

2. free the allocated space

#### Compound statement node

1. set is\_function to 0, so that the generated code will be correct, then visit child node

#### PrintNode

1. set load\_val to 1, so that in variable reference, I will load the value and put it in stack

2. pop the value from the stack and print

#### BinaryOperatorNode and UnaryOperatorNode

1. pop one value for unary operation node and pop two value for binary operation node

2. for mathematic operator (+,-,*,/,mod), I use the corresponding instruction code, the push back to stack

3. for relation operation, instead of using the corresponding code, I do the compare and branch to local label(C), in there, I push 1 to the stack if the condition is true and push -1 to the stack if the condition is false, so that if there is more than one relation operator, I can compare the result

#### FunctionInvocationNode

1. put the argument to a(0-7) and t(0-6), register t is used if argument is more than 8

2. jump to the function and push the return value to the stack

#### VariableReferenceNode

1. I use lookup to get the current symbol entry, then get the entry's current level, if is 0, then it is global variable, else, it is local variable

2. For both variable, I use the flag to determine whether I need to load address or value, then output the corresponding code

#### AssignmentNode

1. set load\_addr to 1, so that I will push the address of the left variable to the stack, then push the value of the right to the stack

2. pop the value and the address, store the value to the address

#### ReadNode

1. set load\_addr to 1, so that I will push the address of the variable to the stack

2. pop the address, jump to readInt and store the return value to the address

#### IfNode

1. get the current label, visit condition

2. pop the condition result and determine branch or not, output a label and add 1 to cur\_label

3. visit if\_body

4. if there is else\_body, visit it and add 1 to cur\_label

5. output the label for the situation that if is done and exist else, add 1 to the cur\label and update the used label

#### WhileNode

1. get the current label, output the label for loop back, visit condition

2. pop the condition result and determine branch or not, output a label, not really used in my second version code

3. visit while\_body

4.  output the jump instruction to the loop back label and the label for the condition not met, add 2 to the cur\label and update the used label

#### ReturnNode

1. pop the value from the stack and move to return register

#### For node

1. set the cur\_label, in order to get the used label number, and prevent other node in compound statement use it

2. visit loop\_var\_decl and init\_stmt first

3. output the label of the loop back part and push the initial loop var into stack

4. visit end\_condition node, so that we can pop the initial condition and the end condition, determine if branch or not

5. visit compound statement node, then output the code to add 1 to loop var

## What is the hardest you think in this project

> Not required, but bonus point may be given.

I think that the most hardest part is to understand the function defined by T.A.s and from the library.

## Feedback to T.A.s

> Not required, but bonus point may be given.

I think that the assembly code for condition part can be improve. Since there may be multiple condition combined into the condition for if/while, I think that instead of comparing two value and branch to label(L in the code), using a local label(C in my code) to see whether put 1 or -1 into the stack(1 for condition is true, -1 for condition is not true). So that the next binary/unary node can get it out and keep compare, and after visiting condition node, you can get the top of the stack out and determine the true or false of the condition, then branch to label(L in the code).

Beside that, I think that the return type of lookup can be modified to a pointer of SymbolEntry instead of a constant pointer. The reason is mentioned in the overview.

But, I think that the difficulty is fine.
