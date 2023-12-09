
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

////////////////////////////////////////////////////////////////////
//  PROTO.h
//
//	The declarations associated with the modified ostream
//	driver for PANELFEATURES PROTOCOL to the 630 terminal
//
//
//	Copyright (c) AT&T 1988
//
//	History:
//
//	created		9/21/88	jdi
////////////////////////////////////////////////////////////////////


#define PBUFSIZE 2048
class proto_stream
{
	char *pbuf;
	streambuf *sbuf;
	ostream *ost;

public:
	proto_stream();
	~proto_stream();

	proto_stream& operator<<(char *);
	void flush();
	void put(char);
};
