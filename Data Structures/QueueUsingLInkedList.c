#include <stdio.h>
#include <stdlib.h>

int Enqueue(int value);
int Dequeue(int* value);
int PeekFront(int* value);

int main(void)
{
    int option = 0;
    int value;

    printf("1. Enqueue\n2. Dequeue\n3. Peek front\n4. Quit\n");

    while (option != 4)
    {
        printf("\nChoose an operation: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Enter the value: ");
            scanf("%d", &value);

            Enqueue(value);
            break;

        case 2:
            if (Dequeue(&value) == 0)
            {
                printf("Dequeued: %d\n", value);
            }
            break;

        case 3:
            if (PeekFront(&value) == 0)
            {
                printf("Front element: %d\n", value);
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

typedef struct ListNode
{
    int value;
    struct ListNode* next;

} ListNode;

ListNode* front = NULL;
ListNode* rear = NULL;

int IsEmpty()
{
    return (front == NULL);
}

int Enqueue(int value)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

    if (newNode == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    newNode->value = value;
    newNode->next = NULL;

    if (front == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    return 0;
}

int Dequeue(int* value)
{
    if (IsEmpty())
    {
        printf("Error: queue is empty.\n");
        return -1;
    }

    *value = front->value;
    ListNode* currNode = front;
    front = front->next;

    free(currNode);

    return 0;
}

int PeekFront(int* value)
{
    if (IsEmpty())
    {
        printf("Error: queue is empty.\n");
        return -1;
    }

    *value = front->value;

    return 0;
}
