#include "argparser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ESED_ARGS_GET_STRING(Var, ErrorMsg) \
	++i; \
	if (i == argc) { \
		fprintf(stderr, ErrorMsg); \
		exit(1); \
	} \
	Var = argv[i];

#define ESED_ARGS_GET_INT(Var, ErrorMsg) \
	++i; \
	if (i == argc) { \
		fprintf(stderr, ErrorMsg); \
		exit(1); \
	} \
	Var = atoi(argv[i]);

#define ESED_ARGS_COMMAND_GUARD \
	if (args->command != NULL) { \
		fprintf(stderr, "You can specify only one command\n"); \
		exit(1); \
	}

esedArgs * esedParseArgs(int argc, char ** argv) {

	esedArgs * args = malloc(sizeof(esedArgs));
	args->inputFile = NULL;
	args->outputFile = NULL;
	args->command = NULL;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-i") == 0) {
			ESED_ARGS_GET_STRING(args->inputFile, "Invalid args: file name expected after -i\n");
		} else if (strcmp(argv[i], "-o") == 0) {
			ESED_ARGS_GET_STRING(args->outputFile, "Invalid args: file name expected after -o\n");
		} else if (strcmp(argv[i], "replace") == 0) {
			ESED_ARGS_COMMAND_GUARD
			ESED_ARGS_GET_STRING(const char * from, "Invalid args: from to expected after --replace\n");
			ESED_ARGS_GET_STRING(const char * to, "Invalid args: from to expected after --replace\n");

			esedReplaceCommand * command = malloc(sizeof(esedReplaceCommand));
			command->from = from;
			command->to = to;
			command->command.type = ESED_COMMAND_REPLACE;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "insert") == 0) {
			ESED_ARGS_COMMAND_GUARD
			ESED_ARGS_GET_INT(int lineNumber, "Invalid args: line number and string expected after --insert\n");
			ESED_ARGS_GET_STRING(const char * string, "Invalid args: line number and string expected after --insert\n")

			esedInsertLineCommand * command = malloc(sizeof(esedInsertLineCommand));
			command->lineNumber = lineNumber;
			command->string = string;
			command->command.type = ESED_COMMAND_INSERT_LINE;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "remove") == 0) {
			ESED_ARGS_COMMAND_GUARD
			ESED_ARGS_GET_INT(int lineNumber, "Invalid args: line number expected after --remove\n");

			esedRemoveLineCommand * command = malloc(sizeof(esedRemoveLineCommand));
			command->lineNumber = lineNumber;
			command->command.type = ESED_COMMAND_REMOVE_LINE;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "insert-above") == 0) {
			ESED_ARGS_COMMAND_GUARD
			ESED_ARGS_GET_STRING(const char * pattern, "Invalid args: pattern and string expected after --insert-above\n");
			ESED_ARGS_GET_STRING(const char * string, "Invalid args: pattern and string expected after --insert-above\n");

			esedInsertLineNearPatternCommand * command = malloc(sizeof(esedInsertLineNearPatternCommand));
			command->pattern = pattern;
			command->string = string;
			command->below = 0;
			command->command.type = ESED_COMMAND_INSERT_LINE_NEAR_PATTERN;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "insert-below") == 0) {
			ESED_ARGS_COMMAND_GUARD
			ESED_ARGS_GET_STRING(const char * pattern, "Invalid args: pattern and string expected after --insert-below\n");
			ESED_ARGS_GET_STRING(const char * string, "Invalid args: pattern and string expected after --insert-below\n");

			esedInsertLineNearPatternCommand * command = malloc(sizeof(esedInsertLineNearPatternCommand));
			command->pattern = pattern;
			command->string = string;
			command->below = 1;
			command->command.type = ESED_COMMAND_INSERT_LINE_NEAR_PATTERN;

			args->command = (esedCommand *)command;
		} else {
			if (i == argc) {
				fprintf(stderr, "Unexpected %s, use 'esed -h' for help\n", argv[i]);
				exit(1);
			}
		}
	}

	return args;
}

void esedFreeArgs(esedArgs * args) {
	if (args->command) {
		free(args->command);
	}
	free(args);
}
