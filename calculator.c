#include "calculator.h"
#include "ArrayStack.h"

void printPostfix(char* postfix, int j) {
    printf("Postfix: ");
    for (int i = 0; i < j; i++) {
        printf("%c ", postfix[i]);
    }
    printf("\n");
}

int infixToPostfix(char* infix, char* postfix) {
    int j = 0;
    ArrayStack* opStack = createArrayStack(100, CHARACTER);

    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {
            postfix[j++] = infix[i];
            printf("Current: %c | Stack: ", infix[i]);
            printArrayStack(opStack);
        }
        else if (infix[i] == '+' || infix[i] == '-' ||
            infix[i] == '*' || infix[i] == '/') {
            while (!emptyArrayStack(opStack)) {
                stackElement prevOp = peekArrayStack(opStack);

                if (precedence(infix[i]) <= precedence(prevOp.operator)) {
                    postfix[j++] = popArrayStack(opStack).operator;
                }
                else {
                    break;
                }
            }

            stackElement newOp;
            newOp.operator = infix[i];
            pushArrayStack(opStack, newOp);
            printf("Current: %c | Stack: ", infix[i]);
            printArrayStack(opStack);
        }
        else if (infix[i] == '(') {
            stackElement newOp;
            newOp.operator = infix[i];
            pushArrayStack(opStack, newOp);
        }
        else if (infix[i] == ')') {
            while (!emptyArrayStack(opStack)) {
                stackElement prevOp = popArrayStack(opStack);
                if (prevOp.operator != '(') {
                    postfix[j++] = prevOp.operator;
                }
                else {
                    break;
                }
            }
        }
    }

    while (!emptyArrayStack(opStack)) {
        postfix[j++] = popArrayStack(opStack).operator;
    }

    postfix[j] = '\0'; // Null terminate the postfix expression
    printPostfix(postfix, j);
    return j; // Return the length of postfix
}

int evalPostfix(char* postfix) {
    ArrayStack* valueStack = createArrayStack(100, INTEGER);
    int i = 0;

    while (postfix[i] != '\0') {
        if (postfix[i] >= '0' && postfix[i] <= '9') {
            stackElement newValue;
            newValue.value = (int)(postfix[i] - '0');
            pushArrayStack(valueStack, newValue);
            printf("Current: %c | Stack: ", postfix[i]);
            printArrayStack(valueStack);
        }
        else {
            int i2 = popArrayStack(valueStack).value;
            int i1 = popArrayStack(valueStack).value;

            stackElement result;
            if (postfix[i] == '*') {
                result.value = i1 * i2;
            }
            else if (postfix[i] == '/') {
                result.value = i1 / i2;
            }
            else if (postfix[i] == '+') {
                result.value = i1 + i2;
            }
            else if (postfix[i] == '-') {
                result.value = i1 - i2;
            }
            pushArrayStack(valueStack, result);
            printf("Current: %c | Stack: ", postfix[i]);
            printArrayStack(valueStack);
        }
        i++;
    }

    return popArrayStack(valueStack).value;
}

int precedence(char op) {
    switch (op) {
    case ')':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
        return 0;
    default:
        return 0;
    }
}

//잘모르겠습니다
