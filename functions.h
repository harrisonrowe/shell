#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Shell command prototypes

void runShell(void);
void calcExpression(char**, int);
void getLocalTime(void);
void getPath(void);
void getSys(void);
void putFile(char**, int);
void getFile(char**, int);

// Shell function prototypes

int prefixCalc(int*, int, char**);

#endif