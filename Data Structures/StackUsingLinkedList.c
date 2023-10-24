#include <stdio.h>
#include <stdlib.h>

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

struct ListNode
{
    int value;
    struct ListNode* next;
};

struct ListNode* top = NULL;

int IsEmpty()
{
    return (top == NULL);
}

int Push(int value)
{
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));

    if (!newNode)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    newNode->value = value;
    newNode->next = top;
    top = newNode;
}

int Pop(int* value)
{
    if (IsEmpty())
    {
        printf("Error: stack underflow.\n");
        return -1;
    }

    *value = top->value;
    struct ListNode* currNode = top;
    top = currNode->next;

    free(currNode);

    return 0;
}

int Peek(int* value)
{
    if (IsEmpty())
    {
        printf("Error: stack is empty.\n");
        return -1;
    }

    *value = top->value;

    return 0;
}
