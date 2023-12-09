Main file
	Constant width 65
	Constant stars<Thru 1 width> "*"

	ForEach word Find "[a-zA-Z'-]+" File file
		Inc &count[$word]
	Set count[ (Select |"index"| 'IsNil count)[] ] 0

	Set scale width/Decimal Max count[]
	ForEach cnt count length
		Set bar stars<Thru 1 scale*cnt>
		Print (Frame 2 length) " - " (Frame 5 count[length]) ": " bar "\n"

	Print "Total: " (Add count[]) "\n"
