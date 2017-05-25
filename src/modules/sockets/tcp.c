#include "libzbxsockets.h"

#define TCP_CLOSE		0x07
#define TCP_LISTEN		0x0A

// supported state parameter values
static char *TCP_STATES[] = {
	"", "ESTABLISHED", "SYN_SENT", "SYN_RECV", "FIN_WAIT1",	"FIN_WAIT2",
	"TIME_WAIT",
	"CLOSE",
	"CLOSE_WAIT",
	"LAST_ACK",
	"LISTEN",
	"CLOSING",
};

static char *UDP_STATES[] = {
	"",
	"ESTABLISHED",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"LISTEN",
	"",
};

static int isnull(const char *c, size_t n)
{
	int i = 0;
	for (i = 0; i < n && '\0' != c[i]; i++) {
		if ('0' != c[i]) {
			return 0;
		}
	}

	return 1;
}

static int sockets_tcp_count(
						AGENT_REQUEST *request,
						AGENT_RESULT *result,
						const char *path,
						char **allowed_states)
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
			if (0 == strncmp(allowed_states[i], param_state, 12)) {
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

	while (fgets(buf, sizeof(buf), f)) {
		if (8 == sscanf(buf, "%d: %64[0-9A-Fa-f]:%X %64[0-9A-Fa-f]:%X %X %lX:%lX %*s\n",
										&slot, local_addr, &local_port,
										remote_addr, &remote_port, &state,
										&tx_queue, &rx_queue)
		) {
			// closed sockets with nil remote addr:port are udp listeners
			if (state == TCP_CLOSE &&
					isnull(remote_addr, sizeof(remote_addr)) &&
					0 == remote_port) {
				state = TCP_LISTEN;
			}

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
	return sockets_tcp_count(request, result, "/proc/net/tcp", TCP_STATES);
}

int SOCKETS_TCP6_COUNT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return sockets_tcp_count(request, result, "/proc/net/tcp6", TCP_STATES);
}

int SOCKETS_UDP_COUNT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return sockets_tcp_count(request, result, "/proc/net/udp", UDP_STATES);
}

int SOCKETS_UDP6_COUNT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	return sockets_tcp_count(request, result, "/proc/net/udp6", UDP_STATES);
}
