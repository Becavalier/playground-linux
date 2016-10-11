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
	Linux内核相关命令：

	lsmod 列出当前内核已经加载的LKM；
	

*/