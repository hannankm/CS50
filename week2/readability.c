#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int calculate_grade(string);

int main(void)
{
    string text = get_string("Text: ");
    int grade = calculate_grade(text);
    if (grade >= 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int calculate_grade(string word)
{
    int index;
    int letters = 0;
    int sentences = 0;
    int words = 1;
    float L;
    float S;
    int n = strlen(word);

    for (int i = 0; i < n; i++)
    {
        if (islower(word[i]) || isupper(word[i]))
        {
            letters += 1;
        }
        else if ((word[i]) == '.' || (word[i]) == '?' || (word[i]) == '!')
        {
            sentences += 1;
        }
        else if (isspace(word[i]))
        {
            words += 1;
        }
    }
    L = (letters / (float) words) * 100;
    S = (sentences / (float) words) * 100;
    index = round((0.0588 * L) - (0.296 * S) - 15.8);
    return index;
}
// index = 0.0588 * L - 0.296 * S - 15.8
// L is the average number of letters per 100 words in the text
// S is the average number of sentences per 100 words in the text
// [] {  }
