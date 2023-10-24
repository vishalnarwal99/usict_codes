#include <stdio.h>

int FindAddress(int* dimensions, int* indices, int n, int base_index, int element_size)
{
    int address = 0, multiplier = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        address += indices[i] * multiplier;
        multiplier *= dimensions[i];
    }

    return address * element_size + base_index;
}

int main(void)
{
    int n;

    printf("Enter the dimension of array: ");
    scanf("%d", &n);

    int dimensions[n];
    int base_index;
    int indices[n];
    int element_size;

    printf("Enter the size of array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &dimensions[i]);
    }

    printf("Enter the base index of array: ");
    scanf("%d", &base_index);

    printf("Enter the index to look for: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &indices[i]);
    }

    printf("Enter the size of element: ");
    scanf("%d", &element_size);

    int result = FindAddress(dimensions, indices, n, base_index, element_size);
    printf("The index of element is: %d\n", result);

    return 0;
}
