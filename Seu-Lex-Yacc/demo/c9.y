%token IF INT RETURN CONSTANT STRING_LITERAL IDENTIFIER

%start translation_unit
%%

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers IDENTIFIER '(' ')' compound_statement
	;

compound_statement
	: '{' '}'
	| '{' block_item_list '}'
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	;

declaration
	: declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: INT
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: IDENTIFIER
	| IDENTIFIER '=' assignment_expression
	;

assignment_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	;


%%
