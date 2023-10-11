#include "main.h"

int main(void)
{
	/* Declare variables*/
	char *line = NULL;
	size_t len = 0;
	int characters_read;

	/* Sring tokenization*/
	char *delimiters = " "; /* Set an empty string as a delimiter*/
	char *token;

	printf("shell$ ");
	/* Getting users input*/
	characters_read = getline(&line, &len, stdin);

	if (characters_read == -1)
	{
		perror("Error reading input");
		return(-1);
	}
	else
	{
		/* Process the input using string tokenization*/
		token = strtok(line, delimiters);
		while(token != NULL)
		{
			/**
			 * Here we can check if the token is a built-in command like (i.e, cd, exit)
			 * And handle it separately  
			 */

			/* If it is not a built in command, we execute it*/
			pid_t pid = fork();

			if (pid == -1) /* Changed from 1 to -1*/
			{
				perror("Fork failed");
				free(line);
				return(-1);
			}
			else if (pid == 0)
			{
				/* This is the child process*/
				char *cmdPath = get_path(token);
				char **args = malloc(2 * sizeof(char *));/* Do not forget to free args*/
				if (args == NULL)
				{
					perror("Memory allocation failed");
					free(line);
					exit(EXIT_FAILURE);
				}

				args[0] = token;
				args[1] = NULL;

				printf("command path is %s", cmdPath);

				if (cmdPath == NULL)
				{
					perror("Command not found");
                    free(args); /* Free allocated memory */
                    free(line); /* Free allocated memory */
                    exit(EXIT_FAILURE);
				}

				/* We execute the command with execve*/
				execve(cmdPath, args, environ);

				/* Check if evecve fails*/
				perror("Execve failed");
                free(args); /* Free allocated memory */
                free(line); /* Free allocated memory */
                exit(EXIT_FAILURE);
			}
			else
			{
				/* This is the parent process*/

				int status;
				waitpid(pid, &status, 0);/* We will wait for the child to finish*/

				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				{
					printf("\nChild process %d exited with non-zero status %d\n", pid, WEXITSTATUS(status));
				}
			}

			token = strtok(NULL, delimiters);

		}
		free(line); /* Free allocated memory */
		return(0);
	}
}
