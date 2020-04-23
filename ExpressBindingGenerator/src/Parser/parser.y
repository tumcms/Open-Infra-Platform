%error-verbose

%{
	#include "Parser/node.h"
	#include "Meta/Entity.h"
	#include "Meta/Type.h"
	#include "Meta/EntityAttribute.h"
	#include "Meta/Schema.h"
	#include "General/memory.h"
	#include "General/stack.h"

	#include <cstdio>
	#include <iostream>
	#include <stack>
	#include <cassert>
	#include <string>

	// stuff from flex that bison needs to know about:
	int yylex();
	int yyparse();
	extern FILE *yyin; 
	void yyerror(const char *s);

	using namespace OpenInfraPlatform::ExpressBindingGenerator;

	#include <sstream>
	std::string g_parentName = "";
	bool g_hasParent = false;


	std::stack<int>									integers;
	std::stack<std::string>							ids;
	std::stack<std::string>							enum_ids;
	
	// Entities
	std::stack<std::string>							entity_ids;
	std::stack<std::string>							attribute_ids;
	std::stack<ReferenceCounted<IEntityAttributeType>>	attribute_types;
	std::stack<eEntityAttributeContainerType>      entityAttributeContainerTypes;


	std::stack<Type>								types2;
	std::stack<oip::eType>							types;
	std::stack<std::string>							select_named_types;

	int bound1;
	int bound2;

	Schema* schema; /* the top level root node of our final AST */

	Entity currentEntity;
%}

/* Represents the many different ways we can access our data */
%union {
	OpenInfraPlatform::ExpressBindingGenerator::Node*                node;
	OpenInfraPlatform::ExpressBindingGenerator::SchemaDecl*			schema_decl;
	OpenInfraPlatform::ExpressBindingGenerator::RuleLabelIdentifier* rule_label_id;
	OpenInfraPlatform::ExpressBindingGenerator::DomainRule*          domain_rule;
	OpenInfraPlatform::ExpressBindingGenerator::DomainRules*         domain_rules;
	OpenInfraPlatform::ExpressBindingGenerator::WhereClause*			where_clause;
	OpenInfraPlatform::ExpressBindingGenerator::Expression*			expression;


	int ival;
	float fval;
	char *sval;
}

// define the constant-string tokens:
%token TOKEN_ABS TOKEN_ABSTRACT	TOKEN_ACOS TOKEN_AGGREGATE	TOKEN_ALIAS	TOKEN_AND 				
%token TOKEN_ANDOR				
%token TOKEN_ARRAY				
%token TOKEN_AS					
%token TOKEN_ASIN				
%token TOKEN_ATAN				
%token TOKEN_BAG					
%token TOKEN_BASED_ON			
%token TOKEN_BEGIN				
%token TOKEN_BINARY				
%token TOKEN_BLENGTH 			
%token TOKEN_BOOLEAN 			
%token TOKEN_BY					
%token TOKEN_CASE				
%token TOKEN_CONSTANT			
%token TOKEN_CONST_E				
%token TOKEN_COS 				
%token TOKEN_DERIVE 				
%token TOKEN_DIV 				
%token TOKEN_ELSE 				
%token TOKEN_END 				
%token TOKEN_END_ALIAS			
%token TOKEN_END_CASE 			
%token TOKEN_END_CONSTANT 		
%token TOKEN_END_ENTITY 			
%token TOKEN_END_FUNCTION 		
%token TOKEN_END_IF 				
%token TOKEN_END_LOCAL 			
%token TOKEN_END_PROCEDURE 		
%token TOKEN_END_REPEAT 			
%token TOKEN_END_RULE 			
%token TOKEN_END_SCHEMA 			
%token TOKEN_END_SUBTYPE_CONSTRAINT 
%token TOKEN_END_TYPE 			
%token TOKEN_ENTITY 				
%token TOKEN_ENUMERATION 		
%token TOKEN_ESCAPE 				
%token TOKEN_EXISTS 				
%token TOKEN_EXTENSIBLE 			
%token TOKEN_EXP 				
%token TOKEN_FALSE 				
%token TOKEN_FIXED 				
%token TOKEN_FOR 				
%token TOKEN_FORMAT 				
%token TOKEN_FROM 				
%token TOKEN_FUNCTION			
%token TOKEN_GENERIC 			
%token TOKEN_GENERIC_ENTITY 		
%token TOKEN_HIBOUND  			
%token TOKEN_HIINDEX  			
%token TOKEN_IF  				
%token TOKEN_IN  				
%token TOKEN_INSERT  			
%token TOKEN_INTEGER  			
%token TOKEN_INVERSE  			
%token TOKEN_LENGTH  			
%token TOKEN_LIKE  				
%token TOKEN_LIST  				
%token TOKEN_LOBOUND  			
%token TOKEN_LOCAL  				
%token TOKEN_LOG  				
%token TOKEN_LOG10  				
%token TOKEN_LOG2  				
%token TOKEN_LOGICAL  			
%token TOKEN_LOINDEX  			
%token TOKEN_MOD  				
%token TOKEN_NOT  				
%token TOKEN_NUMBER  			
%token TOKEN_NVL  				
%token TOKEN_ODD  				
%token TOKEN_OF  				
%token TOKEN_ONEOF  				
%token TOKEN_OPTIONAL   			
%token TOKEN_OR   				
%token TOKEN_OTHERWISE   		
%token TOKEN_PI   				
%token TOKEN_PROCEDURE   		
%token TOKEN_QUERY   			
%token TOKEN_REAL   				
%token TOKEN_REFERENCE   		
%token TOKEN_REMOVE   			
%token TOKEN_RENAMED   			
%token TOKEN_REPEAT   			
%token TOKEN_RETURN   			
%token TOKEN_ROLESOF   			
%token TOKEN_RULE   				
%token TOKEN_SCHEMA   			
%token TOKEN_SELECT   			
%token TOKEN_SELF   				
%token TOKEN_SET   				
%token TOKEN_SIN   				
%token TOKEN_SIZEOF   			
%token TOKEN_SKIP   				
%token TOKEN_SQRT   				
%token TOKEN_STRING   			
%token TOKEN_SUBTYPE   			
%token TOKEN_SUBTYPE_CONSTRAINT   
%token TOKEN_SUPERTYPE
%token TOKEN_TAN
%token TOKEN_THEN
%token TOKEN_TO
%token TOKEN_TOTAL_OVER
%token TOKEN_TRUE
%token TOKEN_TYPE
%token TOKEN_TYPEOF
%token TOKEN_UNIQUE
%token TOKEN_UNKNOWN
%token TOKEN_UNTIL
%token TOKEN_USE
%token TOKEN_USEDIN
%token TOKEN_VALUE
%token TOKEN_VALUE_IN
%token TOKEN_VALUE_UNIQUE
%token TOKEN_VAR
%token TOKEN_WHERE
%token TOKEN_WHILE
%token TOKEN_WITH
%token TOKEN_XOR
%token TOKEN_ASSIGNMENT
%token TOKEN_ALL_IN
%token TOKEN_INST_NOT_EQUAL;
%token TOKEN_COMMA
%token TOKEN_PERIOD
%token TOKEN_SEMICOLON
%token TOKEN_COLON
%token TOKEN_INVERTED_COMMA
%token TOKEN_QUOTE
%token TOKEN_UNDERSCORE
%token TOKEN_BRACKET_OPEN
%token TOKEN_BRACKET_CLOSE
%token TOKEN_SQUARE_BRACKET_OPEN
%token TOKEN_SQUARE_BRACKET_CLOSE
%token TOKEN_CURLY_BRACKETS_OPEN
%token TOKEN_CURLY_BRACKETS_CLOSE
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_MULTIPLY
%token TOKEN_SLASH
%token TOKEN_BACKSLASH
%token TOKEN_STROKE
%token TOKEN_EQUAL
%token TOKEN_EXCLAMATION_MARK
%token TOKEN_HASH
%token TOKEN_DOLAR
%token TOKEN_PERCENTAGE
%token TOKEN_AT_SIGN
%token TOKEN_QUESTION_MARK
%token TOKEN_AMPERSAND
%token TOKEN_LESS_THAN_EQUAL
%token TOKEN_GREATER_THAN_EQUAL
%token TOKEN_LESS_THAN
%token TOKEN_GREATER_THAN
%token TOKEN_TILDE
%token TOKEN_CIRCUMFLEX
%token TOKEN_NOT_EQUAL
%token TOKEN_CONCAT_OP;
%token TOKEN_INST_EQUAL;

%token <sval> TOKEN_SIMPLE_ID
%token <sval> TOKEN_INTEGER_LITERAL
%token <sval> TOKEN_REAL_LITERAL
%token <sval> TOKEN_SIMPLE_STRING_LITERAL
%token <sval> TOKEN_BINARY_LITERAL

%type <rule_label_id> rule_label_id 
%type <schema_decl> schema_decl;
%type <domain_rule> domain_rule;
%type <domain_rules> domain_rules;
%type <where_clause> where_clause;
%type <expression> expression built_in_constant;


%start schema_decl;

%%
schema_decl:
	TOKEN_SCHEMA TOKEN_SIMPLE_ID TOKEN_SEMICOLON schema_body TOKEN_END_SCHEMA TOKEN_SEMICOLON
	{
		oip::Schema::getInstance().setName($2);
	};

schema_body:
	%empty
  | type_decl schema_body
  | entity_decl schema_body
  | function_decl schema_body
  | rule_decl schema_body;

function_decl:
	function_head algorithm_head stmt function_decl1 TOKEN_END_FUNCTION TOKEN_SEMICOLON;

function_decl1:
	%empty
  | stmt function_decl1;

function_head:
	TOKEN_FUNCTION function_id function_head1 TOKEN_COLON parameter_type TOKEN_SEMICOLON;

function_head1:
	%empty
  |	TOKEN_BRACKET_OPEN formal_parameter function_head2 TOKEN_BRACKET_CLOSE;

formal_parameter:
	parameter_id formal_parameter1 TOKEN_COLON parameter_type;

formal_parameter1:
	%empty
  | TOKEN_COMMA parameter_id formal_parameter1;

function_head2:
	%empty
  | TOKEN_SEMICOLON formal_parameter function_head2;

algorithm_head:
	algorithm_head1 algorithm_head2 algorithm_head3;

algorithm_head1:
	%empty
  | declaration algorithm_head1;

algorithm_head2:
	%empty
  | constant_decl;

algorithm_head3:
	%empty
  | local_decl;

local_decl:
	TOKEN_LOCAL local_variable local_decl1 TOKEN_END_LOCAL TOKEN_SEMICOLON;

local_decl1:
	%empty
  | local_variable local_decl1;

local_variable:
	variable_id local_variable1 TOKEN_COLON parameter_type local_variable2 TOKEN_SEMICOLON;

local_variable1:
	%empty
  | TOKEN_COMMA variable_id local_variable1;

local_variable2:
	%empty
  | TOKEN_ASSIGNMENT expression;

constant_decl:
	TOKEN_CONSTANT constant_body constant_decl1 TOKEN_END_CONSTANT;

constant_decl1:
	%empty
  | constant_body constant_decl1;

constant_body:
	constant_id TOKEN_COLON instantiable_type TOKEN_ASSIGNMENT expression TOKEN_SEMICOLON;

declaration :
	entity_decl 
  | function_decl 
  | procedure_decl 
  | subtype_constraint_decl 
  | type_decl;

procedure_decl:
	procedure_head algorithm_head procedure_decl1 TOKEN_END_PROCEDURE TOKEN_SEMICOLON;

procedure_decl1:
	%empty
  | stmt procedure_decl1;

procedure_head:
	TOKEN_PROCEDURE procedure_id procedure_head1 TOKEN_SEMICOLON;

procedure_head1:
	%empty
  | TOKEN_BRACKET_OPEN procedure_head2 formal_parameter procedure_head3 TOKEN_BRACKET_CLOSE;

procedure_head2:
	%empty
  | TOKEN_VAR;

procedure_head3:
	%empty
  |	TOKEN_SEMICOLON procedure_head2 formal_parameter procedure_head3;

procedure_id:
	TOKEN_SIMPLE_ID;

stmt:
	alias_stmt
  | assignment_stmt 
  | case_stmt 
  | compound_stmt 
  | escape_stmt
  | if_stmt 
  | null_stmt 
  | procedure_call_stmt 
  | repeat_stmt 
  | return_stmt 
  | skip_stmt;

alias_stmt:
	TOKEN_ALIAS variable_id TOKEN_FOR general_ref alias_stmt1 TOKEN_SEMICOLON stmt alias_stmt2 TOKEN_END_ALIAS TOKEN_SEMICOLON;

alias_stmt1:
	%empty
  | qualifier alias_stmt1;

 alias_stmt2:
	%empty
  | stmt alias_stmt2;

assignment_stmt:
	general_ref assignment_stmt1 TOKEN_ASSIGNMENT expression TOKEN_SEMICOLON;

assignment_stmt1:
	%empty
  | qualifier assignment_stmt1;

case_stmt:
	TOKEN_CASE selector TOKEN_OF case_stmt1 case_stmt2 TOKEN_END_CASE TOKEN_SEMICOLON;

case_stmt1:
	%empty
  | case_action case_stmt1;

case_stmt2:
	%empty
  | TOKEN_OTHERWISE TOKEN_COLON stmt;

case_action:
	case_label case_action1 TOKEN_COLON stmt;

case_action1:
	%empty
  | TOKEN_COMMA case_label case_action1;

case_label:
	expression;

procedure_ref:
	procedure_id;

repeat_control:
	repeat_control1 repeat_control2 repeat_control3;

repeat_control1:
	%empty
  | increment_control;

repeat_control2:
	%empty
  | while_control;

repeat_control3:
	%empty
  | until_control;

selector:
	expression;

subtype_constraint_body:	
	subtype_constraint_body1 subtype_constraint_body2 subtype_constraint_body3;

subtype_constraint_body1:
	%empty
  | abstract_supertype;

subtype_constraint_body2:
	%empty
  | total_over;

subtype_constraint_body3:
	%empty
  | supertype_expression TOKEN_SEMICOLON;

subtype_constraint_head:
	TOKEN_SUBTYPE_CONSTRAINT subtype_constraint_id TOKEN_FOR entity_ref TOKEN_SEMICOLON;

abstract_supertype:
	TOKEN_ABSTRACT TOKEN_SUPERTYPE TOKEN_SEMICOLON;

compound_stmt:
	TOKEN_BEGIN stmt compound_stmt1 TOKEN_END TOKEN_SEMICOLON;

compound_stmt1:
	%empty
  | stmt compound_stmt1;

escape_stmt:
	TOKEN_ESCAPE TOKEN_SEMICOLON;

if_stmt:
	TOKEN_IF logical_expression TOKEN_THEN stmt if_stmt1 if_stmt2 TOKEN_END_IF TOKEN_SEMICOLON;

if_stmt1:
	%empty
  | stmt if_stmt1;

if_stmt2:
	%empty
  | TOKEN_ELSE stmt if_stmt1

null_stmt:
	TOKEN_SEMICOLON;

procedure_call_stmt:
	procedure_call_stmt1 procedure_call_stmt2 TOKEN_SEMICOLON;

procedure_call_stmt1:
	built_in_procedure 
  | procedure_ref;

procedure_call_stmt2:
	%empty
  | actual_parameter_list;

repeat_stmt:
	TOKEN_REPEAT repeat_control TOKEN_SEMICOLON stmt repeat_stmt1 TOKEN_END_REPEAT TOKEN_SEMICOLON; 

repeat_stmt1:
	%empty
  | stmt repeat_stmt1;

return_stmt:
	TOKEN_RETURN return_stmt1 TOKEN_SEMICOLON;

return_stmt1:
	%empty
  | TOKEN_BRACKET_OPEN expression TOKEN_BRACKET_CLOSE;

skip_stmt:
	TOKEN_SKIP TOKEN_SEMICOLON;

subtype_constraint_decl:
	subtype_constraint_head subtype_constraint_body TOKEN_END_SUBTYPE_CONSTRAINT TOKEN_SEMICOLON;

built_in_procedure:
	TOKEN_INSERT
  | TOKEN_REMOVE;

increment_control:
	variable_id TOKEN_ASSIGNMENT bound_1 TOKEN_TO bound_2 increment_control2;

increment_control2:
	%empty
  | TOKEN_BY increment;

subtype_constraint_id:
	TOKEN_SIMPLE_ID;

total_over:
	TOKEN_TOTAL_OVER TOKEN_BRACKET_OPEN entity_ref total_over1 TOKEN_BRACKET_CLOSE TOKEN_SEMICOLON;

total_over1:
	%empty
  | TOKEN_COMMA entity_ref total_over1;

until_control:
	TOKEN_UNTIL logical_expression;

while_control:
	TOKEN_WHILE logical_expression;

bound_1:
	numeric_expression;

bound_2:
	numeric_expression;

increment:
	numeric_expression;

type_decl:
	TOKEN_TYPE TOKEN_SIMPLE_ID TOKEN_EQUAL underlying_type TOKEN_SEMICOLON type_decl2 TOKEN_END_TYPE TOKEN_SEMICOLON
	{
		oip::Type type;
		type.setName($2);
		extern int line_num;

		type.setType(types.top());
		types.pop();

		if(type.getType() == oip::eType::List)
		{
			type.setContainerType(ids.top());
			ids.pop();

			type.setContainerCardinalityMin(bound1);
			type.setContainerCardinalityMax(bound2);
		}

		if(type.getType() == oip::eType::Array)
		{
			type.setContainerType(ids.top());
			ids.pop();

			type.setContainerCardinalityMin(bound1);
			type.setContainerCardinalityMax(bound2);
		}

		if(type.getType() == oip::eType::Enumeration)
		{
			std::vector<std::string> types;
			while(enum_ids.size() > 0)
			{
				types.insert(types.begin(), enum_ids.top());
				enum_ids.pop();
			}
			type.setTypes(types);
			type.setType(oip::eType::Enumeration);
		}

		if(type.getType() == oip::eType::Select)
		{
			std::vector<std::string> types;
			while(select_named_types.size() > 0)
			{
				types.insert(types.begin(), select_named_types.top());
				select_named_types.pop();
			}
			type.setTypes(types);
			type.setType(oip::eType::Select);
		}

		if(type.getType() == oip::eType::Set)
		{
			type.setContainerType(ids.top());
			ids.pop();

			type.setContainerCardinalityMin(bound1);
			type.setContainerCardinalityMax(bound2);
		}
		
		if(type.getType() == oip::eType::Unknown)
		{
			type.setUnderlyingTypeName(ids.top());
			ids.pop();
		}

		oip::Schema::getInstance().addType(type);

		clear(attribute_types);		
	};

type_decl2:
	%empty
  |	where_clause;

where_clause:
	TOKEN_WHERE domain_rules
	{
		$$ = new WhereClause($2);
	};

domain_rules:
		domain_rule TOKEN_SEMICOLON {
			$$ = new DomainRules();
			$$->addDomainRule(std::shared_ptr<DomainRule>($<domain_rule>1));
		}
	|	domain_rules domain_rule TOKEN_SEMICOLON {
			$1->addDomainRule(std::shared_ptr<DomainRule>($<domain_rule>2));
	    }
;

domain_rule:
	rule_label_id TOKEN_COLON expression
	{
		$$ = new DomainRule($1, $3);
	}
  | expression;

expression:
	simple_expression expression1 {
		//std::cout << "muh" << std::endl;
	}
;
	
expression1:
    %empty
	| rel_op_extended simple_expression
 
simple_expression:
	term simple_expression1 {
		//std::cout << "mm" << std::endl;
	}
;
	
simple_expression1: 
	%empty
  | add_like_op term simple_expression1 {
		//std::cout << "muh";
	}; 
 
add_like_op:
	TOKEN_PLUS
  | TOKEN_MINUS
  | TOKEN_OR 
  | TOKEN_XOR;

term:
	factor term1;

term1:
	%empty
  | multiplication_like_op factor term1;

factor:
	simple_factor factor1;

factor1:
	%empty
  | TOKEN_EXP simple_factor factor1;

simple_factor:
  	aggregate_initializer 
  | entity_constructor
  |	enumeration_reference
  | interval 
  | query_expression
  |	primary
  |	unary_op primary
  | TOKEN_BRACKET_OPEN expression TOKEN_BRACKET_CLOSE
  | unary_op TOKEN_BRACKET_OPEN expression TOKEN_BRACKET_CLOSE;
 
query_expression:
	TOKEN_QUERY TOKEN_BRACKET_OPEN variable_id TOKEN_ALL_IN aggregate_source TOKEN_STROKE logical_expression TOKEN_BRACKET_CLOSE;

aggregate_source:
	simple_expression;

logical_expression:
	expression;

entity_constructor:
	entity_ref TOKEN_BRACKET_OPEN entity_constructor1 TOKEN_BRACKET_CLOSE

entity_constructor1:
	%empty
  | expression 
  | expression TOKEN_COMMA entity_constructor1;

unary_op:
	TOKEN_PLUS
  | TOKEN_MINUS 
  | TOKEN_NOT;

interval:
	TOKEN_CURLY_BRACKETS_OPEN interval_low interval_op interval_item interval_op interval_high TOKEN_CURLY_BRACKETS_CLOSE;

interval_op:
	 TOKEN_LESS_THAN
   | TOKEN_LESS_THAN_EQUAL;

interval_low:
	simple_expression;

interval_item:
	simple_expression;

interval_high:
	simple_expression;

multiplication_like_op:
	TOKEN_MULTIPLY
  | TOKEN_SLASH
  | TOKEN_DIV
  | TOKEN_MOD
  | TOKEN_AND
  | TOKEN_CONCAT_OP;

rel_op:
  	TOKEN_LESS_THAN
  | TOKEN_GREATER_THAN
  | TOKEN_LESS_THAN_EQUAL
  | TOKEN_GREATER_THAN_EQUAL
  | TOKEN_NOT_EQUAL
  | TOKEN_EQUAL
  | TOKEN_INST_NOT_EQUAL
  | TOKEN_INST_EQUAL;

rel_op_extended:
	rel_op
  | TOKEN_IN
  | TOKEN_LIKE;
	
built_in_function:
	TOKEN_ABS
  | TOKEN_ACOS
  | TOKEN_ASIN 
  | TOKEN_ATAN 
  | TOKEN_BLENGTH 
  | TOKEN_COS 
  | TOKEN_EXISTS 
  | TOKEN_EXP 
  | TOKEN_FORMAT 
  | TOKEN_HIBOUND 
  | TOKEN_HIINDEX 
  | TOKEN_LENGTH 
  | TOKEN_LOBOUND 
  | TOKEN_LOINDEX 
  | TOKEN_LOG 
  | TOKEN_LOG2 
  | TOKEN_LOG10 
  | TOKEN_NVL 
  | TOKEN_ODD 
  | TOKEN_ROLESOF 
  | TOKEN_SIN 
  | TOKEN_SIZEOF 
  | TOKEN_SQRT 
  | TOKEN_TAN 
  | TOKEN_TYPEOF 
  | TOKEN_USEDIN 
  | TOKEN_VALUE 
  | TOKEN_VALUE_IN 
  | TOKEN_VALUE_UNIQUE;

primary:
    literal
  | qualifiable_factor primary1;
  
primary1:	
    %empty
  | qualifier primary1;

literal:
	binary_literal
  | logical_literal 
  | real_literal
  | string_literal;

logical_literal:
	TOKEN_FALSE 
  | TOKEN_TRUE
  | TOKEN_UNKNOWN;

binary_literal:
	TOKEN_BINARY_LITERAL;

string_literal:
	simple_string_literal;

simple_string_literal:
	TOKEN_SIMPLE_STRING_LITERAL {
		//std::cout << $1 << std::endl;
	}
;
 	
real_literal:
	integer_literal
  | TOKEN_REAL_LITERAL
	{
		//std::cout << "Real literal: " << $1 << std::endl;
	};

integer_literal:
	TOKEN_INTEGER_LITERAL
	{
		int v = atoi($1);
		integers.push(v);
	};

qualifier:
	attribute_qualifier
  | group_qualifier
  | index_qualifier;
	
index_qualifier:
	TOKEN_SQUARE_BRACKET_OPEN index_1 TOKEN_SQUARE_BRACKET_CLOSE
  | TOKEN_SQUARE_BRACKET_OPEN index_1 TOKEN_COLON index_2 TOKEN_SQUARE_BRACKET_CLOSE;

index_1:
	index;

index_2:
	index;

index:
	numeric_expression;
	
qualifiable_factor:
	attribute_ref
  | constant_factor
  | function_call
  | general_ref
  | population;

population:
	entity_ref;

general_ref:
	parameter_ref 
  | variable_ref

parameter_ref:
	parameter_id;

parameter_id:
	TOKEN_SIMPLE_ID;

variable_ref:
	variable_id;

variable_id:
	TOKEN_SIMPLE_ID;

function_call:
	built_in_function function_call1
  | function_ref function_call1;

function_call1:
	%empty
  | actual_parameter_list;

function_ref:
	function_id;

function_id:
	TOKEN_SIMPLE_ID;

actual_parameter_list:
	 TOKEN_BRACKET_OPEN actual_parameter_list1 TOKEN_BRACKET_CLOSE;

actual_parameter_list1:
	%empty
 | parameter 
 | parameter TOKEN_COMMA actual_parameter_list1;
  
parameter:
	expression;

constant_factor:
	built_in_constant
  | constant_ref;

constant_ref:
	constant_id;

constant_id:
	TOKEN_SIMPLE_ID;

built_in_constant:
    TOKEN_PI
  |	TOKEN_SELF {
		$$ = new Self();
    }
  | TOKEN_QUESTION_MARK
	{
		integers.push(999999);
	};
	
underlying_type:
	concrete_types
  | constructed_types;

constructed_types:
	enumeration_type
  | select_type;

select_type:
	TOKEN_SELECT select_list
	{
		types.push(oip::eType::Select);
	};

select_list:
	TOKEN_BRACKET_OPEN named_types select_list2 TOKEN_BRACKET_CLOSE;

select_list2:
    %empty
  | TOKEN_COMMA named_types select_list2;

named_types:
	TOKEN_SIMPLE_ID
	{
		auto a = makeReferenceCounted<EntityAttributeTypeNamedType>();
		a->name = $1;
		attribute_types.push(a);
		
		select_named_types.push($1);
	};

enumeration_type:
	TOKEN_ENUMERATION TOKEN_OF enumeration_items
	{
		types.push(oip::eType::Enumeration);
	};

enumeration_items:
	TOKEN_BRACKET_OPEN enumeration_id enumeration_items2 TOKEN_BRACKET_CLOSE;

enumeration_items2:
	%empty
  | TOKEN_COMMA enumeration_id enumeration_items2;

enumeration_id:
	TOKEN_SIMPLE_ID
	{
		enum_ids.push($1);
	};

aggregation_types:
	array_type
  | bag_type 
  | list_type 
  | set_type;

array_type:
	TOKEN_ARRAY bound_spec TOKEN_OF array_type1 array_type2 instantiable_type
	{
		types.push(oip::eType::Array);
	};

array_type1:
	%empty
	| TOKEN_OPTIONAL;

array_type2:
	%empty
	| TOKEN_UNIQUE;

bag_type:
	TOKEN_BAG bag_type1 TOKEN_OF instantiable_type;

bag_type1:
	%empty
  | bound_spec;

list_type:
	TOKEN_LIST list_type1 TOKEN_OF list_type2 instantiable_type
	{
		types.push(oip::eType::List);
	};

list_type1:
	%empty
  | bound_spec;

list_type2:
	%empty
	| TOKEN_UNIQUE;

set_type:
	TOKEN_SET bound_spec TOKEN_OF instantiable_type
	{
		types.push(oip::eType::Set);
	};

concrete_types:
	aggregation_types
  | simple_types
  | type_ref;

simple_types:
    TOKEN_BINARY
    {
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::Binary;
		attribute_types.push(a);

		types.push(oip::eType::Binary);
		ids.push("BINARY");
	}
  | TOKEN_BINARY TOKEN_BRACKET_OPEN TOKEN_INTEGER_LITERAL TOKEN_BRACKET_CLOSE
	{
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::Binary;
		int width_spec = atoi($3);
		a->width_spec = width_spec;
		attribute_types.push(a);

		types.push(oip::eType::Binary);
		ids.push("BINARY");
	}
  | TOKEN_BOOLEAN
	{
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::Boolean;
		attribute_types.push(a);

		types.push(oip::eType::Boolean);
		ids.push("BOOLEAN");
	}
  |	TOKEN_INTEGER
	{
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::Integer;
		attribute_types.push(a);

		types.push(oip::eType::Integer);
		ids.push("INTEGER");
	}
  | TOKEN_LOGICAL
	{
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::Logical;
		attribute_types.push(a);

		types.push(oip::eType::Logical);
		ids.push("LOGICAL");
	}
  | TOKEN_NUMBER
	{
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::Number;
		attribute_types.push(a);

		types.push(oip::eType::Number);
		ids.push("NUMBER");
	}
  | TOKEN_REAL
    {
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::Real;
		attribute_types.push(a);

		types.push(oip::eType::Real);
		ids.push("REAL");
	}
  | string_type;

string_type:
	TOKEN_STRING
	{
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::String;
		attribute_types.push(a);

		types.push(oip::eType::String);
		ids.push("STRING");
	}
  | TOKEN_STRING width_spec
	{
		auto a =  makeReferenceCounted<EntityAttributeSimpleType>();
		a->type = eType::String;
		attribute_types.push(a);

		types.push(oip::eType::String);
		ids.push("STRING");
	};
	
instantiable_type:
	concrete_types
  | entity_ref;

bound_spec:
	TOKEN_SQUARE_BRACKET_OPEN lower_bound TOKEN_COLON upper_bound TOKEN_SQUARE_BRACKET_CLOSE
	{
		bound2 = integers.top();
		integers.pop();
		bound1 = integers.top();
		integers.pop();
	};

lower_bound:
  numeric_expression;

upper_bound:
  numeric_expression;

aggregate_initializer:
	TOKEN_SQUARE_BRACKET_OPEN aggregate_initializer1 TOKEN_SQUARE_BRACKET_CLOSE {
		//std::cout << "aggregate_initializer" << std::endl;
	}
;

aggregate_initializer1:
  %empty
  | element
  | element TOKEN_COMMA aggregate_initializer1;

element:
	expression
  | expression TOKEN_COLON repetition;

repetition:
	numeric_expression;

numeric_expression:
	simple_expression;

width:
	numeric_expression;

width_spec:
	TOKEN_BRACKET_OPEN width TOKEN_BRACKET_CLOSE;
  | TOKEN_BRACKET_OPEN width TOKEN_BRACKET_CLOSE TOKEN_FIXED;

//logical_type:
//	TOKEN_LOGICAL;

entity_decl:
	entity_head entity_body TOKEN_END_ENTITY TOKEN_SEMICOLON
	{
		oip::Schema::getInstance().addEntity(currentEntity);
		currentEntity = Entity();
		g_hasParent = false;

		clear(attribute_types);
	};

entity_head:
	TOKEN_ENTITY entity_id TOKEN_SEMICOLON
	{
		std::string entityName = entity_ids.top();
		entity_ids.pop();
		
		currentEntity.setName(entityName);
	}
  | TOKEN_ENTITY entity_id subsuper TOKEN_SEMICOLON
  	{
		std::string entityName = entity_ids.top();
		entity_ids.pop();

		currentEntity.setName(entityName);
				
		if(g_hasParent)
			currentEntity.setParentEntity(g_parentName);
	};

entity_id:
	TOKEN_SIMPLE_ID
	{
		entity_ids.push($1);
	}

subsuper:
    supertype_constraint
  | subtype_declaration
  | supertype_constraint subtype_declaration;

supertype_constraint:
	supertype_rule
  | abstract_supertype_declaration;

supertype_rule:
	TOKEN_SUPERTYPE subtype_constraint;

subtype_constraint:
	TOKEN_OF TOKEN_BRACKET_OPEN supertype_expression TOKEN_BRACKET_CLOSE;

supertype_expression:
	supertype_factor
  | one_of;

one_of:
	TOKEN_ONEOF TOKEN_BRACKET_OPEN supertype_expression one_of2 TOKEN_BRACKET_CLOSE;

one_of2:
    %empty
  | TOKEN_COMMA supertype_expression one_of2;

supertype_factor:
	supertype_term;

supertype_term:
	entity_ref;

subtype_declaration:
	TOKEN_SUBTYPE TOKEN_OF TOKEN_BRACKET_OPEN TOKEN_SIMPLE_ID TOKEN_BRACKET_CLOSE
	{
		//std::cout << "Subtype: " << ($4) << std::endl;
		g_parentName = ($4);
		g_hasParent = true;
	}

entity_ref:
	TOKEN_SIMPLE_ID
	{
		ids.push($1);
	};

entity_body:
	%empty
  | entity_body1 entity_body2 entity_body3 entity_body4 entity_body5;

entity_body1:
	%empty
  | explicit_attr entity_body1;

entity_body2:
	%empty
  | derive_clause;

entity_body3:
	%empty
  | inverse_clause;

entity_body4:
	%empty
  | unique_clause;

entity_body5:
	%empty
  | where_clause;

derive_clause:
	TOKEN_DERIVE derived_attr derive_clause1;

derive_clause1:
	%empty
  | derived_attr derive_clause1;

derived_attr:
	attribute_decl TOKEN_COLON parameter_type TOKEN_ASSIGNMENT expression TOKEN_SEMICOLON
	{
		//std::cout << attribute_ids.top() << std::endl;
	};
	

unique_clause:
	TOKEN_UNIQUE unique_rule TOKEN_SEMICOLON unique_clause1;

unique_clause1:
	%empty
  | unique_rule TOKEN_SEMICOLON unique_clause1 ;

unique_rule:
	rule_label_id TOKEN_COLON referenced_attribute unique_rule1
  | referenced_attribute unique_rule1;

unique_rule1:
	%empty
  | TOKEN_COMMA referenced_attribute unique_rule1;

referenced_attribute:
	attribute_ref 
  | qualified_attribute;

rule_label_id:
	TOKEN_SIMPLE_ID	{
		$$ = new RuleLabelIdentifier($1);
	}
;

inverse_clause:
	TOKEN_INVERSE inverse_attr inverse_clause2;

inverse_clause2:
	%empty
  | inverse_attr inverse_clause2;

inverse_attr:
	attribute_decl TOKEN_COLON inverse_attr1 entity_ref TOKEN_FOR attribute_ref inverse_attr4 TOKEN_SEMICOLON;

inverse_attr1:
	%empty
  | inverse_attr2 inverse_attr3 TOKEN_OF;

inverse_attr2:
	TOKEN_SET
  | TOKEN_BAG;

inverse_attr3:
	%empty
  | bound_spec;

inverse_attr4:
	%empty
  | entity_ref TOKEN_PERIOD;
	
attribute_ref:
	attribute_id;

explicit_attr:
	 attribute_decl explicit_attr1 TOKEN_COLON TOKEN_OPTIONAL parameter_type TOKEN_SEMICOLON
	 {
		EntityAttribute att;
		att.name = attribute_ids.top();
		att.optional = true;
		att.type = attribute_types.top();
		attribute_types.pop();

		auto iterator = att.type;

		while (attribute_types.size() >= 2)
		{
			assert(attribute_types.top()->getType() == oip::eEntityAttributeParameterType::eGeneralizedType);

			if(attribute_types.top()->getType() == oip::eEntityAttributeParameterType::eGeneralizedType)	{
				auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
				p->elementType = attribute_types.top();		
				attribute_types.pop();

				iterator = p->elementType;
			}
		}

		if(attribute_types.size() >= 1) {
			assert(iterator->getType() == oip::eEntityAttributeParameterType::eGeneralizedType);
			auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
			p->elementType = attribute_types.top();		
			attribute_types.pop();
		}

		currentEntity.addAttribute(att);
	 }
   | attribute_decl explicit_attr1 TOKEN_COLON parameter_type TOKEN_SEMICOLON
   	 {
		EntityAttribute att;
		att.name = attribute_ids.top();
		att.optional = false;
		att.type = attribute_types.top();
		attribute_types.pop();

		auto iterator = att.type;

		while (attribute_types.size() >= 2)
		{
			assert(attribute_types.top()->getType() == oip::eEntityAttributeParameterType::eGeneralizedType);

			if(attribute_types.top()->getType() == oip::eEntityAttributeParameterType::eGeneralizedType)	{
				auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
				p->elementType = attribute_types.top();		
				attribute_types.pop();

				iterator = p->elementType;
			}
		}

		if(attribute_types.size() >= 1) {
			assert(iterator->getType() == oip::eEntityAttributeParameterType::eGeneralizedType);
			auto p = std::static_pointer_cast<EntityAttributeGeneralizedType>(iterator);
			p->elementType = attribute_types.top();		
			attribute_types.pop();
		}

		currentEntity.addAttribute(att);
	 }
   ;

explicit_attr1:
	%empty
  | TOKEN_COMMA attribute_decl;

parameter_type:
	generalized_types
	{
		auto a =  makeReferenceCounted<EntityAttributeGeneralizedType>();
		attribute_types.push(a);
						
		if(entityAttributeContainerTypes.size() >= 1) {
			a->containerType = entityAttributeContainerTypes.top();
			clear(entityAttributeContainerTypes);	
		}
	}
  | named_types
  |	simple_types;

generalized_types:
	aggregate_type
  | general_aggregation_types
  | generic_entity_type
  | generic_type;

aggregate_type:
	TOKEN_AGGREGATE TOKEN_OF parameter_type
  | TOKEN_AGGREGATE TOKEN_COLON type_label TOKEN_OF parameter_type;

generic_entity_type:
	TOKEN_GENERIC_ENTITY
  | TOKEN_GENERIC_ENTITY TOKEN_COLON type_label;

generic_type:
	TOKEN_GENERIC TOKEN_COLON type_label
  | TOKEN_GENERIC;

type_label:
	type_label_id;
//  | type_label_ref;

type_label_id:
	TOKEN_SIMPLE_ID;

//type_label_ref:
//	type_label_id;

general_aggregation_types:
	general_array_type 
  | general_bag_type 
  | general_list_type 
  | general_set_type;

general_array_type:
	TOKEN_ARRAY general_array_type1 TOKEN_OF general_array_type2 general_array_type3 parameter_type
	{
		entityAttributeContainerTypes.push(eEntityAttributeContainerType::Array);
	};

general_array_type1:
	%empty
  | bound_spec;

general_array_type2:
	%empty
  | TOKEN_OPTIONAL;

general_array_type3:
	%empty
  | TOKEN_UNIQUE;

general_bag_type:
	TOKEN_BAG TOKEN_OF parameter_type
	{
		entityAttributeContainerTypes.push(eEntityAttributeContainerType::Bag);
	}
  | TOKEN_BAG bound_spec TOKEN_OF parameter_type
  	{
		entityAttributeContainerTypes.push(eEntityAttributeContainerType::Bag);
	};

general_list_type:
	TOKEN_LIST general_list_type1 TOKEN_OF general_list_type2 parameter_type
	{
		entityAttributeContainerTypes.push(eEntityAttributeContainerType::List);
	};

general_list_type1:
	%empty
  | bound_spec;

general_list_type2:
	%empty
  | TOKEN_UNIQUE;

general_set_type:
	TOKEN_SET TOKEN_OF parameter_type
	{
		entityAttributeContainerTypes.push(eEntityAttributeContainerType::Set);
	}
  | TOKEN_SET bound_spec TOKEN_OF parameter_type
    {
		entityAttributeContainerTypes.push(eEntityAttributeContainerType::Set);
	};

attribute_decl:
	attribute_id
	{
		//std::cout << attribute_ids.top() << std::endl;
	}
  | redeclared_attribute;

redeclared_attribute:
	qualified_attribute;

qualified_attribute:
	TOKEN_SELF group_qualifier attribute_qualifier
	{
		//std::cout << "qualified_attribute: " << ids.top() << "." << attribute_ids.top() << std::endl;

		currentEntity.addQualifiedAttribute(ids.top(), attribute_ids.top());
		//currentEntity.addSelfDerivedAttribute(ids.top(), attribute_ids.top());
	};

group_qualifier:
	TOKEN_BACKSLASH entity_ref;

attribute_qualifier:
	TOKEN_PERIOD attribute_ref;

attribute_id:
	TOKEN_SIMPLE_ID
	{
		attribute_ids.push($1);
	}

enumeration_reference:
	enumeration_reference1 enumeration_ref;

enumeration_reference1:
	%empty
  | type_ref TOKEN_PERIOD;

enumeration_ref:
	enumeration_id;

type_ref:
	type_id;

type_id:
	TOKEN_SIMPLE_ID
	{
		types.push(oip::eType::Unknown);
		ids.push($1);
	};

abstract_supertype_declaration:
	TOKEN_ABSTRACT TOKEN_SUPERTYPE subtype_constraint
  | TOKEN_ABSTRACT TOKEN_SUPERTYPE;

subtype_constraint:
	TOKEN_OF TOKEN_BRACKET_OPEN supertype_expression TOKEN_BRACKET_CLOSE;

supertype_expression:
	supertype_factor;

supertype_factor:
	supertype_term;

supertype_term:
	entity_ref
  | one_of
  | TOKEN_BRACKET_OPEN supertype_expression TOKEN_BRACKET_CLOSE;

rule_decl:
	rule_head algorithm_head rule_decl1 where_clause TOKEN_END_RULE TOKEN_SEMICOLON
	{
		clear(attribute_types);
	};

rule_decl1:
	%empty
  | stmt rule_decl1;

rule_head:
	TOKEN_RULE rule_id TOKEN_FOR TOKEN_BRACKET_OPEN entity_ref rule_head1 TOKEN_BRACKET_CLOSE TOKEN_SEMICOLON;

rule_head1:
	%empty
  | TOKEN_COMMA entity_ref rule_head1;

rule_id:
	TOKEN_SIMPLE_ID;