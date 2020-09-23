#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#define UPPERCASE 65
#define LOWCASE 97

#define LOG 0

bool checkKey(string key);

void  makeCipherText(string plainText, const string key, char * cipherText);

int main(int argc, char **argv) {

    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string key = argv[1];

    if (checkKey(key))
    {
        printf("Key must contain 26 characters a-z or A-Z\n");
        return 1;
    }

    string plainText = get_string("plaintext: ");

    char * cipherText = NULL;

    makeCipherText (plainText, key, cipherText);

    if (LOG) printf("key: %s\n", key);
    if (LOG) printf("plaintext: %s\n", plainText);

    return 0;
}

void makeCipherText(string plainText, const string key, char * cipherText) {

    unsigned int count = 0;

    for (int i = 0; plainText[i] != '\0'; i++)
        count++;

    cipherText = malloc(count * sizeof(char));

    for (int i = 0; plainText[i] != '\0'; i++)
    {
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            // calculate offset of letter in the plaintext
            int offset = plainText[i] - UPPERCASE;

            // make key uppercase if needed key=abc -> ABC
            if (key[offset] >= 'A' && key[offset] <= 'Z')
                cipherText[i] = key[offset];
            else
                cipherText[i] = (char) key[offset] - 32;


            if (LOG) printf("plainText[%i] = %c; cipherText[%i] = %c; \n", i, plainText[i], i, cipherText[i]);

        } else if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            // calculate offset of letter in the plaintext
            int offset = plainText[i] - LOWCASE;

            // make key lowcase if needed key=ABC -> abc
            if (key[offset] >= 'a' && key[offset] <= 'z')
                cipherText[i] = key[offset];
            else
                cipherText[i] = (char) key[offset] + 32;

            if (LOG) printf("plainText[%i] = %c; cipherText[%i] = %c; \n", i, plainText[i], i, cipherText[i]);
        } else
        {
            cipherText[i] = plainText[i];
            if (LOG) printf("plainText[%i] = %c; cipherText[%i] = %c; \n", i, plainText[i], i, cipherText[i]);
        }

    }

    printf("ciphertext: %s\n", cipherText);

}

bool checkKey(string key) {

    unsigned int count = 0;

    for (int i = 0; (key[i] != '\0') && (i < 26); i++)
    {
        count++;

        if ( !(key[i] >= 'A' && key[i] <= 'Z') && !(key[i] >= 'a' && key[i] <= 'z') )
            return 1;

        for (int j = i + 1; j < 26; j++)
        {
            if (key[i] == key[j])
                return 1;
        }

    }

    if (count == 26)
        return 0;

    return 1;
}
