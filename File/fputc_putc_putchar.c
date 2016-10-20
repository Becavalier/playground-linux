#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *file_handle;


	file_handle = fopen("file.out", "w+");

	fputc('f', file_handle);
	fputc('p', file_handle);
	fputc('u', file_handle);
	fputc('t', file_handle);
	fputc('c', file_handle);
	fputc('\n', file_handle);

	// putc 同 getc 一样，可能被实现为宏函数，所以参数不能是有副作用的；
	putc('p', file_handle);
	putc('u', file_handle);
	putc('t', file_handle);
	putc('c', file_handle);
	putc('\n', file_handle);

	putchar('p');
	putchar('u');
	putchar('t');
	putchar('c');
	putchar('h');
	putchar('a');
	putchar('r');
	putchar('\n');

	fclose(file_handle);
	
	return 0;
}