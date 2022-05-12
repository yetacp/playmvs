#
# Makefile for Linux version of rdrprep
#

DESTDIR  = $(PREFIX)/usr/local/bin
CC = gcc

# Standard flags for all architectures
CFLAGS	 = -O2 -Wall -fPIC 
CFL_370  = -O2 -Wall -fPIC 
LFLAGS	 = -lpthread

# Add default flags for Pentium compilations
ifndef HOST_ARCH
CFLAGS	 += -malign-double 
CFL_370  += -malign-double 
endif

# Handle host architecture if specified
ifeq ($(HOST_ARCH),i386)
CFLAGS	 += -malign-double
CFL_370	 += -malign-double
endif
ifeq ($(HOST_ARCH),i586)
CFLAGS	 += -malign-double 
CFL_370  += -malign-double 
endif
ifeq ($(HOST_ARCH),i686)
CFLAGS	 += -malign-double 
CFL_370  += -malign-double 
endif

EXEFILES = rdrprep

RECV_OBJS = rdrprep.o

all:	   $(EXEFILES)

rdrprep: $(RECV_OBJS)
	$(CC) -o rdrprep $(RECV_OBJS)

install:  $(EXEFILES)
	cp $(EXEFILES) $(DESTDIR)

clean:
	rm -f rdrprep.o rdrprep
	rm -f $(DESTDIR)/$(EXEFILES)
