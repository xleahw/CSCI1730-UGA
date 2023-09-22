#include <stdio.h>

int main() {
    unsigned int x = 0;
    int k;

    // Determine number of bits available for each value
    printf("Please enter k: ");
    scanf("%d", &k);

    if (k != 1 && k != 2 && k != 4 && k != 8 && k != 16 && k != 32) {
        printf("Invalid value of k. Please use 1, 2, 4, 8, 16, or 32.\n");
        return 1;
    }

    int bits_per_value = 32 / k;

    // Get input from user for k unsigned integers
    printf("Please enter %d unsigned ints: ", k);

    for (int i = 0; i < k; i++) {
        unsigned int input;
        scanf("%u", &input);

        // Check if the input integer can be represented with the allotted bits
        if (input >= (1u << bits_per_value)) {
            printf("The integer %u is too large for the allotted bits.\n", input);
            return 1;
        }

        // Store the input integer in x using bitwise operators
        x = (x << bits_per_value) | input;
    }

    printf("Overall Value = %u\n", x);

    return 0;
}
