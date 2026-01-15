/**
 * @file main.c
 * @brief Main game logic for Hangman game.
 *
 * This file contains the implementation of the Hangman game logic.
 */

#include "ascii.h"
#include "options.h"
#include "wordlist.h"
#include "utils.h"


#include <stdio.h> // FILE*, fclose(), fopen(), fprintf(), printf(), getchar()
#include <string.h> // memset(), strcmp(), strlen()
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> // srand()




/**
 * @brief Write the current time to a file (without trailing newline).
 * @param file The file to write to.
 */
static void log_time(FILE* file)
{
    char buff[20];
    struct tm *sTm;

    time_t now = time (0);
    sTm = gmtime (&now);

    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    fprintf(file, "%s: ", buff);
}

/**
 * @brief Get a character other than newline.
 * @returns Any character but '\n'
 */
static char get_char (void)
{
    char c;
    while((c = getchar()) == '\n')
    { }

    return c;
}

/**
 * @brief Ask the user a yes-or-no question.
 * @param question The question text to display.
 * @returns True if the user chooses 'yes'.
 */
static bool ask_yes_no(const char* question)
{
    while(1)
    {
        printf("%s (y/n) ", question);
        char c = get_char();
        if(c == 'y')
        {
            //~ getchar();
            return true;
        }
        else// if(c == 'n')
        {
            return false;
        }
    }
}

/**
 * @brief Search and replace a character.
 * Find a character in a string and copy it to another string.
 * @param word The (hidden) word.
 * @param visible The visible characters of a word.
 * @param character The character in question.
 * @returns True if found.
 */
static bool search_replace_char(const char* word, char* visible, char character)
{
    bool found = false;
    const char* position = word;
    while ((position = strchr_case_insensitive(position, character)) != NULL)
    {
        int index = position - word;
        visible[index] = word[index];
        position++;
        found = true;
    }
    return found;
}

/**
 * @brief Play a round (a single word) of hangman.
 * @param word The word to find.
 */
static bool play_hangman(const char* word, FILE* logfile)
{
    int wordlaenge = strlen(word);
    char visible[wordlaenge+1];
    int misses = 0;

    fprintf(logfile, "-------------------\n");
    log_time(logfile);
    fprintf(logfile, "Game started\n");
    fprintf(logfile, "Word:       \"%s\"\n", word);

    memset(visible, '?', wordlaenge);
    //~ memset(buchstaben, '\0', sizeof(buchstaben));
    visible[wordlaenge] = '\0';

    char eingabe;
    while(misses < 10)
    {
        // Clear the terminal
        //~ printf("\033[2J");

        // Move the cursor to the beginning
        //~ printf("\033[1;1H");

        printf("Fehlversuche:   %d\n", misses);
        printf("Sichtbar:   \"%s\"\n", visible);


        log_time(logfile);
        fprintf(logfile, "Sichtbar:   \"%s\"\n", visible);
        fflush(logfile);
        //~ printf("Buchstaben: \"%s\"\n", buchstaben);

        printf("Hangman: \n%s\n", hangman_string(misses));

        // "Gewonnen" if the strings are equal
        if(strcmp(word, visible) == 0)
        {
            return true;
        }

        // Read letters from the user
        eingabe = getchar();

        // Ignore and skip newline
        if(eingabe == '\n')
            eingabe = getchar();

        // Find the entered lette
        if(!search_replace_char(word, visible, eingabe))
        {
            // Letter not found
            misses = misses + 1;
        }

        //~ buchstaben[strlen(buchstaben)] = eingabe;
    }

    // Verloren.
    return false;
}

/**
 * @brief Play multiple rounds of hangman with a list of words.
 * @param wordfile The filename of the word file to use.
 * @param logfile The log file.
 */
static void play_hangman_multiple_random(const char* wordfile, FILE* logfile)
{
    char** words = WordList_new_from_file(wordfile);
    size_t size = WordList_get_number_of_words(words);
    for(int round = 0; round < size; round++)
    {
        const char* word = WordList_get_next_unused_random_word(words);
        play_hangman(word, logfile);

        WordList_write_to_file(words, "words.txt");

        if(!ask_yes_no("Play another round?"))
            break;

    }
}

/**
 * @brief Main entry point.
 * @param argc The number (count) of commandline arguments.
 * @param argv The array (vector) of commandline arguments.
 */
int main(int argc, char* argv[])
{
    srand(time(NULL));
    FILE* logfile = fopen("logfile.txt", "a");

    log_time(logfile);
    fprintf(logfile, "Program started\n");

    Options_t options = options_parse(argc, argv);

    if(options.word != NULL)
    {
        play_hangman(options.word, logfile);
    }

    if(options.wordfile != NULL)
    {
        if(options.reset == true)
        {
            WordList_t words = WordList_new_from_file(options.wordfile);
            WordList_reset_marks(words);
            WordList_write_to_file(words, options.wordfile);
        }

        play_hangman_multiple_random(options.wordfile, logfile);
    }

    printf("Game ended.\n");

    log_time(logfile);
    fprintf(logfile, "Game ended.\n");

    fclose(logfile);

    return 0;
}
