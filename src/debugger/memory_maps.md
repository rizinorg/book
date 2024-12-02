# Memory Maps

The ability to understand and manipulate the memory maps of a debugged program is important for many different
Reverse Engineering tasks. Rizin offers a rich set of commands to handle memory maps in the binary.
This includes listing the memory maps of the currently debugged binary, removing memory maps,
handling loaded libraries and more.

First, let's see the help message for `dm`, the command which is responsible for handling memory maps:

```
[0x55f2104cf620]> dm?
Usage: dm[?]   # Memory map commands
| dm[j*qt]                # List memory maps
| dm+ <size>              # Allocate <size> bytes at current offset
| dm=                     # List memory maps of current process with ASCII art bars
| dm.                     # Show map name of current address
| dmm[j*.]                # Module memory map commands
| dm-                     # Deallocate memory map at current offset
| dmd[aw]                 # Dump debug map regions to a file (from-to.dmp)
| dmh[?]                  # Glibc heap commands
| dmi[?]                  # List/Load symbols
| dml <file>              # Load contents of file into current map region
| dmp <perms> [<size>]    # Change page at current offset with <size>, protection <perms> / Change dbg.map permissions
                            to <perms>
| dmL <size>              # Allocate <size> bytes at current offset and promote to huge page
| dmS[*] [<addr|libname> [<sectname>]] # List sections of target lib
| dmw[jb?]                # Windows heap commands
| dmx[?]                  # Jemalloc heap commands
```

In this chapter, we'll go over some of the most useful subcommands of `dm` using simple examples.
For the following examples, we'll use a simple
[hello_world](https://github.com/rizinorg/book/tree/master/examples/hello_world) for Linux,
but it'll be the same for every binary.

First things first - open a program in debugging mode:

```
$ rizin -d hello_world
Process with PID 4760 started...
[0x7f12fa1debb0]>
```

> Note that we passed "hello_world" to rizin without "./". rizin will try to find this program in the current
> directory and then in $PATH, even if no "./" is passed. This is contradictory with UNIX systems,
> but makes the behaviour consistent for Windows users

Let's use `dm` to print the memory maps of the binary we've just opened:

```
[0x7f133f022fb0]> dm
0x000055ca0f426000 - 0x000055ca0f427000 - usr     4K s r-- /tmp/hello_world /tmp/hello_world ; tmp_hello_world.r
0x000055ca0f427000 - 0x000055ca0f428000 - usr     4K s r-x /tmp/hello_world /tmp/hello_world ; tmp_hello_world.r_x
0x000055ca0f428000 - 0x000055ca0f429000 - usr     4K s r-- /tmp/hello_world /tmp/hello_world ; tmp_hello_world.r.55ca0f428000
0x000055ca0f429000 - 0x000055ca0f42b000 - usr     8K s rw- /tmp/hello_world /tmp/hello_world ; tmp_hello_world.rw
0x00007f52c4ae0000 - 0x00007f52c4ae1000 - usr     4K s r-- /usr/lib64/ld-linux-x86-64.so.2 /usr/lib64/ld-linux-x86-64.so.2 ; usr_lib64_ld_linux_x86_64.so.2.r
0x00007f52c4ae1000 - 0x00007f52c4b06000 * usr   148K s r-x /usr/lib64/ld-linux-x86-64.so.2 /usr/lib64/ld-linux-x86-64.so.2 ; usr_lib64_ld_linux_x86_64.so.2.r_x
0x00007f52c4b06000 - 0x00007f52c4b11000 - usr    44K s r-- /usr/lib64/ld-linux-x86-64.so.2 /usr/lib64/ld-linux-x86-64.so.2 ; usr_lib64_ld_linux_x86_64.so.2.r.7f52c4b06000
0x00007f52c4b11000 - 0x00007f52c4b15000 - usr    16K s rw- /usr/lib64/ld-linux-x86-64.so.2 /usr/lib64/ld-linux-x86-64.so.2 ; usr_lib64_ld_linux_x86_64.so.2.rw
0x00007fff03836000 - 0x00007fff03858000 - usr   136K s rw- [stack] [stack] ; stack_.rw
0x00007fff038bc000 - 0x00007fff038c0000 - usr    16K s r-- [vvar] [vvar] ; vvar_.r
0x00007fff038c0000 - 0x00007fff038c2000 - usr     8K s r-x [vdso] [vdso] ; vdso_.r_x
0xffffffffff600000 - 0xffffffffff601000 - usr     4K s --x [vsyscall] [vsyscall] ; vsyscall_.__x
```

For those of you who prefer a more visual way, you can use `dm=` to see the memory maps using an ASCII-art bars.
This will be handy when you want to see how these maps are located in the memory.

```
[0x7f52c4afbbb0]> dm=
map   4K - 0x00007f52c4ae0000 |------------------------------| 0x00007f52c4ae1000 r-- /usr/lib64/ld-linux-x86-64.so.2
map 148K * 0x00007f52c4ae1000 |------------------------------| 0x00007f52c4b06000 r-x /usr/lib64/ld-linux-x86-64.so.2
map  44K - 0x00007f52c4b06000 |------------------------------| 0x00007f52c4b11000 r-- /usr/lib64/ld-linux-x86-64.so.2
map  16K - 0x00007f52c4b11000 |------------------------------| 0x00007f52c4b15000 rw- /usr/lib64/ld-linux-x86-64.so.2
map   4K - 0xffffffffff600000 |------------------------------| 0xffffffffff601000 --x [vsyscall]
map 136K - 0x00007fff03836000 |------------------------------| 0x00007fff03858000 rw- [stack]
map  16K - 0x00007fff038bc000 |------------------------------| 0x00007fff038c0000 r-- [vvar]
map   8K - 0x00007fff038c0000 |------------------------------| 0x00007fff038c2000 r-x [vdso]
map   4K - 0x000055ca0f426000 |#######-----------------------| 0x000055ca0f427000 r-- /tmp/hello_world
map   4K - 0x000055ca0f427000 |------#######-----------------| 0x000055ca0f428000 r-x /tmp/hello_world
map   4K - 0x000055ca0f428000 |------------#######-----------| 0x000055ca0f429000 r-- /tmp/hello_world
map   8K - 0x000055ca0f429000 |------------------############| 0x000055ca0f42b000 rw- /tmp/hello_world
```

If you want to know the memory-map you are currently in, use `dm.`:

```
[0x7f52c4afbbb0]> dm.
0x00007f52c4ae1000 - 0x00007f52c4b06000 * usr   148K s r-x /usr/lib64/ld-linux-x86-64.so.2 /usr/lib64/ld-linux-x86-64.so.2 ; usr_lib64_ld_linux_x86_64.so.2.r_x
```

Using `dmm` we can "List modules (libraries, binaries loaded in memory)", this is quite a handy command to see
which modules were loaded.

```
[0x7f52c4afbbb0]> dmm
0x55ca0f426000 0x55ca0f427000  /tmp/hello_world
0x7f52c4ae0000 0x7f52c4ae1000  /usr/lib64/ld-linux-x86-64.so.2
```

> Note that the output of `dm` subcommands, and `dmm` specifically, might be different in various systems and
> different binaries.

We can see that along with our `hello_world` binary itself, another library was loaded which is `ld-linux-x86-64.so.2`.
We don't see `libc` yet and this is because Rizin breaks before `libc` is loaded to memory.
Let's use `dcu` (**d**ebug **c**ontinue **u**ntil) to execute our program until the entry point of the program,
which Rizin flags as `entry0`:

```
[0x7f52c4afbbb0]> dcu entry0
Continue until 0x55ca0f427100
hit breakpoint at: 0x55ca0f427100

[0x55ca0f427100]> dmm
0x55ca0f426000 0x55ca0f427000  /tmp/hello_world
0x7f52c48c8000 0x7f52c48ec000  /usr/lib64/libc.so.6
0x7f52c4ae0000 0x7f52c4ae1000  /usr/lib64/ld-linux-x86-64.so.2
```

Now we can see that `libc.so.6` was loaded as well, great!

Speaking of `libc`, a popular task for binary exploitation is to find the address of a specific symbol in a library.
With this information in hand, you can build, for example, an exploit which uses ROP. This can be achieved using
the `dmi` command. So if we want, for example, to find the address
of [`system()`](http://man7.org/linux/man-pages/man3/system.3.html) in the loaded `libc`,
we can simply execute the following command:

```
[0x55ca0f427100]> dmi libc system
[Symbols]
nth  paddr      vaddr          bind type size lib name   
---------------------------------------------------------
1052 0x0004d2f0 0x7f52c49152f0 WEAK FUNC 45       system
```

Similar to the `dm.` command, with `dmi.` you can see the closest symbol to the current address:

```
[0x55ca0f427100]> dmi. libc system
[Symbols]
nth paddr      vaddr      bind   type   size lib name 
------------------------------------------------------
20  ---------- 0x00004018 GLOBAL NOTYPE 0        _end
```

Another useful command is to list the sections of a specific library. In the following example we'll list
the sections of `ld-linux-x86-64.so.2`:

```
[0x55ca0f427100]> dmS ld-linux-x86-64.so.2
[Sections]
paddr      size    vaddr          vsize   align perm name                                    type     flags         
--------------------------------------------------------------------------------------------------------------------
0x00000000 0x0     ----------     0x0     0x0   ---- ld-linux-x86-64.so.2.                   NULL     
0x00000270 0x1e8   0x7f52c4ae0270 0x1e8   0x0   -r-- ld-linux-x86-64.so.2..gnu.hash          GNU_HASH alloc
0x00000458 0x3c0   0x7f52c4ae0458 0x3c0   0x0   -r-- ld-linux-x86-64.so.2..dynsym            DYNSYM   alloc
0x00000818 0x2ca   0x7f52c4ae0818 0x2ca   0x0   -r-- ld-linux-x86-64.so.2..dynstr            STRTAB   alloc
0x00000ae2 0x50    0x7f52c4ae0ae2 0x50    0x0   -r-- ld-linux-x86-64.so.2..gnu.version       VERSYM   alloc
0x00000b38 0xec    0x7f52c4ae0b38 0xec    0x0   -r-- ld-linux-x86-64.so.2..gnu.version_d     VERDEF   alloc
0x00000c28 0x18    0x7f52c4ae0c28 0x18    0x0   -r-- ld-linux-x86-64.so.2..rela.dyn          RELA     alloc
0x00000c40 0x18    0x7f52c4ae0c40 0x18    0x0   -r-- ld-linux-x86-64.so.2..relr.dyn          NUM      alloc
0x00001000 0x24ebb 0x7f52c4ae1000 0x24ebb 0x0   -r-x ld-linux-x86-64.so.2..text              PROGBITS alloc,execute
0x00026000 0x64e8  0x7f52c4b06000 0x64e8  0x0   -r-- ld-linux-x86-64.so.2..rodata            PROGBITS alloc
0x0002c4e8 0x9a4   0x7f52c4b0c4e8 0x9a4   0x0   -r-- ld-linux-x86-64.so.2..eh_frame_hdr      PROGBITS alloc
0x0002ce90 0x36f8  0x7f52c4b0ce90 0x36f8  0x0   -r-- ld-linux-x86-64.so.2..eh_frame          PROGBITS alloc
0x00030588 0x40    0x7f52c4b10588 0x40    0x0   -r-- ld-linux-x86-64.so.2..note.gnu.property NOTE     alloc
0x000312e0 0x1ba0  0x7f52c4b112e0 0x1ba0  0x0   -rw- ld-linux-x86-64.so.2..data.rel.ro       PROGBITS write,alloc
0x00032e80 0x170   0x7f52c4b12e80 0x170   0x0   -rw- ld-linux-x86-64.so.2..dynamic           DYNAMIC  write,alloc
0x00033000 0x1104  0x7f52c4b13000 0x1104  0x0   -rw- ld-linux-x86-64.so.2..data              PROGBITS write,alloc
0x00034104 0x0     0x7f52c4b14110 0x1d0   0x0   -rw- ld-linux-x86-64.so.2..bss               NOBITS   write,alloc
0x00034104 0x33    ----------     0x33    0x0   ---- ld-linux-x86-64.so.2..comment           PROGBITS merge,strings
0x00034138 0x40f8  ----------     0x40f8  0x0   ---- ld-linux-x86-64.so.2..symtab            SYMTAB   
0x00038230 0x23f4  ----------     0x23f4  0x0   ---- ld-linux-x86-64.so.2..strtab            STRTAB   
0x0003a624 0xc8    ----------     0xc8    0x0   ---- ld-linux-x86-64.so.2..shstrtab          STRTAB   
```
