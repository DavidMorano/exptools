CC=CC
CCFLAGS = -O
BSD=

SRC = Timers.c Tim.c

OBJS = Timers.o Tim.o

Timers.o : Timers.c
	$(CC) $(CCFLAGS) -c Timers.c

Tim.o : Tim.c
	$(CC) $(CCFLAGS) -c Tim.c

libTim.a : $(OBJS)
	   ar r libTim.a $(OBJS)
	   if test "$(BSD)"; then ranlib libTim.a; fi

clean : rm -f *.o *.a
	
