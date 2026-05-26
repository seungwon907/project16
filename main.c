#include <stdio.h>
#include "calculator.h"
#pragma warning (disable:4996)

int main() {
    char infix[100];
    char postfix[100];

    printf("ют╥б: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    int result = evalPostfix(postfix);

    printf("\nResult: %d\n", result);
    return 0;
}
