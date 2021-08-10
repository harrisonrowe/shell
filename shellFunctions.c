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

// Remove all files in specified directory
void removeDirFiles(DIR* dir, char* dirname){
    struct dirent* pDir;
    while ((pDir = readdir(dir)) != NULL){
        // Get each filename
        char* filename = pDir->d_name;
        // Check file name, exclude "." and ".."
        if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0){
            // Adjust filename for directory prefix
            char fname[MAX_SIZE] = "";
            addDirPrefix(fname, dirname, filename);
            // Check if file has been removed successfully
            if (remove(fname) == 0){
                printf("\n\t\033[0;35mRemoved File: \033[0m%s", filename);
            } else {
                printf("\n\t\033[0;35mCannot Remove File: \033[0m %s", filename);
            }
        }
    }
}

// Copy single file contents into new specified directory
void copyFile(char* filename, char* dirname){
    // Check if file is valid file
    FILE* readFile = fopen(filename, "r");
    if (readFile == NULL){
        // File not found error, continue to next file
        printf("\n\t\033[0;31mError:\033[0m %s not found.", filename);
        return;
    }
    // Since file exists, create new file in working directory
    char fname[MAX_SIZE] = "";
    addDirPrefix(fname, dirname, filename);
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
    // Close file pointer
    fclose(readFile);
    fclose(writeFile);
}

void addDirPrefix(char* fname, char* dirname, char* filename){
    strcat(fname, dirname);
    strcat(fname, "/");
    strcat(fname, filename);
}