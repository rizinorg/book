# IOLI 0x03

This is the fourth crackme.

```
$ ./crackme0x03
IOLI Crackme Level 0x03
Password: letmein
Invalid Password!
```

Checking for strings with `rz-bin -z ./crackme0x03` gives us the following result:

```
$ rz-bin -z ./crackme0x03
[Strings]
nth paddr      vaddr      len size section type  string                    
---------------------------------------------------------------------------
0   0x000005ec 0x080485ec 17  18   .rodata ascii Lqydolg#Sdvvzrug$
1   0x000005fe 0x080485fe 17  18   .rodata ascii Sdvvzrug#RN$$$#=,
2   0x00000610 0x08048610 24  25   .rodata ascii IOLI Crackme Level 0x03\n
3   0x00000629 0x08048629 10  11   .rodata ascii Password: 
```

Note that the 'Invalid Password!' and the 'Password OK :)' strings have been seemingly replaced by random
gibberish.

Let's analyze.

```
$ rizin ./crackme0x03
[0x08048360]> aaa
[0x08048360]> pdg @ main

undefined4 main(void)
{
    int32_t var_18h;
    int32_t var_10h;
    int32_t var_ch;
    int32_t var_8h;
    
    sym.imp.printf("IOLI Crackme Level 0x03\n");
    sym.imp.printf("Password: ");
    sym.imp.scanf(data.08048634, &var_8h);
    sym.test(var_8h, 0x52b24);
    return 0;
}
```

This looks quite straightforward, `var_8h` is the result of `scanf` which the function `sym.test(var_8h, 0x52b24)`
apparently compares to the value `0x52b24`.

And indeed entering the decimal value of `0x52b24` (338724) gives us a pass.

```
$ ./crackme0x03
IOLI Crackme Level 0x03
Password: 338724
Password OK!!! :)
```

But let's dive a bit deeper to see what `sym.test()` is actually doing!

```C
[0x08048360]> pdg @ sym.test

void sym.test(int32_t arg_4h, unsigned long arg_8h)
{
    if (arg_4h == arg_8h) {
        sym.shift("Sdvvzrug#RN$$$#=,");
    } else {
        sym.shift("Lqydolg#Sdvvzrug$");
    }
    return;
}
```

It's a two path conditional jump which compares two parameters and then does a shift. We can guess that `shift()`
is most likely some sort of decoding step of the seemingly random strings (shift cipher, e.g. Caesar cipher).

To confirm our suspicions let's analyze `sym.shift()`.

```
[0x08048360]> pdg @ sym.shift

// WARNING: Variable defined which should be unmapped: var_98h

void sym.shift(char *s)
{
    uint32_t uVar1;
    int32_t var_98h;
    unsigned long var_80h;
    int32_t var_7ch;
    
    var_80h = 0;
    while( true ) {
        uVar1 = sym.imp.strlen(s);
        if (uVar1 <= var_80h) break;
        *(char *)((int32_t)&var_7ch + var_80h) = s[var_80h] + -3;
        var_80h = var_80h + 1;
    }
    *(undefined *)((int32_t)&var_7ch + var_80h) = 0;
    sym.imp.printf(data.080485e8, &var_7ch);
    return;
}
```

If we clean this up a bit it becomes more evident what is going on.

```C
void shift(char *str)
{
    uint32_t len = strlen(str);
    char res[len + 1];
    
    int32_t idx = 0;
    while( idx < len ) {
        res[idx] = str[idx] - 3; // Subtract character code by 3
        idx++;
    }
    res[idx] = 0; // Add null terminator
    printf("%s\n", res);
    return;
}
```

We can see that each character in `str` is subtracted by 3 to produce the final result.

With this knowledge we can take a shot at decoding the strings. We can use the `pos` command to apply
the subtraction needed for decoding and printing the result.

```shell
$ rizin ./crackme0x03
[0x08048360]> aaa
[0x08048360]> fs strings
[0x08048360]> fl
0x080485ec 18 str.Lqydolg_Sdvvzrug
0x080485fe 18 str.Sdvvzrug_RN
0x08048610 25 str.IOLI_Crackme_Level_0x03
0x08048629 11 str.Password:
[0x08048360]> pos 0x03 @ str.Lqydolg_Sdvvzrug @! 18
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x080485ec  496e 7661 6c69 6420 5061 7373 776f 7264  Invalid Password
0x080485fc  21fd                                     !.
[0x08048360]> pos 0x03 @ str.Sdvvzrug_RN @! 18
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x080485fe  5061 7373 776f 7264 204f 4b21 2121 203a  Password OK!!! :
0x0804860e  29fd                                     ).
```

However, some functions may not be as easy to understand as this one, in which case it may be useful to be able to run
the code. Rizin provides us two ways of doing this: by using the debugger, or by emulation (using ESIL). 

Let's first see how we can achieve this using the debugger. We will be wanting to pass the encoded strings
to `shift()`. We know `shift` takes one parameter `s`, which is an address to a (null terminated) string.
We can see where on the stack local variables and arguments are using the `afvl` command.

```shell
$ rizin -d ./crackme0x03
[0xf7f04630]> aa
[0xf7f04630]> afvl @ sym.shift
var int32_t var_98h @ stack - 0x98
var int32_t var_80h @ stack - 0x80
var int32_t var_7ch @ stack - 0x7c
arg int32_t arg_4h @ stack + 0x4
```

We can see that `s` starts at a 4 byte offset from the stack pointer.

```shell
[0xf7f04630]> dcu main                      # run until program start
Continue until 0x08048498
hit breakpoint at: 0x8048498
[0x08048498]> *esp+4=str.Lqydolg_Sdvvzrug   # 'push' address onto the stack (note the 4 byte offset)
[0x08048498]> dr eip=sym.shift              # set instruction pointer to start of shift()
[0x08048498]> dcr                           # run shift() until it returns
Invalid Password!
[0x0804846d]> *esp+4=str.Sdvvzrug_RN        # and now for the other string
[0x08048498]> dr eip=sym.shift
[0x08048498]> dcr
Password OK!!! :)
```

Emulation is a bit more tricky because we can't make external calls to functions like `strlen()` and `printf()`.
So we have to manually skip over them and set the registers accordingly. Below is an example.

```bash
[0x08048414]> s 0x08048445		# the 'sub al, 0x03'
[0x08048445]> aei				# init VM
[0x08048445]> aeim				# init memory
[0x08048445]> aeip				# init ip
[0x08048445]> ar eax=0x41		# set eax=0x41 -- 'A'
[0x08048445]> ar				# show current value of regs
oeax = 0x00000000
eax = 0x00000041
ebx = 0x00000000
ecx = 0x00000000
edx = 0x00000000
esi = 0x00000000
edi = 0x00000000
esp = 0x00178000
ebp = 0x00178000
eip = 0x08048445
eflags = 0x00000000
[0x08048445]> V					# enter Visual mode
# 'p' or 'P' to change visual mode
# I prefer the [xaDvc] mode
# use 's' to step in and 'S' to step over
[0x08048442 [xaDvc]0 0% 265 ./crackme0x03]> diq;?0;f t.. @ sym.shift+46 # 0x8048442
dead at 0x00000000
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x00178000  0000 0000 0000 0000 0000 0000 0000 0000  ................
0x00178010  0000 0000 0000 0000 0000 0000 0000 0000  ................
0x00178020  0000 0000 0000 0000 0000 0000 0000 0000  ................
0x00178030  0000 0000 0000 0000 0000 0000 0000 0000  ................
   oeax 0x00000000      eax 0x00000041      ebx 0x00000000      ecx 0x00000000
    edx 0x00000000      esi 0x00000000      edi 0x00000000      esp 0x00178000
    ebp 0x00178000      eip 0x08048445   eflags 0x00000000
       :   0x08048442      0fb600         movzx eax, byte [eax]
       :   ;-- eip:
       :   0x08048445      2c03           sub al, 3
       :   0x08048447      8802           mov byte [edx], al
       :   0x08048449      8d4584         lea eax, [var_7ch]
       :   0x0804844c      ff00           inc dword [eax]
       :=< 0x0804844e      ebd4           jmp 0x8048424
           ; CODE XREF from sym.shift @ 0x8048432
           0x08048450      8d4588         lea eax, [var_78h]
```
