IOLI 0x02
=========

This is the third one.

```
$ ./crackme0x02
IOLI Crackme Level 0x02
Password: hello
Invalid Password!
```

Firstly, let's check it with rz-bin.
```
$ rz-bin -z ./crackme0x02
[Strings]
nth paddr      vaddr      len size section type  string
―――――――――――――――――――――――――――――――――――――――――――――――――――――――
0   0x00000548 0x08048548 24  25   .rodata ascii IOLI Crackme Level 0x02\n
1   0x00000561 0x08048561 10  11   .rodata ascii Password:
2   0x0000056f 0x0804856f 15  16   .rodata ascii Password OK :)\n
3   0x0000057f 0x0804857f 18  19   .rodata ascii Invalid Password!\n
```

Similar to 0x01, there's no explicit password string here. So, it's time to analyze it with Rizin.
```
[0x08048330]> aa
[x] Analyze all flags starting with sym. and entry0 (aa)
[0x08048330]> pdf@main
            ; DATA XREF from entry0 @ 0x8048347
/ 144: int main (int argc, char **argv, char **envp);
|           ; var int32_t var_ch @ ebp-0xc
|           ; var int32_t var_8h @ ebp-0x8
|           ; var int32_t var_4h @ ebp-0x4
|           ; var int32_t var_sp_4h @ esp+0x4
|           0x080483e4      55             push ebp
|           0x080483e5      89e5           mov ebp, esp
|           0x080483e7      83ec18         sub esp, 0x18
|           0x080483ea      83e4f0         and esp, 0xfffffff0
|           0x080483ed      b800000000     mov eax, 0
|           0x080483f2      83c00f         add eax, 0xf                ; 15
|           0x080483f5      83c00f         add eax, 0xf                ; 15
|           0x080483f8      c1e804         shr eax, 4
|           0x080483fb      c1e004         shl eax, 4
|           0x080483fe      29c4           sub esp, eax
|           0x08048400      c70424488504.  mov dword [esp], str.IOLI_Crackme_Level_0x02 ; [0x8048548:4]=0x494c4f49 ; "IOLI Crackme Level 0x02\n"
|           0x08048407      e810ffffff     call sym.imp.printf         ; int printf(const char *format)
|           0x0804840c      c70424618504.  mov dword [esp], str.Password: ; [0x8048561:4]=0x73736150 ; "Password: "
|           0x08048413      e804ffffff     call sym.imp.printf         ; int printf(const char *format)
|           0x08048418      8d45fc         lea eax, [var_4h]
|           0x0804841b      89442404       mov dword [var_sp_4h], eax
|           0x0804841f      c704246c8504.  mov dword [esp], 0x804856c  ; [0x804856c:4]=0x50006425
|           0x08048426      e8e1feffff     call sym.imp.scanf          ; int scanf(const char *format)
|           0x0804842b      c745f85a0000.  mov dword [var_8h], 0x5a    ; 'Z' ; 90
|           0x08048432      c745f4ec0100.  mov dword [var_ch], 0x1ec   ; 492
|           0x08048439      8b55f4         mov edx, dword [var_ch]
|           0x0804843c      8d45f8         lea eax, [var_8h]
|           0x0804843f      0110           add dword [eax], edx
|           0x08048441      8b45f8         mov eax, dword [var_8h]
|           0x08048444      0faf45f8       imul eax, dword [var_8h]
|           0x08048448      8945f4         mov dword [var_ch], eax
|           0x0804844b      8b45fc         mov eax, dword [var_4h]
|           0x0804844e      3b45f4         cmp eax, dword [var_ch]
|       ,=< 0x08048451      750e           jne 0x8048461
|       |   0x08048453      c704246f8504.  mov dword [esp], str.Password_OK_: ; [0x804856f:4]=0x73736150 ; "Password OK :)\n"
|       |   0x0804845a      e8bdfeffff     call sym.imp.printf         ; int printf(const char *format)
|      ,==< 0x0804845f      eb0c           jmp 0x804846d
|      |`-> 0x08048461      c704247f8504.  mov dword [esp], str.Invalid_Password ; [0x804857f:4]=0x61766e49 ; "Invalid Password!\n"
|      |    0x08048468      e8affeffff     call sym.imp.printf         ; int printf(const char *format)
|      |    ; CODE XREF from main @ 0x804845f
|      `--> 0x0804846d      b800000000     mov eax, 0
|           0x08048472      c9             leave
\           0x08048473      c3             ret

```

With the experience of solving crackme0x01, we can first locate the position of `cmp` instruction by using this simple oneliner:
```
[0x08048330]> pdf@main~cmp
|           0x0804844e      3b45f4         cmp eax, dword [var_ch]
```

Unfortunately, the variable compared to `eax` is stored in the stack. We can't check the value of this variable directly. It's a common case in reverse engineering that we have to derive the value of the variable from the previous sequence. As the amount of code is relatively small, it can be easily done.

for example:
```
|           0x080483ed      b800000000     mov eax, 0
|           0x080483f2      83c00f         add eax, 0xf                ; 15
|           0x080483f5      83c00f         add eax, 0xf                ; 15
|           0x080483f8      c1e804         shr eax, 4
|           0x080483fb      c1e004         shl eax, 4
|           0x080483fe      29c4           sub esp, eax
```

We can easily get the value of `eax`. It's 16.

Directly looking at the disassembly gets hard when the scale of program grows. Rizin's flagship decompiler [rz-ghidra](https://github.com/rizinorg/rz-ghidra) might be of help, here. You can install it easily:
```
rz-pm -i rz-ghidra
```

Decompile `main()` with the following command (like `F5` in IDA):
```C
[0x08048330]> pdg
undefined4 main(void)
{
    uint32_t var_ch;
    undefined4 var_8h;
    int32_t var_4h;
    
    printf("IOLI Crackme Level 0x02\n");
    printf("Password: ");
    scanf(0x804856c, &var_4h);
    if (var_4h == 0x52b24) {
        printf("Password OK :)\n");
    } else {
        printf("Invalid Password!\n");
    }
    return 0;
}
```

It's more human-readable now. To check the string in `0x804856c`, we can:
* Seek
* Print the string
```
[0x08048330]> s 0x804856c
[0x0804856c]> ps
%d
```
It's exactly the format string of `scanf()`. And rz-ghidra recognizes that the second argument (eax) is a pointer and it points to `var_4h`. Which means our input will be stored in `var_4h`.

We can easily write out the pseudo code here.
```C
var_ch = (var_8h + var_ch)^2;
if (var_ch == our_input)
  printf("Password OK :)\n");
```

Given the initial status that `var_8h` is `0x5a`, `var_ch` is `0x1ec`, we have
var_ch = 338724 (0x52b24):

```
$ rz-ax '=10' '(0x5a+0x1ec)*(0x5a+0x1ec)'
338724

$ ./crackme0x02
IOLI Crackme Level 0x02
Password: 338724
Password OK :)
```

And we finish the crackme0x02.
