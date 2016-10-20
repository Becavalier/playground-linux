/**
 * 文件系统调用(由 Linux/Unix 直接提供)方法：
 *
 * open / read / write / close / ioctl
 * lseek / fstat / stat / lstat / dup / dup2
 *
 * 1、执行系统调用时，Linux 必须从用户态切换到内核态；
 * 2、硬件会限制对底层系统调用一次所能读写的数据块大小；
 *
 * 三种文件描述符：0 / 1 / 2
 * 对应标准库中的：stdin / stdout / stderr
 *
 * 标准I/O库方法：
 *
 * fopen / fread / fwrite / fclose 
 * fflush / fseek 
 * fgetc / getc / getchar
 * fputs / puts / putchar 
 * fgets / gets
 * printf / fprintf / sprintf
 * scanf / fsacnf / ssanf
 *
 * 调试 Segmentation fault (core dumped)：
 * 设置 core 文件最大块大小： ulimit -c 512
 * 进入 gdb 进行调试： gdb 【运行程序名】 core
 * 使用 bt 命令进行调试： bt
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

#define yearsecs (60 * 60 * 24 * 365) 

int main(int argc, char *argv[]) {

	char* args;

	if(argc == 2) {
		args = argv[1];
	}

	if(strcasecmp(args, "system") == 0) {
		
		int file_in, file_out, read_len;
		// Just a buffer
		char buf[1024];
		struct stat statbuf;
		mode_t modes;

		if ((file_in = open("file.in", O_RDONLY)) != -1) {

			fstat(file_in, &statbuf);

			// Print the info of file "file.in"

			// fdisk -l => sda1 => 8/1
			printf("st_dev: %d\\%d\n", major(statbuf.st_dev), minor(statbuf.st_dev));
			printf("st_gid: %d\n", statbuf.st_gid);
			printf("st_uid: %d\n", statbuf.st_uid);
			printf("st_atime: %ld\n", (long) (statbuf.st_atime / yearsecs) + 1970);
			printf("st_ctime: %ld\n", (long) (statbuf.st_ctime / yearsecs) + 1970);

			if(S_ISREG(statbuf.st_mode)) {
				printf("%s\n", "This is a normal file.");
			}

			if(S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)) {
				printf(" (%s) rdev = %d/%d",  
	                    (S_ISCHR(statbuf.st_mode)) ? "character" : "block",  
	                    major(statbuf.st_rdev), minor(statbuf.st_rdev));  
			}
			
			// Create a new file "file.out"
			file_out = open("file.out", O_WRONLY|O_APPEND|O_CREAT|O_EXCL, S_IWUSR);

			if(file_out == -1) {
				printf("%s\n", "Error occurred when creating file 'file.out', trying to remove it.");
				
				//
			}

			while((read_len = read(file_in, buf, sizeof(buf))) > 0) {
				write(file_out, buf, read_len);
			}	
		}

		if(close(file_in) == -1 || close(file_out) == -1) {
			printf("%s\n", "Error occurred when closing file.");
		}
	} 

	if(strcasecmp(args, "stdio") == 0) {
		FILE *file_in, *file_out;
		char buf[1024], char_buf;

		// Create a new file "file.out"
		/*
			使用r+选项，将r选择项的功能扩充为即允许读也允许写文件。（该文件必须存在）
			使用w+选项建立一个可读可写的新文件。（若文件不存在则建立文件）
			使用a+可以从文件的当前位置开始往文件中添加内容，而用可同时读写文件。（若文件不存在则建立文件，若存在则将数据添加到文件尾）。
		*/

		file_out = fopen("file.out", "a+");

		if((file_in = fopen("file.in", "r")) != NULL) {
			while(!feof(file_in)) {
				int count = fread(buf, sizeof(buf), 1, file_in);
				if(count > 0) {
					fwrite(buf, sizeof(buf), count, file_out);
				}
				// fflush(file_out);
			}

			// Detect the rest
			fseek(file_out, 0, SEEK_END);
    		fseek(file_in, ftell(file_out), SEEK_SET);

    		while(!feof(file_in)) {
    			int count = fread(&char_buf, sizeof(char_buf), 1, file_in);
				if(count > 0) {
					fwrite(&char_buf, sizeof(char_buf), count, file_out);
				}
    		}

			fclose(file_in);
			fclose(file_out);
		}
	}

}
