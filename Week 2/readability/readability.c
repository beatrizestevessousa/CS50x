#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Average of letter per 100 words
    float l = (float) letters / (float) words * 100;

    // Average of sentences per 100 words
    float s = (float) sentences / (float) words * 100;

    // Index grade
    float index = 0.0588 * l - 0.296 * s - 15.8;

    if ((int) index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((int) index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

// Counting the number of letters
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Check if it is a letter
        if (islower(text[i]) != 0 || isupper(text[i]) != 0)
        {
            count += 1;
        }
    }
    return count;
}

// Counting the number of words
int count_words(string text)
{
    int count = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Check if is a space
        if (isspace(text[i]) != 0)
        {
            count += 1;
        }
    }
    return count;
}

// Counting the number of sentences
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Check if it is a punctuation signal
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count += 1;
        }
    }
    return count;
}
