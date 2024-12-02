## Sections

The concept of sections is tied to the information extracted from the binary. We can display this information by using
the `i` command.

Displaying information about sections:

```
[0x00001100]> iS
paddr      size  vaddr      vsize align perm name               type       flags         
-----------------------------------------------------------------------------------------
0x00000000 0x0   ---------- 0x0   0x0   ----                    NULL       
0x00000318 0x1c  0x00000318 0x1c  0x0   -r-- .interp            PROGBITS   alloc
0x00000338 0x50  0x00000338 0x50  0x0   -r-- .note.gnu.property NOTE       alloc
0x00000388 0x20  0x00000388 0x20  0x0   -r-- .note.ABI-tag      NOTE       alloc
0x000003a8 0x24  0x000003a8 0x24  0x0   -r-- .gnu.hash          GNU_HASH   alloc
0x000003d0 0x120 0x000003d0 0x120 0x0   -r-- .dynsym            DYNSYM     alloc
0x000004f0 0xae  0x000004f0 0xae  0x0   -r-- .dynstr            STRTAB     alloc
0x0000059e 0x18  0x0000059e 0x18  0x0   -r-- .gnu.version       VERSYM     alloc
0x000005b8 0x30  0x000005b8 0x30  0x0   -r-- .gnu.version_r     VERNEED    alloc
0x000005e8 0xc0  0x000005e8 0xc0  0x0   -r-- .rela.dyn          RELA       alloc
0x000006a8 0x90  0x000006a8 0x90  0x0   -r-- .rela.plt          RELA       alloc,info
0x00001000 0x1b  0x00001000 0x1b  0x0   -r-x .init              PROGBITS   alloc,execute
0x00001020 0x70  0x00001020 0x70  0x0   -r-x .plt               PROGBITS   alloc,execute
0x00001090 0x10  0x00001090 0x10  0x0   -r-x .plt.got           PROGBITS   alloc,execute
0x000010a0 0x60  0x000010a0 0x60  0x0   -r-x .plt.sec           PROGBITS   alloc,execute
0x00001100 0x199 0x00001100 0x199 0x0   -r-x .text              PROGBITS   alloc,execute
0x0000129c 0xd   0x0000129c 0xd   0x0   -r-x .fini              PROGBITS   alloc,execute
0x00002000 0x12  0x00002000 0x12  0x0   -r-- .rodata            PROGBITS   alloc
0x00002014 0x34  0x00002014 0x34  0x0   -r-- .eh_frame_hdr      PROGBITS   alloc
0x00002048 0xac  0x00002048 0xac  0x0   -r-- .eh_frame          PROGBITS   alloc
0x00002d90 0x8   0x00003d90 0x8   0x0   -rw- .init_array        INIT_ARRAY write,alloc
0x00002d98 0x8   0x00003d98 0x8   0x0   -rw- .fini_array        FINI_ARRAY write,alloc
0x00002da0 0x1f0 0x00003da0 0x1f0 0x0   -rw- .dynamic           DYNAMIC    write,alloc
0x00002f90 0x70  0x00003f90 0x70  0x0   -rw- .got               PROGBITS   write,alloc
0x00003000 0x10  0x00004000 0x10  0x0   -rw- .data              PROGBITS   write,alloc
0x00003010 0x0   0x00004010 0x8   0x0   -rw- .bss               NOBITS     write,alloc
0x00003010 0x65  ---------- 0x65  0x0   ---- .comment           PROGBITS   merge,strings
0x00003078 0x2b8 ---------- 0x2b8 0x0   ---- .symtab            SYMTAB     
0x00003330 0x18a ---------- 0x18a 0x0   ---- .strtab            STRTAB     
0x000034ba 0x107 ---------- 0x107 0x0   ---- .shstrtab          STRTAB     
```

As you may know, binaries have sections and maps. The sections define the contents of a portion of the file that can be
mapped in memory (or not). What is mapped is defined by the segments.

Firmware images, bootloaders and binary files usually place various sections of a binary at different addresses in
memory. To represent this behavior, rizin offers the `iS`. Use `iS?` to get the help message. To list all created
sections use `iS` (or `iSj` to get the json format). The `iS=` will show the region bars in ascii-art.

You can create a new mapping using the `om` subcommand as follows:

```
om fd vaddr [size] [paddr] [rwx] [name]
```

For Example:
```
[0x00001100]> om 4 0x00000100 0x00400000 0x0001ae08 rwx test
```

You can also use `oml` command to view information about mapped sections:

```
[0x00001100]> oml
 1 fd: 4 +0x00000000 0x00004020 - 0x0000408f r-- vmap.reloc-targets
 2 fd: 3 +0x00000000 0x00000000 - 0x00000737 r-- fmap.LOAD0
 3 fd: 3 +0x00001000 0x00001000 - 0x000012a8 r-x fmap.LOAD1
 4 fd: 3 +0x00002000 0x00002000 - 0x000020f3 r-- fmap.LOAD2
 5 fd: 5 +0x00000000 0x00004010 - 0x00004017 rw- mmap.LOAD3
 6 fd: 6 +0x00002d90 0x00003d90 - 0x0000400f r-- vmap.LOAD3
 7 fd: 4 +0x0001ae08 0x00000100 * 0x004000ff r-x test
 ```

Use `om?` to get all the possible subcommands. To list all the defined maps use `oml` (or `omlj` to get the json
format). To get the ascii art view use `oml=`. 

It is also possible to delete the mapped section using the `om- mapid` command.

For Example:

```
[0x00001100]> om- 7
```
