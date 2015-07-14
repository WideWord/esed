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
 	
	char element;

	//we go until extracting line
	fprintf(stderr,"#1");
	for (int i=0; i!=cmd->lineNumber-1; i++)
	{
		fgets (&element, 1, in);
		for (int number_of_element=0; element!='\n'; number_of_element++)
			fprintf (out, "%c", element);
			fgets (&element, 1, in);
		fprintf (out, "\n");
	}

	//we "miss" extracting line
	fprintf(stderr,"#2");
	fgets (&element, 1, in);
	for (int number_of_element=0; element!='\n'; number_of_element++)
		fgets (&element, 1, in);

	//we go until EOF
	fprintf(stderr,"#3");
	fgets (&element, 1, in);
	while (element!=EOF)
	{
		fprintf (out, "%c", element);
		fgets (&element, 1, in);
	}
	fprintf(stderr,"#4");
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	fprintf(stderr, "Insert near pattern operation not implemented, pattern = '%s', string = '%s', below = '%d'\n", cmd->pattern, cmd->string, cmd->below);
}
