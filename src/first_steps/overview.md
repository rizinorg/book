## The Rizin Framework

Rizin is a free and open source reverse engineering framework which provides a complete binary analysis experience. The project is a fork of radare2 with a focus on usability, stability, and working features, which strives to provide a welcoming environment for developers and users alike.

At its core, Rizin is a set of small command-line utilities. They can be used in tandem with Rizin or can be used independently according to its specefic purposes.

This chapter will give you a brief introduction about these tools, but you can check the dedicated sections for each tool at the end of this book.

### rizin

The main tool of the whole framework. It has the hexadecimal editor and debugger at its core. Rizin allows you to open a number of input/output sources as if they were simple, plain files, including disks, network connections, kernel drivers, processes under debugging, and so on.

It implements an advanced command line interface for moving around a file, analyzing data, disassembling, binary patching, data comparison, searching, replacing, and visualizing. It can be scripted with a variety of languages, including Python, Haskell, OCaml, JavaScript, and others.

### rz-bin

A program to extract information from executable binaries, such as ELF, PE, Java CLASS, Mach-O, plus any format supported by rizin plugins. rz-bin is used by the core to get data like exported symbols, imports, file information, cross references (xrefs), library dependencies, and sections.

### rz-asm

A command line assembler and disassembler for multiple architectures (including Intel x86 and x86-64, MIPS, ARM, PowerPC, Java, and myriad of others).

#### Examples
```
$ rz-asm -a java 'nop'
00
```
```
$ rz-asm -a x86 -d '90'
nop
```
```
$ rz-asm -a x86 -b 32 'mov eax, 33'
b821000000
```
```
$ echo 'push eax;nop;nop' | rz-asm -f -
509090
```

### rz-hash

An implementation of a block-based hash tool. From small text strings to large disks, rz-hash supports multiple algorithms, including MD4, MD5, CRC16, CRC32, SHA1, SHA256, and others.
rz-hash can be used to check the integrity or track changes of big files, memory dumps, or disks.

### Examples
```
$ rz-hash file
file: 0x00000000-0x00000007 sha256: 887cfbd0d44aaff69f7bdbedebd282ec96191cce9d7fa7336298a18efc3c7a5a
```
```
$ rz-hash -a md5 file
file: 0x00000000-0x00000007 md5: d1833805515fc34b46c2b9de553f599d
```
### rz-diff

A binary diffing utility that implements multiple algorithms. It supports byte-level or delta diffing for binary files, and code-analysis diffing to find changes in basic code blocks obtained from the rizin code analysis.

### rz-find

A program to find byte patterns in files.

### rz-egg

A frontend for r_egg. rz-egg compiles programs written in a simple high-level language into tiny binaries for x86, x86-64, and ARM.

#### Examples

```
$ cat hi.r
/* hello world in r_egg */
write@syscall(4); //x64 write@syscall(1);
exit@syscall(1); //x64 exit@syscall(60);

main@global(128) {
 .var0 = "hi!\n";
 write(1,.var0, 4);
 exit(0);
}
$ rz-egg -O -F hi.r
$ ./hi
hi!

$ cat hi.c
main@global(0,6) {
 write(1, "Hello0", 6);
 exit(0);
}
$ rz-egg hi.c
$ ./hi.c.bin
Hello
```

### rz-run

A launcher for running programs within different environments, with different arguments,
permissions, directories, and overridden default file descriptors. rz-run is useful for:

* Solving crackmes
* Fuzzing
* Test suites

A lot can be done using `rz-run`, here are a few examples demonstrating its capabilities:

#### Sample rz-run script
```
$ cat foo.rrz
#!/usr/bin/rz-run
program=./pp400
arg0=10
stdin=foo.txt
chdir=/tmp
#chroot=.
./foo.rrz
```

#### Connecting a program with a socket
```
$ nc -l 9999
$ rz-run program=/bin/ls connect=localhost:9999
```

#### Debugging a program redirecting STDIO into another terminal

1 - Open a new terminal and type 'tty' to get a terminal name:

```
$ tty ; clear ; sleep 999999
/dev/ttyS010
```

2 - Create a new file containing the following rz-run profile named foo.rrz:
```
#!/usr/bin/rz-run
program=/bin/ls
stdio=/dev/ttys010
```

3 - Launch the following rizin command:
```
rizin -r foo.rrz -d /bin/ls
```

### rz-ax

A minimalistic mathematical expression evaluator for the shell that is useful for making base conversions between floating point values, hexadecimal representations, hexpair strings to ASCII, octal to integer, and more. It also supports endianness settings and can be used as an interactive shell if no arguments are given.

#### Examples

```
$ rz-ax 1337
0x539

$ rz-ax 0x400000
4194304

$ rz-ax -b 01111001
y

$ rz-ax -S rizin
72616461726532

$ rz-ax -s 617765736f6d65
awesome
```
