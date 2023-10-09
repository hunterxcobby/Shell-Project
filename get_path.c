#include "main.h"

/**
 * This basically contains
 * the path to search
*/

char *path_check(char *command) /* This takes the tokenized string as argument and calls it command*/
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);/* Not to modify the original environment variable*/

    /* THe tokenization*/
    char *dir = strtok(path_copy, ":");

    /* Create a loop to iterate*/
    while(dir != NULL)
    {
        char *full_path = malloc(strlen(dir) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);

        printf("full path is %s", full_path);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");/* Proceed to the next directory*/
    }
    free(path_copy);
    /* If no executable is found, we return NULL*/
    return(NULL);
}