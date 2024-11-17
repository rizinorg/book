## Strings

The `-z` option is used to list readable strings found in the .rodata section of ELF binaries, or the .text section
of PE files. Example:

```
$ rz-bin -z /usr/bin/ls | head
[Strings]
nth paddr      vaddr      len size section type  string                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
-------------------------------------------------------
0   0x00019007 0x00019007 5   6    .rodata ascii =fff?
1   0x00019630 0x00019630 11  12   .rodata ascii dev_ino_pop
2   0x000196a8 0x000196a8 10  11   .rodata ascii sort_files
3   0x000196b3 0x000196b3 6   7    .rodata ascii posix-
4   0x000196ba 0x000196ba 4   5    .rodata ascii main
5   0x00019790 0x00019790 10  11   .rodata ascii ?pcdb-lswd
6   0x000197a0 0x000197a0 65  66   .rodata ascii # Configuration file for dircolors, a utility to help you set the
```

With the `-zr` option, this information is represented as a rizin commands list. It can be used in a rizin session to automatically create a flag space called "strings" pre-populated with flags for all strings found by rz-bin.
Furthermore, this script will mark corresponding byte ranges as strings instead of code.
```

$ rz-bin -zr /usr/bin/ls | head
fs stringsf str.dev_ino_pop 12 @ 0x000160f8
Cs 12 @ 0x000160f8
f str.sort_files 11 @ 0x00016188
Cs 11 @ 0x00016188
f str.posix 7 @ 0x00016193
Cs 7 @ 0x00016193
f str.main 5 @ 0x0001619a
Cs 5 @ 0x0001619a
f str.pcdb_lswd 11 @ 0x00016250
Cs 11 @ 0x00016250
```

