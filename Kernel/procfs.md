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

* /proc/modules

> 显示系统已经动态加载的模块信息；

* /proc/partitions

> 显示系统当前的分区信息；


### 