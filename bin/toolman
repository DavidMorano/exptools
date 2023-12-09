#!/bin/sh

# toolman - print man pages

# $TOOLS may not be set correctly until the user reads the introductory news.
if test -n "$TOOLS" -a -d $TOOLS/lib/toolnews
then	:
else	echo 'The TOOLS environment variable must be set to the exptools home directory' >&2
	echo 'and exported; see the following introduction to exptools.' >&2
	sleep 2
	${PAGER:-cat} `logdir exptools`/lib/toolnews/Intro >&2
	exit 1
fi

# added to increase the likelihood of getting system versions of sort, etc.
PATH=/bin:/usr/bin:$PATH
export PATH

# Variables used to parse argument line and build "find" command
FND_NAME=	# a name of a file to find, may contain meta-characters
FND_DIRS=	# set to a list of dirs to use as the roots for find
FND_NEW=	# set to "-newer ${TM_TIME}" if -N option is used
FND_FILTER=	# set to "| egrep -v -f${TM_TIME}" if -N option and file exists
TM_TIME=$HOME/.toolman_time

# Variables used to prepare command lines for printing
TM_ACTION="cat"	# set to "print", "cat", or "list"
: ${TM_PRCMD:=""}
if [ -z "$TM_PRCMD" -a -x "$TOOLS/lib/toolman/toolman_local" ]
then TM_PRCMD="$TOOLS/lib/toolman/toolman_local"
fi
OPTS=""		# options for print command line

# the opr options are obsolete (can use -O); kept for backward compatibility
OPR_GOPTS="a:b:c:d:f:j:o:u:sz12"
TM_GOPTS="CLNXxD:O:P:"
OPTIONS=`getopt "${TM_GOPTS}${OPR_GOPTS}" "$@"`
if [ $? -ne 0 ]
then	echo "Usage: toolman [-XCL] [-D package] [-O printoption]... [-P printscript] tools" >&2
	echo "or     toolman -N [-L] [-D package] [-O printoption]... [-P printscript]" >&2
	echo "See the manual page (type \"toolman toolman\") for other information." >&2
	exit 1
fi
eval set -- `echo "$OPTIONS" | sed 's/[^ ][^ ]*/"&"/g'`

# pg is not in the default PATH on Suns, and may not be in the user's PATH
# on mips
if test -n "$PAGER"
then	pager=$PAGER
elif test -x /usr/bin/pg
then	pager=/usr/bin/pg
elif test -x /usr/5bin/pg
then	pager=/usr/5bin/pg
else	pager=cat
fi

# quick check for the common interactive case of a single standard man page
if test $# = 2 -a $1 = '--' -a -f "$TOOLS/man/1.$2"
then	$pager $TOOLS/man/1.$2	# note: pg isn't in the default path on Suns
	exit 0
fi

SKIP_OPTARG=FALSE
for i in "$@"
do
	# only parse toolman's options, not any arguments
	# (e.g. don't parse 'printoption' in  -O printoption)
	if test $SKIP_OPTARG = TRUE
	then
		# argument from previous iteration's option has now been skipped
		SKIP_OPTARG=FALSE
	else
		case $i in
		--)	shift
			break
			;;
		'')	: ignore this
			;;
		-X|-x)	# -x is a common error; but dwim (do what I mean)
			if [ "${TM_ACTION}" != "list" ]; then TM_ACTION="print"; fi
			shift
			;;
		-P)	TM_PRCMD="$2"
			if [ "${TM_ACTION}" != "list" ]; then TM_ACTION="print"; fi
			shift 2
			SKIP_OPTARG=TRUE
			;;
		-N)	if [ ! -f ${TM_TIME} ]
			then	echo "Creating ${TM_TIME} file for next use of toolman -N." >&2
				touch ${TM_TIME}
				exit 0
			fi
			FND_NEW="-newer ${TM_TIME}"
			if [ "${TM_ACTION}" != "list" ]; then TM_ACTION="print"; fi
			shift
			;;
		-L)	TM_ACTION="list"
			shift
			;;
		-D)	case $2 in
			'all')
				FND_DIRS="$FND_DIRS $TOOLS/man $TOOLS/lib/*/man"
				;;
			'man'|'standard')
				FND_DIRS="$FND_DIRS $TOOLS/man"
				;;
			'optional')
				FND_DIRS="$FND_DIRS $TOOLS/lib/*/man"
				;;
			'provider')
				FND_DIRS="$FND_DIRS $TOOLS/adm/upd1.1/man"
				;;
			*/*)
				# Slash found in argument
				FND_DIRS="$FND_DIRS $2"
				;;
			*)
				# No slash found in argument
				FND_DIRS="$FND_DIRS $TOOLS/lib/$2/man"
				;;
			esac
			shift 2
			SKIP_OPTARG=TRUE
			;;
		-C)	FND_NAME="-name '[01].Contents' -o -name '[01].Index'"
			FND_DIRS="$FND_DIRS $TOOLS/man"
			shift
			;;
		-O)	OPTS="$OPTS $2"
			shift 2
			SKIP_OPTARG=TRUE
			;;
		-[!-])	OPTS="$OPTS $1"
			case "$2" in
			-*)	shift
				;;
			*)	OPTS="$OPTS $2"
				shift 2
				SKIP_OPTARG=TRUE
				;;
			esac
			;;
		esac
	fi
done

# remove the temp files on exit; preserve the return code when exit is trapped
TEMP1=/usr/tmp/toolman1$$
TEMP2=/usr/tmp/toolman2$$
_exit() { _exit_code=${1:-'0'}; /bin/rm -f $TEMP1 $TEMP2; exit ${_exit_code}; }
trap "_exit 1" 1 2 3
trap '/bin/rm -f $TEMP1 $TEMP2; exit ${_exit_code}' 0 

if [ "$FND_NEW" ]	# -N option
then
	if test -s $TM_TIME
	then	FND_FILTER="| egrep -v -f$TM_TIME"
	fi
else
	if [ -z "${*}${FND_NAME}" ]	# No tool list or other name selection
	then	echo "No tool list on the command line (see the manual page)"  >&2
		exit 1
	fi
	rm -f $TEMP1	# make sure it's empty
	for i in "$@"
	do
		case $i in
		'*')	FND_NAME="-name '[0-8].*'"
			break
			;;
		'')	break
			;;
		*)	echo "/[0-8].$i$" >>$TEMP1
			FND_FILTER="| cgrep -f$TEMP1"
			;;
		esac
	done
fi

if [ "$FND_NAME" ]
then
	FND_NAME="\\( $FND_NAME \\)"
else
	FND_NAME="-name '[0-8].*'"
fi

if [ "$FND_DIRS" ]
then
	FND_DIRS=`ls -d $FND_DIRS 2> /dev/null`
	if [ -z "$FND_DIRS" ]
	then	echo "The directories you specified don't exist." >&2
		exit 1
	fi
else
FND_DIRS="$TOOLS/man $TOOLS/lib/*/man $TOOLS/adm/*/man"
fi

eval find $FND_DIRS $FND_NAME $FND_NEW -print $FND_FILTER >$TEMP2
if [ ! -s "$TEMP2" ]
then
	if [ "$TM_ACTION" = "list" ]
	then	echo "No manual pages to list"  >&2
	elif [ "$FND_NEW" ]
	then 	echo "No new manual pages to print" >&2
	else	echo "Can't find any manual pages to print." >&2
	fi
	_exit 1
fi
newcount=`cat $TEMP2 | wc -l | tr -d ' '`
if test "$FND_NEW" -a $newcount -ge `ls $TOOLS/man | wc -l`
then	echo "Too many ($newcount) new manual page files; probably all were touched." >&2
	touch ${TM_TIME}
	_exit 1
fi

# xargs avoids overflowing the argument list to "ls -i"
cat $TEMP2 | xargs ls -i |	\
# awk now puts the package name first and the manual page name second
# make sure Contents winds up the very first and Index winds up second
# Also try to print user manual pages (from -D option) first.  The method
# is far from perfect, but it's better than nothing for now.
awk -F/ '
$(NF-3) == "lib" && $(NF-4) == "exptools"	{print $(NF-2) " " $NF " " $0; next}
$NF ~ /Contents|Index/	{print "002 " $NF " " $0; next}	# contents files
$(NF-2) == "exptools"	{print "003 " $NF " " $0; next}	# standard package
			{print "001 " $NF " " $0; next}	# user files
' | \
# sort by inumber
sort  +2 -3un | \
# sort by package and man page name
sort +0 -2df -o $TEMP2

case "$TM_ACTION" in
"list")	cat $TEMP2 | sed 's/[ 	][0-8]\./ /' | awk '
	BEGIN		{ printf "%-16s%s\n", "Package", "Tool"
			  printf "--------------------------------\n"
			}
	$1 == "001"	{ printf "%-16s%s\n", "provider", $2; next }
	$1 == "002"	{ printf "%-16s%s\n", "standard", $2; next }
	$1 == "003"	{ printf "%-16s%s\n", "standard", $2; next }
			{ printf "%-16s%s\n", $1, $2 }'
	_exit 0
	;;
"cat")	$pager `awk '{print $4}' $TEMP2`
	_exit 0
	;;
"print")
	if [ -n "$TM_PRCMD" ]
	then	awk '{print $4}' $TEMP2 | xargs $TM_PRCMD $OPTS
	elif test -n "`$TOOLS/bin/where opr`"
	then	XEROX_OFF="12"
		XEROX_JOB="TOOLMAN"
		OPROPTS=""
		TM_SIDES="2"
		if [ "$OPTS" ]
		then	set -- $OPTS
			for i in "$@"
			do
				case "$i" in
				-1)	TM_SIDES="1"
					shift
					;;
				-2)	TM_SIDES="2"
					shift
					;;
				-o)	XEROX_OFF=$2
					shift 2
					;;
				-j)	XEROX_JOB=$2
					shift 2
					;;
				-*)	OPROPTS="$OPROPTS $1"
					case "$2" in
					-*)	shift
						;;
					*)	OPROPTS="$OPROPTS $2"
						shift 2
						;;
					esac
					;;
				esac
			done
		fi
		PRCMD="$TOOLS/bin/2pr -P${TM_SIDES} -T"
		OPRCMD="$TOOLS/lib/xerox/37X | xerox -l66 -h${XEROX_OFF} -${TM_SIDES} | opr -txr -r -${TM_SIDES} ${OPROPTS} -j${XEROX_JOB}"
		awk '{print $4}' $TEMP2 | xargs echo ${PRCMD} | awk '
		BEGIN		{ i = 1; open = 0 }
				{ if (open == 0) print "("
				  print
				  open = 1
				}
		NR%6 == 0	{ print ") | '"${OPRCMD}"'" i; i+=1; open = 0 }
		END		{ if (open != 0) print ") | '"${OPRCMD}"'" i }
		' | batch

	elif test -n "`$TOOLS/bin/where prt`"
	then	XEROX_JOB=TOOLMAN
		PRTOPTS=
		TM_SIDES=2
		if [ "$OPTS" ]
		then	set -- $OPTS
			for i in "$@"
			do	case $i in
				-1)	TM_SIDES=1
					shift
					;;
				-2)	TM_SIDES=2
					shift
					;;
				-j)	XEROX_JOB=$2
					shift 2
					;;
				-*)	PRTOPTS="$PRTOPTS $1"
					case $2 in
					-*)	shift
						;;
					*)	PRTOPTS="$PRTOPTS $2"
						shift 2
						;;
					esac
					;;
				esac
			done
		fi
		PRCMD="$TOOLS/bin/2pr -P${TM_SIDES} -T"
		PRTCMD="$TOOLS/lib/xerox/37X | $TOOLS/bin/xerox -l66 -h12 -${TM_SIDES} | prt -l raw -s${TM_SIDES} -j${XEROX_JOB}" ${PRTOPTS}
		awk '{print $4}' $TEMP2 | xargs echo ${PRCMD} | awk '
		BEGIN		{ i = 1; open = 0 }
				{ if (open == 0) print "("
				  print
				  open = 1
				}
		NR%6 == 0	{ print ") | '"${PRTCMD}"'" i; i+=1; open = 0 }
		END		{ if (open != 0) print ") | '"${PRTCMD}"'" i }
		' | batch

	elif test -x $TOOLS/bin/postcpr		# postscript printing
	then	awk '{print $4}' $TEMP2 | xargs cat | \
			$TOOLS/lib/xerox/37X | $TOOLS/bin/postcpr | lp $OPTS

	else	# print without bold and italics fonts
		awk '{print $4}' $TEMP2 | xargs cat | col -b | lp $OPTS
	fi
	if [ "$FND_NEW" ]
	then
		touch ${TM_TIME}
	fi
	_exit 0
	;;
esac
