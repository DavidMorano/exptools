#include	<string.h>
#include	<stdlib.h>
#undef	NDEBUG
#include	"Trace.h"


static const char*	Version = "@(#)Version 08/21/90";


Set(String)		Trace::groups;
Block(FuncData)		Trace::funcData;
int			Trace::funcNdx		= -1;
int			Trace::gotGroups	= 0;
int			Trace::doAll		= 0;

void  Trace::
getGroups(void)
{
	char*	gp;
	char*	cp;
	
	gotGroups = 1;
	gp = getenv("TRACE");
	if(gp == NULL){
		return;
	}
	while((cp = strchr(gp, ',')) != NULL){
		*cp++ = '\0';
		groups.insert(gp);
		gp = cp;
	}
	if(*gp != '\0'){
		groups.insert(gp);
	}
	if(groups.contains("all")){
		doAll = 1;
	}
}
