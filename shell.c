#include "main.h"

void tatata(void);

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
			/* When the user presses CTRL + D*/
			if (feof(stdin))
			{
				builtin_exit();
			}
			else
			{
				perror("Error reading input\n");
				return(-1);
			}
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

			/**
			 * Here we can check if the token is a built-in command like (i.e, cd, exit)
			 * And handle it separately  
			 */

			if (strcmp(line_argument[0], "cd") == 0)
			{
				/* Call for our function*/
				builtin_cd(line_argument[1]);
			}
			else if(strcmp(line_argument[0], "exit")== 0)
			{
				/* We want to exit*/
				builtin_exit();
			}
			else
			{
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

					/* If it is not a built in command, we execute it*/

					/* This is the child process*/


					/* We execute the command with execve*/
					execve(cmdPath, line_argument, environ);

					/* Check if evecve fails*/
					err_msg(line_argument[0]);
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
			}
		}/* loop ends end*/

	}
	free(line); /* Free allocated memory */
	return(0);
}


