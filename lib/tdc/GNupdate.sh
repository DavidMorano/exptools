#
# GNupdate, by Franco E. Barber, CB 3d230c, atlas!feb
# Created 22 Nov 1994.
#
# Update the GN-92-600 datafile, whose name is specified
# by the DATAFILE environment variable, to contain the data
# needed by the current version of the TDC program.
# 
# Leave a copy of the old datafile in the file name specified
# by the DATAFILESAVE environment variable.

UPDATEVERSION="@(#) Version 0.1 94/11/22"


# This variable is set only in the 09-90 version of the file.
# 	BossName
# This variable is set in the 09-90 and 01-94 version of the file.
#	BoxNS
# This variable is set in the 07-94 and later versions.
# 	GN92Version

if [ "x${BossName+DEFINED}" = "xDEFINED" ]
then
	# If BossName is defined, this must be the 09-90 version.

	# Change the variables on the fly.
	WorkAddress1="${WorkAddress}"
	WorkAddress2=""
	WorkAddress3=""
	WorkAddress4=""

	if [ "x$BoxHourManuCheck" != "x" -o \
		"x$BoxHourServiceCheck" != "x" -o \
		"x$BoxHourInstallCheck" != "x" ]
	then
		# An hourly worker.  Probably paid weekly.
		BoxWeekly="X"
		BoxMonthly=""
	else
		BoxWeekly=""
		BoxMonthly="X"
	fi

	unset WorkAddress
	unset BossName
	unset BossWorkPhone
	unset BossWorkAddress1
	unset BossWorkAddress2
	unset BoxINT
	unset BoxHQ
	unset BoxNS
	unset BoxIS
	unset BoxNASSAU
	unset BoxFED
	unset BoxOTHER
	unset BoxOtherSpec
	unset BoxHourManuCheck
	unset BoxHourServiceCheck
	unset BoxHourInstallCheck
	unset BoxSalaManuCheck
	unset BoxSalaNonCheck

	# Rewrite the file to reflect the new variables.
	rm -f ${DATAFILESAVE}
	cp ${DATAFILE} ${DATAFILESAVE}

	# Start the file off with the new version number.
	echo > ${DATAFILE}
	echo "GN92Version=\"${GN92Version}\"" >> ${DATAFILE}

	sed \
		-e '/^$/d' \
		-e '/^GN92Version/d' \
		-e '/^BossName/d' \
		-e '/^BossWorkPhone/d' \
		-e '/^BossWorkAddress1/d' \
		-e '/^BossWorkAddress2/d' \
		-e '/^BoxINT/d' \
		-e '/^BoxHQ/d' \
		-e '/^BoxNS/d' \
		-e '/^BoxIS/d' \
		-e '/^BoxNASSAU/d' \
		-e '/^BoxFED/d' \
		-e '/^BoxOTHER/d' \
		-e '/^BoxOtherSpec/d' \
		-e '/^BoxHourManuCheck/d' \
		-e '/^BoxHourServiceCheck/d' \
		-e '/^BoxHourInstallCheck/d' \
		-e '/^BoxSalaManuCheck/d' \
		-e '/^BoxSalaNonCheck/d' \
		-e '/^WorkAddress/ {
			s/WorkAddress/WorkAddress1/p
			a\
WorkAddress2=""\
WorkAddress3=""\
WorkAddress4=""
			}' \
		< ${DATAFILESAVE} >> ${DATAFILE}

		echo "BoxWeekly=\"${BoxWeekly}\"" >> ${DATAFILE}
		echo "BoxMonthly=\"${BoxMonthly}\""  >> ${DATAFILE}
		

	print - "
It appears that your personal data file, ${DATAFILE},
dates from the time when the ${MYNAME} program supported
the 09-90 version of the GN-92-600 TDC form.
The ${MYNAME} program currently supports the version ${GN92Version}.

The new version of the ${MYNAME} program no longer needs some of the
entries in your personal data file (notably, all those dealing with the
name and address of your supervisor) and now allows your work address
to be split over four lines instead of being confined to just one.

This script has changed the data file to use the new data.
Your "WorkAddress" has been moved, intact, to "WorkAddress1".
Since there isn't much space on the new form for the first line
of the work address, if your address is very long it may overflow
the space available.  If you are affected by this situation, please
edit your personal data file, ${DATAFILE},
and change the contents of the variables WorkAddress1, WorkAddress2,
etc., to spread the address out over multiple lines.

A backup copy of your data file, in case something went wrong
with the conversion, is saved in ${DATAFILESAVE}.
"
	print - "Press return to continue execution."
	read_p JUNK

elif [ "x${BoxNS+DEFINED}" = "xDEFINED" ]
then
	# If we got here, it means that BossName is not defined.
	# If BoxNS is defined, this must be the 01-94 version.

	# Change the variables on the fly.

	if [ "x$BoxHourManuCheck" != "x" -o \
		"x$BoxHourServiceCheck" != "x" -o \
		"x$BoxHourInstallCheck" != "x" ]
	then
		# An hourly worker.  Probably paid weekly.
		BoxWeekly="X"
		BoxMonthly=""
	else
		BoxWeekly=""
		BoxMonthly="X"
	fi

	unset BoxNS
	unset BoxIS
	unset BoxNASSAU
	unset BoxFED
	unset BoxOTHER
	unset BoxOtherSpec
	unset BoxHourManuCheck
	unset BoxHourServiceCheck
	unset BoxHourInstallCheck
	unset BoxSalaManuCheck
	unset BoxSalaNonCheck

	# Rewrite the file to reflect the new variables.
	rm -f ${DATAFILESAVE}
	cp ${DATAFILE} ${DATAFILESAVE}

	# Start the file off with the new version number.
	echo > ${DATAFILE}
	echo "GN92Version=\"${GN92Version}\"" >> ${DATAFILE}

	sed \
		-e '/^$/d' \
		-e '/^GN92Version/d' \
		-e '/^BoxNS/d' \
		-e '/^BoxIS/d' \
		-e '/^BoxNASSAU/d' \
		-e '/^BoxFED/d' \
		-e '/^BoxOTHER/d' \
		-e '/^BoxOtherSpec/d' \
		-e '/^BoxHourManuCheck/d' \
		-e '/^BoxHourServiceCheck/d' \
		-e '/^BoxHourInstallCheck/d' \
		-e '/^BoxSalaManuCheck/d' \
		-e '/^BoxSalaNonCheck/d' \
		< ${DATAFILESAVE} >> ${DATAFILE}

		echo "BoxWeekly=\"${BoxWeekly}\"" >> ${DATAFILE}
		echo "BoxMonthly=\"${BoxMonthly}\""  >> ${DATAFILE}

	print - "
It appears that your personal data file, ${DATAFILE},
dates from the time when the ${MYNAME} program supported
the 01-94 version of the GN-92-600 TDC form.
The ${MYNAME} program currently supports version ${GN92Version}.

The new version of the ${MYNAME} program no longer needs some of the
entries in your personal data file (notably, all those dealing with the
check boxes at the top of the form).

This script has made a backup copy of your data file
and has changed the data file to use the new data.
A backup copy of your data file, in case something went wrong
with the conversion, is saved in ${DATAFILESAVE}.
"
	print - "Press return to continue execution."
	read_p JUNK



else
	# If we get here, then the data file is not the 09-90
	# and it's not the 01-94 versions, so it must be 07-94
	# or later.  These newer versions have a data file version
	# variable in the data file, so we use that variable to
	# determine what to change.

	case "${datafileGN92Version}" in
	"07-94" )
		# The current version, no conversion necessary.
		;;
	*)	# unknown version.
		echo "
Your data file, ${DATAFILE}, appears to be corrupted.
The ${MYNAME} program is unable to figure out what version
of the ${MYNAME} program the data file corresponds to.

Your data file, ${DATAFILE},
has been renamed ${DATAFILESAVE}
and saved for you to examine if you want to do so.
Because the data file can not be interpreted properly,
you will be prompted to re-enter the data.

"
		rm -f ${DATAFILESAVE}
		mv ${DATAFILE} ${DATAFILESAVE}

		print - "Press return to continue execution."
		read_p JUNK
		;;
	esac
fi


