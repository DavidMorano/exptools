.final			:	.USE
	$(CC) -g  -o $(<) $(*) 

STDINCLUDE.CC   =   /homer/hector/h1/jss/include/CC /usr/local/include/CC /usr/include
CC				=	~jss/bin/CC
CCFLAGS         =    -g -DBSD
LDFLAGS         =    -g -DBSD

.OPTIONS    	:   -mu
.MAIN       	:   .ALL


INTSET_SRC  =  Int_set.c settest.c

settest     :: .final $(INTSET_SRC)

