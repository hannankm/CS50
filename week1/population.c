#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int starting_population;
    do
    {
        starting_population = get_int("Start size: ");
    }
    while (starting_population < 9);

    // TODO: Prompt for end size
    int ending_population;
    do
    {
        ending_population = get_int("End Size: ");
    }
    while (ending_population < starting_population);


    // TODO: Calculate number of years until we reach threshold
    int year = 0;
    while (starting_population < ending_population)
    {
        starting_population = starting_population + starting_population / 3 - starting_population / 4;
        year++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", year);
}
