#include "includes.h"

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

void getLocalTime(void){
    // Use structure to present current local date and time
    time_t currentTime;
    struct tm *ti;
    time(&currentTime);
    ti = localtime(&currentTime);
    ti->tm_hour += 9; // Offset defualt time
    // Print output
    printf("\n\t\033[0;35mDate and time:\033[0m %s", asctime(ti));
}

void getPath(void){
    // Use linux cwd and char array as buffer to locate current path
    char cwd[MAX_SIZE];
    getcwd(cwd, sizeof(cwd));
    printf("\n\t\033[0;35mCurrent path:\033[0m %s\n", cwd);
}

void getSys(void){
    // Check operating system
    char os[MAX_SIZE];
    #ifdef _WIN32
        strcpy(os, "Windows");
    #elif __APPLE__
        strcpy(os, "MacOS");
    #elif __linux__
        strcpy(os, "Linux");
    #elif __unix__
        strcpy(os, "Other Unix System");
    #else
        strcpy(os, "Unable to detect OS");
    #endif 
    // Print OS and CPU
    printf("\n\t\033[0;35mOperating System:\033[0m %s\n\t\033[0;35mSystem CPU:\033[0m ", os);
    system("grep -m 1 'model name' /proc/cpuinfo");
}   

void putFile(char** cmd, int size){

}

void getFile(char** cmd, int size){
    
}