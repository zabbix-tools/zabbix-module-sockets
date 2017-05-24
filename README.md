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
sockets.tcp.count[<state>]                  return the number of tcp sockets in
                                            the given state

sockets.modver[]                            version of the loaded module
```

### sockets.tcp.count

Supported states include:

- `ESTABLISHED`
- `SYN_SENT`
-	`SYN_RECV`
-	`FIN_WAIT1`
-	`FIN_WAIT2`
-	`TIME_WAIT`
-	`CLOSE`
-	`CLOSE_WAIT`
-	`LAST_ACK`
-	`LISTEN`
-	`CLOSING`

If the state parameter is empty, all the total number of sockets in any state is
returned.

E.g.

    $ zabbix_get -s 127.0.0.1 -k sockets.tcp.count[listen]
    2

    $ netstat -tl4
    tcp        0      0 0.0.0.0:ssh             0.0.0.0:*               LISTEN
    tcp        0      0 0.0.0.0:zabbix-agent    0.0.0.0:*               LISTEN

For greater understanding, see the [TCP/IP State Transition Diagram](http://www.cs.northwestern.edu/~agupta/cs340/project2/TCPIP_State_Transition_Diagram.pdf)
by Gordon McKinney, 2002.
