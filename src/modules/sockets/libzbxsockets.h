#ifndef LIBZBXSVC_H
#define LIBZBXSVC_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>

// Zabbix source headers
#define HAVE_TIME_H 1
#include <sysinc.h>
#include <module.h>
#include <common.h>
#include <log.h>
#include <zbxjson.h>
#include <version.h>
#include <db.h>

#ifndef MAX
#define MAX(a, b)     ( (a) < (b) ? (b) : (a) )
#endif

#ifndef ZBX_MODULE_API_VERSION
#define ZBX_MODULE_API_VERSION  ZBX_MODULE_API_VERSION_ONE
#endif

#define LOG_PREFIX              "[sockets] "

#define _PATH_PROCNET_TCP		"/proc/net/tcp"
#define _PATH_PROCNET_TCP6		"/proc/net/tcp6"
#define _PATH_PROCNET_UDP		"/proc/net/udp"
#define _PATH_PROCNET_UDP6		"/proc/net/udp6"
#define _PATH_PROCNET_UNIX		"/proc/net/unix"

// timeout set by host agent
int timeout;

enum
{
	STAT_COUNT,
	STAT_SEND_QUEUE,
	STAT_RECV_QUEUE
};

int tcp_stat(AGENT_REQUEST*, AGENT_RESULT*, const char*, int, int);
int unix_count(AGENT_REQUEST*, AGENT_RESULT*);

#endif
