all: libzbxsockets.pp

libzbxsockets.mod: libzbxsockets.te
	checkmodule -m -M libzbxsockets.te -o libzbxsockets.mod

libzbxsockets.pp: libzbxsockets.mod
	semodule_package -m libzbxsockets.mod -o libzbxsockets.pp

clean-local:
	rm -vf libzbxsockets.mod libzbxsockets.pp

install-data-local: libzbxsockets.pp
	$(INSTALL) -d $(DESTDIR)$(datarootdir)/selinux/packages/$(PACKAGE_NAME)
	$(INSTALL) -m 0644 libzbxsockets.pp \
		$(DESTDIR)$(datarootdir)/selinux/packages/$(PACKAGE_NAME)/libzbxsockets.pp

# .PHONY: all clean install

EXTRA_DIST = libzbxsockets.te
