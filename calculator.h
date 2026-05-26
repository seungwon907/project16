#include <stdio.h>
#include <stdlib.h>

extern int infixToPostfix(char* infix, char* postfix);
extern int evalPostfix(char* postfix);
extern int precedence(char op);
extern int printArrayStackLine(struct arrayStack* s); 
