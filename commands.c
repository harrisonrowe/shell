#include "includes.h"

void calcExpression(char** cmd, int size){
    
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
    printf("\n\t\033[0;35mOperating System:\033[0m %s\n\t\033[0;35mSystem CPU:\033[0m ", os);
    system("grep -m 1 'model name' /proc/cpuinfo");
}   

void putFile(char** cmd, int size){

}

void getFile(char** cmd, int size){

}