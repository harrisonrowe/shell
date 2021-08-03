#include "includes.h"

// Runs the shell terminal
void runShell(void){
    // Variables
    char cmdLine[MAX_SIZE]; // Store command from console
    // While statement to run until quit
    while (strcmp(cmdLine, "quit") != 0){
        // Get & scan for input
        printf("\n\033[0;35m>\033[0m ");
        scanf("%[^\n]%*c", cmdLine);
        // Store shell line arguments as a ragged array
        char** cmd = 0;
        int size = 0;
        // Get command as array of strings, using token from strtok
        char* token = strtok(cmdLine, " ");
        // Store each command as a ragged array using array of char pointers
        while (token != NULL){
            // Reallocate space for each string, then allocate number of characters within the string
            cmd = (char**) realloc(cmd, (size+1)*sizeof(*cmd));
            cmd[size] = malloc(sizeof(char)*strlen(token));
            // Assign token string, move to next using space as the delimiter
            cmd[size++] = token;
            token = strtok(NULL, " ");
        }
        // Check command operation
        if (strcmp(cmd[0], "calc") == 0){
            // Run calculation
            calcExpression(cmd, size);
        } else if (strcmp(cmd[0], "time") == 0){
            // Print current date and time
            getLocalTime();
        } else if (strcmp(cmd[0], "path") == 0){
            // Print current directory
            getPath();
        } else if (strcmp(cmd[0], "sys") == 0){
            // Print name & version of OS and CPU
            getSys();
        } else if (strcmp(cmd[0], "put") == 0){
            // Put files in the specified directory
            putFile(cmd, size);
        } else if (strcmp(cmd[0], "get") == 0){
            // Prints contents of a file to the console
            getFile(cmd, size);
        } else if (strcmp(cmd[0], "quit") == 0){
            // Print exit message
            printf("\n\t\033[0;35mExiting Shell...\033[0m\n");
        } else {
            // Print unknown command
            printf("\n\t\033[0;31mError:\033[0m Unknown Command.\n");
            // Clear scanf buffer
            fflush(stdin); 
        }
        // Free command 2d array
        for (int i = 0; i < size; i++){
            free(cmd[i]);
        }
        free(cmd);
    }
}