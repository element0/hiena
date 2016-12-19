Production Instruction
======================



## Examples (Psuedo Code) ##

	[1] = source "file://~/test/hiena/test.divine"
	[2] = fragment (12-24) [1]
	[3] = fragment (45-78) [1]
	[4] = transform strip_indents [3] > buffer
	[5] = fragment (7-12) [4]
	[6] = fragment (13-26) [4]
	[7] = transform strip_indents [6] > buffer
	[8] = fragment (1-5) [7]


## Grammar ##

	production 	: source_production
				| fragment_production
				| transform_production
				;


	production_instruction
		: production_script
		;

	production_script
		: production_expression
		| production_script production_expression
		;

	production_expression
		: production_node
		| production_node production_op production_node
		| production_expression production_op production_node
