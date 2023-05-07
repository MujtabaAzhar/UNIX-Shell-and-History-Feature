#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
char History[1024];
char *temp[64];
int counter=0;
void add_command_to_history(char **command )
{
	History[counter]=*command;
	counter++;
}
void print_history()
{
	int j;
	for(j=0;j<10;j++)
	{
		printf("%d\n", History[j]);
	}
	
}
void parse(char *line, char **argv)
{
	while (*line != '\0') 		
	{
		while (*line == ' ' || *line == '\t' || *line == '\n')
		*line++ = '\0'; 	/* replace white spaces with 0 */
		*argv++ = line; /* save the argument position */
		while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
		line++;
	}
	*argv = '\0';		
}

void execute(char **argv)
{
	pid_t pid;
	int status;
	if ((pid = fork()) < 0) 	
	{
		printf("Forking Child Process Failed\n");
		exit(1);
	}
	else if (pid == 0) 
	{ 						
		if (execvp(*argv, argv) < 0) 		
		{
			printf("exec Failed\n");
			exit(1);
		}
	}
	else		 
	{
		while (wait(&status) != pid);
	}
}

void main(void)
{
	char line[1024]; 		
	char *argv[64]; 		
	while (1) 
	{				
		printf("osh->");	
		gets(line); 
		printf("\n");
		parse(line, argv);			 
		if (strcmp(argv[0], "!!") == 0)
		{
		printf("\nUSER CALL FOR RECENT HISTORY !! \n");
		}
		if(strcmp(argv[0], "history") == 0)
		{
			print_history();
			printf("\nHISTORY FUNCTION IS CALLED\n");
		}
		if (strcmp(argv[0], "exit") == 0)		
		exit(0);
		add_command_to_history(argv);		
		execute(argv); 				
	}
}
