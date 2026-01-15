/**
 * @file options.h
 * @brief Command line handling.
 *
 * This file contains the logic for command line parsing.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

/**
 * @brief Holds options for the game.
 */
typedef struct
{
    /// Word to guess.
    const char* word;

    /// File with words.
    const char* wordfile;

    /// Reset used marks.
    bool reset;

    /// Game difficulty.
    int difficulty;
} Options_t;


/**
 * @brief Parse the given commandline options.
 * @returns A struct with the parsed options.
 */
Options_t options_parse(int argc, char **argv);

#endif
