#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	/**
	 * man 2 open 
	 * int open(const char *path, int oflags);
	 * int open(const char *path, int oflags, mode_t mode);
	 *
	 * open("myfile", O_CREAT, S_IRUSR|S_IXOTH);
	 *
	 * umask
	 *
	 * int close(int fildes); 返回0（成功）-1（出错）
	 *
	 * ioctl 用于控制设备及其描述符行为和配置底层服务的接口
	 */


}