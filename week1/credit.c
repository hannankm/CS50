#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // accept credit card number
    long number = get_long("Number: ");
    long credit_card = number;
    int total = 0;
    int digit = 0;
    int num = 3;
    int num1;
    int num2;
    int digits = 0;
    while (number > 0)
    {
        if (number < 100 && number >= 10)
        {
            num2 = number;
        }

        if (number < 10)
        {
            num1 = number;
        }

        digit = number % 10;
        if (num % 2 == 0)
        {
            digit = digit * 2;
            int sum = 0;
            int dig;
            while (digit > 0)
            {
                dig = digit % 10;
                sum += dig;
                digit /= 10;
            }
            total += sum;
        }
        else
        {
            total += digit;
        }
        number /= 10;
        num++;
        digits += 1;
    }

    if (total % 10 == 0)
    {
        if (num1 == 4 && (digits == 13 || digits == 16))
        {
            printf("VISA\n");
        }
        else if ((num2 == 34 || num2 == 37) && digits == 15)
        {
            printf("AMEX\n");
        }

        else if ((num2 == 51 || num2 == 52 || num2 == 53 || num2 == 54 || num2 == 55) && digits == 16)
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
