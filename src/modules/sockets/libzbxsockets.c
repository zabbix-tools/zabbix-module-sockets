#include "libzbxsockets.h"

static int SOCKETS_MODVER(AGENT_REQUEST*, AGENT_RESULT*);

ZBX_METRIC *zbx_module_item_list()
{
  static ZBX_METRIC keys[] =
  {
    { "sockets.modver",             0,              SOCKETS_MODVER,             NULL },
    { "sockets.tcp.count",          CF_HAVEPARAMS,  SOCKETS_TCP_COUNT,          NULL },
    { "sockets.tcp6.count",         CF_HAVEPARAMS,  SOCKETS_TCP6_COUNT,         NULL },
    { "sockets.unix.count",         CF_HAVEPARAMS,  SOCKETS_UNIX_COUNT,         NULL },
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

static int SOCKETS_MODVER(AGENT_REQUEST *request, AGENT_RESULT *result)
{
  SET_STR_RESULT(result, strdup(PACKAGE_STRING ", compiled with Zabbix " ZABBIX_VERSION));
  return SYSINFO_RET_OK;
}
