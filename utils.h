/**
 * @file utils.h
 * @brief Utilities
 */


#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Return a random number within a given range.
 * @param min Minimum value.
 * @param max Maximum value.
 * @returns A random number.
 */
int get_random_number(int min, int max);

/**
 * @brief Find a character in a string and ignore case.
 * @returns Pointer to the first occurance or NULL.
 */
char* strchr_case_insensitive(const char* string, char character);

#endif
