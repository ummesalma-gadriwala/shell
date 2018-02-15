# shell
Simple UNIX shell
By: Tasnim Noshin and Umme Salma Gadriwala

Compile: `gcc -o shell shell.c`

Run: `./shell`

Implementation and Functionalities:
1. Creates a child process using the fork() command to execute the command.
   By default, the parent waits while the child process executes.
   Add an ampersand `&` at the end of the command to execute parent and child process concurrently.
2. Does not handle commands with spaces in arguments.
   For instance, `ls -l` is handled as expected but cat "prog one.c" produces unexpected behaviour.
3. Supports history feature for up to 5 most recently entered commands.
4. Two techniques for retrieving commands:
    - `!!` to execute the most recent command in history.
    - `!n` to execute the nth command in history (n must be within the five most recent commands in history).
5. Basic error handling.
