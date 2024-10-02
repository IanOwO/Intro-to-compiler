# hw2 report

|||
|-:|:-|
|Name|Ian Lai|
|ID|110550168|

## How much time did you spend on this project

roughly 10-12 hours

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way. \
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here. 

**Modification in scanner.l**
1. I use the given scanner.l, bacause I met a problem that is hard to fix, which is "error: undeclared". So I change to use the given scanner.l to minimize the error from other part.
2. I add return after every recognized token. To fix the problem "error: undeclared", I add "KW" before all names that I given to tokens, e.x. "KWCOMMA". 

**Implementation of parser.y**

**Declarations part**
1. "%left" is for all operators except "assign" and "not".
2. "%right" is for "assign" and "not". 
	 - For "assign", it should be done from right to left, same as it in C.
	 - For "not", to deal with "not not expression", do it from right to left seems to be more reasonable.
3. Others can just be "%token".

**Rules part**
1. For "zero or more varable and constant declaration/function decalration and definition", I seperate the rule declare part and the zero or more part. The prefix "zero\_more" means that the zero or more part.
2. Most part of rule definition, I do it simply, just written as the given definition.
3. I add "( expression )" to expression, though there is no definition written, but I find out that this is needed.
4. For function calls, zero or more expressions seperated by comma is needed inside the parentheses. I implement it by adding two rules, one is comma\_expression inside the parentheses, the other is nothing inside the parentheses. Then comma\_expression 
5. I define "Function", "Data Types and Declarations", "Statements" and "Expressions" together each, so that I can easily add the expression to others.

## What is the hardest you think in this project

> Not required, but bonus point may be given.

I would say to be figuring out BEGIN is a reserved word and lead to "error: undeclared".

## Feedback to T.A.s

> Not required, but bonus point may be given.

For the expression part, I didn't see the explaination of parentheses, so I think for a while when meeting error '('. I think that it can be mentioned more clearly.
Also, in literal\_constant part, it doesn't contain scientific in the definition part, which confuse me for a while.
