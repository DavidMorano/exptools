CCDIR=/usr/local/C++/2.1
CC=$(CCDIR)/CC
CXXFLAGS=-O
LDFLAGS=
CCLIB=$(CCDIR)/lib++.a

testhmap: testhmap.o Hmap.o
	$(CC) $(LDFLAGS) -o testhmap testhmap.o Hmap.o $(CCLIB)

testhmap.o: testhmap.c Hmap.h
	$(CC) $(CXXFLAGS) -c testhmap.c

Hmap.o: Hmap.c Hmap.h
	$(CC) $(CXXFLAGS) -c Hmap.c

