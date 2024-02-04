## Mapping Files

Rizin's I/O subsystem allows you to map the contents of files into the same I/O space used to contain a loaded binary. New contents can be placed at random offsets.

The `o` command permits the user to open a file, this is mapped at offset 0 unless it has a known binary header and then the maps are created in virtual addresses.

Sometimes, we want to rebase a binary, or maybe we want to load or map the file in a different address.

When launching rizin, the base address can be changed with the `-B` flag. But you must notice the difference when opening files with unknown headers, like bootloaders, so we need to map them using the `-m` flag (or specifying it as argument to the `o` command).

rizin is able to open files and map portions of them at random places in memory specifying attributes like permissions and name. It is the perfect basic tooling to reproduce an environment like a core file, a debug session, by also loading and mapping all the libraries the binary depends on.

Opening files (and mapping them) is done using the `o` (open) command. Let's read the help:

```
[0x00000000]> o?
Usage: o[?]   # Open files and handle opened files
| o <file> [<addr> [<perm>]] # Open <file>
| o+ <file> [<addr> [<perm>]] # Open <file> in write mode
| ol[jqt]                # List opened files
| ol.[jqt]               # Show currently opened file
| o- <fd>                # Close file descriptor
| o--                    # Close all files
| oc <file>              # Close all opened files and open <file>, like relaunching rizin
| oC <len>               # Open a 'malloc://<len>' file, copying the bytes from current offset
| on[+]                  # Open files without parsing binary info
| oo[+bcdmn?]            # Reopen current file
| oL[jqt] [<path>]       # List all IO plugins / Register IO plugin from <path>
| o=                     # List opened files in ASCII-art bars
| oa <arch> <bits> [<filename>] # Specify <arch> and <bits> for the file <filename> or the current one if none is specified
| ob[?]                  # Handle binary files
| ou <fd>                # Use specified <fd>
| op[npr]                # Select prioritized file
| om[?]                  # Handle IO maps
| ox <fd> <fdx>          # Exchange the descs of <fd> and <fdx> and keep the mapping
```

Prepare a simple layout:

```bash
$ rz-bin -l /bin/ls
[Linked libraries]
libselinux.so.1
librt.so.1
libacl.so.1
libc.so.6

4 libraries
```

Map a file:

```
[0x00001190]> o /bin/zsh 0x499999
```

List mapped files:

```
[0x00000000]> ol
- 6 /bin/ls @ 0x0 ; r
- 10 /lib/ld-linux.so.2 @ 0x100000000 ; r
- 14 /bin/zsh @ 0x499999 ; r
```

Print hexadecimal values from /bin/zsh:

```
[0x00000000]> px @ 0x499999
```

Unmap files using the `o-` command. Pass the required file descriptor to it as an argument:

```
[0x00000000]> o- 14
```

You can also view the ascii table showing the list of the opened files:

```
[0x00000000]> o=
```
