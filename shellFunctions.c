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