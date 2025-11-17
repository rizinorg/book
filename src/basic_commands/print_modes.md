## Print Modes

One of the key features of Rizin is displaying information in many formats. The goal is to offer a selection of display
choices to interpret binary data in the best possible way.

Binary data can be represented as integers, shorts, longs, floats, timestamps, hexpair strings, or more complex formats
like C structures, disassembly listings, decompilation listing, be a result of an external processing...

Below is a list of available print modes listed by `p?`:

```
[0x00001100]> p?
Usage: p[=68abcdDfiImrstuxz] [arg|len] [@addr]  
| p[b|B|xb] [len] ([S])   bindump N bits skipping S bytes
| p[iI][df] [len]         print N ops/bytes (f=func) (see pi? and pdq)
| p[kK] [len]             print key in randomart (K is for mosaic)
| p-[?][jh] [mode]        bar|json|histogram blocks (mode: e?search.in)
| p2 [len]                8x8 2bpp-tiles
| p6[de] [len]            base64 decode/encode
| p8[?][j] [len]          8bit hexpair list of bytes
| p=[?][bep] [N] [L] [b]  show entropy/printable chars/chars bars
| pa[edD] [arg]           pa:assemble  pa[dD]:disasm or pae: esil from hex
| pb[?] [n]               bitstream of N bits
| pB[?] [n]               bitstream of N bytes
| pc[?][p] [len]          output C (or python) format
| pC[aAcdDxw] [rows]      print disassembly in columns (see hex.cols and pdq)
| pd[?] [sz] [a] [b]      disassemble N opcodes (pd) or N bytes (pD)
| pf[?][.nam] [fmt]       print formatted data (pf.name, pf.name $<expr>)
| pF[?][apx]              print asn1, pkcs7 or x509
| pg[?][x y w h] [cmd]    create new visual gadget or print it (see pg? for details)
| ph[?][=|hash] ([len])   calculate hash for a block
| pi[?][bdefrj] [num]     print instructions
| pI[?][iI][df] [len]     print N instructions/bytes (f=func)
| pj[?] [len]             print as indented JSON
| pm[?] [magic]           print libmagic data (see pm? and /m?)
| po[?] hex               print operation applied to block (see po?)
| pp[?][sz] [len]         print patterns, see pp? for more help
| pr[?][glx] [len]        print N raw bytes (in lines or hexblocks, 'g'unzip)
| ps[?][pwz] [len]        print pascal/wide/zero-terminated strings
| pt[?][dn] [len]         print different timestamps
| pu[?][w] [len]          print N url encoded bytes (w=wide)
| pv[?][jh] [mode]        show variable/pointer/value in memory
| px[?][owq] [len]        hexdump of N bytes (o=octal, w=32bit, q=64bit)
| plf                     print the RzIL output of the function
```

Tip: when using json output, you can append the `~{}` to the command to get a pretty-printed version of the output:

```
[0x00000000]> olj
[{"raised":false,"fd":563280,"uri":"malloc://512","from":0,"writable":true,"size":512,"overlaps":false}]
[0x00000000]> olj~{}
[
	{
		"raised": false,
		"fd": 563280,
		"uri": "malloc://512",
		"from": 0,
		"writable": true,
		"size": 512,
		"overlaps": false
	}
]
```

For more on the magical powers of `~` see the help in `?@?`, and the [Rizin Command-line](../first_steps/commandline_rizin.md)
chapter earlier in the book.

### Hexadecimal View

`px` gives a user-friendly output showing 16 pairs of numbers per row with offsets and raw representations:

```
[0x00001100]> px
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x00001100  f30f 1efa 31ed 4989 d15e 4889 e248 83e4  ....1.I..^H..H..
0x00001110  f050 5445 31c0 31c9 488d 3dca 0000 00ff  .PTE1.1.H.=.....
0x00001120  15b3 2e00 00f4 662e 0f1f 8400 0000 0000  ......f.........
```

#### Show Hexadecimal Words Dump (32 bits)

```
[0x00001100]> pxw
0x00001100  0xfa1e0ff3 0x8949ed31 0x89485ed1 0xe48348e2  ....1.I..^H..H..
0x00001110  0x455450f0 0xc931c031 0xca3d8d48 0xff000000  .PTE1.1.H.=.....
0x00001120  0x002eb315 0x2e66f400 0x00841f0f 0x00000000  ......f.........

[0x00001100]> e cfg.bigendian
false

[0x00001100]> e cfg.bigendian=true

[0x00001100]> pxw
0x00001100  0xf30f1efa 0x31ed4989 0xd15e4889 0xe24883e4  ....1.I..^H..H..
0x00001110  0xf0505445 0x31c031c9 0x488d3dca 0x000000ff  .PTE1.1.H.=.....
0x00001120  0x15b32e00 0x00f4662e 0x0f1f8400 0x00000000  ......f.........

[0x00001100]> e cfg.bigendian=false
```

#### 8 bits Hexpair List of Bytes

```
[0x00001100]> p8 16
f30f1efa31ed4989d15e4889e24883e4
```

#### Show Hexadecimal Quad-words Dump (64 bits)

```
[0x00001100]> pxq
0x00001100  0x8949ed31fa1e0ff3  0xe48348e289485ed1   ....1.I..^H..H..
0x00001110  0xc931c031455450f0  0xff000000ca3d8d48   .PTE1.1.H.=.....
0x00001120  0x2e66f400002eb315  0x0000000000841f0f   ......f.........
0x00001130  0x4800002ed93d8d48  0x394800002ed2058d   H.=....H......H9
```

### Date/Time Formats

Currently supported timestamp output modes are:

```
[0x00404888]> pt?
Usage: pt[.dhn]   # Print timestamps
| pt  # Print UNIX epoch time (32 bit `cfg.bigendian`, since January 1, 1970)
| pt. # Print the current time
| ptd # Print MS-DOS time (32 bit `cfg.bigendian`, since January 1, 1980)
| pth # Print Mac HFS time (32 bit `cfg.bigendian`, since January 1, 1904)
| ptn # Print NTFS time (64 bit `cfg.bigendian`, since January 1, 1601)
```

For example, you can 'view' the current buffer as timestamps in the ntfs time:

```
[0x08048000]> e cfg.bigendian=false
[0x08048000]> pt 4
29:04:32948 23:12:36 +0000
[0x08048000]> e cfg.bigendian=true
[0x08048000]> pt 4
20:05:13001 09:29:21 +0000
```

As you can see, the endianness affects the result. Once you have printed a timestamp, you can grep the output, for
example, by year:

```
[0x08048000]> pt ~1974 | wc -l
15
[0x08048000]> pt ~2022
27:04:2022 16:15:43 +0000
```

The default date format can be configured using the `cfg.datefmt` variable. Formatting rules for it follow the well
known strftime(3) format. Check the manpage for more details, but these are the most important:

```
%a  The abbreviated name of the day of the week according to the current locale.
%A  The full name of the day of the week according to the current locale.
%d  The day of the month as a decimal number (range 01 to 31).
%D  Equivalent to %m/%d/%y.  (Yecch—for Americans only).
%H  The hour as a decimal number using a 24-hour clock (range 00 to 23).
%I  The hour as a decimal number using a 12-hour clock (range 01 to 12).
%m  The month as a decimal number (range 01 to 12).
%M  The minute as a decimal number (range 00 to 59).
%p  Either "AM" or "PM" according to the given time value.
%s  The number of seconds since the Epoch, 1970-01-01 00:00:00  +0000 (UTC). (TZ)
%S  The second as a decimal number (range 00 to 60).  (The range is up to 60 to allow for occasional leap seconds.)
%T  The time in 24-hour notation (%H:%M:%S).  (SU)
%y  The year as a decimal number without a century (range 00 to 99).
%Y  The year as a decimal number including the century.
%z  The +hhmm or -hhmm numeric timezone (that is, the hour and minute offset from UTC). (SU)
%Z  The timezone name or abbreviation.
```

### Basic Types

There are print modes available for all basic types. If you are interested in a more complex structure, type `pf??`
for format characters and `pf???` for examples:

```
[0x00499999]> pf??
Usage: pf[j*q] <format>   # Show data using given format string
| pf <format>       # Show data using given format string
| pfj <format>      # Show data using given format string (JSON mode)
| pf* <format>      # Show data using given format string (rizin mode)
| pfq <format>      # Show data using given format string (quiet mode)

Formats:
| b # byte (unsigned)
| B # resolve enum bitfield (see t?)
| c # char (signed byte)
| C # byte in decimal
| d # 0xHEX value (4 bytes) (see 'i' and 'x' formats)
| D # disassemble one opcode
| e # temporarily swap endian
| E # resolve enum name (see t?)
| f # float value (4 bytes)
| F # double float value (8 bytes)
| i # signed integer value (4 bytes) (see 'd' and 'x' formats)
| n # next char specifies size of signed value (1, 2, 4, or 8 byte(s))
| N # next char specifies size of unsigned value (1, 2, 4, or 8 byte(s))
| o # octal value (4 bytes)
| p # pointer reference (2, 4, or 8 bytes)
| q # quadword (8 bytes)
| Q # octoword (uint128_t) (16 bytes)
| r # CPU register (`pf r (eax)plop`)
| s # 32 bit pointer to string (4 bytes)
| s # 32 bit pointer to string (4 bytes)
| t # 32 bit UNIX timestamp (4 bytes)
| T # show ten first bytes of buffer
| u # uleb128 (variable length)
| w # word (2 bytes unsigned short in hex)
| x # 0xHEX value and flag (fd @ addr) (see 'd' and 'i' formats)
| X # show formatted hexpairs
| z # null terminated string
| Z # null terminated wide string
| ? # data structure `pf ? (struct_name)example_name`
| * # next char is pointer (honors 'asm.bits')
| + # toggle show flags for each offset
| : # skip 4 bytes
| . # skip 1 byte
| ; # rewind 4 bytes
| , # rewind 1 byte
```

Use triple-question-mark `pf???` to get some examples using print format strings.

```
[0x00001100]> pf???
Usage: p[=68abcdDfiImrstuxz] [arg|len] [@addr]  
| p[b|B|xb] [len] ([S])   bindump N bits skipping S bytes
| p[iI][df] [len]         print N ops/bytes (f=func) (see pi? and pdq)
| p[kK] [len]             print key in randomart (K is for mosaic)
| p-[?][jh] [mode]        bar|json|histogram blocks (mode: e?search.in)
| p2 [len]                8x8 2bpp-tiles
| p6[de] [len]            base64 decode/encode
| p8[?][j] [len]          8bit hexpair list of bytes
| p=[?][bep] [N] [L] [b]  show entropy/printable chars/chars bars
| pa[edD] [arg]           pa:assemble  pa[dD]:disasm or pae: esil from hex
| pb[?] [n]               bitstream of N bits
| pB[?] [n]               bitstream of N bytes
| pc[?][p] [len]          output C (or python) format
| pC[aAcdDxw] [rows]      print disassembly in columns (see hex.cols and pdq)
| pd[?] [sz] [a] [b]      disassemble N opcodes (pd) or N bytes (pD)
| pf[?][.nam] [fmt]       print formatted data (pf.name, pf.name $<expr>)
| pF[?][apx]              print asn1, pkcs7 or x509
| pg[?][x y w h] [cmd]    create new visual gadget or print it (see pg? for details)
| ph[?][=|hash] ([len])   calculate hash for a block
| pi[?][bdefrj] [num]     print instructions
| pI[?][iI][df] [len]     print N instructions/bytes (f=func)
| pj[?] [len]             print as indented JSON
| pm[?] [magic]           print libmagic data (see pm? and /m?)
| po[?] hex               print operation applied to block (see po?)
| pp[?][sz] [len]         print patterns, see pp? for more help
| pr[?][glx] [len]        print N raw bytes (in lines or hexblocks, 'g'unzip)
| ps[?][pwz] [len]        print pascal/wide/zero-terminated strings
| pt[?][dn] [len]         print different timestamps
| pu[?][w] [len]          print N url encoded bytes (w=wide)
| pv[?][jh] [mode]        show variable/pointer/value in memory
| px[?][owq] [len]        hexdump of N bytes (o=octal, w=32bit, q=64bit)
| plf                     print the RzIL output of the function
```

Some examples are below:
```
[0x00001100]> pf i
0x00001100 = -98693133

[0x00001100]> pf f
0x00001100 = -2.05176598e+35

```

### High-level Languages Views

Valid print code formats for human-readable languages are:

```
0x00001100]> pc?
Usage: pc[?]   # Print bytes as code byte arrays.
| pc [<len>]  # Generate a C/C++ byte array.
| pch         # Generate a C/C++ 16 bits array.
| pcw         # Generate a C/C++ 32 bits array.
| pcd         # Generate a C/C++ 64 bits array.
| pca [<len>] # Generate a byte array in GAS assembly.
| pcA [<len>] # Generate a byte array in GAS assembly with instructions in comments.
| pcb [<len>] # Generate a bash script with the byte array.
| pcg [<len>] # Generate a Golang byte array.
| pcJ [<len>] # Generate a Java byte array.
| pcj [<len>] # Generate a JSON byte array.
| pck [<len>] # Generate a Kotlin byte array.
| pcn [<len>] # Generate a NodeJS buffer.
| pco [<len>] # Generate a Objective-C/C++ byte array.
| pcp [<len>] # Generate a Python byte array.
| pcr [<len>] # Generate a Rust byte array.
| pcs [<len>] # Generate a Swift byte array.
| pcy [<len>] # Generate a Yara match pattern.
| pc* [<len>] # Generate a rizin commands for writing the byte array.
```

If we need to create a .c file containing a binary blob, use the `pc` command, that creates this output. The default
size is like in many other commands: the block size, which can be changed with the `b` command.

We can also just temporarily override this block size by expressing it as an argument.

```
[0x00001100]> pc 32
#define ARRAY_SIZE 32
const uint8_t array[ARRAY_SIZE] = {
  0xf3, 0x0f, 0x1e, 0xfa, 0x31, 0xed, 0x49, 0x89, 0xd1, 0x5e, 0x48, 0x89, 0xe2, 0x48, 0x83, 0xe4,
  0xf0, 0x50, 0x54, 0x45, 0x31, 0xc0, 0x31, 0xc9, 0x48, 0x8d, 0x3d, 0xca, 0x00, 0x00, 0x00, 0xff
};
```

### Strings

Strings are probably one of the most important entry points when starting to reverse engineer a program because they
usually reference information about functions' actions (asserts, debug or info messages...). Therefore, Rizin supports
various string formats:

```
[0x00001100]> ps?
Usage: ps[?]   # Print string at the current offset
| ps[j] <delimiter>=null # Print the autodetected string at the current offset (null->zero-terminated, block->block-terminated)
| ps+[j]                 # Print libc++ std::string (same-endian, ascii, zero-terminated)
| psb[q]                 # Print all the strings in current block
| psc[?]                 # Generate a C/C++ string
| psi[?]                 # Print the first string in the current block
| psp[j] <bits>=8        # Print the pascal string at the current offset
| pss[?]                 # Print string at the current offset in screen (wrap width)
| psm[j]                 # Print buffer as a utf16be string
| psM[j]                 # Print buffer as a utf32be string
| psn[j]                 # Print string with escaped new lines
| psw[j]                 # Print buffer as a utf16le string
| psW[j]                 # Print buffer as a utf32le string
```

Most strings are zero-terminated. Below there is an example using the debugger to continue the execution of a program
until it executes the 'open' syscall. When we recover the control over the process, we get the arguments passed to the
syscall, pointed by %ebx. In the case of the 'open' call, it is a zero terminated string which we can inspect using
`psz`.

```
[0x4A13B8C0]> dcs open
0x4a14fc24 syscall(5) open ( 0x4a151c91 0x00000000 0x00000000 ) = 0xffffffda
[0x4A13B8C0]> dr
  eax  0xffffffda    esi  0xffffffff    eip    0x4a14fc24
  ebx  0x4a151c91    edi  0x4a151be1    oeax   0x00000005
  ecx  0x00000000    esp  0xbfbedb1c    eflags 0x200246
  edx  0x00000000    ebp  0xbfbedbb0    cPaZstIdor0 (PZI)
[0x4A13B8C0]>
[0x4A13B8C0]> psz @ 0x4a151c91
/etc/ld.so.cache
```

### Print Memory Contents

It is also possible to print various packed data types using the `pf` command:

```
[0xB7F08810]> pf xxS @ rsp
0x7fff0d29da30 = 0x00000001
0x7fff0d29da34 = 0x00000000
0x7fff0d29da38 = 0x7fff0d29da38 -> 0x0d29f7ee /bin/ls
```

This can be used to look at the arguments passed to a function. To achieve this, simply pass a 'format memory string'
as an argument to `pf`, and temporally change the current seek position/offset using `@`. It is also possible to define
arrays of structures with `pf`. To do this, prefix the format string with a numeric value. You can also define a name
for each field of the structure by appending them as a space-separated arguments list.

```
[0x4A13B8C0]> pf 2*xw pointer type @ esp
0x00404888 [0] {
   pointer :
(*0xffffffff8949ed31)      type : 0x00404888 = 0x8949ed31
   0x00404890 = 0x48e2
}
0x00404892 [1] {
(*0x50f0e483)    pointer : 0x00404892 = 0x50f0e483
	 type : 0x0040489a = 0x2440
}
```

A practical example for using `pf` on a binary of a GStreamer plugin:

```
$ rizin /usr/lib/gstreamer-1.0/libgsttcp.so
 -- Move the comments to the right changing their margin with asm.cmt.margin
[0x00005020]> aa; pdf @ sym.gst_plugin_tcp_get_desc
[x] Analyze all flags starting with sym. and entry0 (aa)
┌ 8: sym.gst_plugin_tcp_get_desc ();
│ bp: 0 (vars 0, args 0)
│ sp: 0 (vars 0, args 0)
│ rg: 0 (vars 0, args 0)
│           0x000127f0      lea rax, section..data.rel.ro              ; 0x1d460
└           0x000127f7      ret
[0x00005020]> s section..data.rel.ro
[0x0001d460]> pf ii*z*zp*z*z*z*z*z*z major minor name desc init version license source package origin release_datetime
            major : 0x0001d460 = 1
            minor : 0x0001d464 = 18
             name : (*0x15c8e)0x0001d468 = "tcp"
             desc : (*0x17c88)0x0001d470 = "transfer data over the network via TCP"
             init : 0x0001d478 = (qword)0x0000000000011430
          version : (*0x15d0b)0x0001d480 = "1.18.2"
          license : (*0x15d3e)0x0001d488 = "LGPL"
           source : (*0x15d2d)0x0001d490 = "gst-plugins-base"
          package : (*0x17cb0)0x0001d498 = "GStreamer Base Plugins (Arch Linux)"
           origin : (*0x15d12)0x0001d4a0 = "https://www.archlinux.org/"
 release_datetime : (*0x15d43)0x0001d4a8 = "2020-12-06"
```

### Disassembly

The `pd` command is used to disassemble code. It accepts a numeric value to specify how many instructions should be
disassembled. The `pD` command is similar but instead of a number of instructions, it decompiles a given number of
bytes.

* `pd` : Disassemble N instructions (can be negative)
* `pD` : Disassemble N bytes (can be negative)

```
[0x00001100]> pd 1
            ;-- entry0:
            ;-- section..text:
            ;-- _start:
            0x00001100      endbr64                                    ; [14] -r-x section size 409 named .text
```

### Selecting Target Architecture

The architecture flavor for the disassembler is defined by the `asm.arch` eval variable. You can use `e asm.arch=??` to list all available architectures.

```
[0x00001100]> e asm.arch=??
_dAeI 8 16       6502        LGPL3   6502/NES/C64/Tamagotchi/T-1000 CPU
adAeI 8          8051        PD      8051 Intel CPU
_dA__ 32         amd29k      LGPL3   AMD 29k RISC CPU (by deroad)
_dA__ 16 32      arc         GPL3    Argonaut RISC Core
adAeI 16 32 64   arm         BSD     Capstone ARM disassembler
a____ 16 32 64   arm.as      LGPL3   as ARM Assembler (use RZ_ARM32_AS and RZ_ARM64_AS environment) (by pancake)
adAeI 8 16       avr         LGPL3   AVR Atmel
adA_I 16 32 64   bf          LGPL3   Brainfuck (by pancake, nibble) v4.0.0
_dA__ 32         chip8       LGPL3   Chip8 disassembler
_dA__ 16 32 64   cil         LGPL3   .NET Common Intermediate Language
_dA__ 16         cr16        LGPL3   cr16 disassembly plugin
_dA__ 32         cris        GPL3    Axis Communications 32-bit embedded processor (by pancake)
adA__ 32 64      dalvik      LGPL3   AndroidVM Dalvik
ad___ 16         dcpu16      PD      Mojang's DCPU-16
_dA__ 32 64      ebc         LGPL3   EFI Bytecode (by Fedor Sakharov)
adAeI 16         gb          LGPL3   GameBoy(TM) (z80-like) (by condret)
_dAe_ 16         h8300       LGPL3   H8/300 disassembly plugin
_dA_I 32         hexagon     LGPL3   Qualcomm Hexagon (QDSP6) V6 (by Rot127)
_d___ 32         hppa        GPL3    HP PA-RISC
_dA__ 4          i4004       LGPL3   Intel 4004 microprocessor
_dA__ 8          i8080       BSD     Intel 8080 CPU
adA__ 32         java        LGPL-3  Java bytecode disassembler (by deroad)
_d___ 32         lanai       GPL3    LANAI
...
```

### Configuring the Disassembler

There are multiple options which can be used to configure the output of the disassembler. All these options are
described in `el asm.`

```
[0x00001100]> el asm.
        asm.analysis: Analyze code and refs while disassembling (see analysis.strings)
            asm.arch: Set the arch to be used by asm
       asm.assembler: Set the plugin name to use when assembling
         asm.bb.line: Show empty line after every basic block
       asm.bb.middle: Realign disassembly if a basic block starts in the middle of an instruction
            asm.bits: Word size in bits at assembler
           asm.bytes: Display the bytes of each instruction
     asm.bytes.right: Display the bytes at the right of the disassembly
     asm.bytes.space: Separate hexadecimal bytes with a whitespace
           asm.calls: Show callee function related info as comments in disasm
      asm.capitalize: Use camelcase at disassembly
         asm.cmt.col: Column to align comments
        asm.cmt.esil: Show ESIL expressions as comments
     asm.cmt.flgrefs: Show comment flags associated to branch reference
...
```

Currently, there are 130 `asm.` configuration variables so we do not list them all.

### Disassembly Syntax

The `asm.syntax` variable is used to change the flavor of the assembly syntax used by a disassembler engine. To switch
between Intel and AT&T representations:

```
e asm.syntax=intel
e asm.syntax=att
```

You can also check `asm.pseudo`, which is an experimental pseudocode view,
and `asm.esil` which outputs [ESIL](../disassembling/esil.md) ('Evaluable Strings Intermediate Language').
ESIL's goal is to have a human-readable representation of every opcode semantics. Such representations can be evaluated
(interpreted) to emulate effects of individual instructions.

### Print gadgets

In Rizin, visual gadgets allows the users to cast or display the output of a particular Rizin command anywhere on the
screen while in Visual mode. This command is unrelated with displaying [ROP Gadgets](../refcard/intro.html#searching).

Using the commands under `pg` (print gadgets), we can add, remove and change the location of these visual gadgets.
You can add a gadget using `pg`:

```
pg 10 10 10 10 ddr
```

This will add the output of the Rizin command `ddr` be printed on the screen. The four arguments to be passed are
the position (like coordinates) and the height and width of the gadget you would like to see. This command requires
the configuration variable `scr.gadgets` to be turned on.

See `pg?` for more information.

### Print Patterns

The `pp` command group generates deterministic patterns that are handy for fuzzing, debugging, and exploit development.

```
[0x00000000]> pp?
Usage: pp[?]   # Print patterns
| pp[ad] [len]   # Print different patterns
| ppd <len>      # Print De Bruijn pattern of length <len>
| ppd/<value>    # Show the offset of <value> in the default De Bruijn pattern (honors cfg.bigendian)
```

#### De Bruijn patterns

De Bruijn sequences are cyclic patterns in which every substring of the chosen width appears exactly once. They’re perfect for recovering overwrite offsets after a crash.

**Generate a pattern**

```
[0x00000000]> ppd 100
AABAACAADAAEAAFAAGAAHAAIAAJAAKAALAAMAANAAOAAPAAQAARAASAATAAUAAVAAWAAXAAYAAZAAaAAbAAcAAdAAeAAfAAgAAh
```

**Locate an observed value**

Use `ppd/<value>` to look up where a value appears in the default pattern. This is the fastest way to translate a register/memory capture back into an offset.

```
[0x00000000]> e cfg.bigendian=false
[0x00000000]> ppd/ 0x41574141
64
```

The command respects `cfg.bigendian`, so flip it if your target is big-endian:

```
[0x00000000]> e cfg.bigendian=true
[0x00000000]> ppd/ 0x41574141
65
```

**Writing the pattern**

If you prefer to inject the pattern directly, `wD <len>` writes the same data at the current seek, and `wD/<value>` mirrors the lookup behavior:

```
[0x00000000]> wD 100        # Write 100 bytes of the pattern
[0x00000000]> wD/ 0x41574141
64
```

(See [Writing Data](write.md#writing-data) for more on `wD`.)

