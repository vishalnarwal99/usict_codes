#include <stdio.h>
#include <stdlib.h>

typedef struct Term
{
    int coefficient;
    int exponent;

} Term;

typedef struct Polynomial
{
    int size;
    Term* terms;

} Polynomial;

int InputPolynomial(Polynomial* polynomial);
void PrintPolynomial(Polynomial* polynomial);
int AddPolynomials(const Polynomial* polynomial_a, const Polynomial* polynomial_b, Polynomial* result);
int MultiplyPolynomials(const Polynomial* polynomial_a, const Polynomial* polynomial_b, Polynomial* result);

int main(void)
{
    Polynomial polynomial_a = { 0, NULL };
    Polynomial polynomial_b = { 0, NULL };

    Polynomial sum = { 0, NULL };
    Polynomial product = { 0, NULL };

    printf("Input for 'Polynomial A':\n");
    if (InputPolynomial(&polynomial_a) != 0)
    {
        return -1;
    }

    printf("\n'Polynomial A': ");
    PrintPolynomial(&polynomial_a);

    printf("\nInput for 'Polynomial B':\n");
    if (InputPolynomial(&polynomial_b) != 0)
    {
        free(polynomial_a.terms);
        return -1;
    }

    printf("\n'Polynomial B': ");
    PrintPolynomial(&polynomial_b);

    printf("\nSum of 'Polynomial A' and 'Polynomial B':\n");
    if (AddPolynomials(&polynomial_a, &polynomial_b, &sum) == 0)
    {
        PrintPolynomial(&sum);
    }

    printf("\nProduct of 'Polynomial A' and 'Polynomial B':\n");
    if (MultiplyPolynomials(&polynomial_a, &polynomial_b, &product) == 0)
    {
        PrintPolynomial(&product);
    }

    free(polynomial_a.terms);
    free(polynomial_b.terms);
    free(sum.terms);
    free(product.terms);

    return 0;
}

int InputPolynomial(Polynomial* polynomial)
{
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &polynomial->size);

    polynomial->terms = (Term*)malloc(polynomial->size * sizeof(Term));

    if (polynomial->terms == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i < polynomial->size; i++)
    {
        printf("Enter (coefficient exponent) for term %d: ", i + 1);
        scanf("%d %d", &polynomial->terms[i].coefficient, &polynomial->terms[i].exponent);
    }

    return 0;
}

void PrintPolynomial(Polynomial* polynomial)
{
    for (int i = 0; i < polynomial->size; i++)
    {
        printf("%dx^%d", polynomial->terms[i].coefficient, polynomial->terms[i].exponent);
        printf("%s", (i != polynomial->size - 1) ? " + " : "\n");
    }
}

int AddPolynomials(const Polynomial* polynomial_a, const Polynomial* polynomial_b, Polynomial* result)
{
    result->size = 0;
    result->terms = (Term*)malloc((polynomial_a->size + polynomial_b->size) * sizeof(Term));

    if (result->terms == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    int i = 0, j = 0;

    while (i < polynomial_a->size && j < polynomial_b->size)
    {
        if (polynomial_a->terms[i].exponent > polynomial_b->terms[j].exponent)
        {
            result->terms[result->size++] = polynomial_a->terms[i++];
        }
        else if (polynomial_a->terms[i].exponent < polynomial_b->terms[j].exponent)
        {
            result->terms[result->size++] = polynomial_b->terms[j++];
        }
        else
        {
            result->terms[result->size] = polynomial_a->terms[i++];
            result->terms[result->size].coefficient += polynomial_b->terms[j++].coefficient;

            if (result->terms[result->size].coefficient != 0)
            {
                result->size++;
            }
        }
    }

    while (i < polynomial_a->size)
    {
        result->terms[result->size++] = polynomial_a->terms[i++];
    }

    while (j < polynomial_b->size)
    {
        result->terms[result->size++] = polynomial_b->terms[j++];
    }

    return 0;
}

int MultiplyPolynomials(const Polynomial* polynomial_a, const Polynomial* polynomial_b, Polynomial* result)
{
    result->size = 0;
    result->terms = (Term*)malloc((polynomial_a->size * polynomial_b->size) * sizeof(Term));

    if (result->terms == NULL)
    {
        printf("Error: memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i < polynomial_a->size; i++)
    {
        for (int j = 0; j < polynomial_b->size; j++)
        {
            result->terms[result->size] = polynomial_a->terms[i];
            result->terms[result->size].coefficient *= polynomial_b->terms[j].coefficient;
            result->terms[result->size].exponent += polynomial_b->terms[j].exponent;

            if (result->terms[result->size].coefficient != 0)
            {
                result->size++;
            }
        }
    }

    for (int i = 0; i < result->size - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < result->size - i - 1; j++)
        {
            if (result->terms[j].exponent < result->terms[j + 1].exponent)
            {
                Term temp = result->terms[j];
                result->terms[j] = result->terms[j + 1];
                result->terms[j + 1] = temp;

                swapped = 1;
            }
        }
    }

    int merged = 0;

    for (int i = 0; i + merged + 1 < result->size; i++)
    {
        while (result->terms[i].exponent == result->terms[i + merged + 1].exponent)
        {
            result->terms[i].coefficient += result->terms[i + merged + 1].coefficient;
            merged++;
        }

        if (result->terms[i].coefficient == 0)
        {
            i--;
            merged++;
        }

        result->terms[i + 1] = result->terms[i + merged + 1];
    }

    result->size -= merged;

    return 0;
}
