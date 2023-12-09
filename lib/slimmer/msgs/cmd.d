The display command (usually abbreviated to d) allows you to display the
records from a retrieved set. It has the format:
	d <set number>/<format>/<item list>

  <set number> is a number between 1 and the highest numbered set created;

  <format> is a single letter display format. These depend on database but
       b = brief;  f = full;   s = staff.
   <item list> is a general list of items. E.g.  1    2,4-7,15

   Some examples:

       d 1/f/1-4        Full display of items 1 through 4 in set 1.
       d1/f/2           Full display of item 2 in set 1.
       d s4/b/5-13      Brief display of items 5 through 13 in set 4.
       d2/f/3,6         Full display of items 3 and 6 in set 2.
