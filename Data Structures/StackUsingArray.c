#include <stdio.h>

int Push(int value);
int Pop(int* value);
int Peek(int* value);

int main(void)
{
    int option = 0;
    int value;

    printf("1. Push\n2. Pop\n3. Peek\n4. Quit\n");

    while (option != 4)
    {
        printf("\nChoose an operation: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Enter the value: ");
            scanf("%d", &value);

            Push(value);
            break;

        case 2:
            if (Pop(&value) == 0)
            {
                printf("Popped: %d\n", value);
            }
            break;

        case 3:
            if (Peek(&value) == 0)
            {
                printf("Top element: %d\n", value);
            }
            break;

        case 4:
            break;

        default:
            printf("Error: invalid choice.\n");
        }
    }

    return 0;
}

#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;

int IsEmpty()
{
    return (top == -1);
}

int IsFull()
{
    return (top == MAX_SIZE - 1);
}

int Push(int value)
{
    if (IsFull())
    {
        printf("Error: stack overflow.\n");
        return -1;
    }

    stack[++top] = value;

    return 0;
}

int Pop(int* value)
{
    if (IsEmpty())
    {
        printf("Error: stack underflow.\n");
        return -1;
    }

    *value = stack[top--];

    return 0;
}

int Peek(int* value)
{
    if (IsEmpty())
    {
        printf("Error: stack is empty.\n");
        return -1;
    }

    *value = stack[top];

    return 0;
}
