#include <stdio.h>

#define MAX_SIZE 100

int InfixToPrefix(const char* infix, char* postfix);

int main(void)
{
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter the infix expression: ");
    scanf("%s", infix);

    if (InfixToPrefix(infix, postfix) == 0)
    {
        printf("Postfix expression: %s\n", postfix);
    }

    return 0;
}

int Precedence(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
    case '%':
        return 2;

    case '^':
        return 3;

    default:
        return 0;
    }
}

int IsOperator(char character)
{
    return (Precedence(character) > 0);
}

int InfixToPrefix(const char* infix, char* postfix)
{
    char stack[MAX_SIZE];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        if ((infix[i] >= '0' && infix[i] <= '9') ||
            (infix[i] >= 'A' && infix[i] <= 'Z') || (infix[i] >= 'a' && infix[i] <= 'z'))
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            stack[++top] = infix[i];
        }
        else if (infix[i] == ')')
        {
            while (top > -1 && stack[top] != '(')
            {
                postfix[j++] = stack[top--];
            }

            if (top > -1 && stack[top] == '(')
            {
                top--;
            }
        }
        else if (IsOperator(infix[i]))
        {
            while (top > -1 && Precedence(stack[top]) >= Precedence(infix[i]))
            {
                postfix[j++] = stack[top--];
            }

            stack[++top] = infix[i];
        }
    }

    while (top > -1)
    {
        if (stack[top] != '(')
        {
            postfix[j++] = stack[top--];
        }
    }

    postfix[j] = '\0';

    return 0;
}
