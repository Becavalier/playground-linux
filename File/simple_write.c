#include <unistd.h>
#include <stdlib.h>

int main() {

	/**
	 * fildes: 0（标准输入）, 1（标准输出）, 2（错误输出）
	 * prototype： size_t write(int fildes, const void *buf, size_t nbytes);
	 */

	if (write(1, "Here is some data\n", 18) != 18) {
		write(2, "A wirte error has occurred on file descriptor 1\n", 46);
	}

	exit(0);
}