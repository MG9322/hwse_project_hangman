
Hangman
=======

Features
--------

* Main Task 1
  * Supply the word to guess on the command line (Option -w).
  * Let the user guess character by character.
  * Do not distinguish between lower- and uppercase characters
  * Write to log file.
* Task 2
  * Allow the user to directly guess the whole word
* Task 3
  * Support multiple game rounds without restarting the game.
  * Supply a new word for each round in a sensible way.
* Task 4 
  * Instead of supplying the word directly the user has to specify an input file that contains possible words to guess (Option -f).
  * Select any word from that list at random.
* Task 5 
  * Mark used words persistently in the word input file (? or ! at the beginning of a line).
  * Exclude previously used words when selecting a random word.
  * Allow the user to reset the markers in the file. (Option -r)
* Task 6 
  * Draw the interface using ASCII art
* Task 7
  * The program arguments are handled by `getopt(3)`.


Command line arguments
----------------------

-w WORD   Play with a single word.

-f FILE   Play with random words from a file.

-r        Reset used/unused markings. Use with -f.

-d NUMBER Difficulty.

-h        Show help.

Word list format.
-----------------
Words can be supplied from a file.
The file format is one word per line and a marker at the start of the line.
The marker is '?' for words that have not been used yet and '!' for words that have been used.

Documentation
-------------
Functions are documented with doxygen annotations.
Public functions are annotated in the header files,
private function in the source files.
generate doxygen documentation with: make doc 
