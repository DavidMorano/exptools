RowSum table
	ForEach k Thru 1 $table
		Set row_sum[$+] Add table[k][]
	Return row_sum
