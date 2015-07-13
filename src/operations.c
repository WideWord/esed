#include "operations.h"
#include <stdio.h>

void esedReplace(FILE * in, FILE * out, esedReplaceCommand * cmd) {
	fprintf(stderr, "Replace operation not implemented, from = '%s', to = '%s'\n", cmd->from, cmd->to);
}

void esedInsertLine(FILE * in, FILE * out, esedInsertLineCommand * cmd) {
	fprintf(stderr, "Insert operation not implemented, lineNumber = '%d', to = '%s'\n", cmd->lineNumber, cmd->string);
}

void esedRemoveLine(FILE * in, FILE * out, esedRemoveLineCommand * cmd) {
	fprintf(stderr, "Remove operation not implemented, lineNumber = '%d'\n", cmd->lineNumber);
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	fprintf(stderr, "Insert near pattern operation not implemented, pattern = '%s', string = '%s', below = '%d'\n", cmd->pattern, cmd->string, cmd->below);
}
