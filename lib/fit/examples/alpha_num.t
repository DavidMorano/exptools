AlphaNumeral number
	Constant a Ascii "a"
	Set n number
	While GT n 0
		Set s<$+> Char a+Mod (Dec &n) 26
		Set n Whole n/26
	Return Reverse s
