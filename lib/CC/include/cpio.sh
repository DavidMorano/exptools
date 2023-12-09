#ident	"@(#)C++env:incl-master/const-headers/cpio.sh	1.1"
#!/bin/sh
#
# A directory-tree copy command based loosely on cpio -p.  Allows the
# building and installation of cfront on systems which don't have the
# cpio command (if any such systems still exist).
#

link=0
verbose=

case $1 in -*)
	case $1 in *i*|*o*)
		echo "$0: error: can only be used in pass mode"
		exit 1
	;;esac
	case $1 in *l*)
		link=1
	;;esac
	case $1 in *v*)
		verbose=-x
	;;esac
	shift
;;esac

case $# in 1) ;;*)
	echo "usage: $0 [ -lv ] target"
	exit 1
;;esac

sed 's/^\.\///' |
xargs ls -ld |
case $link in 0)
	awk '	BEGIN { TARG = "'$1'"; or = "2>/dev/null ||"; }
		$NF == "." || $NF == ".." { next; }
		/^l/ { print "ln -s", $NF, TARG "/" $(NF-2), or; }
		/^-/ { print "cp "  , $NF, TARG "/" $NF, or; }
		/^d/ { print "mkdir", TARG "/" $NF, or; }
		$1 ~ /^-/ || $1 ~ /^[ld]/ { print "exit 1"; }
		END { print "exit 0"; }'
;;*)
	awk '	BEGIN { TARG = "'$1'"; or = "2>/dev/null ||"; }
		$NF == "." || $NF == ".." { next; }
		/^l/ { print "ln -s", $NF, TARG "/" $(NF-2), or; }
		/^-/ {
			print "ln "  , $NF, TARG "/" $NF, or;
			print "cp "  , $NF, TARG "/" $NF, or;
		}
		/^d/ { print "mkdir", TARG "/" $NF, or; }
		$1 ~ /^-/ || $1 ~ /^[ld]/ { print "exit 1"; }
		END { print "exit 0"; }'
;;esac |
sh $verbose
exit $?
