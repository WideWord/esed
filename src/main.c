
#include <stdio.h>
#include "argparser.h"
#include "operations.h"
#include <stdlib.h>
#include <execinfo.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "sighandlers.h"

#define TMPFNAMESUFFIX ".new"
extern char * tmpFname;

void segfault_handler(int sig);

int main(int argc, char ** argv) {        
        // Set up signal catching
        if(!setHandlers()){
            fprintf(stderr, "Error occured while setting up signal handlers. \n");
            exit(EXIT_FAILURE);
        }
        
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
			fprintf(stderr, "Can't open input file '%s'.\n", args->inputFile);
                        perror("Error occured while opening input file");
			exit(1);
		}
	} else {
		in = stdin;
	}

	FILE * out;
        char tmpFilename[512];
	if (args->outputFile != NULL) {
                // Open tmp file
                strcpy(tmpFilename, args->outputFile);
                strcat(tmpFilename, TMPFNAMESUFFIX);
                tmpFname = tmpFilename;
		out = fopen(tmpFilename, "w");
                if(out == NULL){
                    fprintf(stderr, "Can't open output file '%s'.\n", tmpFilename);
                    perror("Error occured while opening output file");
                    exit(EXIT_FAILURE);
                }
	} else {
		out = stdout;
	}

    /* Operation types described in src/operations.h */
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
        
        // Swap files
        if(args->outputFile != NULL){
            if(rename(tmpFilename, args->outputFile))
                perror("Error occured while swapping output file with tmp file");
        }

	return 0;
}