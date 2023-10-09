#include "main.h"

int main(void)
{
    /* Declare variables*/
    int characters_read;
    char *line = NULL;
    size_t len = 0;

/* String tokenization*/
    char *delimiters = " "; /* Set an empty string as a delimiter*/
    char *token;

    /* Prompt*/
    write(1, "Shell$ ", 7);

    /* Getting the user's input*/
    characters_read = getline(&line, &len, stdin);
    if (characters_read == -1)
    {
        perror("Error reading input");
        return (-1);
    }
    else 
    {
         /* Process the input using string tokenization*/
         token = strtok(line, delimiters);

         while(token != NULL)
         {
            /* Here we can check if the token is built-in command like (i.e, cd,)
             * handle it separately or internally
             */

            /* If it is not built-in, we EXECUTE!!!*/
            /* This is where to fork*/
            pid_t pid = fork();

            if (pid == -1)
            {
                perror("Fork failed");
                return (-1);
            }
            else if (pid == 0)
            {
                /* This is the child process */
                char *cmdPath = path_check(token); /*Assume we have a function to find the commands path*/
                if (cmdPath == NULL)
                {
                    perror("Command not found");
                    exit(1); /* Exited with an error*/
                }
                
                /* We execute the program now with execve*/
                execve(cmdPath, &token, __environ);
                
                /* Check if execve fails*/
                if (execve(cmdPath, &token, __environ) == -1 )
                {
                    perror("Failed to execute the program");
                    exit(EXIT_FAILURE); /* Indicate the command could not be executed*/
                }
                
            }
         }

            return(0);
    }

}
