Meridiem hour minute second
	Constant noon 3600*12
	Constant midnight 3600*24
	Set seconds 3600*hour + 60*minute + second
	Eq seconds 0
		Return "midnight"
	Else LT seconds noon
		Return "am"
	Else Eq seconds noon
		Return "noon"
	Else LT seconds midnight
		Return "pm"
	Else
		Return "midnight"
