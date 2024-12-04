# IOLI 0x06

Onto the seventh crackme.

```
$ rz-bin -z ./crackme0x06
[Strings]
nth paddr      vaddr      len size section type  string                    
---------------------------------------------------------------------------
0   0x00000738 0x08048738 4   5    .rodata ascii LOLO
1   0x00000740 0x08048740 13  14   .rodata ascii Password OK!\n
2   0x0000074e 0x0804874e 20  21   .rodata ascii Password Incorrect!\n
3   0x00000763 0x08048763 24  25   .rodata ascii IOLI Crackme Level 0x06\n
4   0x0000077c 0x0804877c 10  11   .rodata ascii Password: 
```

Doing our routine strings check we can see a new contender: `LOLO`.

```bash
$ ./crackme0x06
IOLI Crackme Level 0x06
Password: LOLO
Password Incorrect!
```

No dice, so let's take a closer look.

```
$ rizin ./crackme0x06
[0x08048400]> aa
[0x08048400]> pdg @ main

// WARNING: [rz-ghidra] Detected overlap for variable var_11h

undefined4 main(undefined4 placeholder_0, undefined4 placeholder_1, char **envp)
{
    int32_t var_88h;
    int32_t var_7ch;
    
    sym.imp.printf("IOLI Crackme Level 0x06\n");
    sym.imp.printf("Password: ");
    sym.imp.scanf(0x8048787, &var_7ch);
    sym.check((int32_t)&var_7ch, (int32_t)envp);
    return 0;
}

[0x08048400]> ps @ 0x8048787
%s
[0x08048400]> afvl @ main
var int32_t var_88h @ stack - 0x88
var int32_t var_7ch @ stack - 0x7c
arg char **envp @ stack + 0xc
```

This looks the same as before, except the program's environment variables `envp` are passed to `check`.

```
[0x08048400]> pdg @ sym.check

// WARNING: Variable defined which should be unmapped: var_28h
// WARNING: Variable defined which should be unmapped: var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_11h

void sym.check(int32_t arg_4h, int32_t arg_8h)
{
    uint32_t uVar1;
    int32_t var_28h;
    int32_t var_24h;
    undefined var_11h;
    int32_t var_10h;
    int32_t var_ch;
    int32_t var_8h;
    
    var_ch = 0;
    var_10h = 0;
    while( true ) {
        uVar1 = sym.imp.strlen(arg_4h);
        if (uVar1 <= (uint32_t)var_10h) break;
        var_11h = *(undefined *)(var_10h + arg_4h);
        sym.imp.sscanf(&var_11h, 0x804873d, &var_8h);
        var_ch = var_ch + var_8h;
        if (var_ch == 0x10) {
            sym.parell(arg_4h, arg_8h);
        }
        var_10h = var_10h + 1;
    }
    sym.imp.printf("Password Incorrect!\n");
    return;
}
```

This looks mostly the same as well. If we follow `envp` (now named `arg_8h`) we can see it gets passed to
`parell`.

```
[0x08048400]> pdg @ sym.parell

// WARNING: Variable defined which should be unmapped: var_18h
// WARNING: Variable defined which should be unmapped: var_14h

void sym.parell(int32_t arg_4h, int32_t arg_8h)
{
    int32_t iVar1;
    int32_t var_18h;
    int32_t var_14h;
    int32_t var_ch;
    int32_t var_8h;
    
    sym.imp.sscanf(arg_4h, 0x804873d, &var_8h);
    iVar1 = sym.dummy(var_8h, arg_8h);
    if (iVar1 != 0) {
        for (var_ch = 0; var_ch < 10; var_ch = var_ch + 1) {
            if ((var_8h & 1U) == 0) {
                sym.imp.printf("Password OK!\n");
                sym.imp.exit(0);
            }
        }
    }
    return;
}
```

We can see that the parity check is still in place, except it's now in a loop that executes 10 times, but only
if `dummy()` returns non-zero.

```
[0x08048400]> pdg @ sym.dummy

// WARNING: Variable defined which should be unmapped: var_18h
// WARNING: Variable defined which should be unmapped: var_14h

undefined4 sym.dummy(undefined4 placeholder_0, int32_t arg_8h)
{
    int32_t iVar1;
    int32_t var_18h;
    int32_t var_14h;
    int32_t var_ch;
    int32_t var_8h;
    
    var_8h = 0;
    do {
        if (*(int32_t *)(var_8h * 4 + arg_8h) == 0) {
            return 0;
        }
        iVar1 = var_8h * 4;
        var_8h = var_8h + 1;
        iVar1 = sym.imp.strncmp(*(undefined4 *)(iVar1 + arg_8h), "LOLO", 3);
    } while (iVar1 != 0);
    return 1;
}
```

Living up to its name, `dummy` does not use its first parameter at all, only the second one is used which is the
`envp` parameter from `main`. Apparently some part of `envp` has to equal "LOL" (only the first 3 characters are used
, note the '3' in `strncmp`).

It will be easier to figure out how `dummy` works if we run the code, so let's use the debugger again!

```shell
$ rizin -d ./crackme0x06
[0xf7fb1630]> aa
[0xf7fb1630]> dcu sym.dummy
Continue until 0x080484b4
IOLI Crackme Level 0x06
Password: 88
hit breakpoint at: 0x80484b4
```

Now we should be at the start of `dummy`, let's see where we can place a breakpoint.

```
[0x080484b4]> pdf
            ; CALL XREF from sym.parell @ 0x8048547
            ;-- eip:
/ sym.dummy(int32_t arg_8h);
|           ; var int32_t var_18h @ stack - 0x18
|           ; var int32_t var_14h @ stack - 0x14
|           ; var int32_t var_ch @ stack - 0xc
|           ; var int32_t var_8h @ stack - 0x8
|           ; arg int32_t arg_8h @ stack + 0x8
|           0x080484b4      push  ebp
|           0x080484b5      mov   ebp, esp
|           0x080484b7      sub   esp, 0x18
|           0x080484ba      mov   dword [var_8h], 0
|       .-> 0x080484c1      mov   eax, dword [var_8h]
|       :   0x080484c4      lea   edx, [eax*4]
|       :   0x080484cb      mov   eax, dword [arg_8h]
|       :   0x080484ce      cmp   dword [edx + eax], 0
|      ,==< 0x080484d2      je    0x804850e
|      |:   0x080484d4      mov   eax, dword [var_8h]
|      |:   0x080484d7      lea   ecx, [eax*4]
|      |:   0x080484de      mov   edx, dword [arg_8h]
|      |:   0x080484e1      lea   eax, [var_8h]
|      |:   0x080484e4      inc   dword [eax]
|      |:   0x080484e6      mov   dword [var_14h], 3
|      |:   0x080484ee      mov   dword [var_18h], 0x8048738           ; str.LOLO
|      |:                                                              ; [0x8048738:4]=0x4f4c4f4c ; "LOLO"
|      |:   0x080484f6      mov   eax, dword [ecx + edx]
|      |:   0x080484f9      mov   dword [esp], eax
|      |:   0x080484fc      call  sym.imp.strncmp                      ; sym.imp.strncmp ; int strncmp(const char *s1, const char *s2, size_t n)
|      |:   0x08048501      test  eax, eax
|      |`=< 0x08048503      jne   0x80484c1
|      |    0x08048505      mov   dword [var_ch], 1
|      |,=< 0x0804850c      jmp   0x8048515
|      `--> 0x0804850e      mov   dword [var_ch], 0
|       |   ; CODE XREF from sym.dummy @ 0x804850c
|       `-> 0x08048515      mov   eax, dword [var_ch]
|           0x08048518      leave
\           0x08048519      ret
```


The instruction at `0x080484f9` looks like a good spot. This is just before `strncmp` is called, so we can see
what value is passed to it.

```
[0x08048502]> db @ 0x080484f9
[0x08048502]> dbc 'psi @r:eax' @ 0x080484f9
[0x08048502]> dcr
PWD=/home/rizin
HOME=/home/rizin
USER=rizin
PATH=/usr/local/sbin:/usr/local/bin:/usr/bin
SHELL=/usr/bin/sh
```

Running `dcr` you should be greeted with all the environment variables passed to the program.
From this we can safely conclude that `dummy` is looking for an environment variable starting with "LOL",
so let's try it.

Remember that there are 3 constraints to the password now:

- Digit sum reaches 16 at some point
- The number is even
- An environment variable starting with "LOL" is set


```bash
$ LOL= ./crackme0x06
IOLI Crackme Level 0x06
Password: 88
Password OK!

$ LOL= ./crackme0x06
IOLI Crackme Level 0x06
Password: 12346
Password OK!
```
