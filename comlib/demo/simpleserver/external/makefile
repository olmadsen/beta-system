CFLAGS = $(CFLAGS) -D_WIN32_WINNT=0x400
CPP_FLAGS = /c /MTd /Zi /Od /D_DEBUG 
EXE_LINK_FLAGS = /NOD /DEBUG
DLL_LINK_FLAGS = /NOD /DLL /DEBUG

LIBS = kernel32.lib uuid.lib advapi32.lib ole32.lib

#################################################
#
# Proxy source files
#
PROXYSTUBRES = simpleserverproxy.res

PROXYSTUBOBJS = dlldata.obj   \
                simpleserverproxy.obj     \
                guids.obj

PROXYSTUBLIBS = kernel32.lib  \
                rpcndr.lib    \
                rpcns4.lib    \
                rpcrt4.lib    \
                uuid.lib      \
                OLEAUT32.LIB

simpleserverproxy.dll : $(PROXYSTUBOBJS) $(PROXYSTUBRES) simpleserverproxy.def
	link /dll /out:simpleserverproxy.dll /def:simpleserverproxy.def   \
		$(PROXYSTUBOBJS) $(PROXYSTUBLIBS) $(PROXYSTUBRES)
	regsvr32  simpleserverproxy.dll

simpleserver.h simpleserverproxy.c guids.c dlldata.c : simpleserver.idl
	midl /h simpleserver.h /iid guids.c /proxy simpleserverproxy.c simpleserver.idl 

dlldata.obj : dlldata.c 
	cl /c /DWIN32 /DREGISTER_PROXY_DLL $(CFLAGS) dlldata.c

simpleserverproxy.obj : simpleserverproxy.c 
	cl /c /DWIN32 /DREGISTER_PROXY_DLL $(CFLAGS) simpleserverproxy.c

simpleserverproxy.res : simpleserverproxy.rc
	rc /fo simpleserverproxy.res simpleserverproxy.rc

