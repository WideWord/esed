#pragma once

typedef enum {
	ESED_COMMAND_UNKNOWN = 0,
	ESED_COMMAND_REPLACE = 1,
	ESED_COMMAND_INSERT_LINE = 2,
	ESED_COMMAND_REMOVE_LINE = 3,
	ESED_COMMAND_INSERT_LINE_NEAR_PATTERN = 4
} esedCommandType;

typedef struct {
	esedCommandType type;
} esedCommand;

typedef struct {
	const char * inputFile;
	const char * outputFile;
	esedCommand * command;
} esedArgs;

typedef struct {
	esedCommand command;
	const char * from;
	const char * to;
} esedReplaceCommand;

typedef struct {
	esedCommand command;
	int lineNumber;
	const char * string;
} esedInsertLineCommand;

typedef struct {
	esedCommand command;
	int lineNumber;
} esedRemoveLineCommand;

typedef struct {
	esedCommand command;
	const char * pattern;
	const char * string;
	int below;
} esedInsertLineNearPatternCommand;
