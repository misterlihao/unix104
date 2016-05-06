#include <cstdio>

using namespace std;
void init() {
#include "init.inc"
}
void wait_for_command() {
#include "wait_for_command.inc"
}
void process_command() {
#include "process_command.inc"
}

int main(int argc, int argv) {
    init();
    while (true) {
        wait_for_command();
        process_command();
    }
}
