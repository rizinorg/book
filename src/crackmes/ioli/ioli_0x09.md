# IOLI 0x09

And that brings us onto the last crackme.

We can also use `rz-diff` to check for string differences.

```
$ rz-diff -t strings crackme0x08 crackme0x09
--- crackme0x08
+++ ./crackme0x09
@@ -1,4 +1,4 @@
-IOLI Crackme Level 0x08

+IOLI Crackme Level 0x09

 Password Incorrect!

 Password OK!

 Password: 
```

The only change is the version info (from 0x08 to 0x09). So let's check for functions.

```
$ rz-diff -t functions crackme0x08 ./crackme0x09
.--------------------------------------------------------------------------------------------------------------------------.
| name0                      | size0 | addr0      | type     | similarity | addr1      | size1 | name1                     |
)--------------------------------------------------------------------------------------------------------------------------(
| sym._init                  | 23    | 0x08048360 | PARTIAL  | 0.826087   | 0x08048388 | 23    | fcn.08048388              |
| sym.imp.__libc_start_main  | 6     | 0x08048388 | COMPLETE | 1.000000   | 0x080483b0 | 6     | sym.imp.__libc_start_main |
| sym.imp.scanf              | 6     | 0x08048398 | COMPLETE | 1.000000   | 0x080483c0 | 6     | sym.imp.scanf             |
| sym.imp.strlen             | 6     | 0x080483a8 | COMPLETE | 1.000000   | 0x080483d0 | 6     | sym.imp.strlen            |
| sym.imp.printf             | 6     | 0x080483b8 | COMPLETE | 1.000000   | 0x080483e0 | 6     | sym.imp.printf            |
| sym.imp.sscanf             | 6     | 0x080483c8 | COMPLETE | 1.000000   | 0x080483f0 | 6     | sym.imp.sscanf            |
| sym.imp.strncmp            | 6     | 0x080483d8 | COMPLETE | 1.000000   | 0x08048400 | 6     | sym.imp.strncmp           |
| sym.imp.exit               | 6     | 0x080483e8 | COMPLETE | 1.000000   | 0x08048410 | 6     | sym.imp.exit              |
| fcn.08048424               | 33    | 0x08048424 | PARTIAL  | 0.939394   | 0x08048444 | 33    | fcn.08048444              |
| sym.__do_global_dtors_aux  | 47    | 0x08048450 | COMPLETE | 1.000000   | 0x08048470 | 47    | fcn.08048470              |
| sym.frame_dummy            | 50    | 0x08048480 | PARTIAL  | 0.940000   | 0x080484a0 | 50    | fcn.080484a0              |
| sym.dummy                  | 112   | 0x080484b4 | PARTIAL  | 0.554745   | 0x080484d4 | 137   | fcn.080484d4              |
| sym.che                    | 30    | 0x08048524 | UNLIKE   | 0.4773     | 0x0804855d | 44    | fcn.0804855d              |
| sym.parell                 | 119   | 0x08048542 | PARTIAL  | 0.581560   | 0x08048589 | 141   | fcn.08048589              |
| sym.check                  | 118   | 0x080485b9 | PARTIAL  | 0.689394   | 0x08048616 | 132   | fcn.08048616              |
| sym.__i686.get_pc_thunk.bx | 4     | 0x08048755 | COMPLETE | 1.000000   | 0x08048766 | 4     | fcn.08048766              |
| sym.__do_global_ctors_aux  | 35    | 0x08048760 | PARTIAL  | 0.942857   | 0x080487f0 | 35    | fcn.080487f0              |
| fcn.0804878d               | 17    | 0x0804878d | PARTIAL  | 0.823529   | 0x0804881d | 17    | fcn.0804881d              |
`--------------------------------------------------------------------------------------------------------------------------'
```

We can see that a few functions have been changed. So let's check it out! We can also see that this
version strips the symbol names again, but that should be no problem. We can easily identify them using the functions diff.

```shell
$ rizin ./crackme0x09
[0x08048420]> aa
[0x08048420]> afr @ main # recursively analyze functions, starting from main
[0x08048420]> afn check @ fcn.08048616
[0x08048420]> afn parell @ fcn.08048589
[0x08048420]> afn che @ fcn.0804855d
[0x08048420]> afn dummy @ fcn.080484d4
[0x08048420]> pdg @ main

// WARNING: Variable defined which should be unmapped: var_8h
// WARNING: [rz-ghidra] Detected overlap for variable var_15h

undefined4 main(undefined4 placeholder_0, undefined4 placeholder_1, char **envp)
{
    int32_t unaff_EBX;
    int32_t var_88h;
    int32_t var_7ch;
    int32_t var_8h;
    
    fcn.08048766();
    sym.imp.printf(unaff_EBX + 0x16c);
    sym.imp.printf(unaff_EBX + 0x185);
    sym.imp.scanf(unaff_EBX + 400, &var_7ch);
    check((int32_t)&var_7ch, (int32_t)envp);
    return 0;
}
```

Looking at `main` we can see some changes: a new function `fcn.08048766` is introduced, and all string addresses have
been replaced by offsets to some base address `unaff_EBX`.

Looking at the functions diff we can see that `fcn.08048766` is named `__i686.get_pc_thunk.bx`. This function is used
in position-independent code to get the addresses of global constants (like string constants). Let's see if we can find
out to which strings these offsets resolve to, but let's first give this new function a name.

```
[0x08048420]> afn sym.__i686.get_pc_thunk.bx @ fcn.08048766
```

To compute the addresses we can use ESIL. But we need to initialize it first.

```
[0x08048420]> s main
[0x080486ee]> aei
[0x080486ee]> aeip
[0x080486ee]> aeim
```

Now we can step through the function, and all pointer arithmetic will be simulated! Open the interactive view
with `v`, and then we can step through using the `s` key to step in and `S` to step over (this also works
when using the debugger).

```bash
[0x080486ee]> v
# opens visual mode
# step through by pressing Shift+S until we hit the instruction
# call instruction to printf()
```

Having landed at the call to `printf` we can now look at what the address in `eax` points to. Exit
visual mode by pressing `q`.


```bash
[0x080486ee]> ar eax
eax = 0x08048869
[0x080486ee]> ps @ 0x08048869
IOLI Crackme Level 0x09
```

We can add this as a comment if we want. This way we don't have to keep doing this ESIL simulation if we forget
what particular string was printed here.

```bash
[0x080486ef]> CC "IOLI Crackme Level 0x09" @ eip
[0x080486ef]> pd 1 @ eip
│           ;-- eip:
│           0x08048722      call  sym.imp.printf                       ; sym.imp.printf ; IOLI Crackme Level 0x09 ; int printf(const char *format)
```

Perfect! Onto the next string. We can skip the call to `printf` with the `aess` command, and then perform two steps using
`aes 2`.

```bash
[0x080486ee]> aess
[0x080486ee]> aes 2
[0x080486ee]> ar eax
eax = 0x08048882
[0x080486ee]> ps @ 0x08048882
Password:
```

We can continue this until we have identified all strings. Or until our curiosity is sated.

Either way, nothing of note has been added or changed in this version, which means that
the password constraints are still the same.

```bash
$ LOL= ./crackme0x09
IOLI Crackme Level 0x09
Password: 12346
Password OK!

$ LOL= ./crackme0x09
IOLI Crackme Level 0x09
Password: 888
Password OK!

$ LD_PRELOAD=./libexit.so LOL= ./crackme0x09
IOLI Crackme Level 0x09
Password: 2
Password Incorrect!
wtf?

$ LD_PRELOAD=./libexit.so LOL= ./crackme0x09
IOLI Crackme Level 0x09
Password: 888
Password OK!
Password Incorrect!
wtf?
```

And that concludes the IOLI crackmes!
