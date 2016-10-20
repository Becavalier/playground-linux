#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *file_handle;

	char *s = (char *) malloc(1024 * sizeof(char)); 

	char *k = (char *) malloc(1024 * sizeof(char));


	file_handle = fopen("file.out", "r");

	while(fgets(s, 1024, file_handle) != NULL)
	{
		printf("%s", s);
	}

	// gets 函数遇到换行符会被丢弃，然后在末尾添加 '\0' 字符;
	printf("%s\n", gets(k));

}