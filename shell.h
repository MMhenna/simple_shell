#ifndef _SHELL_
#define _SHELL_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>

/**
 * struct builtin_d - Defines the builtins functions.
 * @built: The name of the build in command.
 * @f: A pointer to the right builtin function.
 */

typedef struct builtin_d
{
        char *built;
        void (*f)(char *);
} builtin_t;

extern char **environ;

/* parsing.c */
void INThandler(int);
void parse_line(char , size_t, int, char *);
char **token_interface(char *, const char *, int);
char **tokenize(int, char *, const char *);
int count_token(char *, const char *);

/* assistant_functions.c */
int _strcmp(char *, char *);
char *_strdup(char *);
void print_str(char *, int);
int _putchar(char);
int str_len(char *);

/* helper_functions.c */
void double_free(char **);
void single_free(int, ...);
void error_printing(char *, int, char *);
void exec_error(char , int, char *);
/* built_in.c   */
void env_shell(char *);
void exit_shell(char *);
void (*check_built_ins(char *))(char *);
int built_in(char **, char *);

/* print_number.c*/
int print_number(int);

#endif
