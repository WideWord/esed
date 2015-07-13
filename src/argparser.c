#include "argparser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

esedArgs * esedParseArgs(int argc, char ** argv) {

	esedArgs * args = malloc(sizeof(esedArgs));
	args->inputFile = NULL;
	args->outputFile = NULL;
	args->command = NULL;

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-i") == 0) {
			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: file name expected after -i\n");
				exit(1);
			}
			args->inputFile = argv[i];
		} else if (strcmp(argv[i], "-o") == 0) {
			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: file name expected after -o\n");
				exit(1);
			}
			args->outputFile = argv[i];
		} else if (strcmp(argv[i], "--replace") == 0) {
			if (args->command != NULL) {
				fprintf(stderr, "You can specify only one command\n");
				exit(1);
			}

			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: from to expected after --replace\n");
				exit(1);
			}
			const char * from = argv[i];
			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: from to expected after --replace\n");
				exit(1);
			}
			const char * to = argv[i];

			esedReplaceCommand * command = malloc(sizeof(esedReplaceCommand));
			command->from = from;
			command->to = to;
			command->command.type = ESED_COMMAND_REPLACE;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "--insert") == 0) {
			if (args->command != NULL) {
				fprintf(stderr, "You can specify only one command\n");
				exit(1);
			}

			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: line number and string expected after --insert\n");
				exit(1);
			}
			const char * lineNumStr = argv[i];
			int lineNumber = atoi(lineNumStr);
			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: line number and string expected after --insert\n");
				exit(1);
			}
			const char * string = argv[i];

			esedInsertLineCommand * command = malloc(sizeof(esedInsertLineCommand));
			command->lineNumber = lineNumber;
			command->string = string;
			command->command.type = ESED_COMMAND_INSERT_LINE;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "--remove") == 0) {
			if (args->command != NULL) {
				fprintf(stderr, "You can specify only one command\n");
				exit(1);
			}

			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: line number expected after --remove\n");
				exit(1);
			}
			const char * lineNumStr = argv[i];
			int lineNumber = atoi(lineNumStr);

			esedRemoveLineCommand * command = malloc(sizeof(esedRemoveLineCommand));
			command->lineNumber = lineNumber;
			command->command.type = ESED_COMMAND_REMOVE_LINE;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "--insert-above") == 0) {
			if (args->command != NULL) {
				fprintf(stderr, "You can specify only one command\n");
				exit(1);
			}

			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: pattern and string expected after --insert-above\n");
				exit(1);
			}
			const char * pattern = argv[i];

			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: pattern and string expected after --insert-above\n");
				exit(1);
			}
			const char * string = argv[i];

			esedInsertLineNearPatternCommand * command = malloc(sizeof(esedInsertLineNearPatternCommand));
			command->pattern = pattern;
			command->string = string;
			command->below = 0;
			command->command.type = ESED_COMMAND_INSERT_LINE_NEAR_PATTERN;

			args->command = (esedCommand *)command;
		} else if (strcmp(argv[i], "--insert-below") == 0) {
			if (args->command != NULL) {
				fprintf(stderr, "You can specify only one command\n");
				exit(1);
			}

			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: pattern and string expected after --insert-below\n");
				exit(1);
			}
			const char * pattern = argv[i];

			++i;
			if (i == argc) {
				fprintf(stderr, "Invalid args: pattern and string expected after --insert-below\n");
				exit(1);
			}
			const char * string = argv[i];

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
