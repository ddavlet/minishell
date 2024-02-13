#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


// compile with -lreadline flag

int main() {
    char *input;

    // Read a line from the user
    input = readline("Enter a file/directory name: ");


	// Replace the input line with a new string
	rl_replace_line("New command", 1);
	// Redisplay the modified input line
	rl_redisplay();

	if (access(input, R_OK) == 0) {
        printf("File '%s' exists and is readable.\n", input);
    } else {
        perror("Error");
    }
	// Process the input (for example, print it)
    // printf("You entered: %s\n", input);

    // Call rl_on_new_line() to indicate moving to a new line
    // rl_on_new_line();

    // Free the memory allocated by readline
    free(input);

    return 0;
}
