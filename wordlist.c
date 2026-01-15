/**
 * @file wordlist.c
 * @brief Word file functions implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "wordlist.h"


/**
 * @brief Read a whole file into memory.
 * @param filename File name to read.
 */
static char* read_file_contents(const char* filename, long* out_size)
{
    *out_size = -1;  /* default on error */

    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("fopen");
        return NULL;
    }

    // Find file content size
    if (fseek(file, 0, SEEK_END) != 0)
    {
        perror("fseek");
        fclose(file);
        return NULL;
    }
    long size = ftell(file);
    if (size < 0)
    {
        perror("ftell");
        fclose(file);
        return NULL;
    }
    rewind(file);

    // Allocate buffer for file contents + null terminator
    char* buffer = malloc((size_t)size + 1);
    if (buffer == NULL)
    {
        perror("malloc buffer");
        fclose(file);
        return NULL;
    }

    // Read into buffer
    if (fread(buffer, 1, (size_t)size, file) != (size_t)size)
    {
        perror("fread");
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[size] = '\0';  /* Null-terminate */

    fclose(file);
    *out_size = size;
    return buffer;
}

/**
 * @brief Count the number of lines in a file.
 */
static size_t count_lines(const char* string)
{
    size_t count = 0;
    if (!string || !*string)
    {
        return 0;
    }

    const char* p = string;
    while (*p)
    {
        if (*p == '\n')
        {
            count++;
        }
        p++;
    }

    // Handle case if last line doesn't end with newline.
    if (p > string && *(p - 1) != '\n')
    {
        count++;
    }

    return count;
}

/*
 * split_lines_in_place():
 *   Modifies the buffer by replacing each '\n' with '\0'. The pointers array
 *   (lines) is filled so that each element points to the start of a line
 *   within buffer.
 *
 *   If the buffer doesn't end with a '\n', the portion after the last '\n'
 *   is considered one final line.
 *
 *   lines must be large enough to hold line_count pointers plus one NULL
 *   sentinel. The actual line_count should match the number from count_lines().
 *
 *   Returns the number of lines actually set in lines[].
 */
static size_t split_lines_in_place(char* buffer, char** lines, size_t line_count)
{
    size_t idx = 0;
    char* start = buffer;
    char* p = buffer;

    while (*p)
    {
        if (*p == '\n')
        {
            *p = '\0';         /* terminate this line */
            lines[idx++] = start;
            start = p + 1;     /* next line starts after '\n' */
        }
        p++;
    }

    /* If there's leftover text not ended by '\n' and buffer not empty */
    if (start < p)
    {
        lines[idx++] = start;
    }

    lines[idx] = NULL;  /* Sentinel */
    return idx;
}

/*
 * read_file_lines():
 *   1) Get file size.
 *   2) Allocate for array-of-pointers + file content in one block.
 *   3) Read file content into the text region.
 *   4) Count lines & replace '\n' with '\0' to split lines.
 *   5) Fill lines[] with pointers to each line in the buffer.
 *
 * Returns an array of char* (with a NULL sentinel at the end), or NULL on error.
 * A single free() call (on the returned pointer) will free all memory.
 */
WordList_t WordList_new_from_file(const char* filename)
{
    long tmp_size;
    char* tmpbuf = read_file_contents(filename, &tmp_size);
    if (!tmpbuf)
    {
        return NULL;
    }

    size_t line_count = count_lines(tmpbuf);
    size_t pointers_size = (line_count + 1) * sizeof(char* );
    size_t text_size = (size_t)tmp_size + 1;  // +1 for null terminator
    size_t total_size = pointers_size + text_size;

    char** lines = malloc(total_size);
    if (lines == NULL)
    {
        perror("malloc lines");
        free(tmpbuf);
        return NULL;
    }

    char* buffer = (char*) (lines + (line_count + 1));

    memcpy(buffer, tmpbuf, (size_t)tmp_size + 1);

    free(tmpbuf);

    split_lines_in_place(buffer, lines, line_count);

    return lines;
}

void WordList_write_to_file(WordList_t words, const char* filename)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    for(int i = 0; words[i] != NULL; i++)
    {
        fprintf(file, "%s\n", words[i]);
    }

    fclose(file);
}

/**
 * @brief Mark for already used words.
 */
static const char MARK_USED = '!';

/**
 * @brief Mark not yet used words.
 */
static const char MARK_UNUSED = '?';

void WordList_reset_marks(WordList_t words)
{
    for(int i = 0; words[i] != NULL; i++)
    {
        words[i][0] = MARK_UNUSED;
    }
}

size_t WordList_get_number_of_words(WordList_t words)
{
    size_t result = 0;

    while(words[result] != NULL)
    {
        result++;
    }

    return result;
}

const char* WordList_get_next_unused_random_word(WordList_t words)
{
    size_t size = WordList_get_number_of_words(words);
    int number = get_random_number(0, size-1);

    for (int i = 0; i < size; i++)
    {
        if(words[number][0] == MARK_UNUSED)
        {
            words[number][0] = MARK_USED;
            return words[number] + 1;
        }
        number = number + 1;
        number = number % size;
    }

    // Instead of returning an error, reset marks and try again.

    WordList_reset_marks(words);

    return WordList_get_next_unused_random_word(words);
}

void WordList_free(WordList_t words)
{
    free(words);
}
