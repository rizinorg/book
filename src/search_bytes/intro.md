# Searching for Bytes

The Rizin search engine is based on work done by esteve, plus multiple features implemented on top of it. It supports
multiple keyword searches, binary masks, and hexadecimal values. It automatically creates flags for search hit
locations ease future referencing.

Search is initiated by `/` command.
```
[0x00000000]> /?
Usage: /[!bf] [arg]  Search stuff (see 'e??search' for options)
|Use io.va for searching in non virtual addressing spaces
| / foo\x00                    search for string 'foo\0'
| /j foo\x00                   search for string 'foo\0' (json output)
| /! ff                        search for first occurrence not matching, command modifier
| /!x 00                       inverse hexa search (find first byte != 0x00)
| /+ /bin/sh                   construct the string with chunks
| //                           repeat last search
| /a[?][1aoditfmsltf] jmp eax  assemble opcode and search its bytes
| /b                           search backwards, command modifier, followed by other command
| /c[?][adr]                   search for crypto materials
| /d 101112                    search for a deltified sequence of bytes
| /e /E.F/i                    match regular expression
| /E esil-expr                 offset matching given esil expressions $$ = here
| /f                           search forwards, (command modifier)
| /F file [off] [sz]           search contents of file with offset and size
| /g[g] [from]                 find all graph paths A to B (/gg follow jumps, see search.count and analysis.depth)
| /h[t] [hash] [len]           find block matching this hash. See ph
| /i foo                       search for string 'foo' ignoring case
| /m[?][ebm] magicfile         search for magic, filesystems or binary headers
| /o [n]                       show offset of n instructions backward
| /O [n]                       same as /o, but with a different fallback if analysis cannot be used
| /p patternsize               search for pattern of given size
| /P patternsize               search similar blocks
| /s[*] [threshold]            find sections by grouping blocks with similar entropy
| /r[rwx][?] sym.printf        analyze opcode reference an offset
| /R [grepopcode]              search for matching ROP gadgets, semicolon-separated
| /v[1248] value               look for an `cfg.bigendian` 32bit value
| /V[1248] min max             look for an `cfg.bigendian` 32bit value in range
| /w foo                       search for wide string 'f\0o\0o\0'
| /wi foo                      search for wide string ignoring case 'f\0o\0o\0'
| /x ff..33                    search for hex string ignoring some nibbles
| /x ff0033                    search for hex string
| /x ff43:ffd0                 search for hexpair with mask
| /z min max                   search for strings of given size
| /* [comment string]          add multiline comment, end it with '*/'
```

Because everything is treated as a file in Rizin, it does not matter whether you search in a socket, a remote device,
in process memory, or a file.

Note that `/*` starts multiline comment. It's not for searching. Type `*/` to end comment.
