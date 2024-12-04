## Comparing Bytes

For most generic reverse engineering tasks like finding the differences between two binary files, which bytes has
changed, find differences in the graphs of the code analysis results, and other diffing operations you can just use
rz-diff:

```
$ rz-diff -h
```

Inside Rizin, the functionalities exposed by rz-diff are available with the `c` command.

`c` (short for "compare") allows you to compare arrays of bytes from different sources. The command accepts input
in a number of formats and then compares it against values found at current seek position.

```
[0x00001100]> c?
Usage: c[?]   # Compare block with given data
| c[j] <string>    # Compare an escaped <string> with data at current offset
| c1 <addr>        # Compare 8-bit data at current offset with the data at <addr>
| ca[j] <addr> <n> # Compare <n> bytes of data at <addr> with the data at current offset
| cb[j] <num> <n>  # Compare <n> (up to 8) bytes at current offset with a number <num>
| cc <addr>        # Compare hexdump of data of block size at <addr> with the data at current offset
| ccc <addr>       # Show different lines between hexdump of a block of data at <addr> wth the data at current offset
| ccd [<addr>]     # Compare disassembly of block size at <addr> and at the current offset
| cf[j] <file>     # Compare the contents of <file> with the data at current offset
| cu[1248d]        # Unified diff commands
| cw[lrux]         # Compare watcher commands
| cx[j] <hexpair>  # Compare data at current offset with a hexpair string <hexpair> (also return in $?)
| cX[j] <addr>     # Compare hexdump of data of block size at <addr> with the data at current offset using hexdiff output
```

To compare memory contents at current seek position against a given string of values, use `cx`:

```
[0x00001100]> p8 4
7f454c46

[0x00001100]> cx 7f 45 90 46
Compare 3/4 equal bytes
0x00001102 (byte=03)   90 ' '  ->  4c 'L'
Compare 3/4 equal bytes (75%)
[0x00001100]>
```

Another subcommand of the `c` command is `cc` which stands for "compare code".
To compare a byte sequence with a sequence in memory:

```
[0x4A13B8C0]> cc 0x39e8e089 @ 0x4A13B8C0
```

To compare contents of two functions specified by their names:

```
[0x08049A80]> cc sym.main2 @ sym.main
```

The number parameter can be math expressions which use flag names and anything allowed in an expression:

```
[0x00000000]> cx 7f469046

Compare 2/4 equal bytes
0x00000001 (byte=02)   45 'E'  ->  46 'F'
0x00000002 (byte=03)   4c 'L'  ->  90 ' '
```

You can use the compare command to find differences between a current block and a file previously dumped to a disk:

```
rizin /usr/bin/true
[0x00002680]> s 0
[0x00000000]> cf /usr/bin/true
Compare 256/256 equal bytes (100%)
```
