#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *a;             // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;      // highest power 10
    unsigned int size;   // size of allocated dynamic memory in a
} Decimal;

void elong_sub(const Decimal *a, const Decimal *b, Decimal *res) {
    res->size = (a->size > b->size) ? a->size : b->size;
    res->a = (char *)malloc(res->size * sizeof(char));

    int borrow = 0;
    int i = 0;

    while (i < res->size) {
        int diff = borrow;
        if (i < a->size) {
            diff += a->a[a->size - 1 - i] - '0'; // Read digits from the end of the string
        }
        if (i < b->size) {
            diff -= b->a[b->size - 1 - i] - '0'; // Read digits from the end of the string
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res->a[i] = diff + '0';
        i++;
    }

    // Remove leading zeros if any
    while (i > 1 && res->a[i - 1] == '0') {
        i--;
    }

    res->n = i - 1; // highest power 10
}

int main() {
    Decimal a, b, res;

    printf("Enter Decimal a (a>b): ");
    char input_a[100];
    scanf("%s", input_a);
    a.size = strlen(input_a);
    a.a = strdup(input_a); // Allocate memory for a and copy input

    printf("Enter Decimal b (b<a): ");
    char input_b[100];
    scanf("%s", input_b);
    b.size = strlen(input_b);
    b.a = strdup(input_b); // Allocate memory for b and copy input

    elong_sub(&a, &b, &res);

    printf("Result of subtracting b from a: ");
    for (int i = res.n; i >= 0; i--) {
        printf("%c", res.a[i]);
    }
    printf("\n");

    free(a.a); // Free dynamically allocated memory for a
    free(b.a); // Free dynamically allocated memory for b
    free(res.a); // Free dynamically allocated memory for result

    return 0;
}