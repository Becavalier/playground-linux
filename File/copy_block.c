#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * 其他的系统调用：
 *
 * lseek 设置文件的下一个读写位置
 * off_t lseek(int fildes, off_t offset, int whence);
 *
 * fstat\stat\lstat 得到关于文件的状态信息
 * int fstat(int fildes, struct stat *buf);
 * int stat(const char *path, struct stat *buf);
 * int lstat(const char *path, struct stat *buf);
 *
 * dup\dup2 复制文件描述符
 * int dup(int fildes);
 * int dup2(int fildes, int fildes2);
 */

int main() {
	char block[1024];
	int in, out;
	int nread;

	in = open("file.in", O_RDONLY);
	out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	while((nread = read(in, block, sizeof(block))) > 0) {
		write(out, block, nread);
	}
}