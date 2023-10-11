#include "main.h"

/**
 * This basically contains
 * the path to search
 */

char *get_path(char *command) /* It takes the tokenized string as argument and calls it a command*/
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path); /* Not to modify the original environment variable*/

    char *dir = strtok(path_copy, ":");

    /* A loop to iterate and concatenate*/
    while (dir != NULL)
    {
        char *full_path = malloc(strlen(dir) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);
        printf("Constructed full_path: %s\n", full_path);

        /* To see what is in full_path*/
        printf("Checking path: %s\n", full_path);

        /* Check if the file exists */
        if (access(full_path, F_OK) != -1)
        {
            printf("File found\n");
            free(path_copy); /* Free path_copy since it's not used anymore */
            return full_path; /* Return the full path */
        }

        free(full_path);
        dir = strtok(NULL, ":"); /* Proceed to the next directory*/
    }

    printf("File is not found in any directory\n");
    free(path_copy);
    /* if no executable is found, it returns NULL*/
    return NULL;
}
