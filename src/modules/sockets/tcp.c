#include "libzbxsockets.h"

static char *TCP_STATE[] = {
	"",
	"ESTABLISHED",
	"SYN_SENT",
	"SYN_RECV",
	"FIN_WAIT1",
	"FIN_WAIT2",
	"TIME_WAIT",
	"CLOSE",
	"CLOSE_WAIT",
	"LAST_ACK",
	"LISTEN",
	"CLOSING",
};

typedef struct _TCP_SOCKET {
	uint32_t	slot;
	uint32_t	local_addr;
	uint32_t	local_port;
	uint32_t	remote_addr;
	uint32_t	remote_port;
	uint32_t	status;
	uint32_t	tx_queue;
	uint32_t	rx_queue;
} TCP_SOCKET;

int SOCKETS_TCP_COUNT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	int				res = SYSINFO_RET_FAIL, cnt = 0, ok = 0, state = 0;
	FILE			*f = NULL;
	char			buf[4096], *param_state = NULL;
	TCP_SOCKET		skt;

	if (1 < request->nparam) {
		SET_MSG_RESULT(result, strdup("Invalid number of parameters."));
		return res;
	}

	// validate state param
	if ((param_state = get_rparam(request, 0))) {
		for (char *c = param_state; c && *c; c++) {
			*c = toupper(*c);
		}
		for (int i = 1; i < 12; i++) {
			if (0 == strncmp(TCP_STATE[i], param_state, 12)) {
				state = i;
				break;
			}			
			if (i == 11) {
				SET_MSG_RESULT(result, strdup("Invalid TCP state."));
				return res;
			}
		}
	}

	f = fopen("/proc/net/tcp", "r");
	if (NULL == f) {
		zabbix_log(LOG_LEVEL_ERR, LOG_PREFIX "%s", zbx_strerror(errno));
		return res;
	}

	fgets(buf, sizeof(buf), f); // discard headers
	while (fgets(buf, sizeof(buf), f)) {
		if (8 == sscanf(buf, "%i: %X:%X %X:%X %X %X:%X",
										&skt.slot,
										&skt.local_addr,
										&skt.local_port,
										&skt.remote_addr,
										&skt.remote_port,
										&skt.status,
										&skt.tx_queue,
										&skt.rx_queue)) {
			ok = 1;
			if (state)
				if (state != skt.status)
					ok = 0;
			
			if (ok)
				cnt++;
		}
	}

	if (ferror(f)) {
		fclose(f);
		zabbix_log(LOG_LEVEL_ERR, LOG_PREFIX "%s", zbx_strerror(errno));
		return res;
	}

	fclose(f);

	SET_UI64_RESULT(result, cnt);
	res = SYSINFO_RET_OK;
	return res;
}
