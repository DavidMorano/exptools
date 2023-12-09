NumLines in out
	Set numbered File |"w"| out
	ForEach line Lines File in
		Set numbered<$+> Splice (Frame 3 Inc &k) " " line "\n"
