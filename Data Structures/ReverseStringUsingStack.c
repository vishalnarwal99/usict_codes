#include <stdio.h>

#define MAX_SIZE 100

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

int main(void)
{
    char input[MAX_SIZE], output[MAX_SIZE];

    printf("Enter a string: ");
    scanf("%s", input);

    if (ReverseString(input, output) == 0)
    {
        printf("Reversed String: %s\n", output);
    }

    return 0;
}
