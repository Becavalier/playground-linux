## sysctl 动态的对内核系统参数进行设置

> `cd /proc/sys` 此文件夹下包含有关于系统的各种信息，直接读写这些文件可以更改各种系统设置；

> sysctl 系统帮助文档位置："内核代码目录/Documentation/sysctl/README"；

### `sysctl` 命令

> `sudo sysctl -w kernel.hostname=gedubox` 修改系统宿主名；


### `sysctl` 实现原理

> `/kernel/sysctl.c`；

### sysctl 和 procfs 的区别：

> `sysctl` 暴露的信息一般可以进行读写操作，而 `procfs` 是只读信息；
