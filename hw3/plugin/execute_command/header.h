#ifndef __plugin_execute_command_header_h__
#include "structures.h"

struct Command {
char *file;
char **args;
Command * next;
};

void execute_command_process_command(EventData*);
#define __plugin_execute_command_header_h__
#endif
