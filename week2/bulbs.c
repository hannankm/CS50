#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");
    int n = strlen(message);
    int num;
    for (int i = 0; i < n; i++)
    {
        int x = 7;
        int byte [BITS_IN_BYTE] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        num = (int) message[i];
        while (num > 0)
        {
            byte[x] = num % 2;
            num /= 2;
            x --;
        }
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(byte[j]);
        }

        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
