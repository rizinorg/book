# Code Analysis

Code analysis is a common technique used to extract information from assembly code.

Rizin has different code analysis techniques implemented in the core and available in different commands.

All features of Rizin are available from the library APIs as well as from commands.
This gives you the ability to implement your own analysis loops using any programming language, even with Rizin
one-liners, shell scripts, or analysis/core native plugins.

The analysis will show up the internal data structures to identify basic blocks, function trees and to extract
opcode-level information.

The most common rizin analysis sequence utilizes is **analyze all** command (`aa`), which examines all symbols and
entry-points. If the binary is stripped, using advance automated analysis `aaa` will be necessary; advanced analysis
steps can be invoked manually with commands like `aab`, `aar`, or `aac`.

Let's analyse simple [hello_world](https://github.com/rizinorg/book/tree/master/examples/hello_world) program:

```
[0x00001100]> aa
[x] Analyze all flags starting with sym. and entry0 (aa)

[0x00001100]> pdf @ main
            ; DATA XREF from entry0 @ 0x1118
/ int main(int argc, char **argv, char **envp);
|           ; arg int argc @ rdi
|           ; arg char **argv @ rsi
|           ; var int64_t var_48h @ stack - 0x48
|           ; var int64_t var_3ch @ stack - 0x3c
|           ; var int64_t var_30h @ stack - 0x30
|           ; var int64_t var_28h @ stack - 0x28
|           ; var int64_t var_20h @ stack - 0x20
|           ; var int64_t var_18h @ stack - 0x18
|           ; var int64_t var_10h @ stack - 0x10
|           0x000011e9      endbr64
|           0x000011ed      push  rbp
|           0x000011ee      mov   rbp, rsp
|           0x000011f1      sub   rsp, 0x40
|           0x000011f5      mov   dword [var_3ch], edi                 ; argc
|           0x000011f8      mov   qword [var_48h], rsi                 ; argv
|           0x000011fc      lea   rax, [str.Hello]                     ; 0x2004 ; "Hello "
|           0x00001203      mov   qword [var_30h], rax
|           0x00001207      lea   rax, [str.world]                     ; 0x200b ; "world!"
|           0x0000120e      mov   qword [var_28h], rax
|           0x00001212      mov   rax, qword [var_30h]
|           0x00001216      mov   rdi, rax
|           0x00001219      call  sym.imp.strlen                       ; sym.imp.strlen ; size_t strlen(const char *s)
|           0x0000121e      mov   qword [var_20h], rax
|           0x00001222      mov   rax, qword [var_28h]
|           0x00001226      mov   rdi, rax
|           0x00001229      call  sym.imp.strlen                       ; sym.imp.strlen ; size_t strlen(const char *s)
|           0x0000122e      mov   qword [var_18h], rax
|           0x00001232      mov   rdx, qword [var_20h]
|           0x00001236      mov   rax, qword [var_18h]
|           0x0000123a      add   rax, rdx
|           0x0000123d      add   rax, 1
|           0x00001241      mov   rdi, rax
|           0x00001244      call  sym.imp.malloc                       ; sym.imp.malloc ; void *malloc(size_t size)
|           0x00001249      mov   qword [var_10h], rax
|           0x0000124d      cmp   qword [var_10h], 0
|       ,=< 0x00001252      je    0x1292
|       |   0x00001254      mov   rdx, qword [var_30h]
|       |   0x00001258      mov   rax, qword [var_10h]
|       |   0x0000125c      mov   rsi, rdx
|       |   0x0000125f      mov   rdi, rax
|       |   0x00001262      call  sym.imp.strcpy                       ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
|       |   0x00001267      mov   rdx, qword [var_28h]
|       |   0x0000126b      mov   rax, qword [var_10h]
|       |   0x0000126f      mov   rsi, rdx
|       |   0x00001272      mov   rdi, rax
|       |   0x00001275      call  sym.imp.strcat                       ; sym.imp.strcat ; char *strcat(char *s1, const char *s2)
|       |   0x0000127a      mov   rax, qword [var_10h]
|       |   0x0000127e      mov   rdi, rax
|       |   0x00001281      call  sym.imp.puts                         ; sym.imp.puts ; int puts(const char *s)
|       |   0x00001286      mov   rax, qword [var_10h]
|       |   0x0000128a      mov   rdi, rax
|       |   0x0000128d      call  sym.imp.free                         ; sym.imp.free ; void free(void *ptr)
|       `-> 0x00001292      mov   eax, 0
|           0x00001297      leave
\           0x00001298      ret
```

In this example, we analyze the whole file (via `aa`) and then print disassembly of the `main()` function (via `pdf`).
The `aa` command belongs to the family of auto analysis commands and performs only the most basic
auto analysis steps. In Rizin there are many different types of auto analysis commands with a
different analysis depth, including partial emulation: `aa`, `aaa`, `aab`, `aaaa`, ...
There is also a mapping of those commands to the rizin CLI options: `rizin -A`, `rizin -AA`, and so on.

It is common sense that completely automated analysis can produce non sequitur results, thus
Rizin provides separate commands for the particular stages of the analysis allowing fine-grained
control of the analysis process. Moreover, there is a treasure trove of configuration variables
for controlling the analysis outcomes. You can find them via command `el` under `analysis.*` and `emu.*`
variables namespaces.

## Analyze functions

One of the most important "basic" analysis commands is the set of `af` subcommands. `af` means
"analyze function". Using this command you can either allow automatic analysis of the particular
function or perform a completely manual one.

```
[0x00001100]> af?
Usage: af[?]   # Analyze Functions commands
| af [<name>]             # Analyze functions recursively (honors `analysis.calls`)
| afr [<name>]            # Analyze functions recursively
| af+ <name> [<type>]     # Hand craft a function (requires `afb+`)
| af-                     # Delete function
| af-*                    # Delete all function analysis data
| afj <tbl_addr> <elements> # Analyze function jumptable
| afa                     # Analyze function arguments in a call
| afal                    # Analyze function arguments in a call (honors `dbg.funcarg`)
| afb[?]                  # Basic blocks commands
| afB <bits>              # Set asm.bits for the current function
| afs[jb!r]               # Function signatures commands
| afo[j]                  # Show address of current function
| afu <addr>              # Resize and analyze function from current address until addr
| afx[j]                  # List function references
| afS <size>              # Set stack frame size for function at current address
| afv<?>                  # Manipulate arguments/variables in a function
| afl[?]                  # List functions
| afi[j*is]               # Show/edit function information
| afn[as]                 # Analyze function names
| aft                     # Type matching analysis for the function in current seek
| afM                     # Print functions map
| afm <addr>              # Merge two functions
| afc[lor]                # Calling convention
| afd                     # Show function + delta for given offset
```

You can use `afl` to list the functions found by the analysis.

There are a lot of useful commands under `afl` such as `aflj` (lists the function in JSON format; `j` is a common
command suffix to provide JSON output), `aflm` (lists the functions in the syntax found in makefiles), or
`afll` (lists all functions in verbose mode). 

There's also `afl=`, which displays ASCII-art bars with function ranges.

You can find the rest of them under `afl?`.

Some of the most challenging tasks while performing a function analysis are merge, crop, and resize.
As with other analysis commands, you have two modes: semi-automatic and manual.
For the semi-automatic, you can use `afm <function name>` to merge the current function with
the one specified by name as an argument, `aff` to readjust the function after analysis changes or function edits,
`afu <address>` to do the resize and analysis of the current function until the specified address.

Apart from those semi-automatic ways to edit/analyze the function, you can handcraft it in the manual mode with
`af+` command and edit basic blocks of it using `afb` commands.
Before changing the basic blocks of the function it is recommended to check the already presented ones:

```
[0x00003ac0]> afb
0x00003ac0 0x00003b7f 01:001A 191 f 0x00003b7f
0x00003b7f 0x00003b84 00:0000 5 j 0x00003b92 f 0x00003b84
0x00003b84 0x00003b8d 00:0000 9 f 0x00003b8d
0x00003b8d 0x00003b92 00:0000 5
0x00003b92 0x00003ba8 01:0030 22 j 0x00003ba8
0x00003ba8 0x00003bf9 00:0000 81
```

### Handcraft function

Before starting, let's prepare a binary file first, for example:

```C
int code_block()
{
  int result = 0;

  for(int i = 0; i < 10; ++i)
    result += 1;

  return result;
}
```

Then compile it with `gcc -c example.c -m32 -O0 -fno-pie`, we will get the object file `example.o`. Open it with rizin.

Since we haven't analyzed it yet, the `pdf` command will not print out the disassembly here:

```
$ rizin example.o
[0x08000034]> pdf
p: Cannot find function at 0x08000034
[0x08000034]> pd
            ;-- section..text:
            ;-- .text:
            ;-- code_block:
            ;-- eip:
            0x08000034      55             push ebp                    ; [01] -r-x section size 41 named .text
            0x08000035      89e5           mov ebp, esp
            0x08000037      83ec10         sub esp, 0x10
            0x0800003a      c745f8000000.  mov dword [ebp - 8], 0
            0x08000041      c745fc000000.  mov dword [ebp - 4], 0
        ,=< 0x08000048      eb08           jmp 0x8000052
       .--> 0x0800004a      8345f801       add dword [ebp - 8], 1
       :|   0x0800004e      8345fc01       add dword [ebp - 4], 1
       :`-> 0x08000052      837dfc09       cmp dword [ebp - 4], 9
       `==< 0x08000056      7ef2           jle 0x800004a
            0x08000058      8b45f8         mov eax, dword [ebp - 8]
            0x0800005b      c9             leave
            0x0800005c      c3             ret

```

Our goal is to handcraft a function with the following structure

![analyze_one](analyze_one.png)


Create a function at 0x8000034 named code_block:

```
[0x8000034]> af+ 0x8000034 code_block
```

In most cases, we use jump or call instructions as code block boundaries. So the range of first block is from
`0x08000034 push ebp` to `0x08000048 jmp 0x8000052`. Use `afb+` command to add it.

```
[0x08000034]> afb+ code_block 0x8000034 0x800004a-0x8000034 0x8000052
```

Note that the basic syntax of `afb+` is `afb+ function_address block_address block_size [jump] [fail]`.
The final instruction of this block points to a new address (jmp 0x8000052), thus we add the address of jump target
(0x8000052) to reflect the jump info.

The next block (0x08000052 ~ 0x08000056) is more likely an if conditional statement which has two branches. It will
jump to 0x800004a if `less or equal`, otherwise (the fail condition) jump to next instruction - 0x08000058:

```
[0x08000034]> afb+ code_block 0x8000052 0x8000058-0x8000052 0x800004a 0x8000058
```

Follow the control flow and create the remaining two blocks (two branches):

```
[0x08000034]> afb+ code_block 0x800004a 0x8000052-0x800004a 0x8000052
[0x08000034]> afb+ code_block 0x8000058 0x800005d-0x8000058
```

Check our work:

```
[0x08000034]> afb
0x08000034 0x0800004a 00:0000 22 j 0x08000052
0x0800004a 0x08000052 00:0000 8 j 0x08000052
0x08000052 0x08000058 00:0000 6 j 0x0800004a f 0x08000058
0x08000058 0x0800005d 00:0000 5
[0x08000034]> VV
```

![handcraft_one](handcraft_one.png)

There are two very important commands for this: `afc` and `afB`. The latter is a must-know command for some platforms
like ARM. It provides a way to change the "bitness" of a particular function by allowing to select between ARM and
Thumb modes.

`afc` on the other side, allows to manually specify function calling convention. You can find more information on its
usage in [calling_conventions](calling_conventions.md).

## Recursive analysis

There are 5 important program-wide half-automated analysis commands:

- `aab` - perform basic-block analysis ("Nucleus" algorithm)
- `aac` - analyze function calls from one (selected or current function)
- `aaf` - analyze all function calls
- `aar` - analyze data references
- `aad` - analyze pointers to pointers references

Those are only generic semi-automated reference searching algorithms. Rizin provides a
wide choice of manual references' creation of any kind. For this fine-grained control,
you can use `ax` commands.

```
[0x00001100]> ax?
Usage: ax[?]   # Cross references (xrefs)
| ax <addr>           # Add custom xref to addr from current seek
| axc <addr>          # Add generic code xref to addr from current seek
| axC <addr>          # Add call code xref to addr from current seek
| axd <addr>          # Add data xref to addr from current seek
| axs <addr>          # Add string xref to addr from current seek
| axl[j*q]            # List all xrefs
| axt[j*q]            # List xrefs to current seek
| axf[j*q]            # List xrefs from current seek
| axtg                # Display commands to generate graphs according to xrefs
| ax- <addr> [<from>] # Delete xrefs to addr
| ax-*                # Delete all xrefs
| axm <addr>          # Copy xrefs pointing to addr to also point to curseek
| axg[j*]             # Show xrefs graph to reach function at current seek

```

The most commonly used `ax` commands are `axt` and `axf`, especially as a part of various rz-pipe
scripts. Let's say we see the string in the data or a code section and want to find all places
it was referenced from, we should use `axt`:

```
[0x0001783a]> pd 2
;-- str.02x:
; STRING XREF from 0x00005de0 (sub.strlen_d50)
; CODE XREF from 0x00017838 (str.._s_s_s + 7)
0x0001783a     .string "%%%02x" ; len=7
;-- str.src_ls.c:
; STRING XREF from 0x0000541b (sub.free_b04)
; STRING XREF from 0x0000543a (sub.__assert_fail_41f + 27)
; STRING XREF from 0x00005459 (sub.__assert_fail_41f + 58)
; STRING XREF from 0x00005f9e (sub._setjmp_e30)
; CODE XREF from 0x0001783f (str.02x + 5)
0x00017841 .string "src/ls.c" ; len=9
[0x0001783a]> axt
sub.strlen_d50 0x5de0 [STRING] lea rcx, str.02x
(nofunc) 0x17838 [CODE] jae str.02x
```

There are also some useful commands under `axt`. Use `axtg` to generate rizin commands which will help you to create
graphs according to the XREFs.

```
[0x00001100]> s main
[0x000011e9]> axtg
agn 0x1118 "entry0 + 24"
agn 0x11e9 "main"
age 0x1118 0x11e9
```

Use `axt*` to split the rizin commands and set flags on those corresponding XREFs.

Also under `ax` is `axg`, which finds the path between two points in the file by showing an XREFs graph to reach
the location or function. For example:

```
[0x000011e9]> axg
- 0x000011e9 fcn 0x000011e9 main
  - 0x00001118 fcn 0x00001100 entry0
```

Use `axg*` to generate rizin commands which will help you to create graphs using `agn` and `age` commands,
according to the XREFs.

Apart from predefined algorithms to identify functions there is a way to specify
a function prelude with a configuration option `analysis.prelude`. For example, like
`e analysis.prelude=0x554889e5` which means

```
push rbp
mov rbp, rsp
```

on x86\_64 platform. It should be specified _before_ any analysis commands.

## Configuration

Rizin allows changing the behavior of almost any analysis stages or commands.
There are different kinds of configuration options:

- Flow control
- Basic blocks control
- References control
- IO/Ranges
- Jump tables analysis control
- Platform/target-specific options

### Control flow configuration

The two most commonly used options for changing the behavior of control flow analysis in rizin are
`analysis.hasnext` and `analysis.jmp.after`. The first one allows forcing rizin to continue the analysis
after the end of the function, even if the next chunk of the code wasn't called anywhere, thus
analyzing all the available functions. The latter one allows forcing rizin to continue
the analysis even after unconditional jumps.

In addition to those we can also set `analysis.jmp.indir` to follow the indirect jumps, continuing analysis;
`analysis.pushret` to analyze `push ...; ret` sequence as a jump; `analysis.nopskip` to skip the NOP
sequences at a function beginning.

Analysis limits function size to `analysis.fcn_max_size` option.
The default value just works in most use cases, but it's useful to increase that for example when
dealing with obfuscated code. Beware that some of the basic block
control options may disappear in the future in favor of more automated ways to set those.

For some unusual binaries or targets, there is an option `analysis.noncode`. Rizin doesn't try
to analyze data sections as a code by default. But in some cases - malware, packed binaries,
binaries for embedded systems, it is often a case. Thus - this option.

### Reference control

The most crucial options that change the analysis results drastically. Sometimes some can be
disabled to save time and memory when analyzing big binaries.

- `analysis.jmp.ref` - to allow references creation for unconditional jumps
- `analysis.jmp.cref` - same, but for conditional jumps
- `analysis.datarefs` - to follow the data references in code
- `analysis.refstr` - search for strings in data references
- `analysis.strings` - search for strings and creating references

Note that strings references control is disabled by default because it increases the analysis time.

### Analysis ranges

There are a few options for this:

- `analysis.limits` - enables the range limits for analysis operations
- `analysis.from` - starting address of the limit range
- `analysis.to` - the corresponding end of the limit range
- `analysis.in` - specify search boundaries for analysis. You can set it to `io.maps`, `bin.sections`, `dbg.maps`
  and many more. For example:
  - To analyze a specific memory map with `analysis.from` and `analysis.to`, set `analysis.in=dbg.maps`.
  - To analyze in the boundaries set by `analysis.from` and `analysis.to`, set `analysis.in=range`.
  - To analyze in the current mapped segment or section, you can put `analysis.in=bin.segment` or
    `analysis.in=bin.section`, respectively.
  - To analyze in the current memory map, specify `analysis.in=dbg.map`.
  - To analyze in the stack or heap, you can set `analysis.in=dbg.stack` or `analysis.in=dbg.heap`.
  - To analyze in the current function or basic block, you can specify `analysis.in=analysis.fcn` or
    `analysis.in=analysis.bb`.

Please see `e analysis.in=??` for the complete list.

### Jump tables

Jump tables are one of the trickiest targets in binary reverse engineering. There are hundreds
of different types, the end result depending on the compiler/linker and LTO stages of optimization.
Thus, Rizin allows enabling some experimental jump tables detection algorithms using `analysis.jmp.tbl`
option. Eventually, algorithms moved into the default analysis loops once they start to work on
every supported platform/target/test-case.
Two more options can affect the jump tables analysis results too:

- `analysis.jmp.indir` - follow the indirect jumps, some jump tables rely on them
- `analysis.datarefs` - follow the data references, some jump tables use those

### Platform specific controls

There are two common problems when analyzing embedded targets: ARM/Thumb detection and MIPS GP
value. In the case of ARM binaries rizin supports some auto-detection of ARM/Thumb mode switches, but
beware that it uses partial ESIL emulation, thus slowing the analysis process. If you do not
like the results, particular functions' mode can be overridden with `afB` command.

The MIPS GP problem is even trickier. It is basic knowledge that GP value can be different not only
for the whole program but also for some functions. To partially solve that there are options
`analysis.gp` and `analysis.gpfixed`. The first one sets the GP value for the whole program or particular
function. The latter allows to "constantify" the GP value if some code is willing to change its
value, always resetting it if the case. Those are heavily experimental and might be changed in the
future in favor of more automated analysis.

## Visuals

One of the easiest ways to see and check the changes of the analysis commands and variables
is to perform scrolling in a `Vv` special visual mode, allowing functions preview:

![vv](code_analysis_vv.png)

When we want to check how analysis changes affect the result in the case of big functions, we can
use minimap instead, allowing us to see a bigger flow graph on the same screen size. To get into
the minimap mode type `VV` then press `p` twice:

![vv2](code_analysis_vv2.png)

This mode allows you to see the disassembly of each node separately, just navigate between them using the `Tab` key.

## Analysis hints

It is not an uncommon case that analysis results are not perfect even after you tried every single
configuration option. This is where the "analysis hints" rizin mechanism comes in. It allows
to override some basic opcode or meta-information properties, or even to rewrite the whole opcode
string. These commands are located under `ah` namespace:

```
[0x00001100]> ah?
Usage: ah<?>   # Analysis hints
| ahl[j*]              # List all analysis hints
| ahl.[j*]             # List analysis hints at current seek
| ah- [<size>]         # Delete analysis hints in region starting from current seek
| ah-*                 # Delete all analysis hints
| aha <arch>           # Set arch hint
| aha-                 # Delete arch hint
| ahb <bits>           # Set bits hint
| ahb-                 # Delete bits hint
| ahh                  # Set highlight hint
| ahh-                 # Delete highlight hint
| ahc <addr>           # Set jump/call address hint
| ahc-                 # Delete jump/call address hint
| ahe <string>         # Set ESIL string hint
| ahe-                 # Delete ESIL string hint
| ahd <opcode>         # Set opcode hint
| ahd-                 # Delete opcode hint
| ahs <size>           # Set opcode size hint
| ahs-                 # Delete opcode size hint
| ahf <addr>           # Set fallback address hint
| ahf-                 # Delete fallback address hint
| ahF <size>           # Set stackframe size hint
| ahF-                 # Delete stackframe size hint
| ahS <string>         # Set asm syntax hint
| ahS-                 # Delete asm syntax hint
| ahp <pointer>        # Set pointer hint
| ahp-                 # Delete pointer hint
| ahr <return>         # Set function return value hint
| ahr-                 # Delete function return value hint
| ahv <value>          # Set opcode value hint
| ahv-                 # Delete opcode value hint
| aho <string>         # Set opcode type hint
| aho-                 # Delete opcode type hint
| ahi <type> [<nword>] # Set immediate base hint
| ahi-                 # Delete immediate base hint
| aht <struct.member>  # Set structure offset hint
| aht-                 # Delete structure offset hint
| ahts <offset>        # List all matching structure offsets
```

One of the most common cases is to set a particular numeric base for immediate:

```
[0x00003d54]> ahi?
Usage: ahi <type> [<nword>]   # Set immediate base hint
| ahi <base> # Set numeric <base> (2, 8, 10, 16)
| ahi 10|d   # Set base to signed decimal (10), sign bit should depend on receiver size
| ahi 10u|du # Set base to unsigned decimal (11)
| ahi b      # Set base to binary (2)
| ahi o      # Set base to octal (8)
| ahi h      # Set base to hexadecimal (16)
| ahi i      # Set base to IP address (32)
| ahi p      # Set base to htons(port) (3)
| ahi S      # Set base to syscall (80)
| ahi s      # Set base to string (1)

Set base of the N-th immediate (indexing starts from 0):
| ahi 16 1 # Set base of the 1-st immediate to hexadecimal

[0x00003d54]> pd 2
0x00003d54      0583000000     add eax, 0x83
0x00003d59      3d13010000     cmp eax, 0x113
[0x00003d54]> ahi d
[0x00003d54]> pd 2
0x00003d54      0583000000     add eax, 131
0x00003d59      3d13010000     cmp eax, 0x113
[0x00003d54]> ahi b
[0x00003d54]> pd 2
0x00003d54      0583000000     add eax, 10000011b
0x00003d59      3d13010000     cmp eax, 0x113
```

It is notable that some analysis stages or commands add the internal analysis hints,
which can be checked with `ah` command:

```
[0x00003d54]> ah
 0x00003d54 - 0x00003d54 => immbase=2
[0x00003d54]> ah*
 ahi 2 @ 0x3d54
```

Sometimes we need to override jump or call address, for example in case of tricky
relocation, which is unknown for Rizin, thus we can change the value manually.
The current analysis information about a particular opcode can be checked with `ao` command.
We can use `ahc` command for performing such a change:

```
[0x00003cee]> pd 2
0x00003cee      e83d080100     call sub.__errno_location_530
0x00003cf3      85c0           test eax, eax
[0x00003cee]> ao
address: 0x3cee
opcode: call 0x14530
mnemonic: call
prefix: 0
id: 56
bytes: e83d080100
refptr: 0
size: 5
sign: false
type: call
cycles: 3
esil: 83248,rip,8,rsp,-=,rsp,=[],rip,=
jump: 0x00014530
direction: exec
fail: 0x00003cf3
stack: null
family: cpu
stackop: null
[0x00003cee]> ahc 0x5382
[0x00003cee]> pd 2
0x00003cee      e83d080100     call sub.__errno_location_530
0x00003cf3      85c0           test eax, eax
[0x00003cee]> ao
address: 0x3cee
opcode: call 0x14530
mnemonic: call
prefix: 0
id: 56
bytes: e83d080100
refptr: 0
size: 5
sign: false
type: call
cycles: 3
esil: 83248,rip,8,rsp,-=,rsp,=[],rip,=
jump: 0x00005382
direction: exec
fail: 0x00003cf3
stack: null
family: cpu
stackop: null
[0x00003cee]> ah
 0x00003cee - 0x00003cee => jump: 0x5382
```

As you can see, despite the unchanged disassembly view the jump address in opcode was changed
(`jump` option).

If anything of the previously described didn't help, you can simply override shown disassembly with anything you
like:

```
[0x00003d54]> pd 2
0x00003d54      0583000000     add eax, 10000011b
0x00003d59      3d13010000     cmp eax, 0x113
[0x00003d54]> "ahd myopcode bla, foo"
[0x00003d54]> pd 2
0x00003d54                     myopcode bla, foo
0x00003d55      830000         add dword [rax], 0
```
