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
	for (int i(0); i!=cmd->lineNumber-1; i++)
	{
		fgets (in, "%c", element);
		for (int number_of_element(0); element!='\n'; number_of_element++)
			fprintf (out, "%c",element);
			fgets (in, "%c", element);
		fprintf (out, "\n");
	}

	//we "miss" extracting line
	fgets (in, "%c", element);
	for (int number_of_element(0); element!='\n'; number_of_element++)
		fgets (in, "%c", element);

	//we go until EOF
	fgets (in, "%c", element);
	while (element!=EOF)
	{
		fprintf (out, "%c", element);
		fgets (in, "%c", element);
	}
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	fprintf(stderr, "Insert near pattern operation not implemented, pattern = '%s', string = '%s', below = '%d'\n", cmd->pattern, cmd->string, cmd->below);
}
