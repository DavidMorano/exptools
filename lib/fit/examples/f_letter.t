Main letter database
	Set form Cut "[<>]" File letter
	ForEach line Lines File database
		Set data["name" "amount" "fund"] (Cut " *; *" line)[]
		Print form[1]
		ForEach k Thru 2 $form 2
			Print data[ form[k] ] form[k+1]
