#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <vector>
#include <map>

#include <unistd.h>

#include "events.h"
#include "structures.h"
#include "plugin_headers.h"

using namespace std;

map<int, vector<Callback> > event_callbacks;

int const BUFF_LEN_MAX = 128;

void register_event_or_crash(int event);
void register_callback(int event, Callback callback);
void generate_event(int event, EventData *data);

void init() {
#include "register_event.inc"
#include "register_callback.inc"

    generate_event(EVENT_INIT, NULL);
}

char *get_command() {
    char *buffer = (char *)malloc(BUFF_LEN_MAX*sizeof(char));
    if (fgets(buffer, BUFF_LEN_MAX, stdin)) {
        if (buffer[strlen(buffer)-1] == '\n')
            return buffer;
        fprintf(stderr, "command to long, only read %s\n", buffer);
    }

    free(buffer);
    return NULL;
}
void process_command(char* command) {
    EventData data;
    data.field["raw_command"] = command;
    generate_event(EVENT_BEFORE_COMMAND, &data);
    generate_event(EVENT_PROCESS_COMMAND, &data);
}

int main(int argc, char** argv) {
    init();
    while (true) {
        char* command = get_command();
        process_command(command);
    }
}

void register_event_or_crash(int event){
    if (event_callbacks.count(event) != 0) {
        fprintf(stderr, "error: event %d has been registered\n", event);
        exit(1);
    }
    event_callbacks[event] = vector<Callback>();
    printf ("event %d registered\n", event);
}
void register_callback(int event, Callback callback){
    event_callbacks[event].push_back(callback);
}
void generate_event(int event, EventData *data) {
    vector<Callback> const &callbacks = event_callbacks[event];
    for (auto iter = callbacks.begin(); iter != callbacks.end(); iter++) {
        (*iter)(data);
    }
}
