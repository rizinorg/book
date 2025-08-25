## Configuring Search Options

The Rizin search engine can be configured through several configuration variables, modifiable with the `e` command.

```
[0x00000000]> ell cmd.hit
cmd.hit =  ; Run when a search hit is found

[0x00000000]> ell search
search.align = 0 ; Only catch aligned search hits
search.case_sensitive = smart ; Set grep(~) as case smart/sensitive/insensitive [smart, sensitive, insensitive]
search.chunk = 0 ; Chunk size for /+ (default size is asm.bits/8
search.contiguous = true ; Accept contiguous/adjacent search hits
search.distance = 0 ; Search string distance
search.esilcombo = 8 ; Stop search after N consecutive hits
search.flags = true ; All search results are flagged, otherwise only printed
search.from = 0 ; Search start address (inclusive)
search.in = io.maps ; Specify search boundaries [raw, block, bin.section, bin.sections, bin.sections.rwx, bin.sections.r, bin.sections.rw, bin.sections.rx, bin.sections.wx, bin.sections.x, io.map, io.maps, io.maps.rwx, io.maps.r, io.maps.rw, io.maps.rx, io.maps.wx, io.maps.x, dbg.stack, dbg.heap, dbg.map, dbg.maps, dbg.maps.rwx, dbg.maps.r, dbg.maps.rw, dbg.maps.rx, dbg.maps.wx, dbg.maps.x, analysis.fcn, analysis.bb]
search.kwidx = 1 ; Store last search index count
search.maxhits = 0 ; Maximum number of hits (0: no limit)
search.overlap = false ; Look for overlapped search hits
search.prefix = hit ; Prefix name in search hits label
search.show = true ; Show search results
search.to = 0xffffffffffffffff ; Search end address (exclusive)
```

The `search.flags` boolean variable instructs the search engine to flag hits so that they can be referenced later.
If a currently running search is interrupted with `Ctrl-C` keyboard sequence, current search position is flagged
with `search_stop`.
