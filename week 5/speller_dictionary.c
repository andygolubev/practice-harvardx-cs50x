// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 0xFFFF;

// Hash table
node * table[N] = {NULL};

// Counter for dictionary
unsigned int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // make temporary string and copy value
    char str[50] = {0};
    strcpy(str, word);

    // convert to lowcase
    for(int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }


    // Calculate 32 bit hash and convert it to 16 bit because stack size restriction
    unsigned short i = (unsigned short) hash(str);


    if (table[i-1] == NULL) // If hash is not in the array, so the word is not present in the dictionary
    {
        return false;
    }
    else // go throught linked list and look for the word
    {
        node * tmp = table[i-1];

        while (tmp->next != NULL)
        {
            if (strcmp(tmp->word, str) == 0)
                return true;

            tmp = tmp->next;
        }
        // tmp is pointing the last node, so we need to check it too
        if (strcmp(tmp->word, str) == 0)
                return true;

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    // djb2 algorithm

/*
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c;
    }

*/

     // another algorithm from the internet

   unsigned int hash;
   unsigned char *p;

   hash = 0;
   for (p = (unsigned char*)word; *p != '\0'; p++)
      hash = 31 * hash + *p;


    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // make file handler
    FILE *inptr = fopen(dictionary, "r");

    // In case of any error - exit
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 4;
    }

    // Buffer for words in the dictionary
    char buffer [50] = {0};

    // While is not eht end of file read the words
    while (EOF != fscanf(inptr, "%s", buffer))
    {
        // Calculate 32 bit hash and convert it to 16 bit because stack size restriction
        unsigned short i = (unsigned short) hash(buffer);

        // Fill the array
        if (table[i-1] == NULL)
        {
            // This case is if it is the first element in array[i]. It`s the beginning of the linked list
            table[i-1] = malloc(sizeof(node));
            if (table[i-1] == NULL)
            {
                printf("Memory allocation problem\n");
                return 1;
            }
            // copy the value from dictionary file
            strcpy(table[i-1]->word, buffer);
            // make null pointer for the next value
            table[i-1]->next = NULL;
        }
        else
        {
            // In case if a linked list is exist already
            // make temporary pointer
            node * tmp = table[i-1];

            //go to the last element in the linked list
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }

            // make a new node for value
            tmp->next = malloc(sizeof(node));
            if (tmp->next == NULL)
            {
                printf("Memory allocation problem\n");
                return 1;
            }

            // go forward to the new node
            tmp = tmp->next;
            // fill value and make null pointer to the next node
            strcpy(tmp->word, buffer);
            tmp->next = NULL;
        }

    counter++;
    }

    // close dictionary file
    fclose(inptr);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    // Free memory throught all array
    for (int i = 0; i < 0xFFFF; i++)
    {
        if (table[i] != NULL)

        {
            // Use temporary pointer. two pointers are point to the same block
            node * tmp = table[i];

            // Do loop while there is the next element in the linked list
            while (tmp->next != NULL)
            {
                // go forward. Now tmp pointer points the next block, but table[i] point to the current block
                tmp = tmp->next;
                // free current block
                free(table[i]);
                // go forward with table[i] pointer
                table[i] = tmp;
            }
            // after the loop there is a memory block under tmp pointer. we need to free it
            free(tmp);

        }

    }


    return true;
}
