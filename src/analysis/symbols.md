# Symbols

Rizin automatically parses available imports and exports sections in the binary,
moreover, it can load additional debugging information if present.
Two main formats are supported: DWARF and PDB (for Windows binaries).
Note that, unlike many tools rizin doesn't rely on Windows API to parse
PDB files, thus they can be loaded on any other supported platform - e.g.
Linux or OS X.

DWARF debug info loads automatically by default because usually it's stored
right in the executable file. PDB is a bit of a different beast - it is always
stored as a separate binary, thus the different logic of handling it.

At first, one of the common scenarios is to analyze the file from Windows distribution.
In this case, all PDB files are available on the Microsoft server, which is by default
is in options. See all pdb options in rizin:

```
[0x00000000]> ell pdb
pdb.autoload = 0 ; Automatically load the required pdb files for loaded DLLs
pdb.extract = 1 ; Avoid extract of the pdb file, just download
pdb.server = https://msdl.microsoft.com/download/symbols ; Semi-colon separated list of base URLs for Microsoft symbol servers
pdb.symstore = /home/user/.local/share/rizin/pdb ; Path to downstream symbol store
```

Using the variable `pdb.server` you can change the address where Rizin will try to
download the PDB file by the GUID stored in the executable header.
You can make use of multiple symbol servers by separating each URL with a semicolon:

```
[0x00000000]> e pdb.server=https://msdl.microsoft.com/download/symbols;https://symbols.mozilla.org/
```

On Windows,  you can also use local network share paths (UNC paths) as symbol servers.

Because those PDB files are stored as "cab" archives on the server, `pdb.extract=1`
says to automatically extract them.

Note that for the automatic downloading to work you need the "cabextract" tool, and wget/curl installed.

Sometimes you don't need to do that from the Rizin itself, thus - two handy rz-bin options:

```
 -P              Show debug/pdb information
 -PP             Download pdb file for binary
```

where `-PP` automatically downloads the pdb for the selected binary, using those
`pdb.*` config options. `-P` will dump the contents of the PDB file, which is useful
sometimes for a quick understanding of the symbols stored in it.

Apart from the basic scenario of just opening a file, PDB information can be additionally
manipulated by the `id` commands:

```
[0x000051c0]> id?
Usage: id[jqp]   # Debug commands
| id[jq]    # Show DWARF source lines information
| idp[jidx] # PDB commands
```

Where `idpi` is basically the same as `rz-bin -P`.
Note that `idp` can be also used not only in the static analysis mode but also
in the debugging mode, even if connected via WinDbg.

For simplifying the loading PDBs, especially for the processes with many linked DLLs,
Rizin can autoload all required PDBs automatically - you need just set the
`e pdb.autoload=true` option. Then, if you load some file in debugging mode
in Windows, using `rizin -d file.exe` or `rizin -d 2345` (attach to pid 2345), all
related PDB files will be loaded automatically.

DWARF information loading, on the other hand, is completely automated. You don't
need to run any commands/change any options:

```
rizin `which rz-bin`
[0x00002437 8% 300 /usr/local/bin/rz-bin]> pd $r
0x00002437  jne 0x2468                  ;[1]
0x00002439  cmp qword reloc.__cxa_finalize_224, 0
0x00002441  push rbp
0x00002442  mov rbp, rsp
0x00002445  je 0x2453                   ;[2]
0x00002447  lea rdi, obj.__dso_handle   ; 0x207c40 ; "@| "
0x0000244e  call 0x2360                 ;[3]
0x00002453  call sym.deregister_tm_clones ;[4]
0x00002458  mov byte [obj.completed.6991], 1 ; obj.__TMC_END__ ; [0x2082f0:1]=0
0x0000245f  pop rbp
0x00002460  ret
0x00002461  nop dword [rax]
0x00002468  ret
0x0000246a  nop word [rax + rax]
;-- entry1.init:
;-- frame_dummy:
0x00002470  push rbp
0x00002471  mov rbp, rsp
0x00002474  pop rbp
0x00002475  jmp sym.register_tm_clones  ;[5]
;-- blob_version:
0x0000247a  push rbp                    ; ../blob/version.c:18
0x0000247b  mov rbp, rsp
0x0000247e  sub rsp, 0x10
0x00002482  mov qword [rbp - 8], rdi
0x00002486  mov eax, 0x32               ; ../blob/version.c:24 ; '2'
0x0000248b  test al, al                 ; ../blob/version.c:19
0x0000248d  je 0x2498                   ;[6]
0x0000248f  lea rax, str.2.0.1_182_gf1aa3aa4d ; 0x60b8 ; "2.0.1-182-gf1aa3aa4d"
0x00002496  jmp 0x249f                  ;[7]
0x00002498  lea rax, 0x000060cd
0x0000249f  mov rsi, qword [rbp - 8]
0x000024a3  mov r8, rax
0x000024a6  mov ecx, 0x40               ; section_end.ehdr
0x000024ab  mov edx, 0x40c0
0x000024b0  lea rdi, str._s_2.1.0_git__d___linux_x86__d_git._s_n ; 0x60d0 ; "%s 2.1.0-git %d @ linux-x86-%d git.%s\n"
0x000024b7  mov eax, 0
0x000024bc  call 0x2350                 ;[8]
0x000024c1  mov eax, 0x66               ; ../blob/version.c:25 ; 'f'
0x000024c6  test al, al
0x000024c8  je 0x24d6                   ;[9]
0x000024ca  lea rdi, str.commit:_f1aa3aa4d2599c1ad60e3ecbe5f4d8261b282385_build:_2017_11_06__12:18:39 ; ../blob/version.c:26 ; 0x60f8 ; "commit: f1aa3aa4d2599c1ad60e3ecbe5f4d8261b282385 build: 2017-11-06__1
0x000024d1  call sym.imp.puts           ;[?]
0x000024d6  mov eax, 0                  ; ../blob/version.c:28
0x000024db  leave                       ; ../blob/version.c:29
0x000024dc  ret
;-- rabin_show_help:
0x000024dd  push rbp                    ; .//rz-bin.c:27
```

As you can see, it loads function names and source line information.

