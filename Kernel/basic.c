/*

	Note：

	LKM（Loadable Kernel Modules）：可加载内核模块；

	软件体系，按照特权级别分类：用户态（应用程序）、内核态（驱动程序）；

	内核空间模块：内核、驱动程序（需要较高权限），也有一部分驱动程序位于用户态；

*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
/**
 * Dynamic loading of modules into the kernel.
 *
 * Rewritten by Richard Henderson <rth@tamu.edu> Dec 1996
 * Rewritten again by Rusty Russell, 2002
 */

/**
 * module_init() - driver initialization entry point
 * @x: function to be run at kernel boot time or module insertion
 *
 * module_init() will either be called during do_initcalls() (if
 * builtin) or at module insertion time (if a module).  There can only
 * be one per module.
 */

// #define module_init(x)	__initcall(x);

/**
 * module_exit() - driver exit entry point
 * @x: function to be run when driver is removed
 *
 * module_exit() will wrap the driver clean-up code
 * with cleanup_module() when used with rmmod when
 * the driver is a module.  If the driver is statically
 * compiled into the kernel, module_exit() has no effect.
 * There can only be one per module.
 */
// #define module_exit(x)	__exitcall(x);

/*
	LKM的两个入口函数均定义在 module.h 里，包括一些 MODULE_LICENSE 的宏也定义在其中；
	
	module 结构体相当于内核模块的“户籍档案”。

	struct module {
		enum module_state state;
	
		// Member of list of modules
		struct list_head list;  // 模块链表，以链表形式连接所有模块，在 lsmod 命令时用到该项；
		
		// Unique handle for this module
		char name[MODULE_NAME_LEN];
		
		// Sysfs stuff
		struct module_kobject mkobj;
		struct module_attribute *modinfo_attrs;
		const char *version;
		const char *srcversion;
		struct kobject *holders_dir;

		const struct kernel_symbol *syms;
		const unsigned long *crcs;
		unsigned int num_syms;
		...

*/



static int __init first_lkm_init(void) {   // static 表示文件内部函数；__init 编译器属性，为初始化函数；

	int n = 0x1937;

	// printk 在内核中运行的向控制台输出显示的函数；
	printk(KERN_INFO "Hi, I am YHSPY at address 0x%p stack 0x%p.\n", first_lkm_init, &n);

	return 0;
}

static void __exit first_lkm_exit(void) {    // __exit 编译器属性，为卸载函数；

	printk("Exiting from 0x%p ... Bye, YHSPY friends.\n", first_lkm_exit);

}

// 宏，把上述函数挂载到 GCC 的编译工具链上；
// <linux/init.h> 中定义了这两个宏；	
module_init(first_lkm_init);
module_exit(first_lkm_exit);

// 说明模块作者和版权信息的宏调用；
MODULE_AUTHOR("YHSPY");
MODULE_DESCRIPTION("LKM EXAMPLE - YHSPY");
MODULE_LICENSE("GPL");  // 不可随意修改，内核使用的标准协议，用于各个模块之间的交流；


/*
	4096 个字节是一个页的大小；


	Linux内核相关命令：

	lsmod 列出当前内核已经加载的LKM；

	sudo insmod xx.ko 安装某个 LKM；

	sudo rmmod xx.ko 卸载某个 LKM；

	dmesg 用于检测和控制内核环缓冲信息；



	modinfo xx.ko 列出 "xx.ko" 这个 LKM 的相关信息；

	filename:       xx.ko
	license:        GPL
	description:    LKM example - llaolao
	author:         GEDU lab
	srcversion:     645DC5DFA0792778A9AD51E               # 与 .mod.c 文件中的 srcversion 一致
	depends:        
	vermagic:       3.12.2 SMP mod_unload modversions 686 # 支持的内核版本号

	.ko 是一个 ELF 格式的文件；


	readelf -h xx.ko 查看某个 LKM 的 ELF Header 信息：
	ELF Header:
	  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
	  Class:                             ELF32                           # 32 位
	  Data:                              2's complement, little endian
	  Version:                           1 (current)
	  OS/ABI:                            UNIX - System V
	  ABI Version:                       0
	  Type:                              REL (Relocatable file)
	  Machine:                           Intel 80386
	  Version:                           0x1
	  Entry point address:               0x0
	  Start of program headers:          0 (bytes into file)
	  Start of section headers:          930476 (bytes into file)
	  Flags:                             0x0
	  Size of this header:               52 (bytes)
	  Size of program headers:           0 (bytes)
	  Number of program headers:         0
	  Size of section headers:           40 (bytes)
	  Number of section headers:         35
	  Section header string table index: 32
 	
 	readelf -S xx.ko 查看某个 LKM 的 ELF Section 信息：
	Section Headers:
	  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
	  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
	  [ 1] .note.gnu.build-i NOTE            00000000 000034 000024 00   A  0   0  4
	  [ 2] .text             PROGBITS        00000000 000058 000000 00  AX  0   0  4
	  [ 3] .exit.text        PROGBITS        00000000 000058 00001c 00  AX  0   0  1
	  [ 4] .rel.exit.text    REL             00000000 0e3824 000018 08     33   3  4
	  [ 5] .init.text        PROGBITS        00000000 000074 000038 00  AX  0   0  1
	  [ 6] .rel.init.text    REL             00000000 0e383c 000028 08     33   5  4
	  [ 7] .rodata.str1.4    PROGBITS        00000000 0000ac 000058 01 AMS  0   0  4
	  [ 8] .rodata.str1.1    PROGBITS        00000000 000104 00001c 01 AMS  0   0  1
	  [ 9] .modinfo          PROGBITS        00000000 000120 00009a 00   A  0   0  1
	  [10] __versions        PROGBITS        00000000 0001c0 000080 00   A  0   0 32
	  [11] .data             PROGBITS        00000000 000240 000000 00  WA  0   0  4
	  [12] .gnu.linkonce.thi PROGBITS        00000000 000240 000184 00  WA  0   0 32
	  [13] .rel.gnu.linkonce REL             00000000 0e3864 000010 08     33  12  4
	  [14] .bss              NOBITS          00000000 0003c4 000000 00  WA  0   0  4
	  [15] .comment          PROGBITS        00000000 0003c4 000056 01  MS  0   0  1
	  [16] .note.GNU-stack   PROGBITS        00000000 00041a 000000 00      0   0  1
	  [17] .debug_aranges    PROGBITS        00000000 00041a 000028 00      0   0  1
	  [18] .rel.debug_arange REL             00000000 0e3874 000018 08     33  17  4
	  [19] .debug_info       PROGBITS        00000000 000442 007d02 00      0   0  1
	  [20] .rel.debug_info   REL             00000000 0e388c 0033c0 08     33  19  4
	  [21] .debug_abbrev     PROGBITS        00000000 008144 00051e 00      0   0  1
	  [22] .debug_line       PROGBITS        00000000 008662 00206e 00      0   0  1
	  [23] .rel.debug_line   REL             00000000 0e6c4c 000010 08     33  22  4
	  [24] .debug_frame      PROGBITS        00000000 00a6d0 000054 00      0   0  4
	  [25] .rel.debug_frame  REL             00000000 0e6c5c 000020 08     33  24  4
	  [26] .debug_str        PROGBITS        00000000 00a724 00485a 01  MS  0   0  1
	  [27] .debug_loc        PROGBITS        00000000 00ef7e 000070 00      0   0  1
	  [28] .rel.debug_loc    REL             00000000 0e6c7c 000080 08     33  27  4
	  [29] .debug_macinfo    PROGBITS        00000000 00efee 0d4156 00      0   0  1
	  [30] .debug_ranges     PROGBITS        00000000 0e3144 000018 00      0   0  1
	  [31] .rel.debug_ranges REL             00000000 0e6cfc 000020 08     33  30  4
	  [32] .shstrtab         STRTAB          00000000 0e315c 00014d 00      0   0  1
	  [33] .symtab           SYMTAB          00000000 0e6d1c 000260 10     34  34  4
	  [34] .strtab           STRTAB          00000000 0e6f7c 0000ee 00      0   0  1



	

*/