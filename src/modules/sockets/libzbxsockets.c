#include "libzbxsockets.h"

static int SOCKETS_MODVER(AGENT_REQUEST*, AGENT_RESULT*);
static int SOCKETS_COUNT(AGENT_REQUEST*, AGENT_RESULT*);
static int SOCKETS_SENDQ(AGENT_REQUEST*, AGENT_RESULT*);
static int SOCKETS_RECVQ(AGENT_REQUEST*, AGENT_RESULT*);

ZBX_METRIC *zbx_module_item_list()
{
	static ZBX_METRIC keys[] =
	{
		{ "sockets.modver",             0,              SOCKETS_MODVER,             NULL },
		{ "sockets.count",              CF_HAVEPARAMS,  SOCKETS_COUNT,              "tcp" },
		{ "sockets.sendq",				CF_HAVEPARAMS,	SOCKETS_SENDQ,				"tcp" },
		{ "sockets.recvq",				CF_HAVEPARAMS,	SOCKETS_RECVQ,				"tcp" },
		{ NULL }
	};

	return keys;
}

int zbx_module_api_version() {
	return ZBX_MODULE_API_VERSION;
}

int zbx_module_init()
{
	zabbix_log(LOG_LEVEL_DEBUG, LOG_PREFIX "starting v%s", PACKAGE_VERSION);
	return ZBX_MODULE_OK;
}

int zbx_module_uninit()
{ 
	return ZBX_MODULE_OK;
}

int timeout = 3000;
void zbx_module_item_timeout(int t)
{
	timeout = t * 1000;
	zabbix_log(LOG_LEVEL_DEBUG, LOG_PREFIX "set timeout to %ims", timeout);
}

static int dispatch(AGENT_REQUEST *request, AGENT_RESULT *result, int stat)
{
	char *param_proto, *path;
	int proto;

	if (1 > request->nparam) {
		SET_MSG_RESULT(result, strdup("Invalid number of parameters."));
		return SYSINFO_RET_FAIL;
	}

	param_proto = get_rparam(request, 0);
	if (0 == strcmp(param_proto, "unix")) {
		if (stat == STAT_COUNT) {
			return unix_count(request, result);
		}
		
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Invalid protocol: %s", param_proto));
		return SYSINFO_RET_FAIL;
	}
	else if (0 == strcmp(param_proto, "tcp")) {
		proto = IPPROTO_TCP;
		path = _PATH_PROCNET_TCP;
	} else if (0 == strcmp(param_proto, "tcp6")) {
		proto = IPPROTO_TCP;
		path = _PATH_PROCNET_TCP6;
	} else if (0 == strcmp(param_proto, "udp")) {
		proto = IPPROTO_UDP;
		path = _PATH_PROCNET_UDP;
	} else if (0 == strcmp(param_proto, "udp6")) {
		proto = IPPROTO_UDP;
		path = _PATH_PROCNET_UDP6;
	} else {
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Invalid protocol: %s", param_proto));
		return SYSINFO_RET_FAIL;
	}

	return tcp_stat(request, result, path, proto, stat);
}

static int SOCKETS_MODVER(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	SET_STR_RESULT(result, strdup(PACKAGE_STRING ", compiled with Zabbix " ZABBIX_VERSION));
	return SYSINFO_RET_OK;
}

static int SOCKETS_COUNT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return dispatch(request, result, STAT_COUNT);
}

static int SOCKETS_SENDQ(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return dispatch(request, result, STAT_SEND_QUEUE);
}

static int SOCKETS_RECVQ(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return dispatch(request, result, STAT_RECV_QUEUE);
}
