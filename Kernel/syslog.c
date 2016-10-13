/*

	Note：

	syslog - send messages to the system logger
	
	RFC:
	https://tools.ietf.org/html/rfc5424
	
	Prototype:
	void openlog(const char *ident, int option, int facility);
	void syslog(int priority, const char *format, ...);
	void closelog(void);
	

	CLI:
	logger -t GEDU this is a test by Raymond
	logger -p kern.emerg -t GEDU this is a test by Raymond


*/

