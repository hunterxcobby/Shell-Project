#include "main.h"

/**
 * This contains codes
 * for searching through
 * the path 
 */

char *get_path(char *command) /* It takes the tokenized string as argument and calls it a command*/
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path); /* Not to modify the original environment variable*/
    /* Copy of the command*/
    char command_path[1024];
    char *dir = strtok(path_copy, ":");

    /* A loop to iterate and concatenate*/
    while (dir != NULL)
    {
        /* Create a copy of the directory*/
        strcpy(command_path, dir);
        if (command_path[strlen(command_path)- 1] != '/')
        {
            strcat(command_path, "/");
        }

        /* Concatenate the path with the command*/
        strcat(command_path,command);
        
        /* Check if the file exists and is executable */
        if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
        {
            free(path_copy); /* Free path_copy since it's not used anymore */
            return (strdup(command_path)); /* Return the full path */
        }

        /*free(path_copy);*/
        dir = strtok(NULL, ":"); /* Proceed to the next directory*/
    }

    free(path_copy);
    /* if no executable is found, it returns NULL*/
    return (command);
}