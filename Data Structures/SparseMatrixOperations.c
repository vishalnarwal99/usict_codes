#include <stdio.h>
#include <stdlib.h>

typedef struct Triplet
{
    int row;
    int column;
    int value;

} Triplet;

typedef struct Matrix
{
    int rows;
    int columns;
    int size;
    Triplet* triplets;

} Matrix;

int InputSparseMatrix(Matrix* matrix);
void PrintSparseMatrix(Matrix* matrix);
int AddSparseMatrix(const Matrix* matrix_a, const Matrix* matrix_b, Matrix* result);
int TransposeSparseMatrix(const Matrix* matrix, Matrix* result);
int MultiplySparseMatrix(const Matrix* matrix_a, const Matrix* matrix_b, Matrix* result);

int main(void)
{
    Matrix matrix_a = { 0, 0, 0, NULL };
    Matrix matrix_b = { 0, 0, 0, NULL };

    Matrix sum = { 0, 0, 0, NULL };
    Matrix transpose = { 0, 0, 0, NULL };
    Matrix product = { 0, 0, 0, NULL };

    printf("Input for 'Sparse Matrix A':\n");
    if (InputSparseMatrix(&matrix_a) != 0)
    {
        return -1;
    }

    printf("\n'Sparse Matrix A':\n");
    PrintSparseMatrix(&matrix_a);

    printf("\nInput for 'Sparse Matrix B':\n");
    if (InputSparseMatrix(&matrix_b) != 0)
    {
        free(matrix_a.triplets);
        return -1;
    }

    printf("\n'Sparse Matrix B':\n");
    PrintSparseMatrix(&matrix_b);

    printf("\nSum of 'Sparse Matrix A' and 'Sparse Matrix B':\n");
    if (AddSparseMatrix(&matrix_a, &matrix_b, &sum) == 0)
    {
        PrintSparseMatrix(&sum);
    }

    printf("\nTranspose of 'Sparse Matrix A':\n");
    if (TransposeSparseMatrix(&matrix_a, &transpose) == 0)
    {
        PrintSparseMatrix(&transpose);
    }

    printf("\nProduct of 'Sparse Matrix A' and 'Sparse Matrix B':\n");
    if (MultiplySparseMatrix(&matrix_a, &matrix_b, &product) == 0)
    {
        PrintSparseMatrix(&product);
    }

    free(matrix_a.triplets);
    free(matrix_b.triplets);
    free(sum.triplets);
    free(transpose.triplets);
    free(product.triplets);

    return 0;
}

int InputSparseMatrix(Matrix* matrix)
{
    printf("Enter the dimension (rows columns) of the matrix: ");
    scanf("%d %d", &matrix->rows, &matrix->columns);

    printf("Enter the number of elements in the matrix: ");
    scanf("%d", &matrix->size);

    matrix->triplets = (Triplet*)malloc(matrix->size * sizeof(Triplet));

    if (matrix->triplets == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i < matrix->size; i++)
    {
        printf("Enter (row column value) for triplet %d: ", i + 1);
        scanf("%d %d %d", &matrix->triplets[i].row, &matrix->triplets[i].column, &matrix->triplets[i].value);
    }

    return 0;
}

void PrintSparseMatrix(Matrix* matrix)
{
    printf("%5s %7s %6s\n", "Row", "Column", "Value");

    for (int i = 0; i < matrix->size; i++)
    {
        printf("%5d %7d %6d\n", matrix->triplets[i].row, matrix->triplets[i].column, matrix->triplets[i].value);
    }
}

int AddSparseMatrix(const Matrix* matrix_a, const Matrix* matrix_b, Matrix* result)
{
    if (matrix_a->rows != matrix_b->rows || matrix_a->columns != matrix_b->columns)
    {
        printf("Error: incompatible matrix dimension.\n");
        return -1;
    }

    result->rows = matrix_a->rows;
    result->columns = matrix_a->columns;
    result->size = 0;
    result->triplets = (Triplet*)malloc((matrix_a->size + matrix_b->size) * sizeof(Triplet));

    if (result->triplets == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    int i = 0, j = 0;

    while (i < matrix_a->size && j < matrix_b->size)
    {
        if (matrix_a->triplets[i].row < matrix_b->triplets[j].row ||
            (matrix_a->triplets[i].row == matrix_b->triplets[j].row && matrix_a->triplets[i].column < matrix_b->triplets[j].column))
        {
            result->triplets[result->size++] = matrix_a->triplets[i++];
        }
        else if (matrix_a->triplets[i].row > matrix_b->triplets[j].row ||
            (matrix_a->triplets[i].row == matrix_b->triplets[j].row && matrix_a->triplets[i].column > matrix_b->triplets[j].column))
        {
            result->triplets[result->size++] = matrix_b->triplets[j++];
        }
        else
        {
            result->triplets[result->size] = matrix_a->triplets[i++];
            result->triplets[result->size].value += matrix_b->triplets[j++].value;

            if (result->triplets[result->size].value != 0)
            {
                result->size++;
            }
        }
    }

    while (i < matrix_a->size)
    {
        result->triplets[result->size++] = matrix_a->triplets[i++];
    }

    while (j < matrix_b->size)
    {
        result->triplets[result->size++] = matrix_b->triplets[j++];
    }

    return 0;
}

int TransposeSparseMatrix(const Matrix* matrix, Matrix* result)
{
    result->rows = matrix->columns;
    result->columns = matrix->rows;
    result->size = matrix->size;
    result->triplets = (Triplet*)malloc(result->size * sizeof(Triplet));

    if (result->triplets == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i < matrix->size; i++)
    {
        result->triplets[i].row = matrix->triplets[i].column;
        result->triplets[i].column = matrix->triplets[i].row;
        result->triplets[i].value = matrix->triplets[i].value;
    }

    for (int i = 0; i < result->size - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < result->size - i - 1; j++)
        {
            if (result->triplets[j].row > result->triplets[j + 1].row ||
                (result->triplets[j].row == result->triplets[j + 1].row && result->triplets[j].column > result->triplets[j + 1].column))
            {
                Triplet temp = result->triplets[j];
                result->triplets[j] = result->triplets[j + 1];
                result->triplets[j + 1] = temp;

                swapped = 1;
            }
        }
    }

    return 0;
}

int MultiplySparseMatrix(const Matrix* matrix_a, const Matrix* matrix_b, Matrix* result)
{
    if (matrix_a->columns != matrix_b->rows)
    {
        printf("Error: incompatible matrix dimension.\n");
        return -1;
    }

    result->rows = matrix_a->rows;
    result->columns = matrix_b->columns;
    result->size = 0;
    result->triplets = (Triplet*)malloc((matrix_a->rows * matrix_b->columns) * sizeof(Triplet));

    if (result->triplets == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    Matrix b_transpose = { 0, 0, 0, NULL };

    if (TransposeSparseMatrix(matrix_b, &b_transpose) != 0)
    {
        return -1;
    }

    for (int i = 0; i < matrix_a->size;)
    {
        for (int j = 0; j < b_transpose.size;)
        {
            int term_i = i, term_j = j;
            int sum = 0;

            while (term_i < matrix_a->size && matrix_a->triplets[term_i].row == matrix_a->triplets[i].row &&
                term_j < b_transpose.size && b_transpose.triplets[term_j].row == b_transpose.triplets[j].row)
            {
                if (matrix_a->triplets[term_i].column < b_transpose.triplets[term_j].column)
                {
                    term_i++;
                }
                else if (matrix_a->triplets[term_i].column > b_transpose.triplets[term_j].column)
                {
                    term_j++;
                }
                else
                {
                    sum += matrix_a->triplets[term_i].value * b_transpose.triplets[term_j].value;
                    term_i++, term_j++;
                }
            }

            if (sum != 0)
            {
                result->triplets[result->size++] = (Triplet){ i, j, sum };
            }

            int column = b_transpose.triplets[j].row;

            while (j < b_transpose.size && b_transpose.triplets[j].row == column)
            {
                j++;
            }
        }

        int row = matrix_a->triplets[i].row;

        while (i < matrix_a->size && matrix_a->triplets[i].row == row)
        {
            i++;
        }
    }

    free(b_transpose.triplets);

    return 0;
}
