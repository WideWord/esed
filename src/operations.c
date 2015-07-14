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
	fprintf(stderr, "Remove operation not implemented, lineNumber = '%d'\n", cmd->lineNumber);
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	char str[50];
	int sym = 0;
	fgets(str,sizeof(str),in);
	int patsym = 0;
	int status = 0;
	int l = strlen(str);
	int i = strlen(cmd->pattern);
	if(str == NULL){
		printf("1 \n");
	}
	fgets(str,sizeof(str),in);
	if(str == NULL){
		printf("1 \n");
	}
	printf("%d \n", i);
	while(str != NULL){
		fgets(str,sizeof(str),in);
		//if(strlen(str - 1 != strlen(cmd->pattern)){
		//		status = 0;
		//	}
		//else
		 while(str[sym] != '\n'){
			if(cmd->pattern[patsym]==str[sym]){
				status = 1;
				sym++;
				patsym++;
			}
			else if(cmd->pattern[patsym] == '?'){
				sym++;
				patsym++;
			}
			//else if(cmd->pattern[patsym] == '*'){
			//	while(cmd->pattern[patsym] != currentStr[sym]){

			//	}
		}
		if(status == 1){
			if(cmd->below == 0){
				fputs(cmd->string, out);
				fputs(str, out);
			}
			else{
				fputs(str, out);
				fputs(cmd->string, out);
			}
		}
		else {fputs(str, out);}
		fgets(str,sizeof(str),in);
	}

}
