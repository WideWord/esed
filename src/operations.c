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


int search_star(char * string, const char * pat, int strnum, int starnum){
	int status = 0;
	int found_letter = 0;
	if(starnum == strlen(pat) - 1){
		return 1;
	}
	while(string[strnum] != '\n'){
	if(pat[starnum+1]=='*'){
		starnum++;
	}
	if(pat[starnum + 1] == string[strnum] || pat[starnum + 1] == '?'){
		found_letter = 1;
		status =  search_char(string, pat, strnum, starnum + 1);
		if(status == 1){
			return status;
		}
	}
	strnum++;
}
	return 0;
}


int search_char(char * string, const char * pat, int strnum, int patnum){
	while(string[strnum] != '\n'){
		if(string[strnum] == pat[patnum] || pat[patnum] == '?'){        
			if((patnum == strlen(pat) - 1) && (strlen(string) - 2 > strnum)){ //check for the end of pattern
				return 0;
			}
			strnum++;
			patnum++;
		}
		else if(pat[patnum] == '*'){
			return search_star(string, pat, strnum, patnum);
		}
		else return 0;
	}
	if(patnum == strlen(pat)){
		return 1;
	}
	else{
		return 0;
	}
}


int pattern_search(char * string, const char * pat){
		int status = search_char(string, pat, 0, 0);
		return status;
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	char str[1024];
	int status = 0; // 1 - found pattern, 0 - not
	do{
		fgets(str,1024,in);
		status = pattern_search(str, cmd->pattern);
		if(status == 1){
			if(cmd->below == 0){
				fputs(cmd->string, out);
				fputc('\n', out);
				fputs(str, out);
			}
			else{
				fputs(str, out);
				fputc('\n', out);
				fputs(cmd->string, out);
				}
		}
		else {fputs(str, out);}
	}while(!feof(in));

}