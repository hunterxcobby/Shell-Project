#include "main.h"

int main(void)
{
	/* Declare variables*/
	char *line = NULL;
	size_t len = 0;
	int characters_read;

	/* Sring tokenization*/
	char *delimiters = " \n"; /* Set an empty string as a delimiter*/
	char *tokens;
	char *line_argument[1024];
	int pid;
	/*char **args;*/


	while (1)
	{
		/* Prompt*/
		write(1, "Shell$ ", 7);

		/* Getting users input*/
		characters_read = getline(&line, &len, stdin);

		if (characters_read == -1)
		{
			perror("Error reading input");
			return(-1);
		}
		else if (characters_read == 1)
		{
			continue;
		}
		else 
		{
			int idx = 0;

			/* Process the input using string tokenization*/
			tokens = strtok(line, delimiters);

			/* We use a null terminating tokenization*/
			while(tokens != NULL)
			{
				line_argument[idx] = tokens;
				tokens = strtok(NULL, delimiters);
				idx++;
			}
			line_argument[idx] = NULL;


			pid = fork();

			if (pid == -1) /* Changed from 1 to -1*/
			{
				perror("Fork failed");
				free(line);
				return(-1);
			}
			else if (pid == 0)
			{
				/*pid_t pid;*/
				char *cmdPath = get_path(line_argument[0]);
				if (cmdPath != NULL) 
				{
					/**
					 * Here we can check if the token is a built-in command like (i.e, cd, exit)
					 * And handle it separately  
					 */

					/* If it is not a built in command, we execute it*/

					/* This is the child process*/


					/* We execute the command with execve*/
					execve(cmdPath, line_argument, environ);

					/* Check if evecve fails*/
					perror("Execve failed");
					free(line); /* Free allocated memory */
					exit(1);
				}

			}
			else
			{
				/* This is the parent process*/

				int status;
				waitpid(pid, &status, 0);

				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				{
					printf("\nChild process %d exited with non-zero status %d\n", pid, WEXITSTATUS(status));
				}
			}

		}/* loop ends end*/

	}
	free(line); /* Free allocated memory */
	return(0);
}


