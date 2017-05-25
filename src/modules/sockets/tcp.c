#include "libzbxsockets.h"

// supported state parameter values
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

static int sockets_tcp_count(
						AGENT_REQUEST *request,
						AGENT_RESULT *result,
						const char *path)
{
	int				res = SYSINFO_RET_FAIL, count = 0;
	FILE			*f = NULL;
	char			buf[4096];

	char			*c, *param_state;
	int				i, ok, filter_state;

	char			local_addr[128], remote_addr[128];
	int				slot, local_port, remote_port, state;
	unsigned long	tx_queue, rx_queue;

	if (1 < request->nparam) {
		SET_MSG_RESULT(result, strdup("Invalid number of parameters."));
		return res;
	}

	// validate state parameter
	filter_state = 0;
	if ((param_state = get_rparam(request, 0))) {
		for (c = param_state; c && *c; c++) {
			*c = toupper(*c);
		}
		for (i = 1; i < 12; i++) {
			if (0 == strncmp(TCP_STATE[i], param_state, 12)) {
				filter_state = i;
				break;
			}			
			if (i == 11) {
				SET_MSG_RESULT(result, strdup("Invalid TCP state."));
				return res;
			}
		}
	}

	if (NULL == (f = fopen(path, "r"))) {
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Failed to open %s: %s", path, zbx_strerror(errno)));
		return res;
	}
	if (NULL == fgets(buf, sizeof(buf), f)) {
		// discard header - errors handled later
	}

	while (fgets(buf, sizeof(buf), f)) {
		if (8 == sscanf(buf, "%d: %64[0-9A-Fa-f]:%X %64[0-9A-Fa-f]:%X %X %lX:%lX %*s\n",
										&slot, local_addr, &local_port,
										remote_addr, &remote_port, &state,
										&tx_queue, &rx_queue)
		) {
			ok = 1;
			if (filter_state) {
				if (filter_state != state) {
					ok = 0;
				}
			}
			if (ok) {
				count++;
			}
		}
	}

	if (ferror(f)) {
		fclose(f);
		SET_MSG_RESULT(result, zbx_dsprintf("Error reading %s: %s", path, zbx_strerror(errno)));
		return res;
	}

	fclose(f);
	SET_UI64_RESULT(result, count);
	res = SYSINFO_RET_OK;
	return res;
}

int SOCKETS_TCP_COUNT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return sockets_tcp_count(request, result, "/proc/net/tcp");
}

int SOCKETS_TCP6_COUNT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return sockets_tcp_count(request, result, "/proc/net/tcp6");
}
