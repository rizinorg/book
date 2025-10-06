# Rz-find

`rz-find` is the command line frontend of the `rz_search` library. Which allows you to search for strings, sequences of bytes with binary masks, etc

```bash
$ rz-find -h
Usage: rz-find [-mXnzZhqv] [-a align] [-b sz] [-f/t from/to] [-[e|s|w|S|I] str] [-x hex] -|file|dir ..
 -a align Only accept aligned hits
 -b size  Set block size
 -e regex Search for regex matches (can be used multiple times)
 -E cmd   Execute command for each file found
 -f from  Start searching from address 'from'
 -F file  Read the contents of the file and use it as keyword
 -h       Show this help
 -i       Identify filetype (rizin -nqcpm file)
 -j       Output in JSON
 -m       Magic search, file-type carver
 -M str   Set a binary mask to be applied on keywords
 -n       Do not stop on read errors
 -r       Print using rizin commands
 -s str   Search for a specific string (can be used multiple times)
 -w str   Search for a specific wide string (can be used multiple times). Assumes str is UTF-8.
 -I str   Search for an entry in import table.
 -S str   Search for a symbol in symbol table.
 -t to    Stop search at address 'to'
 -q       Quiet - do not show headings (filenames) above matching contents (default for searching a single file)
 -v       Show version information
 -x hex   Search for hexpair string (909090) (can be used multiple times)
 -X       Show hexdump of search results
 -z       Search for zero-terminated strings
 -Z       Show string found on each search hit
```

That's how to use it, first we'll search for "lib" inside the `/bin/ls` binary.

```bash
$ rz-find -s lib /usr/bin/ls
```
```
0x319
0x11f3
0x13b7
0x1b5ea
0x1b792
```

Note that the output is pretty minimal, and shows the offsets where the string `lib` is found. We can then use
this output to feed other tools.

Counting results:

```bash
$ rz-find -s lib /usr/bin/ls | wc -l
```
```
5
```

Displaying results with context:

```bash
$ export F=/usr/bin/ls
$ for a in `rz-find -s lib $F` ; do \
    rizin -ns $a -qc'x 32' $F ; done
```
```
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x00000319  6c69 6236 342f 6c64 2d6c 696e 7578 2d78  lib64/ld-linux-x
0x00000329  3836 2d36 342e 736f 2e32 0000 0000 0004  86-64.so.2......
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x000011f3  6c69 6263 5f73 7461 7274 5f6d 6169 6e00  libc_start_main.
0x00001203  6973 7770 7269 6e74 0073 6967 7072 6f63  iswprint.sigproc
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x000013b7  6c69 6263 2e73 6f2e 3600 474c 4942 435f  libc.so.6.GLIBC_
0x000013c7  4142 495f 4454 5f52 454c 5200 474c 4942  ABI_DT_RELR.GLIB
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x0001b5ea  6c69 6273 2f00 5554 462d 3800 e280 9900  libs/.UTF-8.....
0x0001b5fa  a1af 0022 00a1 0765 00e2 8098 0060 0073  ..."...e.....`.s
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x0001b792  6c69 622f 7873 7472 746f 6c2e 6300 4153  lib/xstrtol.c.AS
0x0001b7a2  4349 4900 0000 6361 6e6e 6f74 2064 6574  CII...cannot det
```

rz-find can also be used as a replacement of `file` to identify the mimetype of a file using the internal magic
database of Rizin.

```bash
$  rz-find -i /usr/bin/ls
```
```
0x00000000 1 ELF 64-bit LSB shared object, x86-64, version 1
```

Also works as a `strings` replacement, similar to what you do with `rz-bin -z`, but without caring about parsing
headers and obeying binary sections.

```bash
$ rz-find -z /usr/bin/ls | grep http
```
```
# https://wiki.xiph.org/MIME_Types_and_File_Extensions
# https://wiki.xiph.org/MIME_Types_and_File_Extensions
https://www.gnu.org/gethelp/
https://www.gnu.org/software/coreutils/
Report any translation bugs to <https://translationproject.org/team/>
https://gnu.org/licenses/gpl.html
```
