## procfs 伪（虚拟）文件系统

`cd /proc` 此文件夹下包含有关于进程以及系统的各种信息

### 进程文件夹信息

* maps 

> 描述进程里映射的库文件（.so 文件）；

* cmdline

> 命令行参数；

* /proc/cpuinfo

> 系统当前的CPU信息；

* status

> 查看当前的进程的相关信息；

* /proc/interrupts

> 查看系统的中断信息；

> LOC 中断：内核的基础驱动中断；

* /proc/meminfo

> 系统的物理内存使用情况；

* /proc/vmstat

> 系统的虚拟内存使用情况；

* /proc/ioports

> 系统的端口映射情况；

> ...

> 0000-001f : dma1

> 0020-0021 : pic1

> 0040-0043 : timer0

> 0050-0053 : timer1

> 0060-0060 : keyboard

> 0064-0064 : keyboard

> 0070-0071 : rtc_cmos

> ...

> X86 架构的 IO 地址空间大小是64K，即16位；


* /proc/modules

> 显示系统已经动态加载的模块信息；

* /proc/partitions

> 显示系统当前的分区信息；

* /proc/cmdline

> 显示内核的命令行信息；


### 创建新的 proc 文件

```c
static ssize_t proc_lll_read(struct *filp, char __user *buf, size_t count, loff_t *offp)
{
	int n = 0,ret;
	char secrets[100];

	printk(KERN_INFO "proc_lll_read is called file %p, buf %p count %d off %llx\n", filp, buf, count, *offp);

	sprintf(secrets, "Kernel secrets balabala %s...\n", filp->f_path.dentry->d_iname);

	n = strlen(secrets);
	if(*offp < n)
	{
		copy_to_user(buf, secrets, n + 1);
		*offp = n + 1；
		ret = n + 1;
	}
	else
		ret = 0;

	return ret;
}

static struct proc_dir_entry *proc_lll_entry = NULL;

static const struct file_operation proc_lll_fops = {
	.owner = THIS_MODULE,
	.read = proc_lll_read
};

proc_lll_entry = proc_create("llaolao", 0, NULL, &proc_lll_fops);

if(proc_lll_entry)
	proc_remove(proc_lll_entry);

```

### 使用 Seq File 来创建新的 proc 文件 (linux/fs/seq_file.c)

对创建 proc 文件的操作进行了封装；

```c
static int version proc_show(struct seq_file *m, void *v)
{
	seq_print(m, linux_proc_banner,
		utsname()->sysname,
		utsname()->release,
		utname()->version
		);
	return 0;
}

static int version_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, version_proc_show, NULL);
}

static const struct file_operations version_proc_fops = {
	.open    = version_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release
};

static int __init proc_version_init(void)
{
	proc_create("version", 0, NULL, &version_proc_fops);
	return 0;
}
fs_install(proc_version_init);

```

