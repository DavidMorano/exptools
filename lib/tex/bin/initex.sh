: use /bin/sh
#
# shell script front-end for initex and inimf
#
case $0 in
	inimf*|*/inimf*)
		_real=${TOOLS:?}/lib/tex/bin/inimf
		;;
	initex*|*/initex*)
		_real=${TOOLS:?}/lib/tex/bin/initex
		;;
	*)
		echo $0: internal error in script. Contact the providers. 1>&2
		exit 11
esac

# append default paths
TEXFONTS=${TEXFONTS:+$TEXFONTS:}.:$TOOLS/lib/tex/fonts #yes, adding "."
MFINPUTS=${MFINPUTS:+$MFINPUTS:}.:$TOOLS/lib/tex/mf
MFPOOL=${MFPOOL:+$MFPOOL:}.:$TOOLS/lib/tex/mf
_localdir=/usr/local/TeX/macros
if [ -d $_localdir ]
then
	TEXINPUTS=${TEXINPUTS:+$TEXINPUTS:}.:$_localdir:$TOOLS/lib/tex/macros
else
	TEXINPUTS=${TEXINPUTS:+$TEXINPUTS:}.:$TOOLS/lib/tex/macros
fi
TEXPOOL=${TEXPOOL:+$TEXPOOL:}.:$TOOLS/lib/tex		#but no initex...
export TEXFONTS MFINPUTS MFPOOL TEXINPUTS TEXPOOL

$_real $*
