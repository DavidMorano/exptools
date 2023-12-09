Arabic roman
	Constant units["" "I" "II" "III" "IV" "V" "VI" "VII" "VIII" "IX"] Thru 0 9
	Constant tens["" "X" "XX" "XXX" "XL" "L" "LX" "LXX" "LXXX" "XC"] units[]
	Constant hundreds["" "C" "CC" "CCC" "CD" "D" "DC" "DCC" "DCCC" "CM"] units[]
	Constant thousands["" "M" "MM" "MMM"] units[]
	Constant place { units tens hundreds thousands }
	Constant re { (Splice "(" (Splice |"|"| (Keys units)[Thru 2 $]) ")$") \
				  (Splice "(" (Splice |"|"| (Keys tens)[Thru 2 $]) ")$") \
				  (Splice "(" (Splice |"|"| (Keys hundreds)[Thru 2 $]) ")$") \
				  (Splice "(" (Splice |"|"| (Keys thousands)[Thru 2 $]) ")$") }
	Set r roman
	Do
		Set digit Match re[Inc &k] r
		Set arabic<$+> place[k][digit]
	While Not IsNull Set r r<Thru 1 $-$digit>
	Return Reverse arabic
