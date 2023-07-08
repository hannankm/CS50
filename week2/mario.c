#include <cs50.h>
#include <stdio.h>

int main(void)
{
//accept the height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int j = 1; j <= height; j++)
    {
        for (int y = height - j; y > 0 ; y--)
        {
            printf(" ");
        }
        for (int x = 0; x < j; x++)
        {
            printf("#");
        }
        printf("  ");
        for (int x = 0; x < j; x++)
        {
            printf("#");
        }
        printf("\n");

    }


}
