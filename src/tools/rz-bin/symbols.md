## Symbols (Exports)

With rz-bin, the generated symbols list format is similar to the imports list. Use the `-s` option to get it:

```
$ rz-bin -s /usr/bin/ls | head
[Symbols]
nth paddr      vaddr      bind   type   size lib name                            
---------------------------------------------------------------------------------
104 ---------- 0x00025280 GLOBAL OBJ    8        __progname
105 ---------- 0x00025290 GLOBAL OBJ    4        optind
107 ---------- 0x000252a8 WEAK   OBJ    8        program_invocation_name
108 ---------- 0x000252a8 GLOBAL OBJ    8        __progname_full
109 0x00024200 0x00025200 GLOBAL OBJ    8        obstack_alloc_failed_handler
110 ---------- 0x000252c0 GLOBAL OBJ    8        stderr
111 ---------- 0x00025280 WEAK   OBJ    8        program_invocation_short_name
```

With the `-sr` option rz-bin produces a rizin script instead. It can later be passed to the core to automatically
flag all symbols and to define corresponding byte ranges as functions and data blocks.

```
$ rz-bin -sr /usr/bin/ls | head
fs symbols
f sym.obstack_allocated_p 56 0x000150a0
f sym.program_invocation_name 8 0x0021f600
f sym.stderr 8 0x0021f620
f sym.obstack_begin_1 21 0x00014f90
f sym.program_invocation_name 8 0x0021f600
f sym.obstack_alloc_failed_handler 8 0x0021f5c0
f sym.optarg 8 0x0021f5f8
f sym.stdout 8 0x0021f5e8
f sym.program_invocation_short_name 8 0x0021f5e0
```

