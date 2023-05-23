#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string.h>

extern char **environ;

void print_prompt(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void sigint_handler(int sig);
char **command_parser(char *line, const char *delimiter);
char *get_path();
int set_path(const char *new_path);
int add_to_path(const char *dir);
char *custom_strtok(char *str, const char *delim);
char *custom_strdup(const char *s);
int builtin_env(void);
int handle_exit(char **args);
int handle_cd(char **args);
int handle_command_separator(char *progname, char *line);
void custom_sprintf(char *str, const char *format, int number);
char *custom_strncpy(char *destination, const char *source, size_t num);
int handle_logical_operators(char *progname, char *line);


#endif /* MAIN_H */
