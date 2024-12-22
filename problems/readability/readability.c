#include <cs50.h>
#include <stdio.h>

int main(void)
{

    string text = get_string("Text: ");

    int i = 0;
    int letters = 0;
    int words = 0;
    int sentences = 0;
    while (text[i] != '\0')
    {

        char char_at_i = text[i];

        if ((char_at_i >= 97 && char_at_i <= 122) || (char_at_i >= 65 && char_at_i <= 90))
        {
            letters++;
        }
        else if (char_at_i == 32)
        {
            words++;
        }
        else if (char_at_i == 46 || char_at_i == 63 || char_at_i == 33)
        {
            sentences++;
        }

        i++;
    }
    words++;


    float level = (0.0588 * (letters * 1.0 / words * 100) - 0.296 * (sentences * 1.0 / words * 100) - 15.8);

    if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", level);
    }

}


