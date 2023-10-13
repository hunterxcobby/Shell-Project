#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *get_path(char *command);
extern char **environ;

/* For builtin*/
void builtin_cd(char *args);
void builtin_exit(void);
void err_msg(char *command);

#endif 

