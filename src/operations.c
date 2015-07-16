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


int search_star(char * string, const char * pat, int strnum, int starnum, int status){
	int ssnum;
	if(starnum == strlen(pat) - 1){
		return 1;
	}
	while(string[strnum] != '\n'){
		strnum++;
		if(string[strnum] == pat[starnum + 1]){
			status = search_char(string, pat, strnum, starnum + 1, status);

			if(status == 0){
				strnum++;
				status = search_star(string, pat, strnum, starnum, status);
			}
			else {
				return status;
			}
		}
	}
	return status;
}


int search_char(char * string, const char * pat, int strnum, int patnum, int status){
	while(string[strnum] != '\n'){
		if(string[strnum] == pat[patnum] || pat[patnum] == '?'){
			if(patnum == strlen(pat)-1 && string[strnum + 1] != '\n'){
				return 0;
			}
			status = 1;
			patnum++;
			strnum++;
		}
		else{
			if(pat[patnum] == '*'){
				status = search_star(string, pat, strnum, patnum, status);
				return status;
			}
			else{
				return 0;
			}
		}
	}
	return status;
}


int pattern_search(char * string, const char * pat){
	//if(strlen(string) - 1 < strlen(pat)){
	//	return 0;
	//}
	//else {
		int status = search_char(string, pat, 0, 0, 0);
		return status;
	//}
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	char str[50];
	int sym = 0;
	fgets(str,strlen(str),in);
	int status = 0;
	if(str == NULL){
		printf("1 \n");
	}
	fgets(str,strlen(str),in);
	while(!feof(in)){
		//if(strlen(str - 1 != strlen(cmd->pattern)){
		//		status = 0;
		//	}
		//else
		status = pattern_search(str, cmd->pattern);
		printf("%d\n", status);
		 /*while(str[sym] != '\n'){
			if(cmd->pattern[patsym]==str[sym]){
				status = 1;
				sym++;
				patsym++;
			}
			else if(cmd->pattern[patsym] == '?'){
				sym++;
				patsym++;
			}
			sym++;
			patsym++;
			//else if(cmd->pattern[patsym] == '*'){
			//	while(cmd->pattern[patsym] != currentStr[sym]){

			//	}
		}*/
		if(status == 1){
			if(cmd->below == 0){
				fputs(cmd->string, out);
				fputc('\n', out);
				fputs(str, out);
				fputc('\n', out);
			}
			else{
				fputs(str, out);
				fputs(cmd->string, out);
				fputc('\n', out);
				}
		}
		else {fputs(str, out);}

		fgets(str,sizeof(str),in);
	}

}
