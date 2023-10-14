#include "main.h"

/* this is to print the erro message*/
void err_msg(char *command)
{
    char *err_msg;
    char *err_msg2;
    
    /* Display the error message*/
    /* If the command wasn't found*/
    err_msg = "Command '";
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    write(STDERR_FILENO, command, strlen(command));
    err_msg2 = "' not found\n";
    write(STDERR_FILENO, err_msg2, strlen(err_msg2));
    exit(EXIT_FAILURE); /*This goes back to the execve*/

}
