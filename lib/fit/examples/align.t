Align data
	Set num DoEach 'Find "^([+-]*[0-9]+)|(~.[0-9]+)$" data
	Set left Max 0 (DoEach '$ {num[][1]})[]
	ForEach parts num
		Print (Frame left parts[1]) parts[2] "\n"
