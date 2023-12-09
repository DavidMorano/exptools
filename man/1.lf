


     LLLLFFFF((((1111))))                       ((((8888////22226666////88880000))))                       LLLLFFFF((((1111))))



     NNNNAAAAMMMMEEEE
          lf, ll - list contents of directory

     SSSSYYYYNNNNOOOOPPPPSSSSIIIISSSS
          llllffff [ ----aaaabbbbccccddddffffiiiillllmmmmnnnnqqqqrrrrssssttttuuuuvvvvxxxx1111AAAACCCCFFFFRRRR ] name ...
          llll [ _l_f options ] name ...
          llllllll [ _l_f options ] name ...
          llllssss [ _l_f options ] name ...
          llllxxxx [ _l_f options ] name ...

     DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
          For each directory argument, _l_f lists the contents of the
          directory; for each file argument, _l_f repeats its name and
          any other information requested.  The output is sorted
          alphabetically by default.  When no argument is given, the
          current directory is listed.  When several arguments are
          given, the arguments are first sorted appropriately, but
          file arguments appear before directories and their contents.

          There are several major listing formats.  The format chosen
          depends on whether the output is going to a teletype, and
          may also be controlled by option flags.  The default format
          for a teletype is to list the contents of directories in
          multi-column format, with the entries sorted down the
          columns.  (Files which are not the contents of a directory
          being interpreted are always sorted across the page rather
          than down the page in columns.  This is because the
          individual file names may be arbitrarily long.  This format
          may be requested with _l_x or ----xxxx.) If the standard output is
          not a teletype, the default format is to list one entry per
          line.  (This is the ----1111 option.) A long listing, detailing
          much information about the file, can be requested with _l_l or
          ----llll.) Finally, there is a stream output format in which files
          are listed across the page, separated by `,' characters.
          The ----mmmm flag or _l invocation enables this format.

          When invoked as _l_f the ----FFFF option is automatically turned on,
          if the output is a teletype.

          There are an unbelievable number of options:

          ----llll   List in long format, giving mode, number of links,
               owner, group, size in bytes, and time of last
               modification for each file.  (See below.) If the file
               is a special file the size field will instead contain
               the major and minor device numbers.

          ----nnnn   Same as ----llll except owner and group are printed as
               integers instead of searching the password and group
               files for translations.

          ----tttt   Sort by time modified (latest first) instead of by



     Page 1                                           (printed 4/5/85)






     LLLLFFFF((((1111))))                       ((((8888////22226666////88880000))))                       LLLLFFFF((((1111))))



               name, as is normal.

          ----aaaa   List all entries; usually entries beginning with `....'
               are suppressed.

          ----AAAA   List all entries except `....' and `........'

          ----ssss   Give size in blocks, including indirect blocks, for
               each entry.

          ----dddd   If argument is a directory, list only its name, not its
               contents (mostly used with ----llll to get status on
               directory).

          ----rrrr   Reverse the order of sort to get reverse alphabetic or
               oldest first as appropriate.

          ----uuuu   Use time of last access instead of last modification
               for sorting (----tttt) or printing (----llll).

          ----cccc   Use time of file creation for sorting or printing.

          ----iiii   Print i-number in first column of the report for each
               file listed.

          ----ffff   Force each argument to be interpreted as a directory
               and list the name found in each slot.  This option
               turns off ----llll,,,, ----tttt,,,, ----ssss,,,, and ----rrrr,,,, and turns on ----aaaa;;;; the
               order is the order in which entries appear in the
               directory.

          ----mmmm   force stream output format.

          ----1111   force one entry per line output format, e.g. to a
               teletype.

          ----CCCC   force multi-column output, e.g. to a file or a pipe.

          ----vvvv   on multi-column output, vary column width with length
               of file names.

          ----qqqq   force printing of non-graphic characters in file names
               as the character `?'; this normally happens only if the
               output device is a teletype.

          ----bbbb   force printing of non-graphic characters to be in the
               \ddd notation, in octal.

          ----xxxx   force columnar printing to be sorted across rather than
               down the page; this is the default if the last
               character of the name the program is invoked with is an
               `x'.



     Page 2                                           (printed 4/5/85)






     LLLLFFFF((((1111))))                       ((((8888////22226666////88880000))))                       LLLLFFFF((((1111))))



          ----FFFF   cause directories to be marked with a leading and
               trailing square brackets `[ _d_i_r ]' and executable files
               to be marked with a leading `*'; this is the default if
               the last character of the name the program is invoked
               with is a `f'.

          ----RRRR   recursively list subdirectories encountered.

          The mode printed under the ----llll option contains 11 characters
          which are interpreted as follows:  the first character is

          dddd  if the entry is a directory;
          bbbb  if the entry is a block-type special file;
          cccc  if the entry is a character-type special file;
          mmmm  if the entry is a multiplexor-type character special
             file;
          ----  if the entry is a plain file.

          The next 9 characters are interpreted as three sets of three
          bits each.  The first set refers to owner permissions; the
          next to permissions to others in the same user-group; and
          the last to all others.  Within each set the three
          characters indicate permission respectively to read, to
          write, or to execute the file as a program.  For a
          directory, `execute' permission is interpreted to mean
          permission to search the directory for a specified file.
          The permissions are indicated as follows:

          rrrr  if the file is readable;
          wwww  if the file is writable;
          xxxx  if the file is executable;
          ----  if the indicated permission is not granted.

          The group-execute permission character is given as ssss if the
          file has set-group-ID mode; likewise the user-execute
          permission character is given as ssss if the file has set-
          user-ID mode.

          The last character of the mode (normally `x' or `-') is tttt if
          the 1000 bit of the mode is on.  See _c_h_m_o_d(1) for the
          meaning of this mode.

          When the sizes of the files in a directory are listed, a
          total count of blocks, including indirect blocks is printed.

     FFFFIIIILLLLEEEESSSS
          /etc/passwd
          /etc/group

     BBBBUUUUGGGGSSSS
          Newline and tab are considered printing characters in file
          names.



     Page 3                                           (printed 4/5/85)






     LLLLFFFF((((1111))))                       ((((8888////22226666////88880000))))                       LLLLFFFF((((1111))))



          The output device is assumed to be 80 columns wide.

          The option setting based on whether the output is a teletype
          is undesirable as ``ls -s'' is much different than
          ``ls -s | lpr''.  On the other hand, not doing this setting
          would make old shell scripts which used _l_s almost certain
          losers if this version of ``ls'' were used.
















































     Page 4                                           (printed 4/5/85)



