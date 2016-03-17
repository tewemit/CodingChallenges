
#=====================================================================================
#  This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
# Purpose: Part of course Assignment (programming in the Unix Environment)
# 
# Author: Tewelle Gerechaal
# 		   Blekinge Institute of Technology, BTH, Sweden
#====================================================================================== 
PROG=	adventure
SRCS=	server.c init.c finished.c save.c subr.c vocab.c wizard.c io.c data.c CRC_Checksum.c
OBJECTS= $(SRCS:.c=.o)
HIDEGAME=hidegame
CFLAGS=-w
LDFLAGS=
CLEANFILES=setup data.c 
EXECUTABLE = Start_Game_Server

data.c: data.txt setup all
	./setup $(.CURDIR)data.txt > data.c
	
setup: setup.c definition.h 
	$(CC) $(CFLAGS) -o setup $(.CURDIR)setup.c
	
all: $(EXECUTABLE) clean
	./$(EXECUTABLE)
	
$(EXECUTABLE): $(SRCS) definition.h
	$(CC) $(CFLAGS) $(SRCS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f *.o

