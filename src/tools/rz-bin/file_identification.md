## File Properties Identification

File type identification is done using `-I`. With this option, rz-bin prints information on a binary type,
like its encoding, endianness, class, operating system:

```
$ rz-bin -I /usr/bin/ls
[Info]
arch     x86
cpu      N/A
baddr    0x00000000
binsz    0x00024280
bintype  elf
bits     64
class    ELF64
compiler N/A
dbg_file N/A
endian   LE
hdr.csum N/A
guid     N/A
intrp    /lib64/ld-linux-x86-64.so.2
laddr    0x00000000
lang     c
machine  AMD x86-64 architecture
maxopsz  16
minopsz  1
os       linux
cc       N/A
pcalign  0
relro    full
rpath    NONE
subsys   linux
stripped true
crypto   false
havecode true
va       true
sanitiz  false
static   false
linenum  false
lsyms    false
canary   true
PIE      true
RELROCS  false
NX       true
```

To make rz-bin output information in format that the main program, Rizin, can understand, pass `-Ir` option to it:

```
$ rz-bin -Ir /bin/ls
e cfg.bigendian=false
e asm.bits=64
e asm.dwarf=true
e bin.lang=c
e file.type=elf
e asm.os=linux
e asm.arch=x86
e asm.pcalign=0
```

