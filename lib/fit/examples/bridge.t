Main
	DisplayHands DealHands

DealHands
	Local Constant suits { "S" "H" "D" "C" }
	Constant suit[Thru 1 52] suits[]
	Constant value[Thru 1 52] Thru 1 13
	Constant deck Transpose { (Sort suit) value }
	Set shuffled_deck Permute deck
	Set hands["North"] HandPicture "North" shuffled_deck[Thru 1 13]
	Set hands["West"] HandPicture "West" shuffled_deck[Thru 14 26]
	Set hands["East"] HandPicture "East" shuffled_deck[Thru 27 39]
	Set hands["South"] HandPicture "South" shuffled_deck[Thru 40 52]
	Return hands

HandPicture position cards[]
	Local suits
	Constant face { "2" "3" "4" "5" "6" "7" "8" "9" "10" "J" "Q" "K" "A" }
	Set hand[suits[]] {}
	ForEach card cards
		Set hand[card[1]][$+] card[2]
	Set pic[$+] Splice "   " position
	ForEach suit suits
		Set pic[$+] Splice suit ": " \
						   Splice |" "| face[ (Reverse Sort hand[suit])[] ]
	Return pic

DisplayHands hands
	Constant blank_line<Thru 1 80> " "
	Constant col 15
	Constant pt["North" "West" "East" "South"] {col 0} {1 5} {2*col 5} {col 10}
	Set page[Thru 1 15] blank_line
	ForEach position Keys hands
		Set (column row) pt[position][]
		ForEach line hands[position]
			Set left_side page[Inc &row]<Thru 1 column-1>
			Set right_side Frame |"L"| page[row]<Thru column $> line
			Set page[row] Splice left_side right_side
	Print |"\n"| (DoEach 'Delete " +$" page)[] ""
