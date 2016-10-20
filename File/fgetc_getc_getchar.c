/*

	fgetc 和 getc 区别在于前者是函数，后者是宏，getc 由 fgetc 通过宏实现；

	宏调用里不能出现有副作用的表达式，因为宏是简单的替换，所以例如 "++i" 的表达式不能出现在宏函数里；

	#define MACRO_SQRT(x) (x)*(x)       
	int func_sqrt(int x)       
	{       
		return x * x;       
	} 

	...

	int i = 2;      
	a = func_sqrt(++i);      
	printf("a = %d, i = %d\n", a, i); 
		
	...

	i = 2;      
	b = MACRO_SQRT(++i);       
	printf("a = %d, i = %d\n", b, i); 

	上述两个函数的结果是不同的；

*/


#include <stdio.h>

#define MACRO_SQRT(x) (x)*(x) 

int func_sqrt(int x)       
{       
	return x * x;       
} 

int main(int argc, char *argv[])
{
	FILE *file_handle;

	char buf[1024], char_buf;


	file_handle = fopen("file.out", "r");

	while((char_buf = fgetc(file_handle)) != EOF)
	{
		printf("%c", char_buf);
	}

	fseek(file_handle, 0, SEEK_SET);

	// getc 是宏函数，不能传入有副作用的参数
	while((char_buf = getc(file_handle)) != EOF)
	{
		printf("%c", char_buf);
	}

	char temp_char = getchar();

	printf("%c\n", temp_char);

	// 测试宏函数和普通函数
	int i = 1;
	int a = func_sqrt(++i);      
	printf("a = %d, i = %d\n", a, i); 
		
	int j = 2;      
	int b = MACRO_SQRT(++j);       
	printf("a = %d, i = %d\n", b, i); 

	fclose(file_handle);
	
	return 0;
}