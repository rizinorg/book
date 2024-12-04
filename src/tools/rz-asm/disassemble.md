## Disassembler

Disassembling is the inverse action of assembling. Rz-asm takes hexpair as an input (but can also take a file
in binary form) and show the human-readable form.

To do this we can use the `-d` option of rz-asm like this:

```
$ rz-asm -a x86 -b 32 -d '90'
nop
```

Rz-asm also has the `-D` flag to show the disassembly like `-d` does, but includes offset and bytes.

In Rizin there are many commands to perform a disassembly from a specific place in memory.

You might be interested in trying if you want different outputs for later parsing with your scripts, or just grep
to find what you are looking for:

### pd N

Disassemble N instructions

### pD N

Disassemble N bytes

### pda

Disassemble all instructions (seeking 1 byte, or the minimum alignment instruction size), which can be useful for ROP

## pi, pI

Same as `pd` and `pD`, but using a simpler output.
