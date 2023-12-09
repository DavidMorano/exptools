/*
** C++ command line Option class
** Release 1.0; June 1990
**
** Written using ATT C++ release 2.0.
**  by: Michael C. Block
**      ATT-BL Dept 46243, WH 1A-101
**      (RV: Access Methods Inc)
** ema: att!m.c.block
*/
class Option {

    public:
	enum Bool {False=0, True=1, Clear=0, Set=1};
	typedef void action (Option*);

    private:
	Option* nextp;
	char* namep;
	char* descp;
	action* what_to_do;
	union {
	    Bool B;
	    long i;
	    char* s;
	    float f;
	} val;
	short nlen;
	char type;
	char flgs;
	char FM_dv ()	{ return 0x01; }  // Default Value
	char FM_slb ()	{ return 0x02; }  // Single Letter Boolean
	void modflg (Bool s, const char fl)
			{ if (s) flgs |= fl; else flgs &= (0xff^fl); }
	int default_value () { return flgs & FM_dv (); }
	void default_value (Bool s) { modflg (s, FM_dv ()); }
	int single_letter_flag () { return flgs & FM_slb (); }
	void single_letter_flag (Bool s) { modflg (s, FM_slb ()); }

	Option* find_overlap ();
	void  add_option (char* s, char t, char* desc, action* funcp);
	int check_single_letter_list (char* flag);
	int set_value (char* flag, char* vstr);
	int setoption (int argc, char* argv[], int& i);
	void print (char* tag, int len=1);

    public:
	friend void Option_list (Option*);
	friend int Option_arguments (int argc, char* argv[]);
	Option (char* s, Bool value, char* desc=0, action* funcp=0);
	Option (char* s, long value, char* desc=0, action* funcp=0);
	Option (char* s, float value, char* desc=0, action* funcp=0);
	Option (char* s, char* value, char* desc=0, action* funcp=0);
	Option (char* s, char value, char* desc=0, action* funcp=0);
	Option (char* s, int value, char* desc=0, action* funcp=0);
	Option (char* s, double value, char* desc=0, action* funcp=0);
	~Option ();
	int given ()		{ return ( default_value () ? 0 : 1 ); }
	int Bvalue ();
	int Bvalue (int i);
	int Bvalue (Bool t);
	long ivalue ();
	long ivalue (long i);
	char* svalue ();
	char* svalue (char* s);
	double fvalue ();
	double fvalue (double f);
	char* name ()		{ return namep; }
	char* description ()	{ return descp ? descp : ""; }
};
