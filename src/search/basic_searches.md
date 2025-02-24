## Basic Search 

A basic search for a plain text string in a file would be something like:

```shell
$ rizin -q -c "/ lib" /bin/ls
Searching 3 bytes in [0x23548,0x23f18)
hits: 0
Searching 3 bytes in [0x0,0x3458)
hits: 4
Searching 3 bytes in [0x4000,0x17091)
hits: 0
Searching 3 bytes in [0x18000,0x1f458)
hits: 1
Searching 3 bytes in [0x22278,0x23540)
hits: 0
Searching 3 bytes in [0x20fd0,0x22278)
hits: 0
0x00000319 hit0_0 ".............../lib64/ld-linux-x86-"
0x00000f9a hit0_1 "_cxa_finalize.__libc_start_main.__c"
0x000014a2 hit0_2 "con.lgetfilecon.libselinux.so.1.lib"
0x000014b2 hit0_3 "libselinux.so.1.libc.so.6.LIBSELINU"
0x00019c6f hit0_4 "-.full-iso.lc./.libs/.lt-./usr/shar"
```

As can be seen from the output above, Rizin generates a "hit" flag for every entry found. You can then use the `ps`
command to see the strings stored at the offsets marked by the flags in this group, and they will have names
of the form `hit0_<index>`:

```
[0x00404888]> / ls
...
[0x00404888]> ps @ hit0_0
lseek
```

You can search for wide-char strings (e.g., Unicode letters) using the `/w` command:

```
[0x00000000]> /w Hello
0 results found.
```

Using Rizin, you can also automatically search for magic signatures in the file. This can be done using `/m`.
The offset and the file format will be displayed after the search.

```
[0x00000000]> /m
-- 0 b1606
0x00000000 1 JPEG image , EXIF standard
0x0000000c 1 TIFF image data, big-endian
0x000b1510 1 7-zip archive data, version 0.3
```

To perform a case-insensitive search for strings use `/i`:

```
[0x0040488f]> /i Stallman
Searching 8 bytes from 0x00400238 to 0x0040488f: 53 74 61 6c 6c 6d 61 6e
[# ]hits: 004138 < 0x0040488f  hits = 0
```

It is possible to specify hexadecimal escape sequences in the search string by prepending them with `\x`:

```
[0x00000000]> / \x7FELF
```

If, instead, you are searching for a string of hexadecimal values, you're probably better off using the `/x` command:

```
[0x00000000]> /x 7F454C46
```

Once the search is done, the results are stored in the `searches` flag space.

```
[0x00000000]> fs
0    0 . strings
1    0 . symbols
2    6 . searches

[0x00000000]> f
0x00000135 512 hit0_0
0x00000b71 512 hit0_1
0x00000bad 512 hit0_2
0x00000bdd 512 hit0_3
0x00000bfb 512 hit0_4
0x00000f2a 512 hit0_5
```

To remove "hit" flags after you do not need them anymore, use the `f- hit*` command.

Often, during long search sessions, you will need to launch the latest search more than once. You can use the `//`
command to repeat the last search.

```
[0x00000f2a]> //     ; repeat last search
```
