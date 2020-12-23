#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;

    do
    {
        dollars = get_float("Enter number of dollars: ");
    }
    while (dollars < 0);

    int total_coins = 0;
    int cents = round(dollars * 100);

    // The following steps make use of the fact that dividing
    // 'cents' by some value N returns the number of times 'N'
    // can fit into 'cents', and taking the modulus of 'cents'
    // with 'N' returns the remainder.

    total_coins += cents / 25;
    cents = cents % 25;

    total_coins += cents / 10;
    cents = cents % 10;

    total_coins += cents / 5;
    cents = cents % 5;

    total_coins += cents;

    printf("%i\n", total_coins);
}
