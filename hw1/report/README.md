# hw1 report

|Field|Value|
|-:|:-|
|Name|Ian Lai|
|ID|110550168|

## How much time did you spend on this project

roughly 3 nights for coding and one night for report

## Project overview

Describe the project structure and how you implemented it.

**About My Code**
1. all rules that does not use predefined macro call LIST\_SOURCE to append to line
2. catch the character which is not accepted b rules should be the last rule and with INITIAL state, since in STRING and COMMENTS, there is no need to check the rules
3. a dot "." is same as the meaning in lex

**delimeters**
 - State : one state, INITIAL
 - Definitions : using several alternations to combine these symbals
 - Rules : call LIST\_TOKEN() macro to print out the delimeter

**Arithmetic, Relational, and Logical Operators**
>*put the rule above identifiers to prevent being recognized as identifiers*
 - State : one state, INITIAL
 - Definitions : seperate these to one character operations, two character operations, operation in reserved words, then use alternations to give definitions to each of them
 - Rules : write the print function for one/two character operations by myself to print %c, and for operations in reserved words,call LIST\_TOKEN()

**Reserved Words**
>*put the rule above identifiers to prevent being recognized as identifiers*
 - State : one state, INITIAL
 - Definitions : define seperately by their given name
 - Rules : use special option "|" to let them have the same action defined by myself, similar to LIST\_TOKEN() but print "KW" before yytext

**Identifiers**
>*the rule should below reserved words, containing reserved words, some operations*
 - State : one state, INITIAL
 - Definitions : first character be A-Z or a-z, the rest of them can be A-Z, a-z, 0-9, or nothing
 - Rules : call LIST\_LITERAL() with "id" as first parameter and yytext as the second parameter

**Integer Constants**
>*0 should belongs to decimal, since it doesn't follow by a sequence of octal digits*
 - State : one state, INITIAL
 - Definitions : define octal and decimal seperately
	 - octal : start with 0, and the rest of them can be 0-9 but not nothing
	 - decimal : define nonzero decimal by starting with 1-9 and the following can be 0-9 or nothing, then do alternations with 0
 - Rules : both call LIST\_LITERAL() with corresponding parameters

**Floating-Point Constants**
>*the rule should be above integer constants and below scientific notations to prevent misrecognition*
 - State : one state, INITIAL
 - Definitions : by consider different situations and define seperately
	 - nonzero_float : start with nonzero decimal, follow by a dot, and then end by one digit or several digits with a nonzero digit, or start with 0, follow by a dot, several digits and end by a nonzero digit
	 - float : nonzero float or "0.0"
 - Rules : call LIST\_LITERAL() with corresponding parameters

**Scientific Notations**
>*the rule should be above integer constants and floating-point constants to prevent misrecognition*
 - State : one state, INITIAL
 - Definitions : start by nonzero decimal or nonzero float, following by E or e, then could have one -/+, and end by a decimal
 - Rules : call LIST\_LITERAL() with corresponding parameters

**String Constants**
>*for IN_STRING state, "" and " should put above . , or the input will fit .  and cause error*
 - State : two state, INITIAL and IN\_STRING
 - Definitions : define str\_copy function, explain in Routines part, an array str\_ to stoer string, and a pointer str\_ptr to point at the start of the string
 - Rules : 
	 - INITIAL :
	1. get "", with no " following, then print empty string
	2. get ", reset array str\_ and str\_ptr, go to IN\_STRING state
	 - IN_STRING : 
	1. get "", and use str\_copy(), with """ and 1 to add " to str\_
	2. get ", print str\_, and go to INITIAL state
	3. get anything else, use str\_copy(), with yytext and 0 to add yytext to str\_ 
 - Routines : define function str\_copy, two parameters, first is the string need to copy to array, second is whether the string contain "
	1. a while loop to copy string to the array, terminate by meeting " or the end
	2. if quote is 1 , then it means that we need to add a quote into the array

**Whitespace**
>*\n will need to print out the current line also, so the rule to print current line is just above error check and with no state*
 - State : one state, INITIAL
 - Definitions : non
 - Rules : LIST\_SOURCE only

**Comments**
>*for COMMENT\_BLOCK and COMMENT\_LINE state, need to put the ending condition before . to prevent recognize as .*
>*the rule of COMMENT\_LINE need to put below that of Pseudocomment*
 - State : three state, INITIAL, COMMENT\_BLOCK, COMMENT\_LINE
 - Definitions : non
 - Rules : 
	 - INITIAL :
	1. get /\*, go to COMMENT\_BLOCK
	2. get // and is not follow by &, go to COMMENT\_LINE
	 - COMMENT\_BLOCK : 
	1. get \*/, go back to INITIAL
	2. get . , LIST\_SOURCE only
	 - COMMENT\_LINE : 
	1. get . and follow by \\n, LIST\_SOURCE and go back to INITIAL
	2. get . , LIST\_SOURCE only

**Pseudocomments**
>*the rule of Pseudocomment need to put above that of COMMENT\_LINE*
 - State : one state, INITIAL
 - Definitions : non
 - Rules : consider 2 cases, one is //&S+, another is //&S+, follow by \\n (S can change to T, and + can change to -)
	1. LIST\_SOURCE, set opt\_src (for S) / opt\_tok (for T) to 1 (for +) or 0 (for -), and go to COMMAND\_LINE
	2. LIST\_SOURCE, set opt\_src (for S) / opt\_tok (for T) to 1 (for +) or 0 (for -)

	

## What is the hardest you think in this project

I would say to be double quotes in string, since its hard to distinguish it between the quotes for string. It takes me a lot of time to try and error.

## Feedback to T.A.s

> Please help us improve our assignment, thanks.
I think that the definition of integer constant is a little bit confusing at first sight, maybe can noted that it does not contain signals (+,-).
