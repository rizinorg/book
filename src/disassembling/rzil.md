# RzIL

RzIL is the new intermediate language in Rizin, primarily intended for representing the semantics of machine code. It is designed as a clone of BAP's [Core Theory](http://binaryanalysisplatform.github.io/bap/api/master/bap-core-theory/Bap_core_theory/), with minor deviations where necessary; it is worth noting that in practice, RzIL is very similar to the SMT representation with bitvectors and bitvector-indexed arrays as well as effects.

More details related to the implementation can be found [here](https://github.com/rizinorg/rizin/blob/dev/doc/rzil.md).

## IL statements

Instructions can are internally represented as [IL statements](https://github.com/rizinorg/rizin/blob/dev/librz/include/rz_il/rz_il_opcodes.h); these statements are expressed as **s-expressions** (symbolic expression) which utilize LISP-like syntax as string format. 

- `aoi` generates a **one-line** LISP-like syntax (JSON format is available via `aoj` command).
- `aoip` generates a **prettified** LISP-like syntax

Here an example using `aoip` (the *prettified* output) of two PowerPC instructions (`stwu` and `mflr`).

```bash
[0x10000488]> pd 2
|           0x10000488      stwu  r1, -0x10(r1)
|           0x1000048c      mflr  r0
[0x10000488]> aoi?
Usage: aoi[p]   # Print the RzIL of next N instructions
| aoi [<n_instructions>]  # Print the RzIL of next N instructions
| aoip [<n_instructions>] # Pretty print the RzIL of next N instructions
[0x10000488]> aoip 2
0x10000488
(seq
  (storew 0
    (+
      (var r1)
      (let v
        (bv 16 0xfff0)
        (ite
          (msb
            (var v))
          (cast 32
            (msb
              (var v))
            (var v))
          (cast 32
            false
            (var v)))))
    (cast 32
      false
      (var r1)))
  (set r1
    (+
      (var r1)
      (let v
        (bv 16 0xfff0)
        (ite
          (msb
            (var v))
          (cast 32
            (msb
              (var v))
            (var v))
          (cast 32
            false
            (var v)))))))
0x1000048c
(set r0
  (cast 32
    false
    (var lr)))
```

The `plf` command allows to generate an in-line representation of the entire function in s-expressions.

```bash
[0x100002bc]> pdf @ sym.example
/ sym.example();
|           ; var int32_t var_1ch @ stack - 0x1c
|           0x1000044c      stwu  r1, -0x10(r1)
|           0x10000450      mflr  r0
|           0x10000454      stw   r0, 0x14(r1)
|           0x10000458      lwz   r0, 0x14(r1)
|           0x1000045c      addi  r1, r1, 0x10
|           0x10000460      mtlr  r0
\           0x10000464      blr
[0x100002bc]> plf @ sym.example
0x1000044c (seq (storew 0 (+ (var r1) (let v (bv 16 0xfff0) (ite (msb (var v)) (cast 32 (msb (var v)) (var v)) (cast 32 false (var v))))) (cast 32 false (var r1))) (set r1 (+ (var r1) (let v (bv 16 0xfff0) (ite (msb (var v)) (cast 32 (msb (var v)) (var v)) (cast 32 false (var v)))))))
0x10000450 (set r0 (cast 32 false (var lr)))
0x10000454 (seq (storew 0 (+ (var r1) (let v (bv 16 0x14) (ite (msb (var v)) (cast 32 (msb (var v)) (var v)) (cast 32 false (var v))))) (cast 32 false (var r0))) empty)
0x10000458 (seq (set r0 (let ea (+ (var r1) (let v (bv 16 0x14) (ite (msb (var v)) (cast 32 (msb (var v)) (var v)) (cast 32 false (var v))))) (let loadw (loadw 0 32 (var ea)) (cast 32 false (var loadw))))) empty)
0x1000045c (seq (set a (var r1)) (set b (let v (bv 16 0x10) (ite (msb (var v)) (cast 32 (msb (var v)) (var v)) (cast 32 false (var v))))) empty (set r1 (+ (var a) (var b))) empty empty empty)
0x10000460 (set lr (cast 32 false (var r0)))
0x10000464 (seq (set CIA (bv 32 0x10000464)) empty empty (set NIA (& (bv 32 0xfffffffc) (var lr))) (jmp (var NIA)))
[0x100002bc]> 
```

The same output of `aoi` can be obtained via `rz-asm` like this:

```bash
$ rz-asm -de -a ppc 7c0802a6
mflr r0
$ rz-asm -Ie -a ppc 7c0802a6
(set r0 (cast 32 false (var lr)))
```

## Emulation

Rizin enables instruction emulation by leveraging RzIL. The emulation can be used to record changes within the VM, like read and writes of registers and memory locations (`e io.buffers=true` is required for memory ops). The emulation is controlled via the `aez` commands.

```bash
[0x00000000]> aez?
Usage: aez<isv?>   # RzIL Emulation
| aezi                     # Initialize the RzIL Virtual Machine at the current offset
| aezs [<n_times>]         # Step N instructions within the RzIL Virtual Machine
| aezse[j] [<n_times>]     # Step N instructions within the RzIL VM and output VM changes (read &
                             write)
| aezsu <address>          # Step until PC equals given address
| aezsue <address>         # Step until PC equals given address and output VM changes (read & write)
| aezv[jqt] [<var_name> [<number>]] # Print or modify the current status of the RzIL Virtual Machine
```

Supported architectures can be inspected via the `La` command. If the architecture has an `I`, as in the example below, it supports RzIL.

```bash
_dAeI 32 64      ppc         BSD     Capstone PowerPC disassembler
```

Here is an example of emulation of a PowerPC binary printing a string via *printf*.

In this example, `r9` contains the base address which is used to calculate the pointer to the string (stored in `r3`) used by 'reloc.printf'.

```bash
[0x1000049c]> pd 3
|           0x1000049c      lis   r9, 0x1000
|           0x100004a0      addi  r3, r9, 0x640
|           0x100004a4      bl    reloc.printf
```

First we need to initialize the RzIL Virtual Machine at the current offset using `aezi`

```bash
[0x1000049c]> aezi?
Usage: aezi   # Initialize the RzIL Virtual Machine at the current offset
[0x1000049c]> aezi
```

Then we execute 2 instructions via `aezs` (quiet) or use `aezse` to see the actual changes within the RzIL VM.

```bash
[0x1000049c]> aezse?
Usage: aezse[j] [<n_times>]   # Step N instructions within the RzIL VM and output VM changes (read & write)
[0x1000049c]> aezse 2 # execute 2 instructions
pc_write(old: 0x1000049c, new: 0x100004a0)
var_write(name: r9, old: 0x0, new: 0x10000000)
pc_write(old: 0x100004a0, new: 0x100004a4)
var_write(name: r3, old: 0x0, new: 0x10000640)
```

It's possible to see (or modify) the values of the registers in the RzIL VM via `aezv`.

```bash
[0x1000049c]> # We can also print the content of the RzIL VM via 'aezv'
[0x1000049c]> aezv?
Usage: aezv[jqt] [<var_name> [<number>]]   # Print or modify the current status of the RzIL Virtual Machine
[0x1000049c]> aezv r3
 r3: 0x10000640
[0x1000049c]> aezv r9
 r9: 0x10000000
```

Now that we know that the string is situated at `0x10000640`, we can print it.

```bash
[0x1000049c]> # hexdump the content of address 0x10000640 with a buffer size of 0x20 bytes.
[0x1000049c]> px @ 0x10000640 @! 0x20
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x10000640  5369 6d70 6c65 2050 5043 2070 726f 6772  Simple PPC progr
0x10000650  616d 2e00 0000 0000 ffff ffff ffff ffff  am..............
[0x1000049c]>
[0x1000049c]> # Decode and print the utf-8 string at address 0x10000640
[0x1000049c]> ps @ 0x10000640
Simple PPC program.
[0x1000049c]>
```
