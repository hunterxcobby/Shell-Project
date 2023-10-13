#include "main.h"

/* This file used for built-in commands */

/* When the user enters cd*/
void builtin_cd(char *args)
{
  /* If the user does not pass any argument*/
  if (args == NULL)
  {
    char *home = getenv("HOME");
    
    if(home == NULL)
    {
        perror("cd: HOME envrionment variable is not set\n");
    }
    else
    {
        /* Take the user home*/
        if (chdir(home) != 0)
        {
            perror("could not change directory");
        }
    }
  }
  else
  {
     /* If the user adds an argument*/
     if (chdir(args) != 0)
        {
            perror("could not change directory");
        }
  }
}

void builtin_exit(void)
{
    printf("\nExiting shell...\n");
    /* Before it exists, it can sleep*/
    sleep(2);
    exit(0); /* Successfully exit*/
}