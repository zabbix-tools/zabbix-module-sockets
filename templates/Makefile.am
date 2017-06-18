TEMPLATES = \
	Template_App_TCP_Sockets_3.2.xml \
	Template_App_UDP_Sockets_3.2.xml \
	Template_App_TCP6_Sockets_3.2.xml \
	Template_App_UDP6_Sockets_3.2.xml \
	Template_App_Unix_Sockets_3.2.xml

EXTRA_DIST = $(TEMPLATES)

# build templates for older versions
TEMPLATES_20 := $(patsubst %_3.2.xml, %_2.0.xml, $(TEMPLATES))
templates: $(TEMPLATES_20)
%_2.0.xml: $(TEMPLATES)
	zabbix-template-converter -o 2.0 $*_3.2.xml > $@ || rm -vf $@

clean-local:
	rm -vf $(TEMPLATES_20)

install-data-local:
	$(INSTALL) -d $(DESTDIR)$(docdir)-$(PACKAGE_VERSION)
	$(INSTALL) -m 0644 \
		Template_App_TCP_Sockets_3.2.xml \
		$(DESTDIR)$(docdir)-$(PACKAGE_VERSION)/Template_App_TCP_Sockets_3.2.xml
	$(INSTALL) -m 0644 \
		Template_App_UDP_Sockets_3.2.xml \
		$(DESTDIR)$(docdir)-$(PACKAGE_VERSION)/Template_App_UDP_Sockets_3.2.xml
	$(INSTALL) -m 0644 \
		Template_App_TCP6_Sockets_3.2.xml \
		$(DESTDIR)$(docdir)-$(PACKAGE_VERSION)/Template_App_TCP6_Sockets_3.2.xml
	$(INSTALL) -m 0644 \
		Template_App_UDP6_Sockets_3.2.xml \
		$(DESTDIR)$(docdir)-$(PACKAGE_VERSION)/Template_App_UDP6_Sockets_3.2.xml
	$(INSTALL) -m 0644 \
		Template_App_Unix_Sockets_3.2.xml \
		$(DESTDIR)$(docdir)-$(PACKAGE_VERSION)/Template_App_Unix_Sockets_3.2.xml

