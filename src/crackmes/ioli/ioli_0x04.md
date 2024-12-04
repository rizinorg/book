# IOLI 0x04

This is the fifth crackme.

```bash
$ rz-bin -z ./crackme0x04
[Strings]
nth paddr      vaddr      len size section type  string                    
---------------------------------------------------------------------------
0   0x0000063b 0x0804863b 13  14   .rodata ascii Password OK!\n
1   0x00000649 0x08048649 20  21   .rodata ascii Password Incorrect!\n
2   0x0000065e 0x0804865e 24  25   .rodata ascii IOLI Crackme Level 0x04\n
3   0x00000677 0x08048677 10  11   .rodata ascii Password: 
```

Checking for strings we see that our old friends "Password OK!" and "Password Incorrect!" are back in their unobfuscated
forms.

```
$ rizin ./crackme0x04
[0x080483d0]> aaa
[0x080483d0]> pdg @ main

undefined4 main(void)
{
    int32_t var_88h;
    int32_t var_7ch;
    
    sym.imp.printf("IOLI Crackme Level 0x04\n");
    sym.imp.printf("Password: ");
    sym.imp.scanf(data.08048682, &var_7ch);
    sym.check((char *)&var_7ch);
    return 0;
}
[0x080483d0]> ps @ data.08048682 
%s
```

This time though, `scanf` takes a *string* and passes it to a function called `check`.

```
[0x080483d0]> pdg @ sym.check

// WARNING: Variable defined which should be unmapped: format
// WARNING: Variable defined which should be unmapped: args

void sym.check(char *s)
{
    uint32_t uVar1;
    char *format;
    va_list args;
    char *var_11h;
    unsigned long var_ch;
    int32_t var_8h;
    
    var_ch = 0;
    stack0xfffffff0 = 0;
    while( true ) {
        uVar1 = sym.imp.strlen(s);
        if (uVar1 <= stack0xfffffff0) break;
        var_11h._0_1_ = s[stack0xfffffff0];
        sym.imp.sscanf(&var_11h, data.08048638, &var_8h);
        var_ch = var_ch + var_8h;
        if (var_ch == 0xf) {
            sym.imp.printf("Password OK!\n");
            sym.imp.exit(0);
        }
        unique0x00003f80 = stack0xfffffff0 + 1;
    }
    sym.imp.printf("Password Incorrect!\n");
    return;
}

[0x080483d0]> afvl @ sym.check
var const char *format @ stack - 0x28
var va_list args @ stack - 0x24
var const char *var_11h @ stack - 0x11
var unsigned long var_ch @ stack - 0xc
var int32_t var_8h @ stack - 0x8
arg const char *s @ stack + 0x4
[0x080483d0]> ps @ 0x8048638 @!2
%d
```

A few things to note: `sscanf` in the `while` loop takes an integer ("%d"), and the result is placed in
`var_8h`, which is subsequently used to increment `var_ch`. As soon as `var_ch` equals 15 (0xf) we gain
entry.

Other than that however it may not be very obvious at first glance what exactly is going on here. So let's start
a debugging session to execute the function.

```bash
$ rizin -d ./crackme0x04
[0xf3666cd0]> aaa
[0xf3666cd0]> dcu main          # execute until start of `main`
[0x08048509]> dr eip=sym.check  # instruction pointer to start of `check`
```

We will want to pass our own strings to `check`, so let's allocate some memory and write a string to it.

```bash
[0x08048509]> dm+ 512 @ -1              # Allocate 512 bytes at anywhere (-1)
ra0=0xf7fbb000
[0x08048509]> wz "letmein" @ 0xf7fbb000 # Write null-terminated string to our allocated memory
[0x08048509]> *esp+4=0xf7fbb000         # store the address under `arg_4h` (stack + 0x04)
```

The password check completes if `var_ch` equals 15 (0xf) so let's add a breakpoint that prints the
value of `var_ch`. We are going to be putting the breakpoint at the comparison of `var_ch` and `0xf`,
try to find it using `pdf @ sym.check`.

```bash
[0x08048508]> pdf @ sym.check # find `cmp dword [var_ch], 0xf` 
...
[0x08048508]> db @ 0x080484d6                       # set breakpoint
[0x08048508]> dbc 'pxw 1 @ esp-0xc' @ 0x080484d6    # execute command on break
[0x08048508]> dcr                                   # execute until return
0xffeefb00  0x000000ff                                   . # l
0xffeefb00  0x000000fe                                   . # e
0xffeefb00  0x000000fd                                   . # t
0xffeefb00  0x000000fc                                   . # m
0xffeefb00  0x000000fb                                   . # e
0xffeefb00  0x000000fa                                   . # i
0xffeefb00  0x000000f9                                   . # n
Password Incorrect!
```

We can see that each letter increments `var_ch` by 4. Remember that `sscanf` in `check` takes a number (%d) as input. And
because we didn't provide any numbers, odds are that '4' was probably some leftover data that happend to sit at the location
of `var_ch`. This was never overwritten because `sscanf` didn't encounter any numbers.

So let's try giving it a number as input.

```bash
[0x08048508]> wz "1234" @ 0xf7fbb010
[0x08048508]> *esp+4=0xf7fbb010
[0x08048508]> dr eip=sym.check
[0x08048508]> dcr
0xffeefb00  0x00000001                                   . # 1
0xffeefb00  0x00000003                                   . # 2
0xffeefb00  0x00000006                                   . # 3
0xffeefb00  0x0000000a                                   . # 4
Password Incorrect!
```

Now we see what the function `check` is actually supposed to do: it increments the counter
by each digit encountered. Or in other words it computes the digit sum, which has to land on 15 at some point during
the computation.

And indeed, cleaning up the decompiled `check` makes this more obvious.

```c
void sym.check(char *s)
{
    int32_t var_11h = 0;
    int32_t sum = 0;
    int32_t d;

    for(int i = 0; i < strlen(s); i++) {
        var_11h = s[i];
        sscanf(&var_11h, "%d", &d);
        sum += d;
        if(sum == 0xf) {
            printf("Password OK!\n");
            exit(0);
        }
    }
    printf("Password Incorrect!\n");
    return;
}
```

```bash
$ ./crackme0x04
IOLI Crackme Level 0x04
Password: 12345
Password OK!

$ ./crackme0x04
IOLI Crackme Level 0x04
Password: 96
Password OK!
```

Using what we discovered when we entered non-digit characters we can get some other passwords to work as well.
```bash
$ ./crackme0x04
IOLI Crackme Level 0x04
Password: 5asdf
Password OK!

$ ./crackme0x04
IOLI Crackme Level 0x04
Password: 0this-will-not-increment1but-this-will:)
Password OK!
```
