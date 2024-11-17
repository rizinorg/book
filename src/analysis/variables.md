# Managing variables

Rizin allows managing local variables, no matter their location, stack or registers.
The variables' auto analysis is enabled by default but can be disabled with `analysis.vars`
configuration option.

The main variables commands are located in `afv` namespace:

```
[0x00001100]> afv?
Usage: afv<?>   # Manipulate arguments/variables in a function
| afvl[j*lt]               # List all variables and arguments of the current function
| afv=                     # List function variables and arguments with disasm refs
| afv- <varname|*>         # Remove all variables/arguments or just the specified one
| afva                     # Analyze function arguments/locals
| afvd [<varname>]         # Display the value of arguments/variables
| afvf                     # Show BP relative stackframe variables
| afvn <new_name> [<old_name>] # Rename argument/variable in current function
| afvR [<varname>]         # List addresses where vars are accessed (READ)
| afvW [<varname>]         # List addresses where vars are accessed (WRITE)
| afvt <varname> <type>    # Change type for given argument/local
| afvx[jav]                # Show argument/variable xrefs in a function
| afvs[j*-gs?]             # Manipulate stack-based arguments/locals
| afvr[j*-gs?]             # Manipulate register-based arguments/locals
```

`afvr` and `afvs` commands are uniform but allow manipulation of
register-based arguments and variables, and SP-based arguments and variables respectively.
If we check the help for `afvr` we will get the way two others commands works too:

```
[0x00001100]> afvr?
Usage: afvr[j*-gs?]   # Manipulate register-based arguments/locals
| afvr[j*] [<reg> <name> [<type>]] # List register-based arguments and locals / Define a new one
| afvr- <varname>            # Delete register-based argument/local with the given name
| afvr-*                     # Delete all register-based arguments/locals
| afvrg <reg> <addr>         # Define register-based arguments and locals get references
| afvrs <reg> <addr>         # Define register-based arguments and locals set references
```

Like many other things variables detection is performed by Rizin automatically, but results
can be changed with those arguments/variables control commands. This kind of analysis
relies heavily on preloaded function prototypes and the calling-convention, thus loading symbols
can improve it. Moreover, after changing something we can rerun variables analysis with
`afva` command. Quite often variables analysis is accompanied by
[types analysis](types.md), see `afta` command.

The most important aspect of reverse engineering - naming things. Of course, you can rename
a variable too, affecting all places it was referenced. This can be achieved with `afvn` for
_any_ type of argument or variable. Or you can simply remove the variable or argument with
`afv-` command.

As mentioned before the analysis loop relies heavily on types information while performing
variables analysis stages. Let's see all variables that found by Rizin:

```
[0x000011e9]> afvs
var unknown_t var_48h @ stack - 0x48
var unknown_t var_3ch @ stack - 0x3c
var unknown_t var_30h @ stack - 0x30
var unknown_t var_28h @ stack - 0x28
var unknown_t var_20h @ stack - 0x20
var unknown_t var_18h @ stack - 0x18
var unknown_t var_10h @ stack - 0x10
```

`unknown_t` means an "undefined" default type for variable whose exact type can't be inferred. Thus comes very
important command - `afvt`, which allows you to change the type of variable:

```
[0x000011e9]> afvt var_48h const char *

[0x000011e9]> afvs
var const char *var_48h @ stack - 0x48
var unknown_t var_3ch @ stack - 0x3c
var unknown_t var_30h @ stack - 0x30
var unknown_t var_28h @ stack - 0x28
var unknown_t var_20h @ stack - 0x20
var unknown_t var_18h @ stack - 0x18
var unknown_t var_10h @ stack - 0x10
```

Less commonly used feature, which is still under heavy development - distinction between
variables being read and written. You can list those being read with `afvR` command and those
being written with `afvW` command. Both commands provide a list of the places those operations
are performed:

```
[0x000011e9]> afvR
   var_3ch
   var_48h
   var_30h  0x1212,0x1254
   var_28h  0x1222,0x1267
   var_20h  0x1232
   var_18h  0x1236
   var_10h  0x124d,0x1258,0x126b,0x127a,0x1286

[0x00003b92]> afvW
[0x000011e9]> afvW
   var_3ch  0x11f5
   var_48h  0x11f8
   var_30h  0x1203
   var_28h  0x120e
   var_20h  0x121e
   var_18h  0x122e
   var_10h  0x1249
[0x00003b92]>
```

## Type inference

The type inference for local variables and arguments is well integrated with the command `aft`.

Let's see an example of this with a simple
[hello_world](https://github.com/rizinorg/book/tree/master/examples/hello_world) binary:

```
[0x00001100]> aa
[x] Analyze all flags starting with sym. and entry0 (aa)

[0x00001100]> s main

[0x000011e9]> pdf
            ; DATA XREF from entry0 @ 0x1118
/ int main(int argc, char **argv, char **envp);
|           ; arg int argc @ rdi
|           ; arg char **argv @ rsi
|           ; var int64_t var_48h @ stack - 0x48
|           ; var int64_t var_3ch @ stack - 0x3c
|           ; var int64_t var_30h @ stack - 0x30
|           ; var int64_t var_28h @ stack - 0x28
|           ; var int64_t var_20h @ stack - 0x20
|           ; var int64_t var_18h @ stack - 0x18
|           ; var int64_t var_10h @ stack - 0x10
|           0x000011e9      endbr64
|           0x000011ed      push  rbp
|           0x000011ee      mov   rbp, rsp
|           0x000011f1      sub   rsp, 0x40
|           0x000011f5      mov   dword [var_3ch], edi                 ; argc
|           0x000011f8      mov   qword [var_48h], rsi                 ; argv
|           0x000011fc      lea   rax, [str.Hello]                     ; 0x2004 ; "Hello "
|           0x00001203      mov   qword [var_30h], rax
|           0x00001207      lea   rax, [str.world]                     ; 0x200b ; "world!"
|           0x0000120e      mov   qword [var_28h], rax
|           0x00001212      mov   rax, qword [var_30h]
|           0x00001216      mov   rdi, rax
|           0x00001219      call  sym.imp.strlen                       ; sym.imp.strlen ; size_t strlen(const char *s)
|           0x0000121e      mov   qword [var_20h], rax
|           0x00001222      mov   rax, qword [var_28h]
|           0x00001226      mov   rdi, rax
|           0x00001229      call  sym.imp.strlen                       ; sym.imp.strlen ; size_t strlen(const char *s)
|           0x0000122e      mov   qword [var_18h], rax
|           0x00001232      mov   rdx, qword [var_20h]
|           0x00001236      mov   rax, qword [var_18h]
|           0x0000123a      add   rax, rdx
|           0x0000123d      add   rax, 1
|           0x00001241      mov   rdi, rax
|           0x00001244      call  sym.imp.malloc                       ; sym.imp.malloc ; void *malloc(size_t size)
|           0x00001249      mov   qword [var_10h], rax
|           0x0000124d      cmp   qword [var_10h], 0
|       ,=< 0x00001252      je    0x1292
|       |   0x00001254      mov   rdx, qword [var_30h]
|       |   0x00001258      mov   rax, qword [var_10h]
|       |   0x0000125c      mov   rsi, rdx
|       |   0x0000125f      mov   rdi, rax
|       |   0x00001262      call  sym.imp.strcpy                       ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
|       |   0x00001267      mov   rdx, qword [var_28h]
|       |   0x0000126b      mov   rax, qword [var_10h]
|       |   0x0000126f      mov   rsi, rdx
|       |   0x00001272      mov   rdi, rax
|       |   0x00001275      call  sym.imp.strcat                       ; sym.imp.strcat ; char *strcat(char *s1, const char *s2)
|       |   0x0000127a      mov   rax, qword [var_10h]
|       |   0x0000127e      mov   rdi, rax
|       |   0x00001281      call  sym.imp.puts                         ; sym.imp.puts ; int puts(const char *s)
|       |   0x00001286      mov   rax, qword [var_10h]
|       |   0x0000128a      mov   rdi, rax
|       |   0x0000128d      call  sym.imp.free                         ; sym.imp.free ; void free(void *ptr)
|       `-> 0x00001292      mov   eax, 0
|           0x00001297      leave
\           0x00001298      ret
```

After applying `aft`:

```
[0x000011e9]> aeim

[0x000011e9]> aft

[0x000011e9]> pdf
            ; DATA XREF from entry0 @ 0x1118
            ;-- rip:
/ int main(int argc, char **argv, char **envp);
|           ; arg int argc @ rdi
|           ; arg char **argv @ rsi
|           ; var char **var_48h @ stack - 0x48
|           ; var int var_3ch @ stack - 0x3c
|           ; var const char *src @ stack - 0x30
|           ; var const char *s2 @ stack - 0x28
|           ; var size_t var_20h @ stack - 0x20
|           ; var size_t size @ stack - 0x18
|           ; var char *dest @ stack - 0x10
|           0x000011e9      endbr64
|           0x000011ed      push  rbp
|           0x000011ee      mov   rbp, rsp
|           0x000011f1      sub   rsp, 0x40
|           0x000011f5      mov   dword [var_3ch], edi                 ; argc
|           0x000011f8      mov   qword [var_48h], rsi                 ; argv
|           0x000011fc      lea   rax, [str.Hello]                     ; 0x2004 ; "Hello "
|           0x00001203      mov   qword [src], rax
|           0x00001207      lea   rax, [str.world]                     ; 0x200b ; "world!"
|           0x0000120e      mov   qword [s2], rax
|           0x00001212      mov   rax, qword [src]
|           0x00001216      mov   rdi, rax                             ; const char *s
|           0x00001219      call  sym.imp.strlen                       ; sym.imp.strlen ; size_t strlen(const char *s)
|           0x0000121e      mov   qword [var_20h], rax
|           0x00001222      mov   rax, qword [s2]
|           0x00001226      mov   rdi, rax                             ; const char *s
|           0x00001229      call  sym.imp.strlen                       ; sym.imp.strlen ; size_t strlen(const char *s)
|           0x0000122e      mov   qword [size], rax
|           0x00001232      mov   rdx, qword [var_20h]
|           0x00001236      mov   rax, qword [size]
|           0x0000123a      add   rax, rdx
|           0x0000123d      add   rax, 1
|           0x00001241      mov   rdi, rax                             ; size_t size
|           0x00001244      call  sym.imp.malloc                       ; sym.imp.malloc ; void *malloc(size_t size)
|           0x00001249      mov   qword [dest], rax
|           0x0000124d      cmp   qword [dest], 0
|       ,=< 0x00001252      je    0x1292
|       |   0x00001254      mov   rdx, qword [src]
|       |   0x00001258      mov   rax, qword [dest]
|       |   0x0000125c      mov   rsi, rdx                             ; const char *src
|       |   0x0000125f      mov   rdi, rax                             ; char *dest
|       |   0x00001262      call  sym.imp.strcpy                       ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
|       |   0x00001267      mov   rdx, qword [s2]
|       |   0x0000126b      mov   rax, qword [dest]
|       |   0x0000126f      mov   rsi, rdx                             ; const char *s2
|       |   0x00001272      mov   rdi, rax                             ; char *s1
|       |   0x00001275      call  sym.imp.strcat                       ; sym.imp.strcat ; char *strcat(char *s1, const char *s2)
|       |   0x0000127a      mov   rax, qword [dest]
|       |   0x0000127e      mov   rdi, rax                             ; const char *s
|       |   0x00001281      call  sym.imp.puts                         ; sym.imp.puts ; int puts(const char *s)
|       |   0x00001286      mov   rax, qword [dest]
|       |   0x0000128a      mov   rdi, rax                             ; void *ptr
|       |   0x0000128d      call  sym.imp.free                         ; sym.imp.free ; void free(void *ptr)
|       `-> 0x00001292      mov   eax, 0
|           0x00001297      leave
\           0x00001298      ret
```

It also extracts type information from format strings like `printf ("fmt : %s , %u , %d", ...)`,
the format specifications are extracted from `analysis/d/spec.sdb`

You could create a new profile for specifying a set of format chars depending on different libraries/operating
systems/programming languages like this:

```
win=spec
spec.win.u32=unsigned int
```

Then change your default specification to a newly created one using this config variable `e analysis.spec=win`

For more information about primitive and user-defined types support in Rizin refer to [types](types.md) chapter.
