#include "main.h"

int main(void)
{
	/* Declare variables*/
	char *line = NULL;
	size_t len = 0;
	int characters_read;

	/* Sring tokenization*/
	char *delimiters = " "; /* Set an empty string as a delimiter*/
	char *tokens;
    char *line_argument[1024];

	/* For the fork*/
	/*pid_t pid;*/

	/*while (1) Start an infinite loop*/ 
	/* Prompt*/
	write(1, "Shell$ ", 7);

	/* Getting users input*/
	characters_read = getline(&line, &len, stdin);

	if (characters_read == -1)
	{
		perror("Error reading input");
		return(-1);
	}
	/*else if (characters_read == 1)
	  {
	  continue;
	  }*/
	else 
	{
        int idx = 0;
		/*pid_t pid;*/
		/* Process the input using string tokenization*/
		tokens = strtok(line, delimiters);
		printf("This is the token=====>>>%s\n", tokens);
        
        while(tokens != NULL)
        {
            line_argument[idx] = tokens;
            tokens = strtok(NULL, delimiters);
            idx++;
        }
        line_argument[idx] = NULL;

        idx = 0;
		while (line_argument[idx] != NULL)
		{
			pid_t pid;
			char *cmdPath = get_path(line_argument[idx]);
			printf("line =====>>>%s\n", line);
			printf("This is the token now=====>>>%s\n", tokens);
			printf("command path is %s\n", cmdPath);
			if (cmdPath != NULL) 
			{
				printf("Executing command: %s\n", cmdPath);
				/**
				 * Here we can check if the token is a built-in command like (i.e, cd, exit)
				 * And handle it separately  
				 */

				/* If it is not a built in command, we execute it*/
				pid = fork();

				if (pid == -1) /* Changed from 1 to -1*/
				{
					perror("Fork failed");
					free(line);
					return(-1);
				}
				else if (pid == 0)
				{

					/* This is the child process*/
					char **args = malloc(2 * sizeof(char *));/* Do not forget to free args*/
					if (args == NULL)
					{
						perror("Memory allocation failed");
						free(line);
						exit(EXIT_FAILURE);
					}

					args[0] = cmdPath;
					args[1] = NULL;

					/* We execute the command with execve*/
					execve(args[0], args, environ);

					/* Check if evecve fails*/
					perror("Execve failed");
					free(args); /* Free allocated memory */
					free(line); /* Free allocated memory */
					exit(1);
				}

			}
			else
			{
				/* This is the parent process*/
            
				int status;
				waitpid(1, &status, 0);/* We will wait for the child to finish*/

				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				{
					printf("\nChild process %d exited with non-zero status %d\n", 1, WEXITSTATUS(status));
				}
			}

			idx++;

		}
		free(line); /* Free allocated memory */
	}
	return(0);
}


