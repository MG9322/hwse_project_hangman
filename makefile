
.PHONY : all doc

all : hangman.exe

doc :
	doxygen doxygen.conf

hangman.exe : main.c ascii.c options.c wordlist.c utils.c
	gcc -std=c99 -Wall -Wpedantic -Wno-unused-parameter $^ -o $@
