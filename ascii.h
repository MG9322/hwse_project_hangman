/**
 * @file ascii.h
 * @brief ASCII art strings.
 */

#ifndef HANGMAN_H
#define HANGMAN_H

/**
 * @brief Returns the string for an ASCII graphic.
 * @param misses  The number of times the player has missed the character.
 * @returns A string depicting a hangman ASCII graphic.
 */
const char* hangman_string(int misses);

#endif
