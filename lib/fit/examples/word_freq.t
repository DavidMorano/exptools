WordFrequency text
	ForEach word Words text
		Inc &count[word]
	ForEach word Sort Keys count
		Print word " " count[word] "\n"
