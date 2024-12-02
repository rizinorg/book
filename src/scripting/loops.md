# Loops

One of the most common task in automation is looping through something,
there are multiple ways to do this in rizin. You can find all these loops
under `@@?`.

We can loop over flags:

```
@@f:flagname-regex
```

For example, we want to see function information with `afi` command:

```
[0x004047d6]> afi
#
offset: 0x004047d0
name: entry0
size: 42
realsz: 42
stackframe: 0
call-convention: amd64
cyclomatic-complexity: 1
bits: 64
type: fcn [NEW]
num-bbs: 1
edges: 0
end-bbs: 1
call-refs: 0x00402450 C
data-refs: 0x004136c0 0x00413660 0x004027e0
code-xrefs:
data-xrefs:
locals:0
args: 0
diff: type: new
[0x004047d6]>
```
Now let's say, for example, that we'd like see a particular field from this output for all functions found by analysis.
We can do that with a loop over all function flags (whose names begin with `fcn.`):

```
[0x004047d6]> fs functions
[0x004047d6]> afi @@f:fcn.* ~name
```

This command will extract the `name` field from the `afi` output of every flag with a name
matching the regexp `fcn.*`.

There are other loops, for example one called `@@F` runs your command on every function found by rizin:

```
[0x004047d6]> afi @@F ~name
```  

We can also loop over a list of offsets, using the following syntax:

```
@@=1 2 3 ... N
```
For example, say we want to see the opcode information for 2 offsets: the current one, and at current + 2:

```
[0x004047d6]> ao @@=$$ $$+2
address: 0x4047d6
opcode: mov rdx, rsp
prefix: 0
bytes: 4889e2
refptr: 0
size: 3
type: mov
esil: rsp,rdx,=
stack: null
family: cpu
address: 0x4047d8
opcode: loop 0x404822
prefix: 0
bytes: e248
refptr: 0
size: 2
type: cjmp
esil: 1,rcx,-=,rcx,?{,4212770,rip,=,}
jump: 0x00404822
fail: 0x004047da
stack: null
cond: al
family: cpu
```

Note we're using the `$$` variable which evaluates to the current offset. Also note
that `$$+2` is evaluated before looping, so we can use the simple arithmetic expressions.

A third way to loop is by having the offsets be loaded from a file. This file should contain
one offset per line.

```
[0x004047d0]> ?v $$ > offsets.txt
[0x004047d0]> ?v $$+2 >> offsets.txt
[0x004047d0]> !cat offsets.txt
4047d0
4047d2
[0x004047d0]> pi 1 @@.offsets.txt
xor ebp, ebp
mov r9, rdx
```

If you want to iterate over all instructions of a basic block, you can do:

```
[0x004047d0]> pi 1 @@i
endbr64
push rbx
test rdi, rdi
je 0x14635
```

In this example the command `pi 1` runs over all the instructions in the current basic block.

If you want to iterate over all instructions of all basic blocks of the current function, you can do:
```
[0x004047d0]> pi 1 @@i @@b
endbr64     
push rbx            
test rdi, rdi
je 0x14635
mov esi, 0x2f    
mov rbx, rdi
[... cut for example ...]
mov rbx, r8                                                                                    
jmp 0x1461a         
mov rax, qword [reloc.stderr]
mov edx, 0x37     
mov esi, 1            
lea rdi, str.A_NULL_argv_0__was_passed_through_an_exec_system_call.                            
mov rcx, qword [rax]
call sym.imp.fwrite
call sym.imp.abort
```

Or if you want to make the split between basic blocks clearer:

```
[0x004047d0]> (_;pi 1 @@i; ?e)() @@b
endbr64     
push rbx            
test rdi, rdi
je 0x14635

mov esi, 0x2f    
mov rbx, rdi
[... cut for example ...]
mov rbx, r8                                                                                    
jmp 0x1461a         

mov rax, qword [reloc.stderr]
mov edx, 0x37     
mov esi, 1            
lea rdi, str.A_NULL_argv_0__was_passed_through_an_exec_system_call.                            
mov rcx, qword [rax]
call sym.imp.fwrite
call sym.imp.abort
```
