## Program Sections

rz-bin called with the `-S` option gives complete information about the sections of an executable.
For each section the index, offset, size, alignment, type and permissions, are shown. The next example demonstrates this:

```
$ rz-bin -S /usr/bin/ls
[Sections]
paddr      size    vaddr      vsize   align perm name               type       flags         
---------------------------------------------------------------------------------------------
0x00000000 0x0     ---------- 0x0     0x0   ----                    NULL       
0x00000318 0x1c    0x00000318 0x1c    0x0   -r-- .interp            PROGBITS   alloc
0x00000338 0x50    0x00000338 0x50    0x0   -r-- .note.gnu.property NOTE       alloc
0x00000388 0x20    0x00000388 0x20    0x0   -r-- .note.ABI-tag      NOTE       alloc
0x000003a8 0x98    0x000003a8 0x98    0x0   -r-- .gnu.hash          GNU_HASH   alloc
0x00000440 0xaf8   0x00000440 0xaf8   0x0   -r-- .dynsym            DYNSYM     alloc
0x00000f38 0x564   0x00000f38 0x564   0x0   -r-- .dynstr            STRTAB     alloc
0x0000149c 0xea    0x0000149c 0xea    0x0   -r-- .gnu.version       VERSYM     alloc
0x00001588 0xe0    0x00001588 0xe0    0x0   -r-- .gnu.version_r     VERNEED    alloc
0x00001668 0x150   0x00001668 0x150   0x0   -r-- .rela.dyn          RELA       alloc
0x000017b8 0x948   0x000017b8 0x948   0x0   -r-- .rela.plt          RELA       alloc,info
0x00002100 0x50    0x00002100 0x50    0x0   -r-- .relr.dyn          NUM        alloc
0x00003000 0x1b    0x00003000 0x1b    0x0   -r-x .init              PROGBITS   alloc,execute
0x00003020 0x640   0x00003020 0x640   0x0   -r-x .plt               PROGBITS   alloc,execute
0x00003660 0x40    0x00003660 0x40    0x0   -r-x .plt.got           PROGBITS   alloc,execute
0x000036a0 0x630   0x000036a0 0x630   0x0   -r-x .plt.sec           PROGBITS   alloc,execute
0x00003cd0 0x14972 0x00003cd0 0x14972 0x0   -r-x .text              PROGBITS   alloc,execute
0x00018644 0xd     0x00018644 0xd     0x0   -r-x .fini              PROGBITS   alloc,execute
0x00019000 0x5453  0x00019000 0x5453  0x0   -r-- .rodata            PROGBITS   alloc
0x0001e454 0x9b4   0x0001e454 0x9b4   0x0   -r-- .eh_frame_hdr      PROGBITS   alloc
0x0001ee08 0x3348  0x0001ee08 0x3348  0x0   -r-- .eh_frame          PROGBITS   alloc
0x00022f50 0x8     0x00023f50 0x8     0x0   -rw- .init_array        INIT_ARRAY write,alloc
0x00022f58 0x8     0x00023f58 0x8     0x0   -rw- .fini_array        FINI_ARRAY write,alloc
0x00022f60 0xaf8   0x00023f60 0xaf8   0x0   -rw- .data.rel.ro       PROGBITS   write,alloc
0x00023a58 0x220   0x00024a58 0x220   0x0   -rw- .dynamic           DYNAMIC    write,alloc
0x00023c78 0x370   0x00024c78 0x370   0x0   -rw- .got               PROGBITS   write,alloc
0x00024000 0x280   0x00025000 0x280   0x0   -rw- .data              PROGBITS   write,alloc
0x00024280 0x0     0x00025280 0x12d8  0x0   -rw- .bss               NOBITS     write,alloc
0x00024280 0x105   ---------- 0x105   0x0   ---- .shstrtab          STRTAB     
```

With the `-Sr` option, rz-bin will flag the start/end of every section, and will pass the rest of information as a comment.

```
$ rz-bin -Sr /usr/bin/ls | head
fs sections
"f section. 1 0x00000000"
"f section..interp 1 0x000002a8"
"f section..note.gnu.build_id 1 0x000002c4"
"f section..note.ABI_tag 1 0x000002e8"
"f section..gnu.hash 1 0x00000308"
"f section..dynsym 1 0x000003b8"
"f section..dynstr 1 0x00000fb8"
"f section..gnu.version 1 0x00001574"
"f section..gnu.version_r 1 0x00001678"
```

