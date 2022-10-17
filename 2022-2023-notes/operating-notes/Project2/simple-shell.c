/**
Mason Manca
Dr.Zhang
CPSC 346
3 October 2022
Prjoect: Project 2—UNIX Shell and History Feature
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include<sys/wait.h>
#include <ctype.h>

#define MAX_LINE		80 /* 80 chars per line, per command, should be enough. */
#define MAX_COMMANDS	9 /* size of history */

char history[MAX_COMMANDS][MAX_LINE]; //the array used to store history commands.
char display_history[MAX_COMMANDS][MAX_LINE]; 
/*the array used for "printf" to display history nicely. Remove special characters like "\n" or "\0"*/

int command_count = 0;

void addtohistory(char inputBuffer[]) {

	int i = 0;
	// update array"history": add the command to history, strcpy(str1,str2);
	strcpy(history[(command_count - 1) % MAX_COMMANDS], inputBuffer);

	// update array"display_history": remove characters like '\n', '\0' in order to display nicely
	while (inputBuffer[i] != '\n' && inputBuffer[i] != '\0'){
		display_history[(command_count - 1) % MAX_COMMANDS][i] = inputBuffer[i];
		i++;
	}
	display_history[(command_count - 1) % MAX_COMMANDS][i] = '\0';
	return;
}

int setup(char inputBuffer[], char *args[],int *background)
{	
	
	//define your local varialbes here;
    int length,		/* # of characters in the command line */
	i,				/* loop index for accessing inputBuffer array */
	command_number,	/* index of requested command number */
	start_string,   // Index of the start of string
	string_arg = 0;     // argument to be added to the string
	bool new_string = true; // boolean for if new value exists

    /* read what the user enters on the command line */
	do {
		printf("osh>");
		fflush(stdout);
		length = read(STDIN_FILENO,inputBuffer,MAX_LINE); 
	}
	while (inputBuffer[0] == '\n'); 

    if (length == 0){
        exit(0);            /* end of user command stream */
	}

    if (length < 0){
		perror("error, bad command");
		exit(-1); // bad command, return -1  
    }

	if(inputBuffer[0] == '!'){

		if(command_count == 0){
			printf("No commands in history\n");
			return -1;
		}

		// statement for 2 !'s
		if (inputBuffer[1] == '!') {
			strcpy(inputBuffer, history[(command_count - 1 ) % MAX_COMMANDS]);
		}
		// statement for !#
		else{
			int num = atoi(&inputBuffer[1]);
			int max;

			if (command_count > MAX_COMMANDS){
				max = MAX_COMMANDS;
			}
			else{
				max = command_count;
			}
			if( num < 1 || num > max){
				printf("Command does not exist in history\n");
				return -1;
			}
			strcpy(inputBuffer, history[num-1]);
		}
	}
	length = strlen(inputBuffer);
	command_count++; 
	// fill in your code here Part II, add the following line for PartII
	addtohistory(inputBuffer);
	
    for (i = 0; i < length; i++) { 
		/* examine every character in the inputBuffer */
		
        switch (inputBuffer[i]){
			case ' ':
			case '\t' : /* argument separators */
				inputBuffer[i] = '\0';
				if(!new_string){
					args[string_arg] = &inputBuffer[start_string];
					new_string = true;
					string_arg++;
				}			
				break;
				
			case '\n':  /* should be the final char examined */
				//fill in your code here, set up the last item args[x] ==NULL;
				inputBuffer[i] = '\0';
				if(!new_string){
					args[string_arg] = &inputBuffer[start_string];
					string_arg++;
				}
				break;
				
	    	default :             /* some other character */
				 //fill in your code here, 
				if(new_string){
					if(inputBuffer[i] == '&'){
						*background = 1;
						break;
					}
					start_string = i;
					new_string = false;
				}

		}
	} /* end of switch */
		/* end of for */
	args[string_arg] = NULL;

	return 1;
}    

int main(void)
{
	//define your local variables here, at the beginning of your program. 
	char inputBuffer[MAX_LINE]; 	/* buffer to hold the command entered */
	int background;             	/* equals 1 if a command is followed by '&' */
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
	pid_t child;            		/* process id of the child process */
	
	

	int shouldrun = 1;
			
    while (shouldrun){  
	    /* Program terminates normally inside setup */
		background = 0;
		
		shouldrun = setup(inputBuffer,args,&background);

		if(strncmp(inputBuffer, "exit", 4) == 0){
			return 0;	
		}
		
		else if (strncmp(inputBuffer, "history", 7) == 0){
			int max;
			if(command_count < MAX_COMMANDS){
				max = command_count;
			}
			else{
				max = MAX_COMMANDS;
			}
			for(int i = max; i > 0; i--){
				printf("%d\t%s\n", i, display_history[i - 1]);
			}
			continue;
		}
	
		if (shouldrun) {
			/* creates a duplicate process! */
			child = fork();
			// pid<0  error
			if(child < 0){
				printf("Error running command!\n closing kernel..\n");
				return -1;
			}
			// pid == 0, it is the child process. use the system call execvp(args[0],args);
			else if (child == 0){
				execvp(args[0],args); 
			}
			// pid > 0, it is the parent. Here you need consider it is foreground or background
			else{
				if(!background){
					while(child != wait(NULL));
				}			
			}
		}
    }
	return 0;
}