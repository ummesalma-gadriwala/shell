//Q2

#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80

void parse(char *buffer, char **args, int *child_with_parent) {
     while (*buffer != '\0') {        
          while (*buffer == ' ' || *buffer == '\t' || *buffer == '\n')
               *buffer++ = '\0';     
          *args++ = buffer;         
          while (*buffer != '\0' && *buffer != ' ' && 
                 *buffer != '\t' && *buffer != '\n') 
               buffer++;             
     }
     if (*buffer == '&')
     	*child_with_parent = 1;
     *args = '\0';                 
}

int main(void) {
	char *args[MAX_LINE/2 +1];
	int should_run = 1;
	int child_with_parent = 0;
	char buffer[MAX_LINE];
	int length;
	pid_t pid;
	while (should_run) {
		printf("osh>");
		//gets(buffer);

		fflush(stdout);
		length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
		parse(buffer, args, &child_with_parent);
		if (strcmp(args[0], "exit") == 0) {
			should_run = 0;
		} else {
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
					should_run = 0;
			} else {	// parent process 
				if (child_with_parent == 0)
					wait();
			}
		}
	}
	return 0;
}
