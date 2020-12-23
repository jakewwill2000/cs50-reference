#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool is_valid_card(long card);
string card_type(long card);
int digit_at_index(long num, int index);
int sum_of_digits(long num);
int num_digits(long num);

int main(void)
{
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card < 0);

    if (!is_valid_card(card))
    {
        printf("INVALID\n");
    }
    else
    {
        string type = card_type(card);
        printf("%s\n", type);
    }
}

// This function accepts a long 'card' which represents a potential credit
// card number. It then passes this card through Luhn's algorithm to determine
// whether it is valid, and returns the boolean result.

bool is_valid_card(long card)
{
    // If the card has fewer than 13 or more than 16 digits, automatically
    // return false, as it must be invalid.
    if (card < pow(10, 12) || card >= pow(10, 16))
    {
        return false;
    }

    // Represents the formula for the sum of digits described in Luhn's algorithm.
    int digits_sum = 0;

    // Starting from the second to last digit, we add the sum of the digits of
    // every other digit in 'card' multiplied by 2.
    long current = card / 10;
    while (current > 0)
    {
        digits_sum += sum_of_digits(digit_at_index(current, 0) * 2);
        current /= 100;
    }

    // Add the digits that weren't counted above to the total.
    current = card;
    while (current > 0)
    {
        digits_sum += digit_at_index(current, 0);
        current /= 100;
    }

    // If digits_sum ends with a zero, return true, otherwise false.
    return (digits_sum % 10 == 0);
}

// This function accepts a long 'card' and determines which type of card
// (VISA, MASTERCARD, or AMEX) it is. We assume that the card that is
// passed in is valid according to Luhn's algorithm, but may still be
// invalid if the requirements for any of the options are not met.

string card_type(long card)
{
    // Obtain the integer represented by the two leftmost digits of 'card'
    int first_two = card / pow(10, num_digits(card) - 2);

    if (first_two > 50 && first_two < 56 && num_digits(card) == 16)
    {
        return "MASTERCARD";
    }

    if (first_two == 34 || first_two == 37 && num_digits(card) == 15)
    {
        return "AMEX";
    }

    // VISA cards are slightly different - we don't need to confirm that
    // the length is correct because our is_valid_card function already
    // determines that the card must be between 13 and 16 digits long.
    // We only need to verify that it begins with a 4.

    int first = card / pow(10, num_digits(card) - 1);
    if (first == 4)
    {
        return "VISA";
    }

    // If the card does not pass any of the above checks, we return that
    // it is invalid.
    return "INVALID";
}

// This function returns the digit located at 'index' steps from the
// right in 'num'.

int digit_at_index(long num, int index)
{
    // Remove the last digit 'index' times from 'num' by dividing by 10.
    for (int i = 0; i < index; i++)
    {
        num = num / 10;
    }

    return num % 10;
}

// This function returns the sum of the digits of 'num'.

int sum_of_digits(long num)
{
    int total = 0;
    while (num > 0)
    {
        total += num % 10;
        num /= 10;
    }

    return total;
}

// This function returns the number of digits in 'num'

int num_digits(long num)
{
    int count = 0;
    while (num > 0)
    {
        num /= 10;
        count += 1;
    }

    return count;
}
