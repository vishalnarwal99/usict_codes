#include <stdio.h>

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

#define MAX_SIZE 100

int queue[MAX_SIZE];
int rear = -1, count = 0;

int IsEmpty()
{
    return (count == 0);
}

int IsFull()
{
    return (count == MAX_SIZE);
}

int Enqueue(int value)
{
    if (IsFull())
    {
        printf("Error: queue is full.\n");
        return -1;
    }

    rear = (rear + 1) % MAX_SIZE;

    queue[rear] = value;
    count++;

    return 0;
}

int Dequeue(int* value)
{
    if (IsEmpty())
    {
        printf("Error: queue is empty.\n");
        return -1;
    }

    int front = (rear + MAX_SIZE - count + 1) % MAX_SIZE;

    *value = queue[front];
    count--;

    return 0;
}

int PeekFront(int* value)
{
    if (IsEmpty())
    {
        printf("Error: queue is empty.\n");
        return -1;
    }

    int front = (rear + MAX_SIZE - count + 1) % MAX_SIZE;

    *value = queue[front];

    return 0;
}
