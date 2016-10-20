/*
		
	1、从历史来看，scanf 系列函数的具体实现均有漏洞；
	2、它们的使用不够灵活；
	3、用它们编写的代码不容易看出正在解析什么；

	# *推荐使用 fread 或 fgets 来获取输入行，用字符串函数来分解输入的参数； 

*/

#include <stdio.h>

int main(int argc, char *argv[])
{
	int num;

	// 格式字符串中的空格用于过滤输入数据中的各种空白字符；
	// "Hello1234" 和 "Hello  1234" 均是有效的；
	scanf("Hello %d", &num);

	printf("%d\n", num);


	char s[256];

	int n;

	float f;

	char c;

	// 返回值是成功读取的数据项个数
	scanf("Hello, %d, %g, %c, %[^\n]", &n, &f, &c, s);



	FILE *file_handle;

	char r[1024], ss[128];

	file_handle = fopen("file.out", "r");

	fscanf(file_handle, "%s", r);

	printf("%s\n", r);


	
	sscanf("sscanf", "%s", ss);

	printf("%s\n", ss);
}