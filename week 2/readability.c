#include <stdio.h>
#include <cs50.h>
#include <math.h>


int charcount (string string_text);
int wordcount (string string_text);
int sentencecount (string string_text);

int main (void)
{
    string txt = get_string("Text: ");

    int letters = charcount(txt);
    int words = wordcount(txt);
    int sentence = sentencecount(txt);

    int index = (int) round(0.0588 * ((float) letters / (float) words) * 100 - 0.296 * ((float) sentence / (float) words) * 100  - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    if (index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }

    printf("Grade %i\n", index);
    return 0;

}

int charcount (string string_text)
{
    unsigned int string_char_count = 0;
    for (int i = 0; string_text[i] != '\0'; i++)
    {
        if ( ! (string_text[i] >= 32  &&  string_text[i] <= 63))
            string_char_count++;
    }

    return string_char_count;
}

int wordcount (string string_text)
{
    unsigned int string_word_count = 0;
    for (int i = 0; string_text[i] != '\0'; i++)
    {
        if (string_text[i] == ' ')
            string_word_count++;
    }

    // If it`s the last word in a string, there won`t be a space. So, I add it manually
    return string_word_count + 1;
}

int sentencecount (string string_text)
{
    unsigned int string_sentence_count = 0;
    for (int i = 0; string_text[i] != '\0'; i++)
    {
        if (string_text[i] == '.' || string_text[i] == '!' || string_text[i] == '?')
            string_sentence_count++;
    }

    return string_sentence_count;
}
