#include "main.h"

/**
 * This basically contains
 * the path to search
 */

char *get_path(char *command) /* It takes the tokenized string as argument and calls it a command*/
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path); /* Not to modify the original environment variable*/
    /* Copy of the command*/
    char command_path[1024];
    char *dir = strtok(path_copy, ":");

    printf("This is the command%s\n", command);
    /* A loop to iterate and concatenate*/
    while (dir != NULL)
    {
        /*printf("This is the dir%s\n", dir);*/
        /* Create a copy of the directory*/
        strcpy(command_path, dir);
        if (command_path[strlen(command_path)- 1] != '/')
        {
            strcat(command_path, "/");
        }

        /*char *full_path = malloc(strlen(dir) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);*/
        /*printf("Constructed full_path: %s\n", full_path);*/

        /* Concatenate the path with the command*/
        strcat(command_path,command);
        
        /*printf("This is the command path%s\n", command_path);*/
        /* Check if the file exists */
        if (access(command_path, X_OK) == 0)
        {
            free(path_copy); /* Free path_copy since it's not used anymore */

            printf("This command path in the function%s\n", command_path);
            return (strdup(command_path)); /* Return the full path */
        }

        /*free(path_copy);*/
        dir = strtok(NULL, ":"); /* Proceed to the next directory*/
    }

    printf("File is not found in any directory\n");
    free(path_copy);
    /* if no executable is found, it returns NULL*/
    return NULL;
}