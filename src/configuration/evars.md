## Configuration Variables

Below is a list of the most frequently used configuration variables. You can get a complete list by issuing `e` command without arguments. For example, to see all variables defined in the "cfg" namespace, issue `e cfg.` (mind the ending dot). You can get help on any eval configuration variable by using `el cfg.`

The `el` command to get help on all the evaluable configuration variables of rizin. As long as the output of this command is pretty large you can combine it with the internal grep `~` to filter for what you are looking for:

```
[0x00000000]> el~color
      graph.gv.graph: Graphviz global style attributes. (bgcolor=white)
       graph.gv.node: Graphviz node style. (color=gray, style=filled shape=box)
          log.colors: Should the log output use colors (TODO)
           scr.color: Enable colors (0: none, 1: ansi, 2: 256 colors, 3: truecolor)
      scr.color.args: Colorize arguments and variables of functions
     scr.color.bytes: Colorize bytes that represent the opcodes of the instruction
      scr.color.grep: Enable colors when using ~grep
       scr.color.ops: Colorize numbers and registers in opcodes
      scr.color.pipe: Enable colors when using pipes
     scr.prompt.mode: Set prompt color based on vi mode
         scr.rainbow: Shows rainbow colors depending of address
         scr.randpal: Random color palete or just get the next one from 'eco'
```

The Visual mode has an eval browser that is accessible through the `Vbe` command.

## Assembly Configuration

### asm.arch: `string`

Defines the target CPU architecture used for disassembling (`pd`, `pD` commands) and code analysis (`a` command). You can find the list of possible values by looking at the result of `e asm.arch=?` or `rz-asm -L`.
It is quite simple to add new architectures for disassembling and analyzing code. There is an interface for that. For x86, it is used to attach a number of third-party disassembler engines, including GNU binutils, Udis86 and a few handmade ones.

### asm.bits: `int`

Determines width in bits of registers for the current architecture.
Supported values:

* 8
* 16
* 32
* 64

Note that not all target architectures support all combinations for asm.bits.

### asm.bytes: `bool`

Show or hide displaying of raw bytes of instructions. By default, it is turned off, resulting in a disassembly like:

```
[0x00005b20]> e asm.bytes
false
[0x00005b20]> pd 5
            0x00005b20      endbr64
            0x00005b24      xor   ebp, ebp
            0x00005b26      mov   r9, rdx
            0x00005b29      pop   rsi
            0x00005b2a      mov   rdx, rsp
```
When turned on, the raw bytes will be displayed along with the instructions:
```
[0x00005b20]> e asm.bytes=true
[0x00005b20]> pd 5
            ;-- entry0:
            ;-- rip:
            0x00005b20      f30f1efa       endbr64
            0x00005b24      31ed           xor   ebp, ebp
            0x00005b26      4989d1         mov   r9, rdx
            0x00005b29      5e             pop   rsi
            0x00005b2a      4889e2         mov   rdx, rsp
```

### asm.cpu: `string`

You can use this configuration variable to define the CPU type. For example, if you had picked the architecture as AVR, you can choose your CPU type (ATmega1281, ATmega2561, etc) using `asm.cpu`.

### asm.flags: `bool`

When set to "true", the disassembler view will have the flags column.

### asm.fcn.size: `bool`

This variable is used to display the size of the function in the disassembly. By default, it is set to false and turning it on would result in a disassembly like the one below:

```
┌ 44: int main (char **argv);
│           ; var int32_t var_4h @ ebp-0x4
│           ; arg char **argv @ esp+0x24
│           0x000011cd      lea   ecx, [argv]
│           0x000011d1      and   esp, 0xfffffff0
```
Here, `44` is the size of the function.

### asm.lines.call: `bool`

If set to "true", draw lines at the left of the disassembly output (`pd`, `pD` commands) to graphically represent control flow changes (jumps and calls) that are targeted inside the current block. Also, see `asm.lines.out`.

### asm.lines.out: `bool`

When set to "true", the disassembly view will also draw control flow lines that go outside of the block.

### asm.offset: `bool`

Show or hide offsets for individual disassembled instructions.

### asm.os: `string`

Selects a target operating system for the currently loaded binary. Usually, OS is automatically detected by Rizin (`rz-bin -rI`). Yet, `asm.os` can be used to switch to a different syscall table employed by another OS.

### asm.pseudo: `bool`

A boolean value to set the psuedo syntax in the disassembly. "False" indicates a native one, defined by the current architecture, "true" activates a pseudocode strings format. For example, it'll transform :

```
│           0x080483ff      e832000000     call 0x8048436
│           0x08048404      31c0           xor eax, eax
│           0x08048406      0205849a0408   add al, byte [0x8049a84]
│           0x0804840c      83f800         cmp eax, 0
│           0x0804840f      7405           je 0x8048416
```
to

```
│           0x080483ff      e832000000     0x8048436 ()
│           0x08048404      31c0           eax = 0
│           0x08048406      0205849a0408   al += byte [0x8049a84]
│           0x0804840c      83f800         var = eax - 0
│           0x0804840f      7405           if (!var) goto 0x8048416
```
It can be useful while disassembling obscure architectures.

### asm.sub.jmp: `bool`

Substitute jump, call and branch targets with function names in the disassembly.

For example, when turned on, it'd display `jal 0x80001a40` as `jal fcn.80001a40` in the disassembly.

### asm.sub.reg: `bool`

Replace register names with arguments or their associated role alias.

For example, if you have something like this:

```
│           0x080483ea      83c404         add esp, 4
│           0x080483ed      68989a0408     push 0x8049a98
│           0x080483f7      e870060000     call sym.imp.scanf
│           0x080483fc      83c408         add esp, 8
│           0x08048404      31c0           xor eax, eax
```
This variable changes it to:
```
│           0x080483ea      83c404         add SP, 4
│           0x080483ed      68989a0408     push 0x8049a98
│           0x080483f7      e870060000     call sym.imp.scanf
│           0x080483fc      83c408         add SP, 8
│           0x08048404      31c0           xor A0, A0
```

### asm.sub.rel: `bool`

A boolean value that substitutes expressions relative to the Program Counter in the disassembly. When turned on, it shows the references as string references.

For example:

```
0x5563844a0181      488d3d7c0e00.  lea rdi, [rip + 0xe7c]    ; str.argv__2d_:__s
```
When turned on, this variable lets you display the above instruction as:

```
0x5563844a0181      488d3d7c0e00.  lea rdi, str.argv__2d_:__s    ; 0x5563844a1004 ; "argv[%2d]: %s\n"
```

### asm.sub.section: `bool`

Prefix offsets in the disassembly with the name of the section or map.

That means, from something like:

```
0x000067ea      488d0def0c01.  lea rcx, [0x000174e0]
```
to the one below, when toggled on.
```
0x000067ea      488d0def0c01.  lea rcx, [fmap.LOAD1.0x000174e0]
```

### asm.sub.varonly: `bool`

Substitutes the variable expression with the local variable name.

For example: `var_14h` as `rbp - var_14h`, in the disassembly.

### asm.syntax: `string`

Changes syntax flavor for disassembler between Intel and AT&T. At the moment, this setting affects Udis86 disassembler for Intel 32/Intel 64 targets only. Supported values are `intel` and `att`.

### asm.tabs: `int`

If your disassembly doesn't fit in your screen or aligns clumsily, `asm.tabs` might be of help. You can use this variable to control the distance between the operands, by setting the number of spaces, while displaying your disassembly.

For example, this is the disassembly with the variable set to 0:
```
[0x000040a7]> e asm.tabs=0
[0x000040a7]> pd 6
│           0x000040a7      push rsp
│           0x000040a8      mov r12d, edi                              ; argc
│           0x000040ab      push rbp
│           0x000040ac      mov rbp, rsi                               ; argv
│           0x000040af      push rbx
│           0x000040b0      sub rsp, 0x48
```
And here's what it would look like after setting it to 6:
```
[0x000040a7]> e asm.tabs=6
[0x000040a7]> pd 6
│           0x000040a7      push  rsp
│           0x000040a8      mov   r12d, edi                            ; argc
│           0x000040ab      push  rbp
│           0x000040ac      mov   rbp,  rsi                            ; argv
│           0x000040af      push  rbx
│           0x000040b0      sub   rsp,  0x48
```

### asm.tabs.once: `bool`

This is a boolean variable that can be set to true if you want to align only the opcodes, excluding the arguments. This makes sense only if you have set `asm.tabs` on.

```
[0x00008290]> e asm.tabs=6
[0x00008290]> e asm.tabs.once=false
[0x00008290]> pd 10
│           0x00008290      mov   ip,   sp
│           0x00008294      push  {r4,  fp,   ip,   lr,   pc}
│           0x00008298      sub   fp,   ip,   4
│           0x0000829c      sub   sp,   sp,   0x24
│           0x000082a0      str   r0,   [fp,  -0x28]
│           0x000082a4      str   r1,   [fp,  -0x2c]
│           0x000082a8      ldr   r3,   [fp,  -0x28]
│           0x000082ac      cmp   r3,   1
│       ┌─< 0x000082b0      bgt   0x82c0
│       │   0x000082b4      mvn   r3,   0
```
In the above example, the opcodes and the operands are aligned. Now, turning it on would align only the opcodes.
```
[0x00008290]> e asm.tabs.once=true
[0x00008290]> pd 10
│           0x00008290      mov   ip, sp
│           0x00008294      push  {r4, fp, ip, lr, pc}
│           0x00008298      sub   fp, ip, 4
│           0x0000829c      sub   sp, sp, 0x24
│           0x000082a0      str   r0, [var_28h]
│           0x000082a4      str   r1, [var_2ch]
│           0x000082a8      ldr   r3, [var_28h]
│           0x000082ac      cmp   r3, 1
│       ┌─< 0x000082b0      bgt   0x82c0
│       │   0x000082b4      mvn   r3, 0
```

### asm.trace: `bool`

A boolean value that controls displaying of tracing information (sequence number and counter) at the left of each opcode. It is used to assist with programs trace analysis.

## Screen Configuration

### scr.color: `int`

This variable specifies the mode for colorized screen output.

* 0 means no colors.
* 1 means 16-colors mode.
* 2 means 256-colors mode.
* 3 means 16 million-colors mode.

If your favorite theme looks weird, try to bump this up.

### scr.seek: `string`

This variable accepts a full-featured expression or a pointer/flag (eg. eip). If set, rizin will set seek position to its value on startup.

### scr.scrollbar: `bool`

If you have set up any [flagzones](http://book.rada.re/basic_commands/flags.html#flag-zones) (`fz?`), this variable will let you display the scrollbar with the flagzones, in Visual mode. Set it to `1` to display the scrollbar at the right end, `2` for the top and `3` to display it at the bottom.

### scr.utf8: `bool`

Show UTF-8 characters instead of ANSI.

### scr.utf8.curvy: `bool`

This variable lets you display curved corners in places like function graphs. This variable requires `scr.utf8` to be turned on.

```
[0x0000415c]> pd 4
│           0x0000415c      cmp   eax, 2
│       ┌─< 0x0000415f      je    0x5001
│       │   0x00004165      cmp   eax, 3
│      ┌──< 0x00004168      jne   0x4348
[0x0000415c]> e scr.utf8.curvy=1
[0x0000415c]> pd 4
│           0x0000415c      cmp   eax, 2
│       ╭─< 0x0000415f      je    0x5001
│       │   0x00004165      cmp   eax, 3
│      ╭──< 0x00004168      jne   0x4348
```

### scr.wheel: `bool`

This variable lets you enable the mouse in Visual mode. Turning this variable on will be useful when you want to use your mouse to scroll through your disassembly or copy something in the Visual mode.

## General Configuration

### cfg.bigendian: `bool`

Change endianness. "true" means big-endian, "false" is for little-endian.
"file.id" and "file.flag" both to be true.

### cfg.fortunes: `bool`

Enables or disables "fortune" messages displayed at each rizin start.

### cfg.fortunes.file: `string`

Rizin has two types for fortunes: tips and fun. Fortunes of the type 'tips' are general tips to help you use Rizin better, whereas the other one prints some lighthearted jokes. You can choose which type of fortune to display, using this variable.

```
[0x00000000]> e cfg.fortunes.file=tips
[0x00000000]> fo
 -- Bindiff two files with '$ rz_diff /bin/true /bin/false'
[0x00000000]> e cfg.fortunes.file=fun
[0x00000000]> fo
 -- Welcome to "IDA - the roguelike"
[0x00000000]>
```
Rizin also supports custom fortunes. You can save your fortunes in a file and provide the relative or absolute path to the same variable, to have them displayed at the startup.

```
[0x00000000]> e cfg.fortunes.file=/path/to/my/fortunes.txt
```

Please make sure that you add these in your `~/.rizinrc` to preserve the changes when you reopen rizin.

### cfg.newtab: `bool`

If this variable is enabled, help messages will be displayed along with command names in tab completion for commands.

## Stack Configuration

### stack.size: `int`

This variable lets you set the size of stack in bytes.

## Command Configuration

## cmd.repeat: `bool`

Sometimes, you may need to run the same commmand repeatedly and that is what `cmd.repeat` is for. When set to `true`, pressing Return key (Enter key) will run the previous command again.

For example:
```
[0x00005bc0]> e cmd.repeat=true
[0x00005bc0]> pd 2
            ;-- entry.fini0:
            0x00005bc0      endbr64
            0x00005bc4      cmp   byte [0x000232c8], 0
```
When turned on, you'd just need to press Enter key to run `pd 2`
```
[0x00005bc0]>
            0x00005bce      cmp   qword [reloc.__cxa_finalize], 0
            0x00005bd6      mov   rbp, rsp
```
