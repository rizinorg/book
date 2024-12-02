# IOLI 0x07

Already onto the eighth crackme!

```shell
$ rz-bin -z ./crackme0x07
[Strings]
nth paddr      vaddr      len size section type  string                    
---------------------------------------------------------------------------
0   0x000007a8 0x080487a8 4   5    .rodata ascii LOLO
1   0x000007ad 0x080487ad 20  21   .rodata ascii Password Incorrect!\n
2   0x000007c5 0x080487c5 13  14   .rodata ascii Password OK!\n
3   0x000007d3 0x080487d3 5   6    .rodata ascii wtf?\n
4   0x000007d9 0x080487d9 24  25   .rodata ascii IOLI Crackme Level 0x07\n
5   0x000007f2 0x080487f2 10  11   .rodata ascii Password: 
```

Doing our routine strings check we see another new contender, wtf? Literally.

```
$ rizin ./crackme0x07
[0x08048400]> aa
[0x08048400]> pdg @ main

// WARNING: [rz-ghidra] Detected overlap for variable var_11h

undefined4 main(undefined4 placeholder_0, undefined4 placeholder_1, char **envp)
{
    int32_t var_88h;
    int32_t var_7ch;
    
    sym.imp.printf("IOLI Crackme Level 0x07\n");
    sym.imp.printf("Password: ");
    sym.imp.scanf(0x80487fd, &var_7ch);
    fcn.080485b9((int32_t)&var_7ch, (int32_t)envp);
    return 0;
}
```

Upping the difficulty, `check` is no longer exported so it's now listed as `fcn.080485b9`.
To make our lives a bit easier, let's set the name manually.

```
[0x08048400]> afn check @ fcn.080485b9
[0x08048400]> pdg @ check

// WARNING: Variable defined which should be unmapped: var_28h
// WARNING: Variable defined which should be unmapped: var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_11h

void check(int32_t arg_4h, int32_t arg_8h)
{
    uint32_t uVar1;
    int32_t iVar2;
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
        sym.imp.sscanf(&var_11h, 0x80487c2, &var_8h);
        var_ch = var_ch + var_8h;
        if (var_ch == 0x10) {
            func_0x08048542(arg_4h, arg_8h);
        }
        var_10h = var_10h + 1;
    }
    func_0x08048524();
    iVar2 = func_0x080484b4(var_8h, arg_8h);
    if (iVar2 != 0) {
        for (var_10h = 0; var_10h < 10; var_10h = var_10h + 1) {
            if ((var_8h & 1U) == 0) {
                sym.imp.printf("wtf?\n");
    // WARNING: Subroutine does not return
                sym.imp.exit(0);
            }
        }
    }
    return;
}
```

This looks like the `check` we've seen in previous version except there is now a parity check slapped on the end of it
where the string "wtf?" is printed.

Before we can continue to the other functions, they have to be analyzed first. We can analyze all functions recursively
using `afr`.

```
[0x08048400]> afr @ check
[0x08048400]> pdg @ check

// WARNING: Variable defined which should be unmapped: var_28h
// WARNING: Variable defined which should be unmapped: var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_11h

void check(int32_t arg_4h, int32_t arg_8h)
{
    uint32_t uVar1;
    int32_t iVar2;
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
        sym.imp.sscanf(&var_11h, 0x80487c2, &var_8h);
        var_ch = var_ch + var_8h;
        if (var_ch == 0x10) {
            fcn.08048542(arg_4h, arg_8h);
        }
        var_10h = var_10h + 1;
    }
    fcn.08048524();
    iVar2 = fcn.080484b4(var_8h, arg_8h);
    if (iVar2 != 0) {
        for (var_10h = 0; var_10h < 10; var_10h = var_10h + 1) {
            if ((var_8h & 1U) == 0) {
                sym.imp.printf("wtf?\n");
    // WARNING: Subroutine does not return
                sym.imp.exit(0);
            }
        }
    }
    return;
}
```

The reason we're doing it this way in this case, is because `aaa` will cause some critical information to
be omitted: namely the code that prints `"wtf?"`, more on that later. 

For now though let's first check out `fcn.08048542`. We can probably already guess its identity as the code structure
remains largely unchanged from the previous versions. But it can't hurt to do our due diligence.

```
[0x08048400]> pdg @ fcn.08048542

// WARNING: Variable defined which should be unmapped: var_18h
// WARNING: Variable defined which should be unmapped: var_14h

void fcn.08048542(int32_t arg_4h, int32_t arg_8h)
{
    int32_t iVar1;
    int32_t var_18h;
    int32_t var_14h;
    int32_t var_ch;
    int32_t var_8h;
    
    sym.imp.sscanf(arg_4h, 0x80487c2, &var_8h);
    iVar1 = fcn.080484b4(var_8h, arg_8h);
    if (iVar1 != 0) {
        for (var_ch = 0; var_ch < 10; var_ch = var_ch + 1) {
            if ((var_8h & 1U) == 0) {
                if (*(int32_t *)0x804a02c == 1) {
                    sym.imp.printf("Password OK!\n");
                }
    // WARNING: Subroutine does not return
                sym.imp.exit(0);
            }
        }
    }
    return;
}
```

That does indeed look like `parell` from the previous versions. And that must make `fcn.080484b4` `dummy`. But look,
there's an extra `if` inside the parity check! Apparently some global variable has to be set to `1` in order for
the password to be valid. 

```
[0x08048400]> pdg @ fcn.080484b4

// WARNING: Variable defined which should be unmapped: var_18h
// WARNING: Variable defined which should be unmapped: var_14h

undefined4 fcn.080484b4(undefined4 placeholder_0, int32_t arg_8h)
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
    *(undefined4 *)0x804a02c = 1;
    return 1;
}

[0x08048400]> afn dummy @ fcn.080484b4
[0x08048400]> afn parell @ fcn.08048542
```

And this must be `dummy`... With an addition. Can you spot it? This is where that global variable that we saw earlier
gets set! On the line containing `*(undefined4 *)0x804a02c = 1;`, more specifically.

But before we continue let's see if there are any other references to or from this global variable.

```
[0x08048400]> axf @ 0x804a02c
[0x08048400]> axt @ 0x804a02c
dummy 0x8048505 [DATA] mov dword [0x804a02c], 1
parell 0x804858f [DATA] cmp dword [0x804a02c], 1
```

It doesn't appear to be the case, so let's go back to `check`.

```
[0x08048400]> pdg @ check

// WARNING: Variable defined which should be unmapped: var_28h
// WARNING: Variable defined which should be unmapped: var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_11h

void check(int32_t arg_4h, int32_t arg_8h)
{
    uint32_t uVar1;
    int32_t iVar2;
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
        sym.imp.sscanf(&var_11h, 0x80487c2, &var_8h);
        var_ch = var_ch + var_8h;
        if (var_ch == 0x10) {
            parell(arg_4h, arg_8h);
        }
        var_10h = var_10h + 1;
    }
    fcn.08048524();
    iVar2 = dummy(var_8h, arg_8h);
    if (iVar2 != 0) {
        for (var_10h = 0; var_10h < 10; var_10h = var_10h + 1) {
            if ((var_8h & 1U) == 0) {
                sym.imp.printf("wtf?\n");
    // WARNING: Subroutine does not return
                sym.imp.exit(0);
            }
        }
    }
    return;
}
```

We still have one unidentified function left: `fcn.08048524`.

```
[0x08048400]> pdg @ fcn.08048524

void fcn.08048524(void)
{
    sym.imp.printf("Password Incorrect!\n");
    // WARNING: Subroutine does not return
    sym.imp.exit(0);
}
```

This doesn't seem to do much, other than to print that the password is incorrect and exit. So let's call it
`print_and_exit`.

```
[0x08048400]> afn print_and_exit @ fcn.08048524
[0x08048400]> pdg @ check

// WARNING: Variable defined which should be unmapped: var_28h
// WARNING: Variable defined which should be unmapped: var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_11h

void check(int32_t arg_4h, int32_t arg_8h)
{
    uint32_t uVar1;
    int32_t iVar2;
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
        sym.imp.sscanf(&var_11h, 0x80487c2, &var_8h);
        var_ch = var_ch + var_8h;
        if (var_ch == 0x10) {
            parell(arg_4h, arg_8h);
        }
        var_10h = var_10h + 1;
    }
    print_and_exit();
    iVar2 = dummy(var_8h, arg_8h);
    if (iVar2 != 0) {
        for (var_10h = 0; var_10h < 10; var_10h = var_10h + 1) {
            if ((var_8h & 1U) == 0) {
                sym.imp.printf("wtf?\n");
    // WARNING: Subroutine does not return
                sym.imp.exit(0);
            }
        }
    }
    return;
}
```

Interestingly, `print_and_exit` is called unconditionally before the second parity check, meaning it is never executed
under normal circumstances. If we had used `aaa` to analyze this binary, Rizin would have noticed this, and it would
have simply omitted it from the disassembly and decompilation outputs.

If you happen to accidentally (or intentionally) run `aaa`, you can remove all function
analysis using `af-*`, after which you can run `aa`, followed by `afr` where needed. 

With that being said, it doesn't seem like the password constraints have changed at all from the previous versions:

- Digit sum reaches 16 at some point
- The number is even
- An environment variable starting with "LOL" is set

Before we close Rizin however let's save this as a project first, so we don't lose all our hard work naming the functions.

```
[0x08048400]> Ps crackme0x07.rzdb
```

And as we concluded, the passwords from the previous version still work.

```shell
$ LOL= ./crackme0x07
IOLI Crackme Level 0x07
Password: 88
Password OK!

$ LOL= ./crackme0x07
IOLI Crackme Level 0x07
Password: 12346
Password OK!
```

## WTF?

We could go to the next one. Technically we've solved this crackme. But we have some unfinished business: the `wtf?`
string. Let's see if we can find a way to reach the code that's supposed to write it to the console!

It's easy enough using the debugger: we can simply set the instruction pointer to some location after
the `print_and_exit` function (remember `dr eip=<address>`).  

We can reopen the current file in debug mode using the `ood` command. We do need an environment variable set that
starts with `LOL`, we can achieve this using the `dor` command. And let's also set a breakpoint at the location
`print_and_exit` is called so we can jump over it manually.

```
[0x08048400]> ood
Process with PID 191704 started...
[0xf173fcd0]> dor setenv=LOL=O
[0xf173fcd0]> pdf @ check
# find 'call print_and_exit'
[0xf173fcd0]> db @ 0x0804862a
[0xf173fcd0]> dc # run the program
IOLI Crackme Level 0x07
Password: 2
hit breakpoint at: 0x804862a
```

Now we should be at the instruction that reads `call print_and_exit` (confirm with `pd 1 @ eip`). Now we need to find
the address of the instruction that comes after this one and set the instruction pointer to equal this value.

```
[0x0804862a]> pd 2 @ eip
│           ;-- eip:
│           0x0804862a b    call  print_and_exit                       ; print_and_exit
│           0x0804862f      mov   eax, dword [arg_8h]
[0x0804862a]> dr eip=0x0804862f
[0x0804862a]> pd 1 @ eip
│           ;-- eip:
│           0x0804862f      mov   eax, dword [arg_8h]
```

With the `print_and_exit` function skipped we can continue execution.

```
[0x0804862a]> dc
wtf?
(191704) Process exited with status=0x0
[0xf3608579]> doc # close the debugging session
```

We've successfully triggered the `wtf?` code using the debugger. But that's no fun! Let's see if there is a way we can
reach that code (semi-)naturally.

In order for the `print_and_exit` function to be called we have to fail `parell` or the digit sum `check`.
Failing `parell` is tricky because the same version has to succeed after `print_and_exit` in order for our desired
string to be printed. So we'll have to fail the digit sum check, which means making sure that our digit sum will
not land on 16 during the computation.

Easy enough! The only problem we have is that `exit` stops the process...  But what if we were to make our own version
of `exit`?

```c 
void exit(int status) {
	void *ret = __builtin_return_address(2);

	__asm__ __volatile__ (
		"leave\n\t"
		"jmp *%0\n\t"
		: "+rm" (ret)
	);
}
```

This turns `exit` into something that, well, *doesn't* exit. `__builtin_return_address` is used to look two
call frames up for a return address (the return address of `print_and_exit`) and jumps to it. Let's save it to a file
called `exit.c`. Compile it to a shared library using `gcc -m32 -shared -o libexit.so exit.c` and then we can preload
it using `LD_PRELOAD`.

```bash
$ LD_PRELOAD=./libexit.so LOL= ./crackme0x07
IOLI Crackme Level 0x07
Password: 2
Password Incorrect!
wtf?
```

There it is!

Now that `exit` is a simple trampoline, something interesting happens when we enter a valid password.

```bash
$ LD_PRELOAD=./libexit.so LOL= ./crackme0x07
IOLI Crackme Level 0x07
Password: 888
Password OK!
Password Incorrect!
wtf?
```

"Password OK!" No. "Password Incorrect!" `wtf?` indeed.
