
TEMPLATES_32 := $(wildcard *_3.2.xml)
TEMPLATES_20 := $(patsubst %_3.2.xml, %_2.0.xml, $(wildcard *_3.2.xml))

EXTRA_DIST = $(TEMPLATES_32)

templates: $(TEMPLATES_20)

%_2.0.xml: $(TEMPLATES_32)
	zabbix-template-converter -o 2.0 $*_3.2.xml > $@ || rm -vf $@

install-data-local:
	$(INSTALL) -d $(DESTDIR)$(docdir)-$(PACKAGE_VERSION)
	$(INSTALL) -m 0644 \
		Template_App_Sockets_3.2.xml \
		$(DESTDIR)$(docdir)-$(PACKAGE_VERSION)/Template_App_Sockets_3.2.xml
