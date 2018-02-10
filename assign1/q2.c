//Q2

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80
#define ARRAY_SIZE 5

void removeLastChar(char *s)
{
     int length;
     length = strlen(s);//Get length of string
     s[length - 1] = '\0';//Set next to last char to null
     return;
}

void update(char **historyArray, char *historyCommand) {
	// shift everything in historyArray back by 1
	int i;
	for (i = 0; i < ARRAY_SIZE; i++) {
		historyArray[i] = historyArray[i+1];
	}
	// add most recent command into history
	//printf("nn");
	//strcpy(historyArray[ARRAY_SIZE-1], historyCommand);
	//printf(&historyCommand);
	historyArray[ARRAY_SIZE-1] = historyCommand;
	int k;
	for (k = 0; k < 5; k++) {
		printf("array %d: %s\n", k, historyArray[k]);
	}
}

// prints out the contents of historyArray in reverse order
void history(char **historyArray, int *histCount) {
	int i; int j = *histCount;
	if (*histCount < ARRAY_SIZE) {
		for(i = (ARRAY_SIZE - *histCount); i < ARRAY_SIZE; i++) {
			printf("%d. %s\n", j, historyArray[i]);
			j--;
		}
	} else {
		for(i = ARRAY_SIZE - 1; i >= 0; i--) {
			printf("%d. %s\n", j, historyArray[i]);
			j--;
		}
	}
}

int parse(char *buffer, char **args, int *child_with_parent) {
	const char s[2] = " ";
   	char *token;
	int count = 0;
   	token = strtok(buffer, s);
   	while (token != NULL) {
   		*args = token;
   		*args++;
   		count++;
   		token = strtok(NULL, s);
   	}
   	
   	// remove the newline character from last element
   	*args--;
   	token = *args;
   	const char t[2] = "\n";
   	token = strtok(*args, t);
   	if (*token == '&') {
   		*child_with_parent = 1;
   		// end like a c-string
   		*args = '\0';
   		count--;
   	} else {
   		*args = token;
   		*args++;
   		*args = '\0'; // end like  a c-string
   	}
   	return count;
}

int main(void) {
	char *args[MAX_LINE/2 +1]; // array of strings
	int should_run = 1;
	int child_with_parent = 0;
	char buffer[MAX_LINE]; // strings
	char historyCommand[MAX_LINE];
	char *historyArray[ARRAY_SIZE] = {"1", "2", "3", "4", "5"};
	int histCount = 0;	

	pid_t pid;
	do {
		printf("osh>");
		fgets(buffer, sizeof(buffer), stdin);
		fflush(stdout);
		strcpy(historyCommand, buffer); // save command to store into history later
		removeLastChar(historyCommand); // removes \n at the end of string
		if (buffer[0] == '\n') { // loop back
			continue;
		}
		int count;
		count = parse(buffer, args, &child_with_parent);
		if (strcmp(args[0], "exit") == 0) {
			should_run = 0;
		} else {
	/**
	* (1) Fork child process using fork()
	* (2) The child process will invoke execvp()
	* (3) if command included &, parent will invoke wait()
	*/	
			// shift everything in historyArray back by 1
			int i;
			for (i = 0; i < ARRAY_SIZE; i++) {
				historyArray[i] = historyArray[i+1];
			}
			// add most recent command into history
			//historyArray[ARRAY_SIZE-1] = historyCommand;
			historyArray[ARRAY_SIZE-1] = malloc(strlen(historyCommand) + 1);
			strcpy(historyArray[ARRAY_SIZE-1], historyCommand);
			int k;
			for (k = 0; k < 5; k++) {
				printf("array %d: %s\n", k, historyArray[k]);
			}
			histCount++;

			pid = fork();
			if (pid == 0) { // child process
				if (strcmp(args[0], "history") == 0) { 
					// history requested
					if (histCount == 0) {
						printf("No command in the history\n");
					} else {
						history(historyArray, &histCount);
					}
					should_run = 0;
					continue;
				} else {
					// regular command
					// update array
					//update(historyArray, historyCommand);
					//histCount++;
					// run command
					int status = execvp(args[0], args);
					if (status == -1) {
						printf("command not found\n");
						should_run = 0;
						continue;
					}
				}
			} else {	// parent process
				if (child_with_parent == 0)
					wait();
			}
		}
	} while (should_run);
	return 0;
}

