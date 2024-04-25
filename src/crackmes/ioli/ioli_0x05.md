IOLI 0x05
=========

This is the sixth crackme.

```
$ rz-bin -z ./crackme0x05
[Strings]
nth paddr      vaddr      len size section type  string                    
---------------------------------------------------------------------------
0   0x0000066b 0x0804866b 13  14   .rodata ascii Password OK!\n
1   0x00000679 0x08048679 20  21   .rodata ascii Password Incorrect!\n
2   0x0000068e 0x0804868e 24  25   .rodata ascii IOLI Crackme Level 0x05\n
3   0x000006a7 0x080486a7 10  11   .rodata ascii Password: 
```

No interesting strings, so let's analyze.

```c
[0x080483d0]> aa
[0x080483d0]> pdg @ main

// WARNING: [rz-ghidra] Detected overlap for variable var_11h

undefined4 main(void)
{
    int32_t var_88h;
    int32_t var_7ch;
    
    sym.imp.printf("IOLI Crackme Level 0x05\n");
    sym.imp.printf("Password: ");
    sym.imp.scanf(0x80486b2, &var_7ch);
    sym.check((int32_t)&var_7ch);
    return 0;
}
[0x080483d0]> ps @ 0x80486b2
%s
```

We can see the same structure is used again: a string is read by `scanf` and is passed to `check`.

```c
[0x080483d0]> pdg @ sym.check

// WARNING: Variable defined which should be unmapped: var_28h
// WARNING: Variable defined which should be unmapped: var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_11h

void sym.check(int32_t arg_4h)
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
        sym.imp.sscanf(&var_11h, 0x8048668, &var_8h);
        var_ch = var_ch + var_8h;
        if (var_ch == 0x10) {
            sym.parell(arg_4h);
        }
        var_10h = var_10h + 1;
    }
    sym.imp.printf("Password Incorrect!\n");
    return;
}
[0x080483d0]> ps @ 0x8048668 @! 2
%d
```

We can see that `check` is mostly the same, except that this time the digit sum has to equal 16 (0x10), after
which a function named `parell` is called.

```c
[0x080483d0]> pdg @ sym.parell

// WARNING: Variable defined which should be unmapped: var_18h
// WARNING: Variable defined which should be unmapped: var_14h

void sym.parell(int32_t arg_4h)
{
    int32_t var_18h;
    int32_t var_14h;
    int32_t var_8h;
    
    sym.imp.sscanf(arg_4h, 0x8048668, &var_8h);
    if ((var_8h & 1U) == 0) {
        sym.imp.printf("Password OK!\n");
        sym.imp.exit(0);
    }
    return;
}
[0x080483d0]> ps @ 0x8048668 @! 2
%d
```

We can see here that the function `parell` takes a string, converts it to an integer and performs a parity
check on it `(var_8h & 1U) == 0`. In this case the least significant bit has to be 0, which means the number
has to be even.

```bash
$ ./crackme0x05
IOLI Crackme Level 0x05
Password: 88
Password OK!

$ ./crackme0x05
IOLI Crackme Level 0x05
Password: 12346
Password OK!
```

And our trick from the previous crackme works as well.

```bash
$ ./crackme0x05
IOLI Crackme Level 0x05
Password: 4asdf
Password OK!

$ ./crackme0x05
IOLI Crackme Level 0x05
Password: 0this-doesnt-count4this-does
Password OK!
```
