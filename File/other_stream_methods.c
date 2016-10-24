#include <stdio.h>

int main(int argc, char *argv[]) 
{
	FILE *file_handle;

	char outbuf[1024];

	fpos_t position;

	file_handle = fopen("file.out", "w+");


	// Setbuf
	setbuf(stdout, outbuf); 

    puts("This is a test of buffered output.\n");

    puts(outbuf);

    fflush(stdout);

    puts(outbuf); 

    // Setvbuf
    




	fgetpos(file_handle, &position);

    fputs("Hello, World!", file_handle);



    long fp = ftell(file_handle);

    printf("The current file indicator position is: %ld\n", fp);


  	rewind(file_handle);
    // fsetpos(file_handle, &position);

    fputs("This is going to override previous content", file_handle);

    // Unlink file
    remove("file.in");


    fclose(file_handle);

}