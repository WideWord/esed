
#include <stdio.h>
#include "argparser.h"
#include "operations.h"
#include <stdlib.h>



int main(int argc, char ** argv) {

	esedArgs * args = esedParseArgs(argc, argv);

	if (args->helpInfoRequested) {
		printf("Usage: esed [-i input_file] [-o output_file] command\n");
		printf("\tcommand may be:\n");
		printf("\t\treplace <from> <to>\n");
		printf("\t\tinsert <at_line> <string_to_insert>\n");
		printf("\t\tremove <line>\n");
		printf("\t\tinsert-below <pattern> <string_to_insert>\n");
		printf("\t\tinsert-above <pattern> <string_to_insert>\n");
		exit(0);
	}

	if (args->command == NULL) {
		fprintf(stderr, "Command not provided, use 'esed -h' for help\n");
		exit(1);
	}

	FILE * in;
	if (args->inputFile != NULL) {
		in = fopen(args->inputFile, "r");
		if (in == NULL) {
			fprintf(stderr, "Input file '%s' does not exist\n", args->inputFile);
			exit(1);
		}
	} else {
		in = stdin;
	}

	FILE * out;
	if (args->outputFile != NULL) {
		out = fopen(args->outputFile, "w");
	} else {
		out = stdout;
	}

	esedOperation operations[] = {
		NULL,
		(esedOperation)esedReplace,
		(esedOperation)esedInsertLine,
		(esedOperation)esedRemoveLine,
		(esedOperation)esedInsertLineNearPattern
	};

	esedOperation operation = operations[args->command->type];
	operation(in, out, args->command);

	esedFreeArgs(args); 

	return 0;
}