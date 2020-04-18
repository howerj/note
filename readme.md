% note(1) | A note taking application

# NAME

NOTE - A note taking application

# SYNOPSES

note args...

note

# DESCRIPTION

	Author:     Richard James Howe
	License:    Unlicense
	Repository: <https://github.com/howerj/note>
	Email:      howe.r.j.89@gmail.com
	Copyright:  2020 Richard James Howe

An incredibly simple note taking application for the command line, written in
C, and easy to use.

## OPTIONS

The operation of the program is very simple. The *note* program interprets no
switches, if no arguments are presents to the program then it reads the from
the note file and prints the results to standard out. If arguments are present
then it appends a log entry consisting of a date/time entry, a tab and then 
those arguments separated by a space with a new line terminating the log entry.

Example usage:

	$ ./note a b c
	$ ./note
	Sat Apr 18 14:51:54 2020        a b c
	$ ./note d e f
	Sat Apr 18 14:51:54 2020        a b c
	Sat Apr 18 14:52:29 2020        d e f

There is not much more to the programs operation.

## ENVIRONMENT VARIABLES

There is one environment variable that should be set by the user of the
program, preferably by setting it in your shells startup script. The
environment variable is called 'NOTE', this variable should point to the log
file this program should use. If the environment variable is not present it
uses the default file 'note.log'.

Examples of '.bashrc' configuration lines that setup a per user log:

	export NOTE="/home/${USER}/note.log";

Or even, to have a daily log file in rotation.

	export NOTE="/home/${USER}/note-$(date '+%Y-%m-%d').log";

You may also want to symlink the 'note' binary to a shorter, single character,
variable, such as 'n':

	cd /path/to/note/
	sudo ln -s note n

Have fun.

## BUILDING

You will need a [C99][] compiler and [GNU Make][] to build and install this
program. Type 'make' to build, you can set the environment variable 'DESTDIR'
to change the install path to 'make install'.

To build the manual page from this 'readme.md' file you will need [pandoc][]
installed. The default log file and the environment variable name used can both
be changed by compile time options, these can be provided to the build system
by an environment variable called 'DEFINES'.

For example, to change the default log file used, using [GCC][] as the
compiler:

	make DEFINES='-DNOTE_DEFAULT_FILE="(\"my-notes.log\")"'

To view all of the defines used, view the source file for the program,
'note.c', it is tiny.

A current limitation is that the date format used for each log entry cannot 
be changed, this may be unfortunate for some but tough luck.

## RETURN STATUS

Zero is returned on success. Non-zero is a failure. The program should fail
under the following circumstances:

- It cannot write to the standard output stream.
- It cannot open the log file for reading (when no arguments are supplied to
  *note*, so *note* is attempting to dump the log file).
- It cannot open the log file for appending (when arguments are supplied to
  *note* for a new log entry).

This is all.

[Unlicense]: https://unlicense.org/
[C99]: https://en.wikipedia.org/wiki/C99
[GNU Make]: https://www.gnu.org/software/make/
[pandoc]: https://pandoc.org/
[GCC]: https://gcc.gnu.org/
