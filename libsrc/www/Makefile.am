all:	libserver.a
	cp libserver.a ../../libs

noinst_LIBRARIES = libserver.a

libserver_a_CPPFLAGS = -I$(top_srcdir)/include -Wall

libserver_a_SOURCES = server.c curl.c http_menu.c

#SRCFLAGS=	-I/usr/include/w3c-libwww -DHAVE_STRERROR
# WWWLIBS defined in .cshrc now
#WWWLIBS=	-lserver -lwwwcore -lwwwapp -lwwwutils -lwwwmime -lwwwcache \
#		-lwwwstream -lwwwdir -lwwwfile -lwwwhttp -lwwwhtml -lwwwnews \
#		-lwwwftp -lwwwxml -lxmlparse -lxmltok -lmd5 -lwwwtelnet \
#		-lwwwtrans -lwwwgopher



