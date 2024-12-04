# Data and Code Analysis

Rizin has a very rich set of commands and configuration options to perform data and code analysis,
to extract useful information from a binary, like pointers, string references,
basic blocks, opcode data, jump targets, cross-references, and much more.
These operations are handled by the `a` (analyze) command family:

```
[0x00001100]> a?
Usage: a  [abdefFghoprxstc] [...]
| a*                 same as afl*;ah*;ax*
| aa[?]              analyze all (fcns + bbs) (aa0 to avoid sub renaming)
| a8 [hexpairs]      analyze bytes
| ab[?] [addr]       analyze block
| ad[?]              analyze data trampoline (wip)
| ad [from] [to]     analyze data pointers to (from-to)
| ae[?] [expr]       analyze opcode eval expression (see ao)
| af[?]              analyze Functions
| aF                 same as above, but using analysis.depth=1
| ag[?] [options]    draw graphs in various formats
| ah[?]              analysis hints (force opcode size, ...)
| ai [addr]          address information (show perms, stack, heap, ...)
| aj                 same as a* but in json (aflj)
| aL                 list all asm/analysis plugins (e asm.arch=?)
| an [name] [@addr]  show/rename/create whatever flag/function is used at addr
| ao[?] [len]        analyze Opcodes (or emulate it)
| aO[?] [len]        Analyze N instructions in M bytes
| ap                 find prelude for current offset
| ar[?]              like 'dr' but for the esil vm. (registers)
| as[?] [num]        analyze syscall using dbg.reg
| av[?] [.]          show vtables
| ax[?]              manage refs/xrefs (see also afx?)
```

In fact, `a` namespace is one of the biggest in rizin tool and allows to control
very different parts of the analysis:

 - Code flow analysis
 - Data references analysis
 - Using loaded symbols
 - Managing different type of graphs, like CFG and call graph
 - Manage variables
 - Manage types
 - Emulation using ESIL VM
 - Opcode introspection
 - Objects information, like virtual tables
