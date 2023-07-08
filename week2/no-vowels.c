// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string word);


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Make sure to enter a word\n");
        return 1;
    }
    else
    {
    string replaced = replace(argv[1]);
    printf("%s\n", replaced);
    }
}

string replace(string word)
{
    string replaced = word;
    for (int i = 0; i<strlen(word);i++)
    {
       switch (word[i])
        {
        case 'a':
            replaced[i] = '6';
            break;
        case 'e':
            replaced[i] = '3';
            break;
        case 'i':
            replaced[i] = '1';
            break;
        case 'o':
            replaced[i] = '0';
            break;
        default:
            replaced[i] = word[i];
        }
    }
    return replaced;
}
