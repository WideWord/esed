#include "operations.h"
#include <stdio.h>

void esedReplace(FILE * in, FILE * out, esedReplaceCommand * cmd) {
	fprintf(stderr, "Replace operation not implemented, from = '%s', to = '%s'\n", cmd->from, cmd->to);
}

void esedInsertLine(FILE * in, FILE * out, esedInsertLineCommand * cmd) {
	fprintf(stderr, "Insert operation not implemented, lineNumber = '%d', to = '%s'\n", cmd->lineNumber, cmd->string);
}

void esedRemoveLine(FILE * in, FILE * out, esedRemoveLineCommand * cmd) {
	//fprintf(stderr, "Remove operation not implemented, lineNumber = '%d'\n", cmd->lineNumber);
 	
	char element;

	//we go until extracting line
	for (int i=0; i!=cmd->lineNumber-1; i++)
	{
		fgets (element, 1, in);
		for (int number_of_element=0; element!='\n'; number_of_element++)
			fprintf (out, "%c",element);
			fgets (element, 1, in);
		fprintf (out, "\n");
	}

	//we "miss" extracting line
	fgets (element, 1, in);
	for (int number_of_element=0; element!='\n'; number_of_element++)
		fgets (element, 1, in);

	//we go until EOF
	fgets (element, 1, in);
	while (element!=EOF)
	{
		fprintf (out, "%c", element);
		fgets (element, 1, in);
	}
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	fprintf(stderr, "Insert near pattern operation not implemented, pattern = '%s', string = '%s', below = '%d'\n", cmd->pattern, cmd->string, cmd->below);
}
