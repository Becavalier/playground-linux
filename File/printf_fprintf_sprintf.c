#include <stdio.h>

int main(int argc, char *argv[])
{
	char initial = 'A';

	char *surname = "Jason";

	float age = 12.5l;


	// %d %o %x %g %f %c %s %e
	printf("Some Numbers: %d %d %d\n", 1, 2, 3);

	printf("Hello Mr %c %s, age %g",initial, surname, age);

	// 宽度为 10 靠右；
	printf("%10s", "Hello");
	// 宽度为 10 靠左；
	printf("%-10s", "Hello");

	printf("%010d", 1234);

	printf("%010.40f\n", 1234.123);

	// 可变字段宽度用 "*"，下一个参数为字段宽度；
	printf("%*s", 10, "Hello");



	char s[1024];

	sprintf(s, "sprinf");

	printf("%s\n", s);


	FILE *file_handle;

	file_handle = fopen("file.out", "w+");

	fprintf(file_handle, "fprintf\n");

	fclose(file_handle);
}