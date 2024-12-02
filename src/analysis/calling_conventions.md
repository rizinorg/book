# Calling Conventions

Rizin uses calling conventions to help in identifying function formal arguments and return types.
It is used also as a guide for basic function prototype and type propagation.

```
[0x00000000]> afc?
Usage: afc[lor]   # Calling convention
| afc [<convention>] # Set/Get calling convention for current function
| afcl[j*kl]         # List all available calling conventions
| afco <db_path>     # Open Calling Convention sdb profile from given path
| afcr[j]            # Show register usage for the current function
[0x00000000]>
```

To list all available calling conventions for current architecture using `afcl` command

```
[0x00000000]> afcl
amd64
amd64syscall
ms
reg
swift
```

The default calling convention for a particular architecture/binary is defined with
`analysis.cc` for user-mode calls and `analysis.syscc` for syscalls.

All this information is loaded via sdb under `/librz/analysis/d/cc-[arch]-[bits].sdb`

```
default.cc=amd64

ms=cc
cc.ms.name=ms
cc.ms.arg1=rcx
cc.ms.arg2=rdx
cc.ms.arg3=r8
cc.ms.arg3=r9
cc.ms.argn=stack
cc.ms.ret=rax
```

`cc.x.argi=rax` is used to set the ith argument of this calling convention to register name `rax`

`cc.x.argn=stack` means that all the arguments (or the rest of them in case there was `argi` for any `i` as
counting number) will be stored in the stack from left to right

`cc.x.argn=stack_rev` same as `cc.x.argn=stack` except for it means argument are passed right to left
