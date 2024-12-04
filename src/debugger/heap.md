# Heap

rizin's `dm` subcommands can also display a map of the heap which is useful for those who are interested in inspecting
the heap and its content. Simply execute `dmh` to show a map of the heap:

```
[0x55c392ae1189]> dmh
Arena @ 0x7f10940c1b80
Chunk(status=free,      addr=0x55c3934c9290, size=0x50, flags=PREV_INUSE)
Chunk(status=allocated, addr=0x55c3934c92e0, size=0x90, flags=PREV_INUSE)
Chunk(status=free,      addr=0x55c3934c9370, size=0x20c90, flags=PREV_INUSE)[top][brk_start: 0x55c3934c9000, brk_end: 0x55c3934ea000]]
```

You can also see a graph layout of the heap:

```
[0x7fae46236ca6]> dmhg
Arena @ 0x7f10940c1b80
Heap Layout
┌────────────────────────────────────┐
│    Malloc chunk @ 0x55c3934c9290   │
│ size: 0x50 status: free            │
└────────────────────────────────────┘
    v
    │
    │
┌────────────────────────────────────┐
│    Malloc chunk @ 0x55c3934c92e0   │
│ size: 0x90 status: allocated       │
└────────────────────────────────────┘
    v
    │
    └──┐
       │
   ┌───────────────────────────────┐
   │  Top chunk @ 0x55c3934c9370   │
   └───────────────────────────────┘
```

To get information about bins of the main arena use the `dmhd` command.

```
[0x55c392ae1189]> dmhd
Tcache bins in Main Arena @ 0x7f10940c1b80
Tcache_bin[03] Items: 1
 -> Chunk(addr=0x55c3934c9290, size=0x50, flags=PREV_INUSE)

Fast bins in Arena @ 0x7f10940c1b80
Fast_bin[01] [size: 0x20] Empty bin
Fast_bin[02] [size: 0x30] Empty bin
Fast_bin[03] [size: 0x40] Empty bin
Fast_bin[04] [size: 0x50] Empty bin
Fast_bin[05] [size: 0x60] Empty bin
Fast_bin[06] [size: 0x70] Empty bin
Fast_bin[07] [size: 0x80] Empty bin

Unsorted bin in Arena @ 0x7f10940c1b80
Found 0 chunks in unsorted bin

Small bins in Arena @ 0x7f10940c1b80
Found 0 chunks in 0 small bins

Large bins in Arena @ 0x7f10940c1b80
Found 0 chunks in 0 large bins
```

Other heap commands can be found under `dmh`, check `dmh?` for the full list.

```
[0x00000000]> dmh?
Usage: dmh[?]   # Glibc heap commands
| dmh[j*l] [<malloc_state>] # List heap chunks of an arena
| dmha                     # List all the arenas
| dmhb[?] [<bin_num|bin_num:malloc_state>] # Display double linked list for bins in an arena. Use dmhbg command for
                                             graphical representation.
| dmhc                     # Get info about heap chunk at current offset
| dmhd[j] [<bin_type>]     # Display state of bins in an arena. <bin_type> can be tcache/fast/unsorted/small/large
| dmhf[?] [<fastbin_num|fastbin_num:malloc_state>] # Display all parsed fastbins of main_arena's or a particular arena
                                                     fastbinY instance
| dmhg [<malloc_state>]    # Display heap graph of a particular arena
| dmhi [<malloc_state>]    # Display heap_info structure/structures for a given arena
| dmhm[*] [<malloc_state>] # List all elements of struct malloc_state
| dmht                     # Display all parsed thread cache bins of all arena's tcache instance
```

Rizin supports Glibc, Jemalloc < 5.0 and Windows heap.

