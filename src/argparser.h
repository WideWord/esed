#pragma once
#include "commands.h"

esedArgs * esedParseArgs(int argc, char ** argv);
void esedFreeArgs(esedArgs * args);
