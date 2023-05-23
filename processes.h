#ifndef PROCESSES_H
#define PROCESSES_H

#include <sys/types.h>
#include <string.h>

pid_t create_process(void);
int execute_command(char *command, char **args, char *program_name);
char *resolve_path(char *command);
int wait_for_process(pid_t pid);
void handle_signal(int signal);
int terminate_process(pid_t pid);

#endif
