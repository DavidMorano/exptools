CmdName c
	Constant cn "_add_remove_read_write"
	Return Either (IsNull c) nil Delete "^_" Match (Splice "_" c "[^_]*") cn
