#ifndef __structures_h__
#define __structures_h__
#include <string>
#include <map>

struct Command {
char *file;
char **args;
};
struct EventData {
    // use void const for both const and nonconst data
    // try const_cast if data is not const and editing is needed
    std::map<std::string, void const*> field;
};
typedef void (*Callback)(EventData*);
#endif
