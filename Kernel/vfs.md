## VFS 虚拟文件系统 核心对象和操作

![image](https://github.com/Becavalier/Linux-Library/tree/master/Kernel/screenshots/vfs.jpg?raw=true)

### 四大核心对象（以面向对象的思想实现的）

* superblock：存储关于文件系统的信息；

> `dumpe2fs -h /dev/sda1` 命令来观察 superblock 的信息（块大小，段大小）；

> ...

> Free inodes:              1821955

> First block:              0

> Block size:               4096

> Fragment size:            4096 

> Reserved GDT blocks:      1022

> Blocks per group:         32768

> Fragments per group:      32768

> Inodes per group:         8192

> Inode blocks per group:   512

> Flex block group size:    16

> ...



* inode(Index Node)：存储关于文件的信息；

> 存储每个文件对应的磁盘块位置；

> `stat sf.sh` 命令来观察 'sf.sh' 文件的信息（Inode信息，块数量）；

> `df -i` 命令来观察磁盘信息（Inode信息）；

* dentry（Directory Entry 目录表表项）：存储一个对应路径所指向的文件的信息；

> 每一个表项对应于一个 'dentry' 结构体，它是一个树形结构；

> 'dcache' 数据结构用于提高查找性能；

* file：存储一个被进程打开的文件信息；

> `debugfs` 交互式命令来调试文件；

> 三个函数 'ioctl'，'unlocked_ioctl' 没有使用内核锁，'compat_ioctl' 用于兼容 32 位系统；



### 四大核心操作

* super_operations：用于内核对文件系统的操作；

> 如 write_inode 和 sync_fs；

* inode_operations：用于内核对文件的操作；

> 如 create 和 link，主要对下提供接口；

* dentry_operations：用于内核对文件夹目录的操作；

> 如 d_compare 和 d_delete；

* file_operations：对已打开文件的操作；

> 如 read 和 write，主要对上提供接口；


### 相关命令

`cat /proc/filesystems` 查看系统已经注册的文件系统;

`mount -t ext4 /dev/mmcblk0p1 /mnt` 挂载文件系统；

手动配置文件系统：`cat /etc/fstab`;

