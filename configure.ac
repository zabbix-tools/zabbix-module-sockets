AC_INIT([zabbix-module-sockets], [1.2.0], [ryan@cavaliercoder.com])
AM_INIT_AUTOMAKE([-Wall -Werror -Wno-portability foreign])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR

# init libtool
# need > v1.4 to drop 'lib' prefix from linker output
LT_PREREQ([1.4.0]) 
LT_INIT

AC_PROG_CC
AC_PROG_CC_STDC
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

# check for stdlib header files
AC_HEADER_STDC

# Checking for Zabbix headers
AX_CHECK_ZABBIX
if test ! "x$found_zabbix" = "xyes"; then
  AC_MSG_ERROR([Zabbix headers not found])
fi

dnl
dnl output
dnl
AC_CONFIG_FILES([
 Makefile
 selinux/Makefile
 src/modules/sockets/Makefile
])
AC_OUTPUT

echo "
Configuration:

  Detected OS:           ${host_os}
  Module install path:   ${libdir}

  Compiler:              ${CC}
  Compiler flags:        ${CFLAGS}

  Library-specific flags:"

if test "x$ZABBIX_CPPFLAGS" != "x"; then
  echo "    zabbix:              ${ZABBIX_CPPFLAGS}"
fi

echo
echo "************************************************************"
echo "*                 Now run '${am_make} install'                   *"
echo "*                                                          *"
echo "*            Thank you for using libzbxsystemd!            *"
echo "*               <http://cavaliercoder.com>                 *"
echo "************************************************************"
echo
