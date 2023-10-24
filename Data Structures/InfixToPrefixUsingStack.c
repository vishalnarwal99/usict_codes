#include <stdio.h>

#define MAX_SIZE 100

int InfixToPrefix(const char* infix, char* prefix);

int main(void)
{
    char infix[MAX_SIZE];
    char prefix[MAX_SIZE];

    printf("Enter the infix expression: ");
    scanf("%s", infix);

    if (InfixToPrefix(infix, prefix) == 0)
    {
        printf("Prefix expression: %s\n", prefix);
    }

    return 0;
}

int ReverseString(const char* input, char* output)
{
    char stack[MAX_SIZE];
    int top = -1;

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (top == MAX_SIZE - 1)
        {
            printf("Error: stack overflow.\n");
            return -1;
        }

        stack[++top] = input[i];
    }

    int i = 0;

    while (top > -1)
    {
        output[i++] = stack[top--];
    }

    output[i] = '\0';

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

int InfixToPrefix(const char* infix, char* prefix)
{
    char stack[MAX_SIZE];
    int top = -1;
    int j = 0;

    char reverse[MAX_SIZE];
    ReverseString(infix, reverse);

    for (int i = 0; reverse[i] != '\0'; i++)
    {
        if ((reverse[i] >= '0' && reverse[i] <= '9') ||
            (reverse[i] >= 'A' && reverse[i] <= 'Z') || (reverse[i] >= 'a' && reverse[i] <= 'z'))
        {
            reverse[j++] = reverse[i];
        }
        else if (reverse[i] == ')')
        {
            stack[++top] = reverse[i];
        }
        else if (reverse[i] == '(')
        {
            while (top > -1 && stack[top] != ')')
            {
                reverse[j++] = stack[top--];
            }

            if (top > -1 && stack[top] == ')')
            {
                top--;
            }
        }
        else if (IsOperator(reverse[i]))
        {
            while (top > -1 && Precedence(stack[top]) >= Precedence(reverse[i]))
            {
                reverse[j++] = stack[top--];
            }

            stack[++top] = reverse[i];
        }

    }

    while (top > -1)
    {
        if (stack[top] != ')')
        {
            reverse[j++] = stack[top--];
        }
    }

    reverse[j] = '\0';
    ReverseString(reverse, prefix);

    return 0;
}
