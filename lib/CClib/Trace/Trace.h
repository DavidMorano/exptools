#ifndef	TraceH
#define	TraceH


#include	<sys/types.h>
#include	<iostream.h>
#include	<iomanip.h>
#include	<String.h>
#include	<Block.h>
#include	<Set.h>

#if	defined(NDEBUG)

#define	traceFcn(Nam)		__trace
#define	traceMsg(Msg)
#define	traceDec(Val)
#define	traceHex(Val)
#define	tracePtr(Val)
#define	traceChr(Val)
#define	traceStr(Val)

#define	traceFcnGrp(Nam,Grp)	__trace
#define	traceMsgGrp(Msg,Grp)
#define	traceDecGrp(Val,Grp)
#define	traceHexGrp(Val,Grp)
#define	tracePtrGrp(Val,Grp)
#define	traceChrGrp(Val,Grp)
#define	traceStrGrp(Val,Grp)

class Trace {
};

#else	/* !defined(NDEBUG)	*/

#if defined(__STDC__)

#define	traceFcn(Nam)		__trace(__FILE__, __LINE__, Nam, "funcs")
#define	traceMsg(Msg)		__trace.msgFunc(__LINE__, Msg)
#define	traceDec(Val)		__trace.decFunc(__LINE__, #Val, Val)
#define	traceHex(Val)		__trace.hexFunc(__LINE__, #Val, Val)
#define	tracePtr(Val)		__trace.ptrFunc(__LINE__, #Val, Val)
#define	traceChr(Val)		__trace.chrFunc(__LINE__, #Val, Val)
#define	traceStr(Val)		__trace.strFunc(__LINE__, #Val, Val)

#define	traceFcnGrp(Nam,Grp)	__trace(__FILE__, __LINE__, Nam, Grp)
#define	traceMsgGrp(Msg,Grp)	__trace.msgFunc(__LINE__, Msg, Grp)
#define	traceDecGrp(Val,Grp)	__trace.decFunc(__LINE__, #Val, Val, Grp)
#define	traceHexGrp(Val,Grp)	__trace.hexFunc(__LINE__, #Val, Val, Grp)
#define	tracePtrGrp(Val,Grp)	__trace.ptrFunc(__LINE__, #Val, Val, Grp)
#define	traceChrGrp(Val,Grp)	__trace.chrFunc(__LINE__, #Val, Val, Grp)
#define	traceStrGrp(Val,Grp)	__trace.strFunc(__LINE__, #Val, Val, Grp)

#else	/* !defined(__STDC__) */

#define	traceFcn(Nam)		__trace(__FILE__, __LINE__, Nam, "funcs")
#define	traceMsg(Msg)		__trace.msgFunc(__LINE__, Msg)
#define	traceDec(Val)		__trace.decFunc(__LINE__, "Val", Val)
#define	traceHex(Val)		__trace.hexFunc(__LINE__, "Val", Val)
#define	tracePtr(Val)		__trace.ptrFunc(__LINE__, "Val", Val)
#define	traceChr(Val)		__trace.chrFunc(__LINE__, "Val", Val)
#define	traceStr(Val)		__trace.strFunc(__LINE__, "Val", Val)

#define	traceFcnGrp(Nam,Grp)	__trace(__FILE__, __LINE__, Nam, Grp)
#define	traceMsgGrp(Msg,Grp)	__trace.msgFunc(__LINE__, Msg, Grp)
#define	traceDecGrp(Val,Grp)	__trace.decFunc(__LINE__, "Val", Val, Grp)
#define	traceHexGrp(Val,Grp)	__trace.hexFunc(__LINE__, "Val", Val, Grp)
#define	tracePtrGrp(Val,Grp)	__trace.ptrFunc(__LINE__, "Val", Val, Grp)
#define	traceChrGrp(Val,Grp)	__trace.chrFunc(__LINE__, "Val", Val, Grp)
#define	traceStrGrp(Val,Grp)	__trace.strFunc(__LINE__, "Val", Val, Grp)

#endif	/* defined(__STDC__) */

struct FuncData {
	String			fileNm;		// File name.
	int			lineNbr;	// Line number of declaration
						// of Trace object.
	String			funcNm;		// Function name.
	String			groupNm;	// String name.
};

Blockdeclare(FuncData);
Setdeclare(String);

class Trace {
	public:
		inline			Trace(const String& file, int line,
					      const String& func,
					      const String& group);
		inline			~Trace(void);
		
		inline void		msgFunc(int line, const String& msg);
		inline void		msgFunc(int line, const String& msg,
						const String& group);
		inline void		decFunc(int line, const String& lbl,
						long val);
		inline void		decFunc(int line, const String& lbl,
						long val, const String& group);
		inline void		hexFunc(int line, const String& lbl,
						ulong val);
		inline void		hexFunc(int line, const String& lbl,
						ulong val, const String& group);
		inline void		ptrFunc(int line, const String& lbl,
						const void	* val);
		inline void		ptrFunc(int line, const String& lbl,
						const void	* val,
						const String& group);
		inline void		chrFunc(int line, const String& lbl,
						char val);
		inline void		chrFunc(int line, const String& lbl,
						char val, const String& group);
		inline void		strFunc(int line, const String& lbl,
						const String& val);
		inline void		strFunc(int line, const String& lbl,
						const String& val,
						const String& group);
		
	private:
		void			getGroups(void);
		inline int		doTrace(const String& group);
		inline void		labelOut(int line);
		
		static Set(String)	groups;
		static Block(FuncData)	funcData;
		static int		funcNdx;
		static int		gotGroups;
		static int		doAll;
};



inline  Trace::
Trace(const String& file, int line, const String& func, const String& group)
{
	funcData.reserve(++funcNdx);
	funcData[funcNdx].fileNm = file;
	funcData[funcNdx].lineNbr = line;
	funcData[funcNdx].funcNm = func;
	funcData[funcNdx].groupNm = group;
	if(!gotGroups){
		getGroups();
	}
	if(doTrace(group)){
		labelOut(line);
		cerr << "Entered." << endl;
	}
}

inline  Trace::
~Trace(void)
{
	if(doTrace(funcData[funcNdx].groupNm)){
		labelOut(funcData[funcNdx].lineNbr);
		cerr << "Returning." << endl;
	}
	--funcNdx;
}

inline void  Trace::
msgFunc(int line, const String& msg)
{
	msgFunc(line, msg, funcData[funcNdx].groupNm);
}

inline void  Trace::
msgFunc(int line, const String& msg, const String& group)
{
	if(doTrace(group)){
		labelOut(line);
		cerr << msg <<  endl;
	}
}

inline void  Trace::
decFunc(int line, const String& lbl, long val)
{
	decFunc(line, lbl, val, funcData[funcNdx].groupNm);
}

inline void  Trace::
decFunc(int line, const String& lbl, long val, const String& group)
{
	if(doTrace(group)){
		labelOut(line);
		cerr << lbl << " = " <<  val << endl;
	}
}

inline void  Trace::
hexFunc(int line, const String& lbl, ulong val)
{
	hexFunc(line, lbl, val, funcData[funcNdx].groupNm);
}

inline void  Trace::
hexFunc(int line, const String& lbl, ulong val, const String& group)
{
	long	flgs;
	
	if(doTrace(group)){
		labelOut(line);
		flgs = cerr.flags();
		cerr << lbl << " = " << setiosflags(ios::showbase) << hex
		     <<  val << endl;
		cerr.flags(flgs);
	}
}

inline void  Trace::
ptrFunc(int line, const String& lbl, const void* val)
{
	ptrFunc(line, lbl, val, funcData[funcNdx].groupNm);
}

inline void  Trace::
ptrFunc(int line, const String& lbl, const void* val, const String& group)
{
	long	flgs;
	
	if(doTrace(group)){
		labelOut(line);
		flgs = cerr.flags();
		cerr << lbl << " = " << setiosflags(ios::showbase) << hex
		     <<  val << endl;
		cerr.flags(flgs);
	}
}

inline void  Trace::
chrFunc(int line, const String& lbl, char val)
{
	chrFunc(line, lbl, val, funcData[funcNdx].groupNm);
}

inline void  Trace::
chrFunc(int line, const String& lbl, char val, const String& group)
{
	if(doTrace(group)){
		labelOut(line);
		cerr << lbl << " = " << "'" << val << "'" << endl;
	}
}

inline void  Trace::
strFunc(int line, const String& lbl, const String& val)
{
	strFunc(line, lbl, val, funcData[funcNdx].groupNm);
}

inline void  Trace::
strFunc(int line, const String& lbl, const String& val, const String& group)
{
	if(doTrace(group)){
		labelOut(line);
		cerr << lbl << " = " << "\"" << val << "\"" << endl;
	}
}

inline int  Trace::
doTrace(const String& group)
{
	return doAll  ||  groups.contains(group);
}

inline void  Trace::
labelOut(int line)
{
	cerr << funcData[funcNdx].fileNm
	     << "(" << line << ")"
	     << funcData[funcNdx].funcNm
	     << " ";
}

#endif	/* defined(NDEBUG)	*/


#endif	/* TraceH	*/
