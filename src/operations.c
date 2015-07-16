#include "operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

void esedReplace(FILE * in, FILE * out, esedReplaceCommand * cmd) {
    char currentChar;
    char buffer[1024];
    
    int currFromIdx = 0;
    int currBufIdx = 0;
    
    while((currentChar = fgetc(in)) != EOF){
        if(currentChar == cmd->from[currFromIdx++]){
            buffer[currBufIdx++] = currentChar;
            buffer[currBufIdx] = 0;
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
	char buffer[512];
	int lineCtr = 1;
	int lineToInsert = cmd->lineNumber;

	char * InsertedLine = malloc((strlen(cmd->string) + 1) * sizeof(char));
	strcpy(InsertedLine, cmd->string);
	InsertedLine[strlen(InsertedLine)] = '\n';
	
	for (;;) {
		size_t readedSize = fread(buffer, 1, sizeof(buffer), in);

		if (readedSize == 0) {
			if (lineToInsert > lineCtr) {
				fputs(InsertedLine, out);
				break;
			}
			else {
				break;
			}
		}

		int lineBegin = 0; 
		int i;
		for (i = 0; i < readedSize; ++i) {
				if (buffer[i] == '\n') {
				
					if (lineToInsert != 1)  {
						if (lineCtr != lineToInsert-1) {
							fwrite(buffer + lineBegin, 1, i - lineBegin + 1, out);
						}
						else	{
							fwrite(buffer + lineBegin, 1, i - lineBegin + 1, out);
							fputs(InsertedLine, out);
						}		
					}
					else {
						if (lineCtr != lineToInsert) {
							fwrite(buffer + lineBegin, 1, i - lineBegin + 1, out);
						}
						else {
							fputs(InsertedLine, out);
							fwrite(buffer + lineBegin, 1, i - lineBegin + 1, out);
							
						}
					}
					lineBegin = i + 1;
					lineCtr++;
				}
		}
        if (lineBegin != readedSize) {
			fwrite(buffer + lineBegin, 1, readedSize - lineBegin, out);
		}
	}	
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

int esedTestStringWithPatternSearchChar(char * string, const char * pat, int strnum, int patnum);

int esedTestStringWithPatternSearchStar(char * string, const char * pat, int strnum, int starnum){
	int status = 0;
	int found_letter = 0;
	if(pat[starnum+1]=='*'){
		starnum++;
	}
	if(starnum == strlen(pat) - 1){
		return 1;
	}
	while(string[strnum] != '\n'){
	if(pat[starnum+1]=='*'){
		starnum++;
	}
	if(pat[starnum + 1] == string[strnum] || pat[starnum + 1] == '?'){
		found_letter = 1;
		status =  esedTestStringWithPatternSearchChar(string, pat, strnum, starnum + 1);
		if(status == 1){
			return status;
		}
	}
	strnum++;
}
	return 0;
}


int esedTestStringWithPatternSearchChar(char * string, const char * pat, int strnum, int patnum) {
	while(string[strnum] != '\n'){
		if(string[strnum] == pat[patnum] || pat[patnum] == '?'){        
			if((patnum == strlen(pat) - 1) && (strlen(string) - 2 > strnum)){ //check for the end of pattern
				return 0;
			}
			strnum++;
			patnum++;
		}
		else if(pat[patnum] == '*'){
			return esedTestStringWithPatternSearchStar(string, pat, strnum, patnum);
		}
		else return 0;
	}
	if(patnum == strlen(pat)){
		return 1;
	}
	else for(int i = patnum; i < strlen(pat); i++){ // 
		if(pat[i] != '*'){ //
			return 0; //
		}
	}
	return 1;
}


int esedTestStringWithPattern(const char * pattern, char * string) {
	int status = esedTestStringWithPatternSearchChar(string, pattern, 0, 0);
	return status;
}

void esedInsertLineNearPattern(FILE * in, FILE * out, esedInsertLineNearPatternCommand * cmd) {
	char str[1024];
	int status = 0; // 1 - found pattern, 0 - not
	for(;;) {
		fgets(str,1024,in);
        if (feof(in)) break;
		status = esedTestStringWithPattern(cmd->pattern, str);
		if (status == 1){
			if (cmd->below == 0){
				fputs(cmd->string, out);
				fputc('\n', out);
				fputs(str, out);
			} else {
				fputs(str, out);
				fputs(cmd->string, out);
				fputc('\n', out);

            }
		} else {
            fputs(str, out);
        }
	} 

}
