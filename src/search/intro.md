# Searching

The Rizin search engine allows you to search for strings, bytes, in files, graphs and fro cryptographic material.
For each search hit it creates a flag for further referencing.
The search behavior can be modified as well.

Search commands are under the `/` group.
```
[0x00000000]> /?
Usage: /<?>   # Search for bytes, regexps, patterns, ..
| /+[jqt] </bin/sh>         # Construct the string with chunks.
| /a[?]                     # Assemble the instruction and search its bytes.
| /c<acrd>                  # Cryptographic material search.
| /d[jqt] <101112>          # Search for a deltified sequence of bytes.
| /F[jqt] <file> [<offset> [<size>]] # Search contents of file with offset and size.
| /o[jqt] [<n>]             # Show offset of n instructions backward.
| /O[jqt] [<n>]             # Same as /o, but with a different fallback if analysis cannot be used.
| /p[jqt] <patternsize>     # Search for pattern of given size.
| /P[jqt] <patternsize>     # Search similar blocks.
| /s[jqt] <threshold>       # Search sections by grouping blocks with similar entropy.
| /g[jqtg]                  # Search for all graph paths A to B (/gg follow jumps, see search.count and
                              analysis.depth).
| /h[jqt] <algo> <hash>     # Search for blocks that have the same hash (see also command `ph`).
| /m[jb]                    # Magic constants search.
| /E[j] <esil-expr>         # offset matching given esil expressions $$ = here.
| /r[acrwx]                 # Reference search.
| /R[jqt/kg]                # Search, List, Query for ROP Gadgets
| /v<1248>                  # Value search.
| /V<1248>                  # Value search.
| /x[jqtr]                  # Raw hexadecimal search.
| /z[jqt]                   # String search.

```

Search settings are under `e search.`
```
[0x00000000]> el search.
        search.align: Address alignment (searches only if 'address % search.align == 0').
search.case_sensitive: Set grep(~) as case smart/sensitive/insensitive
         search.from: Search start address (inclusive)
           search.in: Specify search boundaries
  search.max_threads: Maximum core number. '0' for all cores. '?' to show available.
      search.maxhits: Maximum number of hits ('0' means no limit)
      search.overlap: Look for overlapped search hits
       search.prefix: Prefix name in search hits label
search.show_progress: Show the search process.
search.str.check_ascii_freq: If true, perform check on ASCII frequencies when looking for false positives during string search
search.str.max_length: Maximum string length (in number of characters).
search.str.max_region_size: Maximum allowable size for the string search interval between two memory regions.
search.str.min_length: Smallest string length (in number of characters).
search.str.raw_alignment: Memory sector alignment used for the raw string search (RzBin only. Use search.align for /z).
           search.to: Search end address (exclusive)
          ...
```
