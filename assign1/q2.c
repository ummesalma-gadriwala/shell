//Q2

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80
#define ARRAY_SIZE 100

void history(char **historyArray, int *histCount) {
	int i;
	for(i = 0; i < *histCount; i++){
		//only prints the first char of the command
		printf("%d. %s\n", i, historyArray[i]);
	}
}

int parse(char *buffer, char **args, int *child_with_parent) {
	const char s[2] = " ";
   	char *token;
	int count = 0;
   	token = strtok(buffer, s);
   	//printf("command: ");
   	while (token != NULL) {
   		//printf("%s", token);
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
   	//printf("last char: %s\n", token);
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
	char *args[MAX_LINE/2 +1]; // pointer to the pointer to the first element of array
	int should_run = 1;
	int child_with_parent = 0;
	char buffer[MAX_LINE]; // pointer to the first element of array

	char *historyArray[ARRAY_SIZE];
	int histCount = 0;	

	pid_t pid;
	do {
		printf("osh>");
		fgets(buffer, sizeof(buffer), stdin);
		fflush(stdout);
		if (buffer[0] == '\n') {
			// loop back
			continue;
		}
		int count;
		count = parse(buffer, args, &child_with_parent);
		//printf("count: %d\n",count);
		//printf("end of args: %s\n", args[count]);
		// add command to history array
		if (strcmp(args[0], "exit") == 0) {
			should_run = 0;
		} else if (strcmp(args[0], "history") == 0) {
			if (histCount == 0) {
				printf("\nNo command in the history\n");
			} else {
				//printf("", histCount);
				history(historyArray, &histCount);
			}
			
		} else {
			int i;
			for(i = ARRAY_SIZE-1; i > 0; i--) {
				historyArray[histCount] = historyArray[histCount-1];
			}
			printf("\n%s\n", args[0]);
			historyArray[0] = (args[0]);
			histCount++;
	/**
	* (1) Fork child process using fork()
	* (2) The child process will invoke execvp()
	* (3) if command included &, parent will invoke wait()
	*/	
		
			pid = fork();
			if (pid == 0) { // child process
				int status = execvp(args[0], args);
				if (status == -1)
					printf("Error occured\n");
					continue;
			} else {	// parent process 
				if (child_with_parent == 0)
					wait();
			}
		}
	} while (should_run);
	return 0;
}

