#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

using namespace std;

struct Command {
    char **args;
    Command *next;
} *g_command;

struct ChildGroup {
    pid_t leader_pid;
    ChildGroup *next;
} *g_group;
pid_t g_front_group;

struct CStrList {
    char *str;
    CStrList *next;
};

struct Pipe {
    int pipe[2];
    Pipe *prev;
} *g_pipe;

char g_buffer[BUF_SIZE];

static void get_command();
static void parse_command_relation(char *command);
static void execute_command();

int main(int argc, char** args) {
    while (true) {
        putchar('$');
        get_command();
        execute_command();
    }
}

void get_command(){
    if (fgets(g_buffer, BUF_SIZE, stdin)) {
        char *last_char = &g_buffer[strlen(g_buffer)-1];
        if (last_char == g_buffer)
            return;
        if (*last_char != '\n') {
            fprintf(stderr, "command too long\n");
            return;
        }
        *last_char = '\0';
        parse_command_relation(g_buffer);
    }
    else {
        puts("");
        exit(0);
    }
}

static char **parse_command_args(char *command) {
        CStrList str_list;
        CStrList *prev = &str_list;
        CStrList *cstr;
        char *strtok_context;
        char *tok = strtok_r(command, " ", &strtok_context);
        int count = 0;
        if (tok) do {
            count++;
            cstr = new CStrList();
            cstr->str = tok;
            prev->next = cstr;
            prev = cstr;
        } while (tok = strtok_r(NULL, " ", &strtok_context));
        
        char **args = (char**)calloc((count+1), sizeof(char*));
        cstr = str_list.next;
        for (int i = 0; i < count;i++){
            args[i] = cstr->str;
            prev = cstr;
            cstr = cstr->next;
            delete prev;
        }
        return args;
}
void parse_command_relation(char * buffer){
    Command *cmd;
    char *strtok_context;

    char *tok = strtok_r(buffer, "|", &strtok_context);
    do {
        cmd = new Command();
        if (g_command == NULL)
            g_command = cmd;
        else
            g_command->next = cmd;

        cmd->args = parse_command_args(tok);

    } while (tok = strtok_r(NULL, "|", &strtok_context));
}
void execute_command(){
    while (g_command) {
        Pipe *_pipe_ = new Pipe();
        _pipe_->prev = g_pipe;
        g_pipe = _pipe_;
        pipe(_pipe_->pipe);

        pid_t child_pid = fork();

        // meaningful only for parent
        if (g_front_group == 0)
            g_front_group = child_pid;
        // set child group in both parent and child
        setpgid(child_pid, g_front_group);

        if (child_pid == 0) {
            if (_pipe_->prev) {
                if (dup2(_pipe_->prev->pipe[0], STDIN_FILENO) == -1)
                    perror("dup2 to stdin");
            }
            if (g_command->next) {
                if (dup2(_pipe_->pipe[1], STDOUT_FILENO) == -1)
                    perror("dup2 to stdout");
            }
            execvp(g_command->args[0], g_command->args);
            perror("exec");
        }

        // remove processed command
        Command *next_command = g_command->next;
        delete g_command;
        g_command = next_command;
    }

    // close and delete pipes
    while (g_pipe) {
        Pipe *p = g_pipe->prev;
        close(g_pipe->pipe[0]);
        close(g_pipe->pipe[1]);
        delete g_pipe;
        g_pipe = p;
    }

    while (pid_t pid = waitpid(0 - g_front_group, NULL, 0)) {
        if (pid == -1)
            break;
        fprintf(stderr, "child %d stopped.\n", pid);
    }
    g_front_group = 0;

}
