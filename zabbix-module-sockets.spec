Name          : zabbix-module-sockets
Vendor        : cavaliercoder
Version       : 1.1.0
Release       : 1
Summary       : Linux socket monitoring module for Zabbix

Group         : Applications/Internet
License       : GNU GPLv2
URL           : https://github.com/cavaliercoder/zabbix-module-sockets

Source0       : %{name}-%{version}.tar.gz
Buildroot     : %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires      : zabbix-agent >= 3.2.0

%define module libzbxsockets

%description
zabbix-module-sockets is a loadable Zabbix module that enables Zabbix to monitor
the state of sockets on Linux systems.

%prep
%setup0 -q -n %{name}-%{version}

# fix up some lib64 issues
sed -i.orig -e 's|_LIBDIR=/usr/lib|_LIBDIR=%{_libdir}|g' configure

%build
%configure --enable-dependency-tracking
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%{_libdir}/zabbix/modules/%{module}.so
%{_sysconfdir}/zabbix/zabbix_agentd.d/%{module}.conf
%{_docdir}/%{name}-%{version}/README.md
%{_docdir}/%{name}-%{version}/COPYING
%{_docdir}/%{name}-%{version}/Template_App_TCP_Sockets_3.2.xml
%{_docdir}/%{name}-%{version}/Template_App_UDP_Sockets_3.2.xml
%{_docdir}/%{name}-%{version}/Template_App_TCP6_Sockets_3.2.xml
%{_docdir}/%{name}-%{version}/Template_App_UDP6_Sockets_3.2.xml
%{_docdir}/%{name}-%{version}/Template_App_Unix_Sockets_3.2.xml

%changelog
* Sun Jun 18 2017 Ryan Armstrong <ryan@cavaliercoder.com> 1.1.0-1
- Addeded support for TCP, TCP6, UDP, UDP6 and Unix sockets
- Added support for measuring Send-Q and Recv-Q
- Separated templates for each protocol

* Thu May 25 2017 Ryan Armstrong <ryan@cavaliercoder.com> 1.0.0-1
- Initial release
