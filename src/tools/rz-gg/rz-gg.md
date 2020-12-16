# Rz-gg

rz-gg stands for `rizin egg`, this is the basic block to construct relocatable
snippets of code to be used for injection in target processes when doing exploiting.

rz-gg compiles programs written in a simple high-level language into tiny binaries
for x86, x86-64, and ARM.

You can also access all the rz-gg commands from the rizin shell. They are present
under `g`. See `g?` for more information about how to use them.

By default it will compile it's own `rz-gg` language, but you can also compile C
code using GCC or Clang shellcodes depending on the file extension. Lets create
C file called `helloworld.c`:
```c
int main() {
	write(1, "Hello World\n", 13);
	return 0;
}
```
```
$ rz-gg -a x86 -b32 helloworld.c
e900000000488d3516000000bf01000000b80400000248c7c20d0000000f0531c0c348656c6c6f20576f726c640a00

$ rz-asm -a x86 -b 32 -D e900000000488d3516000000bf01000000b80400000248c7c20d0000000f0531c0c348656c6c6f20576f726c640a00
0x00000000   5               e900000000  jmp 5
0x00000005   1                       48  dec eax
0x00000006   6             8d3516000000  lea esi, [0x16]
0x0000000c   5               bf01000000  mov edi, 1
0x00000011   5               b804000002  mov eax, 0x2000004
0x00000016   1                       48  dec eax
0x00000017   6             c7c20d000000  mov edx, 0xd
0x0000001d   2                     0f05  syscall
0x0000001f   2                     31c0  xor eax, eax
0x00000021   1                       c3  ret
0x00000022   1                       48  dec eax
0x00000023   2                     656c  insb byte es:[edi], dx
0x00000025   1                       6c  insb byte es:[edi], dx
0x00000026   1                       6f  outsd dx, dword [esi]
0x00000027   3                   20576f  and byte [edi + 0x6f], dl
0x0000002a   2                     726c  jb 0x98
0x0000002c   3                   640a00  or al, byte fs:[eax]
```

## Compiling rz-gg example

```
$ cat hello.r
exit@syscall(1);

main@global() {
	exit(2);
}

$ rz-gg -a x86 -b 64 hello.r
48c7c00200000050488b3c2448c7c0010000000f054883c408c3
0x00000000   1                       48  dec eax
0x00000001   6             c7c002000000  mov eax, 2
0x00000007   1                       50  push eax
0x00000008   1                       48  dec eax
0x00000009   3                   8b3c24  mov edi, dword [esp]
0x0000000c   1                       48  dec eax
0x0000000d   6             c7c001000000  mov eax, 1
0x00000013   2                     0f05  syscall
0x00000015   1                       48  dec eax
0x00000016   3                   83c408  add esp, 8
0x00000019   1                       c3  ret

$ rz-asm -a x86 -b 64 -D 48c7c00200000050488b3c2448c7c0010000000f054883c408c3
0x00000000   7           48c7c002000000  mov rax, 2
0x00000007   1                       50  push rax
0x00000008   4                 488b3c24  mov rdi, qword [rsp]
0x0000000c   7           48c7c001000000  mov rax, 1
0x00000013   2                     0f05  syscall
0x00000015   4                 4883c408  add rsp, 8
0x00000019   1                       c3  ret
```

You can also compile for ARM. For that, specify the architecture as `arm`:

```
$ rz-gg -a arm -b 32 hello.r
00482de90200a0e30c008de508109de50170a0e3000000ef0088bde8

$ rz-asm -a arm -b 32 -D 00482de90200a0e30c008de508109de50170a0e3000000ef0088bde8
0x00000000   4                 00482de9  push {fp, lr}
0x00000004   4                 0200a0e3  mov r0, 2
0x00000008   4                 0c008de5  str r0, [sp, 0xc]
0x0000000c   4                 08109de5  ldr r1, [sp, 8]
0x00000010   4                 0170a0e3  mov r7, 1
0x00000014   4                 000000ef  svc 0
0x00000018   4                 0088bde8  pop {fp, pc}
```

## Tiny binaries

You can create tiny binaries for your code using the `-F` flag in rz-gg,
or the `-C` in rz-bin.

```c
$ cat helloworld.r
int main() {
	write(1, "Hello World\n", 13);
	return 0;
}

$ rz-gg -O -F helloworld.c

$ ./helloworld
Hello World

$ wc -c < helloworld
259
```
We can see that the size of the binary is just 259 bytes.

## Output format

You can change the output format using the `-f` flag. Here's an example of
changing it to python:

```
$ rz-gg -O -F -f python helloworld.r

$ xxd helloworld | head -n 3
00000000: 696d 706f 7274 2073 7472 7563 740a 6275  import struct.bu
00000010: 6620 3d20 7374 7275 6374 2e70 6163 6b20  f = struct.pack
00000020: 2822 3133 3942 222c 202a 5b0a 3078 3535  ("139B", *[.0x55
```

You can set the output format to C, PE, ELF, Mach-O, raw, python or javascript.