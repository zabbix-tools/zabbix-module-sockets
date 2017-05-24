lib_LTLIBRARIES = libzbxsockets.la

libzbxsockets_la_SOURCES = \
	libzbxsockets.h \
	libzbxsockets.c \
	tcp.c

libzbxsockets_la_CFLAGS = \
	$(DBUS_CPPFLAGS) \
	$(ZABBIX_CPPFLAGS)

libzbxsockets_la_LDFLAGS = \
	-shared \
	-module \
	-avoid-version \
	$(DBUS_LDFLAGS)

install-data-hook: install-module install-module-conf

# move module into correct location
install-module:
	rm -f \
		$(DESTDIR)$(libdir)/libzbxsockets.la \
		$(DESTDIR)$(libdir)/libzbxsockets.so
	$(MKDIR_P) $(DESTDIR)$(libdir)/zabbix/modules/
	$(INSTALL) -m 644 ./.libs/libzbxsockets.so \
		$(DESTDIR)$(libdir)/zabbix/modules/libzbxsockets.so
	
# install config file
install-module-conf:
	$(MKDIR_P) $(DESTDIR)$(sysconfdir)/zabbix/zabbix_agentd.d
	test -f "$(DESTDIR)$(sysconfdir)/zabbix/zabbix_agentd.d/libzbxsockets.conf" || \
		$(INSTALL) -m 0644 ../../../conf/libzbxsockets.conf \
			$(DESTDIR)$(sysconfdir)/zabbix/zabbix_agentd.d/libzbxsockets.conf
