#include <stdio.h>
#include <stdlib.h>

int frobcmp(const void* arr_a, const void* arr_b)
{
const char* a = *(char **) arr_a;
const char* b = *(char **) arr_b; //type casting and dereferencing to get pointers to two char arrays
while((*a != ' ') && (*b != ' '))
{
    if ((*a ^ 42) < (*b ^ 42))
    {
    	return -1;
    }
    else if ((*a ^ 42) > (*b ^ 42))
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

int main(void)
{
char* word = (char*)malloc(sizeof(char)); //pointer to word
int letter_i = 0; //letter iterator
char** wordList = (char**)malloc(sizeof(char*)); //array of pointers to words
int word_i = 0; //word iterator

char cur;

while(!feof(stdin) && !ferror(stdin))
{
	cur = getchar();
	if (ferror(stdin)) 
	{
		fprintf(stderr, "error in reading");
		exit(1);
	}

	if (cur == ' ' && letter_i == 0) //repeat loop and ignore this character if there is no word and just a space
	{
		continue;
	}

	if (cur == EOF) //exit loop if reached end of file
	{
		break;
	}

	word = realloc(word, (letter_i + 1) * sizeof(char)); //add character
	word[letter_i] = cur;
	letter_i++;

	if(word == NULL)
	{
		fprintf(stderr, "error in memory allocation");
		exit(1);
	}

	if (cur == ' ' && letter_i > 1) //letter_i will never be == 1 as the minimum is one letter + sp
	{
		wordList = realloc(wordList, (word_i + 1) * sizeof(char*)); //add word to wordlist
		wordList[word_i] = word;
		word_i++;

		if(wordList == NULL)
		{
			fprintf(stderr, "error in memory allocation");
			exit(1);
		}

		letter_i = 0; //reset letter adding once word is added to wordlist
		word = NULL; //free word pointer by pointing it elsewhere and allocating memory again
		word = (char*)malloc(sizeof(char)); 

	}
}

//if standard input ends in a partial record with no trailing space
if (letter_i != 0)
{
	//add space to word
	word = realloc(word, (letter_i + 1) * sizeof(char)); //add character
	word[letter_i] = ' ';

	if(word == NULL)
	{
		fprintf(stderr, "error in memory allocation");
		exit(1);
	}

	//add word to list

	wordList = realloc(wordList, (word_i + 1) * sizeof(char*)); //add word to wordlist
	wordList[word_i] = word;
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
for (i = 0; i < word_i; i++) //output the characters
{
	for(j=0; wordList[i][j] != ' '; j++)
	{
		if(putchar(wordList[i][j]) == EOF)
		{
			fprintf(stderr, "error in outputting");
			exit(1);
		}
	}

	putchar(' ');
}

for(i = 0; i < word_i; i++)
{
	free(wordList[i]); //free each word (character pointer) within the list
}

free(wordList); //free the array of character pointers

exit(0);
}