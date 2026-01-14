/**
 * @file options.c
 * @brief Command line handling implementation.
 */

#include "options.h"

#ifdef _WIN32
#include <windows.h>
#include <getopt.h>
#else
#define _POSIX_C_SOURCE 2
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Display program help.
 * @param The program executable name (as in argv[0]).
 */
static void print_help(const char* program_name)
{
    printf(
        "%s - Hangman Game\n"
        "    -w WORD    Play with a single word.                \n"
        "    -f FILE    Play with random words from a file.     \n"
        "    -r         Reset used/unused markings. Use with -f.\n"
        "    -d NUMBER  Set game difficulty.                    \n"
        "    -h         Show help.                              \n"
        , program_name);
}


Options_t options_parse(int argc, char **argv)
{
    Options_t options = {0};

    char c;
    while ((c = getopt (argc, argv, "w:f:d:rh")) != -1)
    {
        switch (c)
        {
        case 'w':
            options.word = optarg;
            break;
        case 'f':
            options.wordfile = optarg;
            break;
        case 'd':
            options.difficulty = atoi(optarg);
            break;
        case 'r':
            options.reset = true;
            break;
        default:
            printf("Wrong commandline option\n");
        case 'h':
            print_help(argv[0]);
            exit(1);
            break;
        }
    }
    return options;
}
