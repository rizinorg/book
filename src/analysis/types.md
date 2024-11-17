# Types

Rizin supports C-syntax data type definitions. Most of the related commands are located in `t` namespace:

```
[0x00001100]> t?
Usage: t[?]   # Types, noreturn, signatures, C parser and more
| t[j*l] [<type>] # List all types / Show type information
| t- <type>       # Remove the type
| t-*             # Remove all types
| tc[dc]          # List loaded types in C format
| td <type>       # Define type from C definition
| te[jbcdf]       # List loaded enums
| tf[j-c?]        # List loaded functions definitions
| tn[j-?]         # Manage noreturn function attributes and marks
| to[es]          # Open C header file and load types from it
| tp[vx]          # Print formatted type casted to the address
| ts[jlcd]        # List loaded structures
| tt[jc]          # List loaded typedefs
| tu[jlcd]        # List loaded unions
| tx[fgl]         # Type xrefs
```

Note that the basic (atomic) types are not those from the C standard -
not `char`, `_Bool`, or `short`. Because those types can be different
from one platform to another, Rizin uses `definite` types like as
`int8_t` or `uint64_t` and will convert `int` to `int32_t` or `int64_t`
depending on the binary or debuggee platform/compiler.

Basic types can be listed using the `t` command. For structured types, you 
can use `ts`, `tu`, or `te` for structs, unions, and enums, respectively:

```
[0x000051c0]> t
char
char *
int
int16_t
int32_t
int64_t
int8_t
long
long long
...
```

### Loading types

There are three easy ways to define a new type:
* Passing a string to the `td` command
* Passing a file with the `to <filename>` command
* Using your defined `cfg.editor` by calling the `to -` command

```
[0x000051c0]> td "struct foo {char* a; int b;}"
[0x000051c0]> cat ~/rizin-regressions/bins/headers/s3.h
struct S1 {
    int x[3];
    int y[4];
    int z;
};
[0x000051c0]> to ~/rizin-regressions/bins/headers/s3.h
[0x000051c0]> ts
foo
S1
```

Also, note there is a config option to specify include directories for types parsing

```
[0x00000000]> el~dir.type
dir.types: Default path to look for cparse type files
[0x00000000]> e dir.types
/usr/include
```

### Printing types

Notice below we have used `ts` command, which basically converts the C type 
description into the sequence of `pf` commands. See more about 
[print format](../basic_commands/print_modes.md).

The `tp` command uses the `pf` string to print all the members of type at the current offset/given address:

```
[0x000051c0]> ts foo
pf zd a b
[0x000051c0]> tp foo
 a : 0x000051c0 = 'hello'
 b : 0x000051cc = 10
[0x000051c0]> tp foo 0x000053c0
 a : 0x000053c0 = 'world'
 b : 0x000053cc = 20
```

Also, you could fill your own data into the struct and print it using `tpx` command

```
[0x000051c0]> tpx foo 4141414144141414141442001000000
 a : 0x000051c0 = AAAAD.....B
 b : 0x000051cc = 16
```

### Linking Types

The `tp` command only performs a temporary cast. We can use the `avga` command to 
define a global variable of a specified type, which is linked to an address.

```
[0x000051c0]> avga struct_1 S1 @ 0x51cf
[0x000051c0]> avg
global struct S1 struct_1 @ 0x000051cf
```

Moreover, the link will be shown in the disassembly output or visual mode:

```
[0x000051c0 15% 300 /bin/ls]> pd $r @ entry0
 ;-- entry0:
 0x000051c0      xor ebp, ebp
 0x000051c2      mov r9, rdx
 0x000051c5      pop rsi
 0x000051c6      mov rdx, rsp
 0x000051c9      and rsp, 0xfffffffffffffff0
 0x000051cd      push rax
 0x000051ce      push rsp
(S1 struct_1)
 x : 0x000051cf = [ 2315619660, 1207959810, 34803085 ]
 y : 0x000051db = [ 2370306049, 4293315645, 3860201471, 4093649307 ]
 z : 0x000051eb = 4464399
 0x000051f0      lea rdi, loc._edata         ; 0x21f248
 0x000051f7      push rbp
 0x000051f8      lea rax, loc._edata         ; 0x21f248
 0x000051ff      cmp rax, rdi
 0x00005202      mov rbp, rsp
```

Once the struct is linked, Rizin tries to propagate structure offset in the function at the current 
offset, to run this analysis on the whole program or at any targeted functions after all structs are 
linked you have `aat` command:

```
[0x00000000]> aat?
Usage: aat [<func_name>]   # Analyze all/given function to convert immediate to linked structure offsets
```

Note sometimes the emulation may not be accurate, for example as below:

````
|0x000006da  push rbp
|0x000006db  mov rbp, rsp
|0x000006de  sub rsp, 0x10
|0x000006e2  mov edi, 0x20               ; "@"
|0x000006e7  call sym.imp.malloc         ;  void *malloc(size_t size)
|0x000006ec  mov qword [local_8h], rax
|0x000006f0  mov rax, qword [local_8h]

````

The return value of `malloc` may differ between two emulations, so you have to set the hint for return 
value manually using `ahr` command, so run `tl` or `aat` command after setting up the return value hint.

```
[0x000006da]> ahr?
Usage: ahr <return>   # Set function return value hint
```

### Structure Immediates

There is one more important aspect of using types in rizin - using `aht` you
can change the immediate in the opcode to the structure offset.
Let's see a simple example of [R]SI-relative addressing

```
[0x000052f0]> pd 1
0x000052f0      mov rax, qword [rsi + 8]    ; [0x8:8]=0
```
Here `8` - is some offset in the memory, where `rsi` probably holds
some structure pointer. Imagine that we have the following structures
```

[0x000052f0]> td "struct ms { char b[8]; int member1; int member2; };"
[0x000052f0]> td "struct ms1 { uint64_t a; int member1; };"
[0x000052f0]> td "struct ms2 { uint16_t a; int64_t b; int member1; };"
```
Now we need to set the proper structure member offset instead of `8` in this instruction.
At first, we need to list available types matching this offset:

```
[0x000052f0]> ahts 8
ms.member1
ms1.member1
```

Note, that `ms2` is not listed, because it has no members with offset `8`.
After listing available options we can link it to the chosen offset at
the current address:

```
[0x000052f0]> aht ms1.member1
[0x000052f0]> pd 1
0x000052f0      488b4608       mov rax, qword [rsi + ms1.member1]    ; [0x8:8]=0
```

### Managing enums

* Printing all fields in enum using `te` command

```
[0x00000000]> td "enum Foo {COW=1,BAR=2};"
[0x00000000]> te Foo
COW = 0x1
BAR = 0x2
```

* Finding matching enum member for given bitfield and vice-versa

```
[0x00000000]> te Foo 0x1
COW
[0x00000000]> teb Foo COW
0x1
```
