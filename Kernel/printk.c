/*

	Note：

	grep -R "printk" | wc -l

	printk -> vprintk_emit（产生消息头） -> log_store 将消息先输出到环形缓冲区（128k）再输出到 -> {文件、虚拟设备、控制台}

*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>



static int __init first_lkm_init(void) {   // static 表示文件内部函数；__init 编译器属性，为初始化函数；

	int n = 0x1937;

	// printk 在内核中运行的向控制台输出显示的函数；
	printk(KERN_INFO "Hi, I am llaolao at address 0x%p\n",
	    llaolao_init);

    printk(KERN_INFO "symbol: 0x%pF\n",
	    llaolao_init);

    printk(KERN_INFO "stack: 0x%p\n",
        &n);
    
	return 0;
}

static void __exit first_lkm_exit(void) {    // __exit 编译器属性，为卸载函数；

	printk("Exiting from 0x%p ... Bye, YHSPY friends.\n", first_lkm_exit);

	printk(KERN_EMERG "Testing message with different severity level\n");
    printk(KERN_ALERT "Testing message with different severity level\n");
    printk(KERN_CRIT "Testing message with different severity level\n");
    printk(KERN_ERR "Testing message with different severity level\n");
    printk(KERN_WARNING "Testing message with different severity level\n");
    printk(KERN_NOTICE "Testing message with different severity level\n");
    printk(KERN_INFO "Testing message with different severity level\n");
    printk(KERN_DEBUG "Testing message with different severity level\n");

}

// 宏，把上述函数挂载到 GCC 的编译工具链上；
// <linux/init.h> 中定义了这两个宏；	
module_init(first_lkm_init);
module_exit(first_lkm_exit);

// 说明模块作者和版权信息的宏调用；
MODULE_AUTHOR("YHSPY");
MODULE_DESCRIPTION("LKM EXAMPLE - YHSPY");
MODULE_LICENSE("GPL");  // 不可随意修改，内核使用的标准协议，用于各个模块之间的交流；
