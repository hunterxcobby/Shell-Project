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
            printf("%s\n", token);
            token = strtok(NULL, delimiters);
         }
            return(0);
    }

}
