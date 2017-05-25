# zabbix-module-sockets

zabbix-module-sockets is a loadable Zabbix module that enables Zabbix to query
the state of sockets - including tcp, udp, unix, raw, etc.

## Install

```bash
$ ./configure --with-zabbix=/usr/src/zabbix-3.2.5
$ make
$ sudo make install
```

If you are using a packaged version of Zabbix, you may with to redirect the
installation directories as follows:

```
$ sudo make prefix=/usr sysconfdir=/etc libdir=/usr/lib64 install
```

## Keys

```
sockets.tcp.count[<state>]      return the number of tcp sockets in the given
                                state

sockets.tcp.sendq[<state>]      returns the total sum of all buffers in the send
                                queue for all tcp sockets in the given state

sockets.tcp.recvq[<state>]      returns the total sum of all buffers in the
                                receive queue for all tcp sockets in the given
                                state

sockets.tcp6.count[<state>]     return the number of ipv4 tcp sockets in the
                                given state

sockets.tcp6.sendq[<state>]     returns the total sum of all buffers in the send
                                queue for all tcp6 sockets in the given state

sockets.tcp6.recvq[<state>]     returns the total sum of all buffers in the
                                receive queue for all tcp6 sockets in the given
                                state

sockets.udp.count[<state>]      return the number of udp sockets in the given
                                state

sockets.udp.sendq[<state>]      returns the total sum of all buffers in the send
                                queue for all udp sockets in the given state

sockets.udp.recvq[<state>]      returns the total sum of all buffers in the
                                receive queue for all udp sockets in the given
                                state

sockets.udp6.count[<state>]     return the number of ipv6 udp sockets in the
                                given state

sockets.udp6.sendq[<state>]     returns the total sum of all buffers in the send
                                queue for all udp6 sockets in the given state

sockets.udp6.recvq[<state>]     returns the total sum of all buffers in the
                                receive queue for all udp6 sockets in the given
                                state

sockets.unix.count[<state>]     returns the number of unix sockets in the given
                                state

sockets.modver[]                            version of the loaded module
```

### sockets.tcp.count

Supported states include:

- `ESTABLISHED`
- `SYN_SENT`
- `SYN_RECV`
- `FIN_WAIT1`
- `FIN_WAIT2`
- `TIME_WAIT`
- `CLOSE`
- `CLOSE_WAIT`
- `LAST_ACK`
- `LISTEN`
- `CLOSING`

If the state parameter is empty, all the total number of sockets in any state is
returned.

E.g.

    $ zabbix_agentd -t sockets.tcp.count[listen]
    sockets.tcp.count[listen]                     [u|2]

    $ netstat -tl4
    Active Internet connections (only servers)
    Proto Recv-Q Send-Q Local Address           Foreign Address         State
    tcp        0      0 0.0.0.0:ssh             0.0.0.0:*               LISTEN
    tcp        0      0 0.0.0.0:zabbix-agent    0.0.0.0:*               LISTEN

For greater understanding, see the [TCP/IP State Transition Diagram](http://www.cs.northwestern.edu/~agupta/cs340/project2/TCPIP_State_Transition_Diagram.pdf)
by Gordon McKinney, 2002.

### sockets.unix.count

Supported states include:

- `FREE`
- `UNCONNECTED`
- `CONNECTING`
- `CONNECTED`
- `DISCONNECTING`
- `LISTEN`

E.g.

    $ zabbix_agentd -t sockets.unix.count[listen]
    sockets.unix.count[listen]                    [u|33]

    $ netstat -xl
    Active UNIX domain sockets (only servers)
    Proto RefCnt Flags       Type       State         I-Node   Path
    unix  2      [ ACC ]     STREAM     LISTENING     17910    private/tlsmgr
    unix  2      [ ACC ]     STREAM     LISTENING     17914    private/rewrite
    unix  2      [ ACC ]     STREAM     LISTENING     17917    private/bounce
    ...
