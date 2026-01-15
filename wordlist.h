/**
 * @file wordlist.h
 * @brief Word file functions.
 *
 * This file contains logic for the word file.
 * The word file holds words for the player to guess.
 * The file format is one word per line and a marker at the start of the line.
 * The marker is '?' for words that have not been used yet and '!' for words that have been used.
 */
#ifndef WORDLIST_H
#define WORDLIST_H

#include <stddef.h>

typedef char** WordList_t;

/**
 * @brief Read word list from a file.
 * @param filename The file name.
 */
WordList_t WordList_new_from_file(const char* filename);

/**
 * @brief Write word list to a file.
 * @param words The word list.
 * @param filename The file name.
 */
void WordList_write_to_file(WordList_t words, const char* filename);

/**
 * @brief Get a random word that has not been used before.
 * @param words The word list.
 * @return An unused word or NULL.
 */
const char* WordList_get_next_unused_random_word(WordList_t words);

/**
 * @brief Get the number of words in the word list.
 * @param words The word list.
 * @return The number of words in the word list.
 */
size_t WordList_get_number_of_words(WordList_t words);

/**
 * @brief Reset all words to unused.
 * @param words The word list.
 */
void WordList_reset_marks(WordList_t words);

/**
 * @brief Free the word list.
 * @param words The word list.
 */
void WordList_free(WordList_t words);

#endif
