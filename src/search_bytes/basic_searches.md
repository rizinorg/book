## Basic Search 

A basic search for a plain text string in a file would be something like:

    $ rizin -q -c "/ lib" /bin/ls
    Searching 3 bytes in [0x23520-0x23f58]
    hits: 0
    Searching 3 bytes in [0x0-0x3638]
    hits: 4
    Searching 3 bytes in [0x4000-0x17401]
    hits: 0
    Searching 3 bytes in [0x18000-0x1f8b0]
    hits: 1
    Searching 3 bytes in [0x22278-0x23518]
    hits: 0
    Searching 3 bytes in [0x20f70-0x22278]
    hits: 0
    0x00000319 hit0_0 ./lib64/ld-linux-x86-.
    0x0000103f hit0_1 ._cxa_finalize__libc_start_main__c.
    0x0000152b hit0_2 .txattrgetxattrlibcap.so.2libc.so.
    0x00001537 hit0_3 .ttrlibcap.so.2libc.so.6GLIBC_2.2.
    0x0001a015 hit0_4 .-full-isolc/.libs/lt-/usr/shar.

As can be seen from the output above, rizin generates a "hit" flag for every entry found. You can then use the `ps` command to see the strings stored at the offsets marked by the flags in this group, and they will have names of the form `hit0_<index>`:

    [0x00404888]> / ls
    ...
    [0x00404888]> ps @ hit0_0
    lseek

You can search for wide-char strings (e.g., unicode letters) using the `/w` command:

    [0x00000000]> /w Hello
    0 results found.

Using Rizin, you can also automatically search for magic signatures in the file. This can be done using `/m`. The offset and the file format will be displayed after the search.

    [0x00000000]> /m
	-- 0 b1606
	0x00000000 1 JPEG image , EXIF standard
	0x0000000c 1 TIFF image data, big-endian
	0x000b1510 1 7-zip archive data, version 0.3

To perform a case-insensitive search for strings use `/i`:

    [0x00000000]> /i hello
    Searching 5 bytes in [0x4028-0x4070]
    hits: 0
    Searching 5 bytes in [0x0-0x630]
    hits: 0
    Searching 5 bytes in [0x1000-0x1161]
    hits: 0
    Searching 5 bytes in [0x2000-0x20b4]
    hits: 1
    Searching 5 bytes in [0x4018-0x4020]
    hits: 0
    Searching 5 bytes in [0x3dd0-0x4018]
    hits: 0
    0x00002004 hit0_0 .Hello, World!; .

It is possible to specify hexadecimal escape sequences in the search string by prepending them with "\x":

    [0x00000000]> / \x7FELF

if, instead, you are searching for a string of hexadecimal values, you're probably better of using the `/x` command:

    [0x00000000]> /x 7F454C46

Once the search is done, the results are stored in the `search` flag space.

    [0x00000000]> fsl
        0 * classes
        2 * functions
        1 * imports
        0 * platform.ports
        0 * registers
        0 * registers.extended
        0 * registers.mmio
       12 * relocs
        1 * search
       25 * sections
       14 * segments
        1 * strings
       19 * symbols

You can list the flags in the `search` flag space by selecting it with `fs` and listing the flags with `fl`:

    [0x00000000]> fs search
    [0x00000000]> fl
    0x00002004 5 hit0_0

To remove "hit" flags after you do not need them anymore, use the `f- hit*` command.

Often, during long search sessions, you will need to launch the latest search more than once. You can use the `//` command to repeat the last search.

    [0x00000f2a]> //     # Repeat last search
