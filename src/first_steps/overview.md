## The Rizin Framework


Rizin is a free and open-source reverse engineering framework that delivers a comprehensive binary analysis experience. It focuses on usability, stability, and functional features, striving to create a welcoming environment for developers and users.

At its core, Rizin consists of a set of small command-line utilities. These utilities can be used in tandem with Rizin or independently, each serving specific purposes. While this chapter provides a brief introduction to these tools, dedicated sections for each tool can be found at the end of this book for more detailed information.

### rizin

The primary command line tool within the framework is `rizin`. It encompasses various features such as a disassembler, hexadecimal editor, and debugger. Rizin enables you to treat multiple input/output sources, such as plain text files, executables, kernel drivers, processes, etc., as if they were straightforward text files.

It incorporates a sophisticated command line interface for navigating through the accessed resource, analyzing data, disassembling, patching binaries, comparing data, searching, replacing, and visualizing. Furthermore, scripting capabilities are available with a range of languages, including Python, Haskell, OCaml, JavaScript, and others.

### rz-bin

The `rz-bin` utility serves the purpose of extracting information from executable binaries, encompassing formats like ELF, PE, Java CLASS, Mach-O, and any other format supported by rizin plugins. Within the core functionality, `rz-bin` plays a crucial role in obtaining data such as exported symbols, imports, file details, cross references, library dependencies, and sections.

#### Examples
```
$ rz-bin -I unknown.bin
[Info]
arch     x86
cpu      N/A
baddr    0x00000000
binsz    0x000213b3
bintype  elf
bits     64
class    ELF64
compiler GCC: (GNU) 13.2.1 20230801
dbg_file N/A
endian   LE
hdr.csum N/A
guid     N/A
intrp    /lib64/ld-linux-x86-64.so.2
laddr    0x00000000
lang     c
machine  AMD x86-64 architecture
maxopsz  16
minopsz  1
os       linux
cc       N/A
pcalign  0
relro    full
rpath    NONE
subsys   linux
stripped true
crypto   false
havecode true
va       true
sanitiz  false
static   false
linenum  false
lsyms    false
canary   true
PIE      true
RELROCS  false
NX       true
```

### rz-asm

The `rz-asm` tool operates as a command line assembler and disassembler, catering to various architectures such as Intel x86 and x86-64, MIPS, ARM, PowerPC, Java, and numerous others.

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

`rz-hash` stands as an implementation of a block-based hash tool. It offers support for a range of algorithms, including `MD4`, `MD5`, `CRC`, `SHA1`, `SHA256`, and more, accommodating both small text strings and large files. Its utility extends to checking the integrity or monitoring changes in substantial files and memory dumps.

### Examples
```
$ rz-hash file.bin
file: 0x00000000-0x00000007 sha256: 887cfbd0d44aaff69f7bdbedebd282ec96191cce9d7fa7336298a18efc3c7a5a
```
```
$ rz-hash -a md5 file.bin
file: 0x00000000-0x00000007 md5: d1833805515fc34b46c2b9de553f599d
```
### rz-diff


The `rz-diff` utility serves as a binary diffing tool, implementing various algorithms. It facilitates byte-level or delta diffing for binary files and code-analysis diffing to identify alterations in fundamental code blocks derived from the rizin code analysis.

This tool optimally leverages multi-threading to enhance performance, particularly on CPU-intensive and time-consuming tasks.

### rz-find

`rz-find` operates as a program designed to locate byte patterns in files. It provides the capability to search for various types of signatures, including strings in different encodings such as ASCII, UTF-8, wide, and more, across multiple encoding types.

### rz-gg

`rz-gg` is a tool designed to compile programs written in a simple high-level language into compact binaries suitable for x86, x86-64, and ARM architectures.

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
$ rz-gg -O -F hi.r
$ ./hi
hi!

$ cat hi.c
main@global(0,6) {
 write(1, "Hello0", 6);
 exit(0);
}
$ rz-gg hi.c
$ ./hi.c.bin
Hello
```

### rz-run

`rz-run` functions as a launcher for executing programs within diverse environments, allowing customization of various aspects such as arguments, permissions, directories, and overridden default file descriptors. This utility proves beneficial for activities like solving crackmes, fuzzing, and running test suites.

The versatility of `rz-run` is evident in its capabilities. Here are a few examples illustrating how it can be utilized:

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

`rz-ax` stands out as a minimalistic mathematical expression evaluator tailored for the shell. Its utility extends to facilitating base conversions between floating-point values, hexadecimal representations, hexpair strings to ASCII, octal to integer, and more. Notably, it supports endianness settings and can serve as an interactive shell when invoked without arguments.

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
