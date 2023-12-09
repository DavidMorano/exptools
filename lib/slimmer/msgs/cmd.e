The examine command (usually abbreviated to e) allows you to look at
the actual index for the database. It shows you the terms indexed from
the database in alphabetical order.  Note that it displays index terms
derived from all fields. This acts much like a permuted index in
helping you find index terms like what you desire - or how the particular
database indexed a particular concept.

The display is alphabetical surrounding the term you enter. Each index
term is listed along with the number of documents indexed by the given
term. Each index term is also given a number in the expand list (e1 - e15).

Expand list items can be used as search terms. For example, the term "e5"
is the same as entering the index term corresponding to "e5". And of course
they can all be used in combination:
      s ((e5 and youth)  not s4) and e12
