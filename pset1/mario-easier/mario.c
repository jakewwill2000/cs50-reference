#include <cs50.h>
#include <stdio.h>

void print_chars(char c, int n);

int main(void) 
{
    int height;
    do 
    {
        height = get_int("Enter the height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++) 
    {
        print_chars(' ', height - i);
        print_chars('#', i);

        printf("\n");
    }
}

// This function prints the character 'c', 'n' times

void print_chars(char c, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        printf("%c", c);
    }
}
