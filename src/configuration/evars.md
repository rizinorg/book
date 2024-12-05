## Evaluable Variables

Rizin incorporates "evaluable variables", which are configuration variables that influence the behavior of analysis, visuals, assembly, and more.

Below you can find a compilation of the most frequently used configuration variables.

Utilize the `el` command to list all the evaluable variables in Rizin. If the output is extensive, you can narrow it down by combining it with the internal grep `~` to filter for specific information or by appending the sub-space after the command, such as `el cfg`.

Example:

```bash
[0x00000000]> el scr.color
           scr.color: Enable colors (0: none, 1: ansi, 2: 256 colors, 3: truecolor)
      scr.color.args: Colorize arguments and variables of functions
     scr.color.bytes: Colorize bytes that represent the opcodes of the instruction
      scr.color.grep: Enable colors when using ~grep
       scr.color.ops: Colorize numbers and registers in opcodes
      scr.color.pipe: Enable colors when using pipes
[0x00000000]> el* scr.color
e scr.color=3
e scr.color.args=true
e scr.color.bytes=true
e scr.color.grep=false
e scr.color.ops=true
e scr.color.pipe=false
[0x00000000]> e scr.color=2
```

## Assembly Configuration

This section provides instructions on altering the behavior of the assembler and disassembler.

### asm.arch: `string`

The `asm.arch` configuration variable establishes the target CPU architecture employed for disassembling (`pd`, `pD` commands) and code analysis (`a` command). The list of potential values can be retrieved by examining the output of `e asm.arch=?` or `rz-asm -L`.

Adding new architectures for disassembling and analyzing code is a straightforward process with a dedicated interface. For x86, this interface facilitates the integration of various third-party disassembler engines, such as GNU binutils, and a selection of custom ones.

### asm.bits: `int`

The `asm.bits` configuration variable dictates the width in bits of registers for the current architecture. The supported values vary depending on the architecture, and you can explore them by using `rz-asm -L` or `e asm.bits=?`.

### asm.bytes: `bool`

When `asm.bytes` is set to `true`, it enables the display of raw bytes of instructions. By default, it is turned off, resulting in a disassembly format like shown below. When activated, the raw bytes will be shown alongside the instructions.

```bash
# you can disable this also via `e asm.bytes=false`
[0x00005fa0]> pd 5 @e:asm.bytes=false
            ;-- entry0:
            0x00005fa0      endbr64
            0x00005fa4      xor   ebp, ebp
            0x00005fa6      mov   r9, rdx
            0x00005fa9      pop   rsi
            0x00005faa      mov   rdx, rsp
# you can enable this also via `e asm.bytes=true`
[0x00005fa0]> pd 5 @e:asm.bytes=true
            ;-- entry0:
            0x00005fa0      f30f1efa       endbr64
            0x00005fa4      31ed           xor   ebp, ebp
            0x00005fa6      4989d1         mov   r9, rdx
            0x00005fa9      5e             pop   rsi
            0x00005faa      4889e2         mov   rdx, rsp
```

### asm.cpu: `string`

The `asm.cpu` configuration variable enables you to specify the CPU type. For example, if you've chosen the architecture as AVR, you can designate your CPU type (e.g., ATmega1281, ATmega2561, etc.) using `asm.cpu`. To view all available CPU types of the selected architecture, you can use the command `e asm.cpu=?`.

### asm.platform: `string`

The `asm.platform` configuration variable allows you to choose the platform, and it will load the corresponding platform profile during analysis. Refer to the section about [CPU and platform profiles](../analysis/cpu_platform_profiles.md) for more information.

### asm.flags: `bool`

When `asm.flags` is set to `true`, the disassembler view will include the flags column.

### asm.fcn.size: `bool`

The `asm.fcn.size` variable is employed to show the size of the function in the disassembly. By default, it is set to false, and enabling it would lead to a disassembly format similar to the one below:

```bash
# you can enable this also via `e asm.fcn.size=true`
[0x00004050]> pd 10 @e:asm.fcn.size=true
            ; DATA XREF from entry0 @ 0x5fb8
/ 7992: int main(int argc, char **argv, char **envp);
| stack: 31 (vars 31, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push  r15
|           0x00004056      push  r14
|           0x00004058      push  r13
|           0x0000405a      push  r12
|           0x0000405c      push  rbp
|           0x0000405d      push  rbx
|           0x0000405e      sub   rsp, 0xf8
|           0x00004065      mov   rbx, qword [rsi]                     ; argv
|           0x00004068      mov   dword [var_118h], edi                ; argc

```
Here, `7992` is the size of the function.

### asm.lines.call: `bool`

When `asm.lines.call` is set to `true`, lines are drawn at the left of the disassembly output (`pd`, `pD` commands). These lines graphically represent control flow changes, such as jumps and calls, that are targeted inside the current block. Also, refer to `asm.lines.out`.

### asm.lines.out: `bool`

When `asm.lines.out` is set to `true`, the disassembly view will draw control flow lines that extend beyond the block.

### asm.offset: `bool`

The `asm.offset` configuration variable determines whether to show or hide offsets for individual disassembled instructions.

### asm.os: `string`

The `asm.os` configuration variable lets you select a target operating system for the currently loaded binary. Typically, the OS is automatically detected by Rizin (command `i` or via `rz-bin -I /path/to/bin`). However, `asm.os` can be employed to switch to a different syscall table used by another OS.

### asm.pseudo: `bool`

The `asm.pseudo` configuration variable is a boolean value used to set the pseudo syntax in the disassembly. When set to `false`, it indicates a native syntax defined by the current architecture. When set to `true`, it activates a pseudocode strings format; this feature can be beneficial when disassembling obscure architectures.

```bash
# you can disable this also via `e asm.pseudo=false`
[0x00100508]> pd 10 @e:asm.pseudo=false
            ;-- _start:
/ entry0(int64_t arg_18h, int64_t arg_8h, int64_t arg_10h, int64_t arg1, int64_t arg2, int64_t arg4, int64_t arg5);
|           ; arg int64_t arg1 @ r3
|           ; arg int64_t arg2 @ r4
|           ; arg int64_t arg4 @ r6
|           ; arg int64_t arg5 @ r7
|           ; var int64_t var_1h @ stack - 0x1
|           ; arg int64_t arg_8h @ stack + 0x8
|           ; arg int64_t arg_10h @ stack + 0x10
|           ; arg int64_t arg_18h @ stack + 0x18
|           0x00100508      lis   r2, 0x1e                             ; start.S:65 ; 0x1e0000
|                                                                      ; sym..iplt
|           0x0010050c      addi  r2, r2, 0x7c00
|           0x00100510      mr    r9, r1                               ; start.S:67
|           0x00100514      rldicr r1, r1, 0, 0x3b                     ; start.S:69
|           0x00100518      li    r0, 0                                ; start.S:70
|           0x0010051c      stdu  r1, -0x80(r1)                        ; start.S:71
|           0x00100520      mtlr  r0                                   ; start.S:72
|           0x00100524      std   r0, 0(r1)                            ; start.S:73
|           0x00100528      ld    r8, -0x7ff0(r2)                      ; start.S:77 ; 0x194c40
|                                                                      ; sym..rodata
|       ,=< 0x0010052c      b     0x101048                             ; start.S:80
# you can enable this also via `e asm.pseudo=true`
[0x00100508]> pd 10 @e:asm.pseudo=true
            ;-- _start:
/ entry0(int64_t arg_18h, int64_t arg_8h, int64_t arg_10h, int64_t arg1, int64_t arg2, int64_t arg4, int64_t arg5);
|           ; arg int64_t arg1 @ r3
|           ; arg int64_t arg2 @ r4
|           ; arg int64_t arg4 @ r6
|           ; arg int64_t arg5 @ r7
|           ; var int64_t var_1h @ stack - 0x1
|           ; arg int64_t arg_8h @ stack + 0x8
|           ; arg int64_t arg_10h @ stack + 0x10
|           ; arg int64_t arg_18h @ stack + 0x18
|           0x00100508      r2 = (0x1e << 16)                          ; start.S:65 ; 0x1e0000
|                                                                      ; sym..iplt
|           0x0010050c      r2 += 0x7c00
|           0x00100510      r9 = r1                                    ; start.S:67
|           0x00100514      r1 = rol64(r1, 0) & 0x1f                   ; start.S:69
|           0x00100518      r0 = 0                                     ; start.S:70
|           0x0010051c      [r1 - 0x80] = r1                           ; start.S:71
|           0x00100520      lr = r0                                    ; start.S:72
|           0x00100524      [r1 + 0] = r0                              ; start.S:73
|           0x00100528      r8 = [r2 - 0x7ff0]                         ; start.S:77 ; 0x194c40
|                                                                      ; sym..rodata
|       ,=< 0x0010052c      goto 0x101048                              ; start.S:80

```

### asm.sub.jmp: `bool`

The `asm.sub.jmp` configuration variable substitutes jump, call, and branch targets with function names in the disassembly. For instance, when activated, it would display `jal 0x80001a40` as `jal fcn.80001a40` in the disassembly.

### asm.sub.reg: `bool`

asm.sub.reg Replace register names with arguments or their associated role alias.

For example, if you have something like this:

```bash
[0x00004050]> pd 4 @e:asm.sub.reg=false
            ; DATA XREF from entry0 @ 0x5fb8
            ; DATA XREF from fcn.00015be0 @ 0x17078
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x0000405d      push  rbx
|           0x0000405e      sub   rsp, 0xf8
|           0x00004065      mov   rbx, qword [rsi]                     ; argv
|           0x00004068      mov   dword [var_118h], edi                ; argc
[0x00004050]> pd 4 @e:asm.sub.reg=true
            ; DATA XREF from entry0 @ 0x5fb8
            ; DATA XREF from fcn.00015be0 @ 0x17078
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x0000405d      push  rbx
|           0x0000405e      sub   SP, 0xf8
|           0x00004065      mov   rbx, qword [A1]                      ; argv
|           0x00004068      mov   dword [var_118h], A0                 ; argc

```

### asm.sub.rel: `bool`

The `asm.sub.rel` configuration variable, when set to true, substitutes expressions relative to the Program Counter in the disassembly. When activated, it displays the references as string references.

```bash
[0x00004050]> pd 30 @e:asm.sub.rel=false ~lea
|     |||   0x000040bb      lea   rsi, [rip + 0x15f51]                 ; str..libs
[0x00004050]> pd 30 @e:asm.sub.rel=true ~lea
|     |||   0x000040bb      lea   rsi, str..libs                       ; 0x1a013 ; "/.libs/" ; const char *s2
```

### asm.sub.section: `bool`

The `asm.sub.section` configuration variable, when set, prefixes offsets in the disassembly with the name of the section or map.

```bash
[0x00004050]> pd 30 @e:asm.sub.rel=false ~lea
0x000067ea      488d0def0c01.  lea rcx, [0x000174e0]
[0x00004050]> pd 30 @e:asm.sub.rel=true ~lea
0x000067ea      488d0def0c01.  lea rcx, [fmap.LOAD1.0x000174e0]
```

### asm.sub.varonly: `bool`

The `asm.sub.varonly` configuration variable, when enabled, substitutes the variable expression with the local variable name. For instance, it would display `var_118h` as `rsp + var_118h` in the disassembly.

```bash
[0x00004050]> pd 10 @e:asm.sub.varonly=false
            ; DATA XREF from entry0 @ 0x5fb8
            ; DATA XREF from fcn.00015be0 @ 0x17078
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push  r15
|           0x00004056      push  r14
|           0x00004058      push  r13
|           0x0000405a      push  r12
|           0x0000405c      push  rbp
|           0x0000405d      push  rbx
|           0x0000405e      sub   rsp, 0xf8
|           0x00004065      mov   rbx, qword [rsi]                     ; argv
|           0x00004068      mov   dword [rsp + var_118h], edi          ; argc
[0x00004050]> pd 10 @e:asm.sub.varonly=true
            ; DATA XREF from entry0 @ 0x5fb8
            ; DATA XREF from fcn.00015be0 @ 0x17078
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push  r15
|           0x00004056      push  r14
|           0x00004058      push  r13
|           0x0000405a      push  r12
|           0x0000405c      push  rbp
|           0x0000405d      push  rbx
|           0x0000405e      sub   rsp, 0xf8
|           0x00004065      mov   rbx, qword [rsi]                     ; argv
|           0x00004068      mov   dword [var_118h], edi                ; argc
```

### asm.syntax: `string`

The `asm.syntax` configuration variable enables you to change the syntax flavor for disassembler syntax. Supported values can be queried using `e asm.syntax=?`.

```bash
[0x00004050]> pd 10 @e:asm.syntax=att
            ; DATA XREF from entry0 @ 0x5fb8
            ; DATA XREF from fcn.00015be0 @ 0x17078
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      pushq %r15
|           0x00004056      pushq %r14
|           0x00004058      pushq %r13
|           0x0000405a      pushq %r12
|           0x0000405c      pushq %rbp
|           0x0000405d      pushq %rbx
|           0x0000405e      subq  $0xf8, %rsp
|           0x00004065      movq  (%rsi), %rbx                         ; argv
|           0x00004068      movl  %edi, var_118h                       ; argc
[0x00004050]> pd 10 @e:asm.syntax=masm
            ; DATA XREF from entry0 @ 0x5fb8
            ; DATA XREF from fcn.00015be0 @ 0x17078
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push  r15
|           0x00004056      push  r14
|           0x00004058      push  r13
|           0x0000405a      push  r12
|           0x0000405c      push  rbp
|           0x0000405d      push  rbx
|           0x0000405e      sub   rsp, 0f8h
|           0x00004065      mov   rbx, qword [rsi]                     ; argv
|           0x00004068      mov   dword [var_118h], edi                ; argc
[0x00004050]> pd 10 @e:asm.syntax=intel
            ; DATA XREF from entry0 @ 0x5fb8
            ; DATA XREF from fcn.00015be0 @ 0x17078
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push  r15
|           0x00004056      push  r14
|           0x00004058      push  r13
|           0x0000405a      push  r12
|           0x0000405c      push  rbp
|           0x0000405d      push  rbx
|           0x0000405e      sub   rsp, 0xf8
|           0x00004065      mov   rbx, qword [rsi]                     ; argv
|           0x00004068      mov   dword [var_118h], edi                ; argc
```

### asm.tabs: `int`

If the disassembly output doesn't fit on your screen or appears awkwardly aligned, `asm.tabs` can be helpful. You can adjust the spacing between operands by setting the number of spaces while displaying your disassembly using this variable.

For example:

```bash
[0x00004050]> pd 10 @e:asm.tabs=0
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push r15
|           0x00004056      push r14
|           0x00004058      push r13
|           0x0000405a      push r12
|           0x0000405c      push rbp
|           0x0000405d      push rbx
|           0x0000405e      sub rsp, 0xf8
|           0x00004065      mov rbx, qword [rsi]                       ; argv
|           0x00004068      mov dword [var_118h], edi                  ; argc
[0x00004050]> pd 10 @e:asm.tabs=6
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push  r15
|           0x00004056      push  r14
|           0x00004058      push  r13
|           0x0000405a      push  r12
|           0x0000405c      push  rbp
|           0x0000405d      push  rbx
|           0x0000405e      sub   rsp, 0xf8
|           0x00004065      mov   rbx, qword [rsi]                     ; argv
|           0x00004068      mov   dword [var_118h], edi                ; argc

```

### asm.tabs.once: `bool`

`asm.tabs.once` represents a boolean variable, which can be configured as true if the alignment is desired solely for opcodes, omitting the arguments. This configuration is meaningful only when `asm.tabs` has been previously enabled.

```bash
[0x00004050]> pd 10 @e:asm.tabs=10 @e:asm.tabs.once=false
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push      r15
|           0x00004056      push      r14
|           0x00004058      push      r13
|           0x0000405a      push      r12
|           0x0000405c      push      rbp
|           0x0000405d      push      rbx
|           0x0000405e      sub       rsp,      0xf8
|           0x00004065      mov       rbx,      qword [rsi]            ; argv
|           0x00004068      mov       dword [var_118h], edi            ; argc
[0x00004050]> pd 10 @e:asm.tabs=10 @e:asm.tabs.once=true
/ int main(int argc, char **argv, char **envp);
| stack: 29 (vars 29, args 0)
| rg: 2 (vars 0, args 2)
|           0x00004050      endbr64
|           0x00004054      push      r15
|           0x00004056      push      r14
|           0x00004058      push      r13
|           0x0000405a      push      r12
|           0x0000405c      push      rbp
|           0x0000405d      push      rbx
|           0x0000405e      sub       rsp, 0xf8
|           0x00004065      mov       rbx, qword [rsi]                 ; argv
|           0x00004068      mov       dword [var_118h], edi            ; argc

```

### asm.trace: `bool`

`asm.trace` is a boolean parameter governing the display of tracing details (sequence number and counter) adjacent to each opcode. Its purpose is to aid in the analysis of program traces.

## Debug Configuration

### dbg.follow.child: `bool`

The variable `dbg.follow.child` allows tracking the child process when encountering a fork (system call) during debugging. Its default setting is `false`, causing the parent process to be traced.

## Screen Configuration

### scr.color: `int`

The variable `scr.color` designates the mode for displaying colorized output on the screen.

* `0` no colors (black and white)
* `1` ANSI colors (16 basic ANSI colors)
* `2` 256 colors (256 scale colors)
* `3` truecolor (24bit true color)

### scr.visual.mode: `int`

The variable `scr.visual.mode` enables the configuration of a default view for the visual mode. This variable accepts an integer value, which corresponds to the following modes:

* `0` - Hexadecimal view
* `1` - Disassembly view
* `2` - Debug mode
* `3` - Color blocks (entropy)
* `4` - Print in string format

For instance, if you prefer the disassembly view every time you initiate visual mode, you can include `e scr.visual.mode=1` in your `rizinrc` [initial script](initial_scripts.md).

### scr.seek: `string`

The variable `scr.seek` can be assigned a full-featured expression or a pointer/flag (e.g., `eip`). When configured, Rizin will initialize the seek position to the specified value upon startup.

### scr.scrollbar: `bool`

When you have configured any [flagzones](../basic_commands/flags.html#flag-zones) (`fz?`), the `scr.scrollbar` variable facilitates the display of the scrollbar alongside the flagzones in Visual mode. Set it to `1` for displaying the scrollbar at the right end, `2` for the top, and `3` to position it at the bottom.

### scr.utf8: `bool`

The variable `scr.utf8` toggles the display of UTF-8 characters instead of ANSI characters.

### scr.utf8.curvy: `bool`

The `scr.utf8.curvy` variable enables the presentation of curved corners in locations such as function graphs. It is dependent on having the `scr.utf8` setting activated.

```bash
[0x0000415c]> pd 4
│           0x0000415c      cmp   eax, 2
│       ┌─< 0x0000415f      je    0x5001
│       │   0x00004165      cmp   eax, 3
│      ┌──< 0x00004168      jne   0x4348
[0x0000415c]> e scr.utf8.curvy=true
[0x0000415c]> pd 4
│           0x0000415c      cmp   eax, 2
│       ╭─< 0x0000415f      je    0x5001
│       │   0x00004165      cmp   eax, 3
│      ╭──< 0x00004168      jne   0x4348
```

### scr.wheel: `bool`

The `scr.wheel` variable permits the activation of the mouse in Visual mode. Enabling this variable proves beneficial when you wish to utilize your mouse for scrolling through disassembly or copying content in Visual mode.

## General Configuration

### cfg.bigendian: `bool`

The `cfg.bigendian` setting alters the endianness, where "true" indicates big-endian, and "false" corresponds to little-endian.

### cfg.fortunes: `bool`

The `cfg.fortunes` option allows you to enable or disable the display of "fortune" messages that appear at each Rizin start.

### cfg.fortunes.file: `string`

Rizin offers two categories of fortunes: `tips` and `fun`. Fortunes categorized as `tips` provide general advice to enhance your usage of Rizin, while the other category offers lighthearted jokes. You can specify the type of fortune to display by utilizing the `cfg.fortunes.file` variable.

```bash
[0x00000000]> fortune @e:cfg.fortunes.file=tips
 -- Interpret rizin scripts with '. <path-to-script>'. Similar to the bash source alias command.
[0x00000000]> fortune @e:cfg.fortunes.file=fun
 -- For a full list of commands see `strings /dev/urandom`
[0x00000000]>
```

Rizin additionally supports custom fortunes. You can store your own fortunes in a file and then specify the relative or absolute path to that file using the same variable. This allows your custom fortunes to be displayed at startup.

```bash
[0x00000000]> fortune @e:cfg.fortunes.file=/path/to/my/fortunes.txt
```

Ensure to include these configurations in your `rizinrc` file to retain the changes when reopening Rizin.

### cfg.newtab: `bool`

Enabling the `cfg.newtab` variable results in the display of help messages alongside command names during tab completion for commands.

## Stack Configuration

### stack.size: `int`

The `stack.size` variable allows you to define the size of the stack hexdump in visual debug, specified in bytes.

## Command Configuration

## cmd.repeat: `bool`

At times, you might find the need to execute a particular command repeatedly, and that's where `cmd.repeat` comes into play. When configured as `true`, pressing the Return key (Enter key) will rerun the previous command. This may alter the current offset.

For example:
```bash
[0x00005bc0]> e cmd.repeat=true
[0x00005bc0]> pd 2
            ;-- entry.fini0:
            0x00005bc0      endbr64
            0x00005bc4      cmp   byte [0x000232c8], 0
[0x00005bc4]>
            0x00005bce      cmp   qword [reloc.__cxa_finalize], 0
            0x00005bd6      mov   rbp, rsp
[0x00005bd6]>
```
