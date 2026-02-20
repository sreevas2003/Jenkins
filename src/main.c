#include <stdio.h>
#include "add.h"
#include "mul.h"
#include "sub.h"

int main() {
    int Addition = add(5, 3);
    printf("Result: %d\n", Addition);
    int Multiplication = mul(5, 3);
    printf("Result: %d\n", Multiplication);
    int Subtraction = sub(5, 3);
    printf("Result: %d\n", Subtraction);
    return 0;
}
