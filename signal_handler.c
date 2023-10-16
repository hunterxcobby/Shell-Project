#include "main.h"

/* This is for handling signals*/

/* CRTL + C*/
void signal_handler(int signal)
{
    char *prompt = "\nShell$ ";

    (void)signal; /* To prevent the ununsed variable error*/
    write(1, prompt, strlen(prompt));
    /* Clear the buffer*/
    fflush(stdout);
}