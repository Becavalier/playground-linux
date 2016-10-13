/*
	
	https://www.kernel.org/doc/Documentation/console/console.txt
	
	Note：
	
	配置串口终端：（ubuntu）
	/etc/grub.d/40_custom
	
	配置 console：
	linux   /boot/vmlinuz-3.12.2 root=UUID=eb5d8aee-6a0f-4257-b5b8-8d6731ba6764 ro debug splash console=ttyS1,115200n8
	
	讲控制台输出级别改为3：
	1、sudo dmesg -n 3 
	2、修改 /etc/sysctl.conf 中 kernel.printk = xxxx;

	显示当前系统的消息显示级别：
	cat /proc/sys/kernel/printk
	# 4417
	四个数字分别对应：
	1、控制台日志级别；
	2、默认的消息日志级别，调用 printk 时的默认日志级别；
	3、控制台日志级别的最小值；
	4、默认的控制台日志级别，即第一项的默认值；

	

*/

int console_printk[4] = {
	CONSOLE_LOGLEVEL_DEFAULT, /* consle_loglevel */
	MESSAGE_LOGLEVEL_DEFAULT, /* default_message_loglevel */
	CONSOLE_LOGLEVEL_MIN,     /* minimum_console_loglevel */
	CONSOLE_LOGLEVEL_DEFAULT, /* default_console_loglevel */
}
