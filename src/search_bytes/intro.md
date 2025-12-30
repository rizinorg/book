# Searching for Bytes

The Rizin search engine is based on work done by esteve, plus multiple features implemented on top of it. It supports
multiple keyword searches, binary masks, and hexadecimal values. It automatically creates flags for search hit
locations ease future referencing.

Search is initiated by `/` command.
```
[0x00000000]> /?
Usage: /<?>   # Search for bytes, regexps, patterns, ..
│ /+[jqt] </bin/sh>         # Construct the string with chunks.
│ /a[?]                     # Assemble the instruction and search its bytes.
│ /c<chem?>                 # Cryptographic material search.
│ /d[jqt] <101112>          # Search for a deltified sequence of bytes.
│ /F[jqt] <file> [<offset> [<size>]] # Search the content of a file.
│ /o[j] [<n>]               # Show offset of n instructions backward.
│ /O[j] [<n>]               # Same as /o, but with a different fallback if analysis cannot be used.
│ /p[jqt] <patternsize>     # Search for pattern of given size.
│ /P[jqt] <patternsize>     # Search similar blocks.
│ /g[jg]                    # Search for all graph paths A to B.
│ /m[jqtb]                  # Magic constants search.
│ /r[acrwx]                 # Reference search.
│ /R[?]                     # Search, List, Query for ROP Gadgets
│ /v[?]                     # Value search.
│ /x[jqtr]                  # Raw hexadecimal search.
│ /z[jqt]                   # String search.
```

Because everything is treated as a file in Rizin, it does not matter whether you search in a socket, a remote device,
in process memory, or a file.

Note that `/*` starts multiline comment. It's not for searching. Type `*/` to end comment.
