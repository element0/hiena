Dcel IO
=======

## Structure ##

	dcel_io
		dcel

	dcel
		production_node

	production_node
		buffer
		storage
		production_instruction


## Read Operation ##

Performed by the parser grammer.  A stack of buffers is generated, and the read request is returned by reading off the stack.

The parser grammer puts buffers onto the stack as they become available.

Variables:

	BUFSTACK_T bufferstack;

Grammer of the read operation:

	output_buf	: dcel buffer
				{ if this evaluates, we're done }
				| dcel storage
				{ if this evaluates, we're done }
				| dcel production
				{ otherwise, we parse the production }
				;
	
	production 	: source_production
				| fragment_production
				| transform_production
				;

	source_production
				: source_op source_address
				;
	
	fragment_production
				: fragment_op production_id fragment_bounds
				;

	transform_production
				: transform_op transform_command_script transform_end
				;
	
	transform_command_script
				: transform_command
				| transform_command_script cmdsep transform_command_line
				;

	transform_command
				: transform_command_id tranform_command_args
				;
	
	transform_command_args
				: transform_command_arg
				| transform_command_args argsep transform_command_arg
				;

	transform_command_arg
				: production_id
				| transform_command_parenthetical
				;

	transform_command_parenthetical
				: parenstart transform_command parenend
				;


