# Registers

The registers are part of a user area stored in the context structure used by the scheduler. This structure can be
manipulated to get and set the values of those registers, and, for example, on Intel hosts, it is possible to
directly manipulate DR0-DR7 hardware registers to set hardware breakpoints.

There are different commands to get values of registers. For the General Purpose ones use:

```
[0x55ca0f427100]> dr
rax = 0x0000000000000038
rbx = 0x0000000000000000
rcx = 0x00007fff03855298
rdx = 0x00007f52c4ae4080
r8 = 0x0000000000000000
r9 = 0x00000000000007f8
r10 = 0x00007fff03855190
r11 = 0x0000000000000206
r12 = 0x000055ca0f427100
r13 = 0x00007fff03855280
r14 = 0x0000000000000000
r15 = 0x0000000000000000
rsi = 0x00007f52c4b148b8
rdi = 0x00007f52c4b142e0
rsp = 0x00007fff03855280
rbp = 0x0000000000000000
rip = 0x000055ca0f427100
cs = 0x0000000000000033
rflags = 0x0000000000000206
orax = 0xffffffffffffffff
ss = 0x000000000000002b
fs = 0x00007f52c48c5740
gs = 0x0000000000000000
ds = 0x0000000000000000
es = 0x0000000000000000
fs_base = 0x0000000000000000
gs_base = 0x0000000000000000

[0x55ca0f427100]> dr rip ; get value of 'rip'
rip = 0x000055ca0f427100 

[0x4A13B8C0]> dr rip = esp   ; set 'rip' as esp
```

Interaction between a plugin and the core is done by commands returning Rizin instructions. This is used, for example,
to set flags in the core to set  values of registers.

```
[0x55ca0f427100]> dr* ; Appending '*' will show rizin commands
ar rax = 0x0000000000000038
ar rbx = 0x0000000000000000
ar rcx = 0x00007fff03855298
ar rdx = 0x00007f52c4ae4080
ar r8 = 0x0000000000000000
ar r9 = 0x00000000000007f8
ar r10 = 0x00007fff03855190
ar r11 = 0x0000000000000206
ar r12 = 0x000055ca0f427100
ar r13 = 0x00007fff03855280
ar r14 = 0x0000000000000000
ar r15 = 0x0000000000000000
ar rsi = 0x00007f52c4b148b8
ar rdi = 0x00007f52c4b142e0
ar rsp = 0x00007fff03855280
ar rbp = 0x0000000000000000
ar rip = 0x000055ca0f427100
ar cs = 0x0000000000000033
ar rflags = 0x0000000000000206
ar orax = 0xffffffffffffffff
ar ss = 0x000000000000002b
ar fs = 0x00007f52c48c5740
ar gs = 0x0000000000000000
ar ds = 0x0000000000000000
ar es = 0x0000000000000000
ar fs_base = 0x0000000000000000
ar gs_base = 0x0000000000000000
```

An old copy of registers is stored all the time to keep track of the changes done during execution
of a program being analyzed. This old copy can be accessed with `oregs`.

```
[0x55ca0f427100]> dro
rax = 0x0000000000000038
rbx = 0x0000000000000000
rcx = 0x00007fff03855298
rdx = 0x00007f52c4ae4080
r8 = 0x0000000000000000
r9 = 0x00000000000007f8
r10 = 0x00007fff03855190
r11 = 0x0000000000000206
r12 = 0x000055ca0f427100
r13 = 0x00007fff03855280
r14 = 0x0000000000000000
r15 = 0x0000000000000000
rsi = 0x00007f52c4b148b8
rdi = 0x00007f52c4b142e0
rsp = 0x00007fff03855280
rbp = 0x0000000000000000
rip = 0x000055ca0f427101
cs = 0x0000000000000033
rflags = 0x0000000000000206
orax = 0xffffffffffffffff
ss = 0x000000000000002b
fs = 0x00007f52c48c5740
gs = 0x0000000000000000
ds = 0x0000000000000000
es = 0x0000000000000000
fs_base = 0x0000000000000000
gs_base = 0x0000000000000000
```
Current state of registers

```
[0x55ca0f427100]> dr
rax = 0x0000000000000038
rbx = 0x0000000000000000
rcx = 0x00007fff03855298
rdx = 0x00007f52c4ae4080
r8 = 0x0000000000000000
r9 = 0x00000000000007f8
r10 = 0x00007fff03855190
r11 = 0x0000000000000206
r12 = 0x000055ca0f427100
r13 = 0x00007fff03855280
r14 = 0x0000000000000000
r15 = 0x0000000000000000
rsi = 0x00007f52c4b148b8
rdi = 0x00007f52c4b142e0
rsp = 0x00007fff03855280
rbp = 0x0000000000000000
rip = 0x000055ca0f427100
cs = 0x0000000000000033
rflags = 0x0000000000000206
orax = 0xffffffffffffffff
ss = 0x000000000000002b
fs = 0x00007f52c48c5740
gs = 0x0000000000000000
ds = 0x0000000000000000
es = 0x0000000000000000
fs_base = 0x0000000000000000
gs_base = 0x0000000000000000
```

Value stored in rip have changed.

To store and restore register values you can just dump the output of 'dr*' command to disk and then
re-interpret it again:

```
[0x55ca0f427100]> dr* > regs.saved ; save registers
[0x55ca0f427100]> drp regs.saved ; restore
```

EFLAGS can be similarly altered. E.g., setting selected flags:

```
[0x55ca0f427100]> dr eflags = pst
[0x55ca0f427100]> dr eflags = azsti
```

You can get a string which represents latest changes of registers using `drd` command (diff registers):

```
[0x4A13B8C0]> drd
rip = 0x55ca0f427100 was 0x55ca0f427101 delta 0xffffffffffffffff
```
