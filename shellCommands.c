#include "includes.h"

// Called from shell, gets value from prefixCalc function
void calcExpression(char** cmd, int size){
    // Checks command expression
    if (size > 1){
        int curr_pos = 1;
        int value = prefixCalc(&curr_pos, size-1, cmd);
        // Print calculated value
        printf("\n\t\033[0;35mValue:\033[0m %d\n", value);
    } else {
        // Error with expression input arguments
        printf("\n\t\033[0;31mError:\033[0m Enter a valid expression. \n");
    }
}

// Use linux tm structure to present current local date and time
void getLocalTime(void){
    // Use unix time structure
    time_t currentTime;
    struct tm *ti;
    time(&currentTime);
    ti = localtime(&currentTime);
    // ti->tm_hour += 9; // Offset cygwin default time
    // Print output
    printf("\n\t\033[0;35mDate and time:\033[0m %s", asctime(ti));
}

// Gets current working directory and prints to console
void getPath(void){
    // Use unix cwd and char array as buffer to locate current path
    char cwd[MAX_SIZE];
    getcwd(cwd, sizeof(cwd));
    printf("\n\t\033[0;35mCurrent path:\033[0m %s\n", cwd);
}

// Get system information
void getSys(void){
    // Get current OS type
    char os[MAX_SIZE] = "";
    #ifdef _WIN32
        strcpy(os, "Windows");
    #elif __APPLE__
        strcpy(os, "Apple");
    #elif __linux__
        strcpy(os, "Linux");
    #elif __unix__
        strcpy(os, "Unix OS");
    #else
        strcpy(os, "Unidentified Operating System");
    #endif
    // Print OS type
    printf("\n\t\033[0;35mOS Type:\033[0m %s", os);
    // Get OS version (used in command terminal)
    printf("\n\t\033[0;35mOS Version:\033[0m ");
    system("cat /proc/version");
    // Get CPU info
    printf("\t\033[0;35mSystem CPU:\033[0m ");
    system("grep -m 1 'model name' /proc/cpuinfo"); // Grep finds model name of CPU and prints
}

// Push files into new directory
void putFile(char** cmd, int size){
    // Check size of command - at least 3 arguments
    if (size > 2){
        // Check if force flag is set
        bool force = false;
        int maxArg = size; // Find max file argument in cmd
        if (strcmp(cmd[size-1], "-f") == 0){
            force = true;
            maxArg--;
        }
        // Check if dirname exists within current path
        char dirname[MAX_SIZE];
        strcpy(dirname, cmd[1]);
        DIR* dir = opendir(dirname);
        if (dir){
            // Directory exists
            if (force){
                printf("\n\t%s\033[0;35m found!\033[0m\n", dirname);
                // Remove existing files
                removeDirFiles(dir, dirname);
            } else {
                // Directory exists and force not flagged
                printf("\n\t\033[0;31mError:\033[0m Directory already exists. \n");
                return;
            }
        } else {
            // Create new directory
            mkdir(dirname);
        }
        printf("\n\n\t%s \033[0;35mready. Copying Files... \033[0m\n", dirname);
        // Copy files into new directory by push each file into new directory
        for (int i = 2; i < maxArg; i++){
            // Copy file contents, with cmd[i] = filename
            copyFile(cmd[i], dirname);
        }
        // Close directory
        closedir(dir);
        printf("\n\n\t%s \033[0;35mcreated successfully!\033[0m\n", dirname);
    } else {
        // Print error, not enough arguments
        printf("\n\t\033[0;31mError:\033[0m Specify more arguments (dirname, filenames, -f). \n");
    }
}

// Get file contents and dump onto shell
void getFile(char** cmd, int size){
    // Check command size
    if (size == 2){
        FILE* fp = fopen(cmd[1], "r"); // Open in read mode
        int maxLines = 40; // Number of lines given on a dump
        // Check if file is found
        if (fp != NULL){ 
            char* line = NULL;
            size_t length = 0, read;
            int lineNumber = 0;
            // Print formatting
            printf("\n\t\033[0;35m%s \n\n", cmd[1]);
            while (read = getline(&line, &length, fp) != -1){
                // Each line from file, print line, increase line number by 1
                printf("\t\033[0;35m%d:\033[0m %s", lineNumber+1, line);
                lineNumber++;
                if (lineNumber % maxLines == 0){
                    // Reset, wait for keyboard input
                    getch();
                }
            }
            // Free pointers
            free(line);
            printf("\n\n\t\033[0;35mEnd of File.\033[0m \n");
        } else {
            // File not found error
            printf("\n\t\033[0;31mError:\033[0m File not found in current directory. \n");
        }
        // Close file pointer
        fclose(fp);
    } else {
        // Command incorrect
        printf("\n\t\033[0;31mError:\033[0m Enter command followed by single filename. \n");
    }
}