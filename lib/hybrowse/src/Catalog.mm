'\" Create a (variable) list item with a reference
'\" Arguments:  document  section
'\"    "section" defaults to "Table of Contents"
.de hL
.LI "\\*(Rf \\$1"
.RS
.ie '\\$2'' .hT "\\$1" "Table of Contents"
.el .hT "\\$1" "\\$2"
.RF
..
.H 1 "Standard hybrowse Documents"
This is default hybrowse Catalog.
It's not very interesting, so most applications should override it
with a catalog listing the application's documents.
See the Admin document for details.
.P
.VL 16
.hL Help
a reference document that lists all the browser commands
.hL Tutorial "Basic Commands"
an introduction to the browser for new users
.hL Admin Introduction
instructions on how to format documents for access by the browser
.LE
