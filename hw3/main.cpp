#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 1024

using namespace std;

struct Task {
    char **args;
    char *in_file;
    char *out_file;
    int background;
    Task *next;
} *g_task;

struct ChildGroup {
    pid_t leader_pid;
    ChildGroup *next;
} *g_group;
pid_t g_front_group;

struct CStrList {
    char *str;
    CStrList *next;
};

char g_buffer[BUF_SIZE];

static void get_command();
static void parse_task_relation(char *command);
static void execute_task();

int main(int argc, char** args) {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    while (true) {
        putchar('$');
        get_command();
        execute_task();
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
        parse_task_relation(g_buffer);
    }
    else {
        puts("");
        exit(0);
    }
}

static void parse_task_fields(Task *task,char *command) {
        CStrList str_list;
        CStrList *prev = &str_list;
        CStrList *cstr;
        char *strtok_context;
        char *tok = strtok_r(command, " ", &strtok_context);
        int count = 0;
        int redir_in = 0;
        int redir_out = 0;

        if (tok) do {
            if (redir_in){
                task->in_file = tok;
                redir_in = redir_out = 0;
                continue;
            }
            if (redir_out){
                task->out_file = tok;
                redir_in = redir_out = 0;
                continue;
            }
                
            if (strcmp(tok, "<") == 0) {
                redir_in = 1;
                continue;
            } else if (strcmp(tok, ">") == 0) {
                redir_out = 1;
                continue;
            } else if (strcmp(tok, "&") == 0) {
                task->background = 1;
                break;
            }
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
        task->args = args;
}
void parse_task_relation(char * buffer){
    Task *prev_cmd = NULL;
    char *strtok_context;

    char *tok = strtok_r(buffer, "|", &strtok_context);
    do {
        Task *cmd = new Task();
        if (prev_cmd == NULL) // g_task is NULL too
            g_task = prev_cmd = cmd;
        else
            prev_cmd->next = cmd;

        parse_task_fields(cmd, tok);
        prev_cmd = cmd;
    } while (tok = strtok_r(NULL, "|", &strtok_context));
}
void execute_task(){
    int prev_pipefd[2] = {-1,-1};
    int group_id = 0;
    while (g_task) {
        int pipefd[2];
        pipe(pipefd);
        pid_t child_pid = fork();

        // meaningful only for parent
        if (group_id == 0) {
            group_id = child_pid;
            if (!g_task->background)
                g_front_group = group_id;
        }
        // set child group in both parent and child
        setpgid(child_pid, group_id);

        if (child_pid == 0) { // is child
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            // command pipeline
            if (prev_pipefd[0] != -1) { // not first command
                if (dup2(prev_pipefd[0], STDIN_FILENO) == -1)
                    perror("dup2 to stdin");
                close(prev_pipefd[0]);
                close(prev_pipefd[1]);
            }

            if (g_task->next) { // not last command
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                    perror("dup2 to stdout");
                close(pipefd[0]);
                close(pipefd[1]);
            }
            else {
                close(pipefd[0]);
                close(pipefd[1]);
            }

            // file redirect
            if (g_task->in_file) {
                int fd = open(g_task->in_file, O_RDONLY);
                if (fd != -1) {
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
                else {
                    perror("open file");
                }
            }
            if (g_task->out_file) {
                int fd = open(g_task->out_file, O_WRONLY|O_CREAT, 0666);
                if (fd != -1) {
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
                else {
                    perror("open file");
                }
            }

            execvp(g_task->args[0], g_task->args);
            perror("exec");
            exit(1);
        }
        // is parent
        if (prev_pipefd[0] != -1) {
            close(prev_pipefd[0]);
            close(prev_pipefd[1]);
        }
        prev_pipefd[0] = pipefd[0];
        prev_pipefd[1] = pipefd[1];

        // remove processed command
        Task *next_command = g_task->next;
        delete g_task;
        g_task = next_command;
    }
    close(prev_pipefd[0]);
    close(prev_pipefd[1]);

    if (group_id == g_front_group) {
        // just work when no job control
        tcsetpgrp(STDERR_FILENO, g_front_group);
        while (pid_t pid = waitpid(-g_front_group, NULL, 0)) {
            if (pid == -1)
                break;
        }
        g_front_group = 0;
        tcsetpgrp(STDERR_FILENO, getpgrp());
    }
}
