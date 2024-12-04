# IOLI 0x08

Time for the ninth crackme.

```
$ rz-bin -z ./crackme0x08
[Strings]
nth paddr      vaddr      len size section type  string                    
---------------------------------------------------------------------------
0   0x000007a8 0x080487a8 4   5    .rodata ascii LOLO
1   0x000007ad 0x080487ad 20  21   .rodata ascii Password Incorrect!\n
2   0x000007c5 0x080487c5 13  14   .rodata ascii Password OK!\n
3   0x000007d3 0x080487d3 5   6    .rodata ascii wtf?\n
4   0x000007d9 0x080487d9 24  25   .rodata ascii IOLI Crackme Level 0x08\n
5   0x000007f2 0x080487f2 10  11   .rodata ascii Password: 
```

It looks like no new strings have been added. Before we jump into analyzing however, let's first see which functions
have changed from the previous version. We can get a nice overview using `rz-diff`.

```
$ rz-diff -t functions crackme0x07 crackme0x08
.--------------------------------------------------------------------------------------------------------------------------.
| name0                     | size0 | addr0      | type     | similarity | addr1      | size1 | name1                      |
)--------------------------------------------------------------------------------------------------------------------------(
| fcn.08048360              | 23    | 0x08048360 | COMPLETE | 1.000000   | 0x08048360 | 23    | sym._init                  |
| sym.imp.__libc_start_main | 6     | 0x08048388 | COMPLETE | 1.000000   | 0x08048388 | 6     | sym.imp.__libc_start_main  |
| sym.imp.scanf             | 6     | 0x08048398 | COMPLETE | 1.000000   | 0x08048398 | 6     | sym.imp.scanf              |
| sym.imp.strlen            | 6     | 0x080483a8 | COMPLETE | 1.000000   | 0x080483a8 | 6     | sym.imp.strlen             |
| sym.imp.printf            | 6     | 0x080483b8 | COMPLETE | 1.000000   | 0x080483b8 | 6     | sym.imp.printf             |
| sym.imp.sscanf            | 6     | 0x080483c8 | COMPLETE | 1.000000   | 0x080483c8 | 6     | sym.imp.sscanf             |
| sym.imp.strncmp           | 6     | 0x080483d8 | COMPLETE | 1.000000   | 0x080483d8 | 6     | sym.imp.strncmp            |
| sym.imp.exit              | 6     | 0x080483e8 | COMPLETE | 1.000000   | 0x080483e8 | 6     | sym.imp.exit               |
| fcn.08048424              | 33    | 0x08048424 | COMPLETE | 1.000000   | 0x08048424 | 33    | fcn.08048424               |
| fcn.08048450              | 47    | 0x08048450 | COMPLETE | 1.000000   | 0x08048450 | 47    | sym.__do_global_dtors_aux  |
| fcn.08048480              | 50    | 0x08048480 | COMPLETE | 1.000000   | 0x08048480 | 50    | sym.frame_dummy            |
| fcn.080484b4              | 112   | 0x080484b4 | COMPLETE | 1.000000   | 0x080484b4 | 112   | sym.dummy                  |
| fcn.08048524              | 30    | 0x08048524 | COMPLETE | 1.000000   | 0x08048524 | 30    | sym.che                    |
| fcn.08048542              | 119   | 0x08048542 | COMPLETE | 1.000000   | 0x08048542 | 119   | sym.parell                 |
| fcn.080485b9              | 118   | 0x080485b9 | COMPLETE | 1.000000   | 0x080485b9 | 118   | sym.check                  |
| fcn.08048755              | 4     | 0x08048755 | COMPLETE | 1.000000   | 0x08048755 | 4     | sym.__i686.get_pc_thunk.bx |
| fcn.08048760              | 35    | 0x08048760 | COMPLETE | 1.000000   | 0x08048760 | 35    | sym.__do_global_ctors_aux  |
| fcn.0804878d              | 17    | 0x0804878d | COMPLETE | 1.000000   | 0x0804878d | 17    | fcn.0804878d               |
`--------------------------------------------------------------------------------------------------------------------------'
```

Look at that! crackme0x08 is completely identical to crackme0x07! With one exception however, crackme0x08 *adds* the
symbol names back. Or looking at it another way: crackme0x07 is the stripped version of crackme0x08.

That means we can solve it the exact same way we solved crackme0x07.

```bash
$ LOL= ./crackme0x08
IOLI Crackme Level 0x08
Password: 12346
Password OK!

$ LOL= ./crackme0x08
IOLI Crackme Level 0x08
Password: 88
Password OK!
```

And our `exit` trampoline from the previous version still works as well.

```bash
$ LD_PRELOAD=./libexit.so LOL= ./crackme0x08
IOLI Crackme Level 0x08
Password: 2
Password Incorrect!
wtf?

$ LD_PRELOAD=./libexit.so LOL= ./crackme0x08
IOLI Crackme Level 0x08
Password: 88
Password OK!
Password Incorrect!
wtf?
```
Analyzing the binary, there is not much to discover that we didn't already know. With the exception that `print_and_exit`
is actually called `che`. And the mysterious global variable referenced in `dummy` is called `LOL`.
