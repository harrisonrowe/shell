#include "includes.h"

// Recursive call to calculate prefix -> infix expression
int prefixCalc(int* curr_index, int last_index, char** cmd){
    // Ensure still in calculation
    if (*curr_index > last_index){
        return 0;
    }
    // Check for single symbol operator
    if (strlen(cmd[*curr_index]) == 1 && *(cmd[*curr_index]) == '+'){
        // Addition operation
        (*curr_index)++;
        int operand1 = prefixCalc(curr_index, last_index, cmd);
        int operand2 = prefixCalc(curr_index, last_index, cmd);
        return operand1 + operand2;
    } else if (strlen(cmd[*curr_index]) == 1 && *(cmd[*curr_index]) == '-'){
        // Subtraction operation
        (*curr_index)++;
        int operand1 = prefixCalc(curr_index, last_index, cmd);
        int operand2 = prefixCalc(curr_index, last_index, cmd);
        return operand1 - operand2;
    } else {
        // Treat as an integer
        int result = atoi(cmd[*curr_index]);
        (*curr_index)++;
        return result;
    }
}

// Called from shell, gets value from prefixCalc function
void calcExpression(char** cmd, int size){
    if (size > 1){
        int curr_pos = 1;
        int value = prefixCalc(&curr_pos, size-1, cmd);
        // Print calculated value
        printf("\n\t\033[0;35mValue:\033[0m %d\n", value);
    } else {
        printf("\n\t\033[0;31mError:\033[0m Enter a valid expression. \n");
    }
}

// Use linux tm structure to present current local date and time
void getLocalTime(void){
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
    // Use linux cwd and char array as buffer to locate current path
    char cwd[MAX_SIZE];
    getcwd(cwd, sizeof(cwd));
    printf("\n\t\033[0;35mCurrent path:\033[0m %s\n", cwd);
}

// Get system information
void getSys(void){
    // Get OS version
    printf("\n\t\033[0;35mOperating System:\033[0m ");
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
        if (strcmp(cmd[size-1], "-f") == 0){
            force = true;
        }
        // Check if dirname exists within current path
        char dirname[MAX_SIZE];
        strcpy(dirname, cmd[1]);
        DIR* dir = opendir(dirname);
        struct dirent* pDir;
        if (dir){
            // Directory exists
            if (force){
                printf("\n\t%s\033[0;35m found!\033[0m\n", dirname);
                // Remove existing files
                while ((pDir = readdir(dir)) != NULL){
                    // Get each filename
                    char* filename = pDir->d_name;
                    // Check file name, exclude "." and ".."
                    if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0){
                        // Adjust filename for directory prefix
                        char fname[] = "";
                        strcat(fname, dirname);
                        strcat(fname, "/");
                        strcat(fname, filename);
                        // Check if file has been removed successfully
                        if (remove(fname) == 0){
                            printf("\n\t\033[0;35mRemoved File: \033[0m %s", filename);
                        } else {
                            printf("\n\t\033[0;35mCannot Remove File: \033[0m %s", filename);
                        }
                    }
                }
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
        // Copy files into new directory
        // Find max file argument in cmd
        int maxArg = 0;
        if (force){
            maxArg = size-1;
        } else {
            maxArg = size;
        }
        // Push each file into new directory
        for (int i = 2; i < maxArg; i++){
            // Get filename from command argument
            char* filename = cmd[i];
            // Check if file is valid file
            FILE* readFile = fopen(filename, "r");
            if (readFile == NULL){
                // File not found error, continue to next file
                printf("\n\t\033[0;31mError:\033[0m %s not found.", filename);
                continue;
            }
            // Since file exists, create new file in working directory
            char fname[] = "";
            strcat(fname, dirname);
            strcat(fname, "/");
            strcat(fname, filename);
            FILE* writeFile = fopen(fname, "w");
            // Copy readFile to writeFile line by line file
            char* line = NULL;
            size_t length;
            // While readFile is not EOF
            while (getline(&line, &length, readFile) != -1){
                // Write line to writeFile
                fprintf(writeFile, line);
            }
            // File creation message
            printf("\n\t\033[0;35mCreated File: \033[0m%s", filename);
            // Close file pointers
            fclose(readFile);
            fclose(writeFile);
        }
        // Close directory
        closedir(dir);
        printf("\n\n\t\033[0;35m%s\033[0m created successfully.\n", dirname);
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