#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


bool ignorecase = false;

unsigned char decode(char a)
{
	a = a ^ 42;
	if(ignorecase)
	{
		a = toupper((unsigned char)a);
	}
	return a;
}

int frobcmp(const void* arr_a, const void* arr_b)
{
const char* a = *(char **) arr_a;
const char* b = *(char **) arr_b; //type casting and dereferencing to get pointers to two char arrays
while((*a != ' ') && (*b != ' '))
{
    if (decode(*a) < decode(*b))
    {
    	return -1;
    }
    else if (decode(*a) > decode(*b))
    {
    	return 1;
    }
    else 
    {
    	a++;
        b++;
    }
}
if((*a == ' ') && (*b == ' '))
{
	return 0;
}
if((*a == ' ') && (*b != ' '))
{
	return -1;
}
if((*a != ' ') && (*b == ' '))
{
	return 1;
}

}

int main(int argc, char *argv[])
{
if(argc == 2 || argc == 3)
	if (strncmp (argv[1], "-f", 2) == 0) //c requires strncmp to compare strings
	{
		ignorecase = true; 
	}

struct stat fileStat; //to get info about the file
int length;  //length of the file

if(fstat(0, &fileStat) < 0)
{
	fprintf(stderr, "file stat error");
	exit(1);
}

if(S_ISREG(fileStat.st_mode)) //if it is a regular file
{
	length = fileStat.st_size;
}

else
{
	length = 0;
}

//printf("%s\n", length);
char* word = (char*)malloc(length * sizeof(char)); //pointer to all the characters in one array
int letter_i = 0; //keeps count of the number of letters
int size = 0; //iterator for the array of characters
char** wordList = (char**)malloc(sizeof(char*)); //array of pointers to words
int word_i = 0; //word iterator
int startWord = 0;
char cur = ' ';

while(read(0, &cur, 1) > 0) //checks for errors (EOF or other error)
{
	if(size >= length) //need to reallocate as it goes if it is not regular
	{
		length++;
		word = realloc(word, length * sizeof(char));
		if(word == NULL)
		{
		fprintf(stderr, "error in memory allocation");
		exit(1);
		}
	}

	if (cur == ' ' && letter_i == 0) //ignores consecutive spaces and leading space
	{
		continue;
	}

	word[size] = cur;
	letter_i++;
	size++;

	if (cur == ' ') 
	{
		wordList = realloc(wordList, (word_i + 1) * sizeof(char*)); //add word to wordlist
		if(wordList == NULL)
		{
			fprintf(stderr, "error in memory allocation");
			exit(1);
		}

		wordList[word_i] = word + startWord;
		word_i++;
		startWord = startWord + letter_i; //move word pointer to point to next word
		letter_i = 0; //reset letter adding once word is added to wordlist
	}
}

//if standard input ends in a partial record with no trailing space
if (letter_i != 0)
{
	length++;
	//add space to word
	word = realloc(word, length * sizeof(char)); //add character

	if(word == NULL)
	{
		fprintf(stderr, "error in memory allocation");
		exit(1);
	}

	word[size] = ' ';

	//add word to list

	wordList = realloc(wordList, (word_i + 1) * sizeof(char*)); //add word to wordlist
	wordList[word_i] = word + startWord;
	word_i++;

	if(wordList == NULL)
	{
		fprintf(stderr, "error in memory allocation");
		exit(1);
	}

}
//sort
qsort(wordList, word_i, sizeof(char*), frobcmp);
int i;
int j;
char c;
char space = ' ';
for (i = 0; i < word_i; i++) //output the characters
{
	for(j=0; wordList[i][j] != ' '; j++)
	{
		c = wordList[i][j];
		if(write(1, &c, 1) < 1) //write character
		{
			fprintf(stderr, "error in writing");
			exit(1);
		}
	}

	if(write(1, &space, 1) < 1) //write space
	{
		fprintf(stderr, "error in writing");
		exit(1);
	}
}

free(word);
free(wordList); //free the array of character pointers

exit(0);
}