/**
 * @file utils.c
 * @brief Utilities implementation.
 */

#include "utils.h"

#include <stdlib.h>
#include <ctype.h> // tolower()


int get_random_number(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


char* strchr_case_insensitive(const char* string, char character)
{
    // Search for the letter in both uppercase and lowercase variants
    char lower = tolower(character);
    char upper = toupper(character);

    // Search as long as we have not reached the end of the string
    while (*string != '\0')
    {
        if (*string == lower || *string == upper)
            return (char*)string;  // Return the pointer to the occurrence
        string++;
    }
    return NULL;
}
