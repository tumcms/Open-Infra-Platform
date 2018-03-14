/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS 
	Generator, a simple early binding generator for EXPRESS.
	Copyright (c) 2016-2017 Technical University of Munich
	Chair of Computational Modeling and Simulation.

	TUM Open Infra Platform Early Binding EXPRESS Generator is free 
	software; you can redistribute it and/or modify it under the terms 
	of the GNU General Public License Version 3 as published by the Free
	Software Foundation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is 
	distributed in the hope that it will be useful, but WITHOUT ANY 
	WARRANTY; without even the implied warranty of MERCHANTABILITY or 
	FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
	for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

%option never-interactive
%option nounistd
%option noyywrap

%{
//---------------------------------------------------------------------------//
// Definitions
//---------------------------------------------------------------------------//
%}

%{
#include "ExpressBinding/src/OpenInfraPlatform/ExpressBinding/Meta/eExpressTokenType.h"
//#include <iostream>
#include "parser.hpp"
#include "ExpressBinding/src/OpenInfraPlatform/ExpressBinding/Parser/node.h"
int line_num = 1;
%}

%{
//---------------------------------------------------------------------------//
// States
//---------------------------------------------------------------------------//
%}

%x IN_COMMENT

digit [0-9]
digits {digit}({digit})*
letter [a-zA-Z]
simple_id {letter}({letter}|{digit}|_)*
integer_literal {digits}
real_literal ({digits}[.]{digits}?((E-|E+){digits})?)

%%

%{
//---------------------------------------------------------------------------//
// Rules
//---------------------------------------------------------------------------//
%}

%{
/* ************  skip white chars and line comments ************** */
%}

" "						{}
[ \t]					;
\n						{ ++line_num; }
[\r]					{} 
[\0]+					{} 

--+[^*/\n]*				{} // line comment

<INITIAL>
{
    "(*"				BEGIN(IN_COMMENT);
}
     
<IN_COMMENT>
{
     "*)"				BEGIN(INITIAL);
     [^*\n]+			// eat comment in chunks
     "*"				// eat the lone star
     \n					line_num++;
}

%{
/* ********************** Operators ************************** */
%}

">="					{ return TOKEN_GREATER_THAN_EQUAL; }
"<="					{ return TOKEN_LESS_THAN_EQUAL; }
">"						{ return TOKEN_GREATER_THAN; }
"<"						{ return TOKEN_LESS_THAN; }
"="						{ return TOKEN_EQUAL; }
"<>"					{ return TOKEN_NOT_EQUAL; }
"?"						{ return TOKEN_QUESTION_MARK; }
":="					{ return TOKEN_ASSIGNMENT; }

%{
/* ********************** Separators ************************** */
%}

";"						{ return TOKEN_SEMICOLON; }
","						{ return TOKEN_COMMA; }
":"						{ return TOKEN_COLON; }
"("						{ return TOKEN_BRACKET_OPEN; }
")"						{ return TOKEN_BRACKET_CLOSE; }
"{"						{ return TOKEN_CURLY_BRACKETS_OPEN; }
"}"						{ return TOKEN_CURLY_BRACKETS_CLOSE; }
"["						{ return TOKEN_SQUARE_BRACKET_OPEN; }
"]"						{ return TOKEN_SQUARE_BRACKET_CLOSE; }
"."						{ return TOKEN_PERIOD; }
"/"						{ return TOKEN_SLASH; }
"\\"					{ return TOKEN_BACKSLASH; }

%{
/* ********************** Misc ******************************** */
%}

"||"					{ return TOKEN_CONCAT_OP; }
"'"						{ return TOKEN_INVERTED_COMMA; }
"\""					{ return TOKEN_QUOTE; }
"_"						{ return TOKEN_UNDERSCORE; }
"+"						{ return TOKEN_PLUS; }
"-"						{ return TOKEN_MINUS; }
"*"						{ return TOKEN_MULTIPLY; }
"|"						{ return TOKEN_STROKE; }
"!"						{ return TOKEN_EXCLAMATION_MARK; }
"#"						{ return TOKEN_HASH; }
"$"						{ return TOKEN_DOLAR; }
"%"						{ return TOKEN_PERCENTAGE; }
"@"						{ return TOKEN_AT_SIGN; }
"&"						{ return TOKEN_AMPERSAND; }
"~"						{ return TOKEN_TILDE; }
"^"						{ return TOKEN_CIRCUMFLEX; }
"<*"					{ return TOKEN_ALL_IN; }
"**"					{ return TOKEN_EXP; }
":=:"					{ return TOKEN_INST_EQUAL; }
":<>:"					{ return TOKEN_INST_NOT_EQUAL; }

%{
/* ********************** Keywords ************************** */
%}

ABS						{ return TOKEN_ABS; }
ABSTRACT				{ return TOKEN_ABSTRACT; }
ACOS 					{ return TOKEN_ACOS; }
AGGREGATE				{ return TOKEN_AGGREGATE; }
ALIAS 					{ return TOKEN_ALIAS; }
AND 					{ return TOKEN_AND; }
ANDOR					{ return TOKEN_ANDOR; }
ARRAY					{ return TOKEN_ARRAY; }
AS						{ return TOKEN_AS; }
ASIN					{ return TOKEN_ASIN; }
ATAN					{ return TOKEN_ATAN; }
BAG						{ return TOKEN_BAG; }
BASED_ON				{ return TOKEN_BASED_ON; }
BEGIN					{ return TOKEN_BEGIN; }
BINARY					{ return TOKEN_BINARY; }
BLENGTH 				{ return TOKEN_BLENGTH; }
BOOLEAN 				{ return TOKEN_BOOLEAN; }
BY						{ return TOKEN_BY; }
CASE					{ return TOKEN_CASE; }
CONSTANT				{ return TOKEN_CONSTANT; }
CONST_E					{ return TOKEN_CONST_E; }
COS 					{ return TOKEN_COS; }
DERIVE 					{ return TOKEN_DERIVE; }
DIV 					{ return TOKEN_DIV; }
ELSE 					{ return TOKEN_ELSE; }
END 					{ return TOKEN_END; }
END_ALIAS				{ return TOKEN_END_ALIAS; }
END_CASE 				{ return TOKEN_END_CASE; }
END_CONSTANT 			{ return TOKEN_END_CONSTANT; }
END_ENTITY 				{ return TOKEN_END_ENTITY; }
END_FUNCTION 			{ return TOKEN_END_FUNCTION; }
END_IF 					{ return TOKEN_END_IF; }
END_LOCAL 				{ return TOKEN_END_LOCAL; }
END_PROCEDURE 			{ return TOKEN_END_PROCEDURE; }
END_REPEAT 				{ return TOKEN_END_REPEAT; }
END_RULE 				{ return TOKEN_END_RULE; }
END_SCHEMA 				{ return TOKEN_END_SCHEMA; }
END_SUBTYPE_CONSTRAINT 	{ return TOKEN_END_SUBTYPE_CONSTRAINT; }
END_TYPE 				{ return TOKEN_END_TYPE; }
ENTITY 					{ return TOKEN_ENTITY; }
ENUMERATION 			{ return TOKEN_ENUMERATION; }
ESCAPE 					{ return TOKEN_ESCAPE; }
EXISTS 					{ return TOKEN_EXISTS; }
EXTENSIBLE 				{ return TOKEN_EXTENSIBLE; }
EXP 					{ return TOKEN_EXP; }
FALSE 					{ return TOKEN_FALSE; }
FIXED 					{ return TOKEN_FIXED; }
FOR 					{ return TOKEN_FOR; }
FORMAT 					{ return TOKEN_FORMAT; }
FROM 					{ return TOKEN_FROM; }
FUNCTION				{ return TOKEN_FUNCTION; }
Generic 				{ return TOKEN_GENERIC; }
GENERIC 				{ return TOKEN_GENERIC; }
GENERIC_ENTITY 			{ return TOKEN_GENERIC_ENTITY; }
HIBOUND  				{ return TOKEN_HIBOUND; }
HIINDEX  				{ return TOKEN_HIINDEX; }
IF  					{ return TOKEN_IF; }
IN  					{ return TOKEN_IN; }
INSERT  				{ return TOKEN_INSERT; }
INTEGER  				{ return TOKEN_INTEGER; }
INVERSE  				{ return TOKEN_INVERSE; }
LENGTH  				{ return TOKEN_LENGTH; }
LIKE  					{ return TOKEN_LIKE; }
LIST  					{ return TOKEN_LIST; }
LOBOUND  				{ return TOKEN_LOBOUND; }
LOCAL  					{ return TOKEN_LOCAL; }
LOG  					{ return TOKEN_LOG; }
LOG10  					{ return TOKEN_LOG10; }
LOG2  					{ return TOKEN_LOG2; }
LOGICAL  				{ return TOKEN_LOGICAL; }
LOINDEX  				{ return TOKEN_LOINDEX; }
MOD  					{ return TOKEN_MOD; }
NOT  					{ return TOKEN_NOT; }
NUMBER  				{ return TOKEN_NUMBER; }
NVL  					{ return TOKEN_NVL; }
ODD  					{ return TOKEN_ODD; }
OF  					{ return TOKEN_OF; }
ONEOF  					{ return TOKEN_ONEOF; }
OPTIONAL   				{ return TOKEN_OPTIONAL; }
OR   					{ return TOKEN_OR; }
OTHERWISE   			{ return TOKEN_OTHERWISE; }
PI   					{ return TOKEN_PI; }
PROCEDURE   			{ return TOKEN_PROCEDURE; }
QUERY   				{ return TOKEN_QUERY; }
REAL   					{ return TOKEN_REAL; }
REFERENCE   			{ return TOKEN_REFERENCE; }
REMOVE   				{ return TOKEN_REMOVE; }
RENAMED   				{ return TOKEN_RENAMED; }
REPEAT   				{ return TOKEN_REPEAT; }
RETURN   				{ return TOKEN_RETURN; }
ROLESOF   				{ return TOKEN_ROLESOF; }
RULE   					{ return TOKEN_RULE; }
SCHEMA   				{ return TOKEN_SCHEMA; }
SELECT   				{ return TOKEN_SELECT; }
SELF   					{ return TOKEN_SELF; }
SET   					{ return TOKEN_SET; }
SIN   					{ return TOKEN_SIN; }
SIZEOF   				{ return TOKEN_SIZEOF; }
SKIP   					{ return TOKEN_SKIP; }
SQRT   					{ return TOKEN_SQRT; }
STRING   				{ return TOKEN_STRING; }
SUBTYPE   				{ return TOKEN_SUBTYPE; }
SUBTYPE_CONSTRAINT   	{ return TOKEN_SUBTYPE_CONSTRAINT; }
SUPERTYPE   			{ return TOKEN_SUPERTYPE; }
TAN   					{ return TOKEN_TAN; }
THEN   					{ return TOKEN_THEN; }
to   					{ return TOKEN_TO; }
TO   					{ return TOKEN_TO; }
TOTAL_OVER   			{ return TOKEN_TOTAL_OVER; }
TRUE   					{ return TOKEN_TRUE; }
TYPE   					{ return TOKEN_TYPE; }
TYPEOF   				{ return TOKEN_TYPEOF; }
UNIQUE   				{ return TOKEN_UNIQUE; }
UNKNOWN   				{ return TOKEN_UNKNOWN; }
UNTIL   				{ return TOKEN_UNTIL; }
USE   					{ return TOKEN_USE; }
USEDIN   				{ return TOKEN_USEDIN; }
VALUE   				{ return TOKEN_VALUE; }
VALUE_IN   				{ return TOKEN_VALUE_IN; }
VALUE_UNIQUE   			{ return TOKEN_VALUE_UNIQUE; }
VAR   					{ return TOKEN_VAR; }
WHERE   				{ return TOKEN_WHERE; }
WHILE   				{ return TOKEN_WHILE; }
WITH   					{ return TOKEN_WITH; }
XOR  					{ return TOKEN_XOR; }

%{
/* ********************     Values        ****************** */
%}

'%'[01]+				{
							yylval.sval = _strdup(yytext);
							return TOKEN_BINARY_LITERAL;
						}

{integer_literal}		{ 
							yylval.sval = _strdup(yytext);
							return TOKEN_INTEGER_LITERAL;
						}
					
{real_literal}          {
							yylval.sval = _strdup(yytext);
							return TOKEN_REAL_LITERAL;
						}
						
{simple_id}				{ 
							//std::cout << yytext << std::endl;
							yylval.sval = _strdup(yytext);
							return TOKEN_SIMPLE_ID;
						}

[\']([\n]|[\000\011-\046\050-\176\201-\237\240-\377]|[\047][\047])*[\']	{ 
																				yylval.sval = _strdup(yytext);
																				return TOKEN_SIMPLE_STRING_LITERAL; 
																		}

%%