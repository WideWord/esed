#pragma once
#include <stdio.h>
#include "commands.h"

typedef void (*esedOperation)(FILE * in, FILE * out, esedCommand * cmd);

void esedReplace(FILE * in, FILE * out, esedReplaceCommand * cmd);
void esedInsertLine(FILE * in, FILE * out, esedInsertLineCommand * cmd);
void esedRemoveLine(FILE * in, FILE * out, esedRemoveLineCommand * cmd);
void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd);
