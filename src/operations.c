#include "operations.h"
#include <stdio.h>
#include <string.h>

void esedReplace(FILE * in, FILE * out, esedReplaceCommand * cmd) {
    char currentChar;
    char buffer[1024];
    
    int currFromIdx = 0;
    int currBufIdx = 0;
    
    while((currentChar = fgetc(in)) != EOF){
        if(currentChar == cmd->from[currFromIdx++]){
            buffer[currBufIdx++] = currentChar;
            buffer[currBufIdx] = NULL;
            if(currBufIdx == strlen(cmd->from)){
                fputs(cmd->to, out);
                currBufIdx = 0;
                currFromIdx = 0;
            }
        }
        else{
            if(currBufIdx > 0){
                fputs(buffer, out);
                currBufIdx = 0;
            }
            currFromIdx = 0;
            fputc(currentChar, out);
        }
    }
}

void esedInsertLine(FILE * in, FILE * out, esedInsertLineCommand * cmd) {
	fprintf(stderr, "Insert operation not implemented, lineNumber = '%d', to = '%s'\n", cmd->lineNumber, cmd->string);
}

void esedRemoveLine(FILE * in, FILE * out, esedRemoveLineCommand * cmd) {
	//fprintf(stderr, "Remove operation not implemented, lineNumber = '%d'\n", cmd->lineNumber);
 	
	char buffer[512];
	int lineCtr = 1;
	int lineToRemove = cmd->lineNumber;

	for (;;) {
		size_t readedSize = fread(buffer, 1, sizeof(buffer), in);

		if (readedSize == 0) break;

		int lineBegin = 0;

		for (int i = 0; i < readedSize; ++i) {
			if (buffer[i] == '\n') {
				if (lineCtr != lineToRemove) {
					fwrite(buffer + lineBegin, 1, i - lineBegin + 1, out);
				}
				lineBegin = i + 1;
				lineCtr++;
			}
		}

		if (lineBegin != readedSize && lineCtr != lineToRemove) {
			fwrite(buffer + lineBegin, 1, readedSize - lineBegin, out);
		}

	}
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	fprintf(stderr, "Insert near pattern operation not implemented, pattern = '%s', string = '%s', below = '%d'\n", cmd->pattern, cmd->string, cmd->below);
}
