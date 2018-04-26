#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkLength(const char* arg1, const char* arg2)
{
	if(strlen(arg1) != strlen(arg2))
	{
		return 0;
	}

	return 1;
}

int checkDup(const char* arg1, const char* arg2)
{
	int i, j;
	for(i = 0; arg1[i] != 0; i++)
		for(j = i + 1; arg2[j] != 0; j++)
		{
			if(arg1[i] == arg2[j])
			{
				return 0;
			}
		}
	return 1;
}

int main(int argc, const char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "incorrect number of arguments");
		exit(1);
	}
	if(checkLength(argv[1], argv[2]) == 0)
	{
		fprintf(stderr, "from and to are of different lengths");
		exit(1);
	}
	if(checkDup(argv[1], argv[1]) == 0)
	{
		fprintf(stderr, "duplicate bytes in from");
		exit(1);
	}
	int i, j;
	char cur;
	while(!feof(stdin) && !ferror(stdin))
	{
		cur = getchar();
		for(i = 0; i < strlen(argv[1]); i++)
		{
			if(argv[1][i] == cur)
			{
				cur = argv[2][i];
			}
		}
		putchar(cur);
	}

}
 