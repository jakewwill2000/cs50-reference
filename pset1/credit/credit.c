#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool is_valid_card(long card);
string card_type(long card);
int digit_at_index(long num, int index);
int sum_of_digits(long num);
int num_digits(long num);

int main(void) {
    long card;

    do {
        card = get_long("Number: ");
    } while (card < 0);

    if (!is_valid_card(card)) {
        printf("INVALID\n");
    } else {
        string type = card_type(card);
        printf("%s\n", type);
    }
}

bool is_valid_card(long card) {
    if (card < pow(10, 12) || card >= pow(10, 16)) {
        return false;
    }

    int digits_sum = 0;

    long current = card / 10;
    while (current > 0) {
        digits_sum += sum_of_digits(digit_at_index(current, 0) * 2);
        current /= 100;
    }

    current = card;
    while (current > 0) {
        digits_sum += digit_at_index(current, 0);
        current /= 100;
    }

    return (digits_sum % 10 == 0);
}

string card_type(long card) {
    int first_two = card / pow(10, num_digits(card) - 2);

    if (first_two > 50 && first_two < 56) {
        return "MASTERCARD";
    }

    if (first_two == 34 || first_two == 37) {
        return "AMEX";
    }

    int first = card / pow(10, num_digits(card) - 1);
    if (first == 4) {
        return "VISA";
    }

    return "INVALID";
}

int digit_at_index(long num, int index) {
    long current = num;

    for (int i = 0; i < index; i++) {
        current = num / 10;
    }

    return current % 10;
}

int sum_of_digits(long num) {
    int total = 0;

    long current = num;
    while (current > 0) {
        total += current % 10;
        current /= 10;
    }

    return total;
}

int num_digits(long num) {
    int count = 0;
    while (num > 0) {
        num /= 10;
        count += 1;
    }

    return count;
}
