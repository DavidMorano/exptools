Lines s
	IsNull s
		Return {}
	Else Same s<$> "\n"
		Return Cut "\n" s<Thru 1 $-1>
	Else
		Return Cut "\n" s
