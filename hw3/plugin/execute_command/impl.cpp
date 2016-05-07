#include <cstdio>

#include "header.h"
using namespace std;

static 

void execute_command_process_command(EventData *data) {
    parse_into_command_group((char*)data->field["command"]);
}
