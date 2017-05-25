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

// timeout set by host agent
int timeout;

// tcp items
int SOCKETS_TCP_COUNT(AGENT_REQUEST*, AGENT_RESULT*);
int SOCKETS_TCP6_COUNT(AGENT_REQUEST*, AGENT_RESULT*);
int SOCKETS_UNIX_COUNT(AGENT_REQUEST*, AGENT_RESULT*);

#endif
