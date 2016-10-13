/*

	syslogd 是一个后台服务；

	用来捕捉 syslog 的消息同时将消息写入文件；
	
	消息捕捉规则：
	/etc/syslog.conf
	...
	mail.info                       -/var/log/mail.info
	mail.warning                    -/var/log/mail.warn
	mail.err                        /var/log/mail.err
	...


	消息滚动机制：
	/etc/logrotate.conf 
	...
	# see "man logrotate" for details
	# rotate log files weekly
	weekly

	# keep 4 weeks worth of backlogs
	rotate 4

	# create new (empty) log files after rotating old ones
	create
	...
	
	实例：
	logger message 命令，
	会将消息默认写入到 /var/log/messages 文件，
	根据 /etc/logrotate.conf 的设置，
	/var/log/messages 每四周产生一个备份 .gz 文件；

	
*/