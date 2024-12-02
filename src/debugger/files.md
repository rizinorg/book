# Files

The Rizin debugger allows the user to list and manipulate the file descriptors from the target process.

This is a useful feature, which is not found in other debuggers, the functionality is similar to the `lsof`
command line tool, but have extra subcommands to change the seek, close or duplicate them.

So, at any time in the debugging session you can replace the stdio file descriptors to use network sockets created
by Rizin, or replace a network socket connection to hijack it.
