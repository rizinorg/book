# Rz-asm

`rz-asm` is an inline assembler/disassembler. Its main function is to get bytes corresponding to given machine
instruction opcode.

```
Usage: rz-asm [-ACdDehLBvw] [-a arch] [-b bits] [-o addr] [-s syntax]
             [-f file] [-F fil:ter] [-i skip] [-l len] 'code'|hex|-
 -a [arch]     Set architecture to assemble/disassemble (see -L)
 -A            Show Analysis information from given hexpairs
 -b [bits]     Set cpu register size (8, 16, 32, 64) (RZ_ASM_BITS)
 -B            Binary input/output (-l is mandatory for binary input)
 -c [cpu]      Select specific CPU (depends on arch)
 -C            Output in C format
 -d, -D        Disassemble from hexpair bytes (-D show hexpairs)
 -e            Use big endian instead of little endian
 -I            Display lifted RzIL code (same input as in -d, IL is also validated)
 -E            Display ESIL expression (same input as in -d)
 -f [file]     Read data from file
 -F [in:out]   Specify input and/or output filters (att2intel, x86.pseudo, ...)
 -h, -hh       Show this help, -hh for long
 -i [len]      Ignore N bytes of the input buffer
 -j            Output in JSON format
 -k [kernel]   Select operating system (linux, windows, darwin, ..)
 -l [len]      Input/Output length
 -L            List Asm plugins: (a=asm, d=disasm, A=analyze, e=ESIL)
 -o, -@ [addr] Set start address for code (default 0)
 -O [file]     Output file name (rz-asm -Bf a.asm -O a)
 -p            Run SPP over input for assembly
 -q            Quiet mode
 -r            Output in rizin commands
 -s [syntax]   Select syntax (intel, att)
 -v            Show version information
 -x            Use hex dwords instead of hex pairs when assembling.
 -w            Describe opcode
 If '-l' value is greater than output length, output is padded with nops
 If the last argument is '-' reads from stdin
Environment:
 RZ_ARCH      e asm.arch # architecture to assemble/disassemble (same as rz-asm -a)
 RZ_ASM_ARCH             # architecture to assemble/disassemble (same as rz-asm -a)
 RZ_ASM_BITS             # cpu register size (8, 16, 32, 64) (same as rz-asm -b)
 RZ_BITS      e asm.bits # cpu register size (8, 16, 32, 64) (same as rz-asm -b)
 RZ_DEBUG                # if defined, show error messages and crash signal
 RZ_NOPLUGINS            # do not load shared plugins (speedup loading)
```

Plugins for supported target architectures can be listed with the `-L` option. Knowing a plugin name,
you can use it by specifying its name to the `-a` option

```
$ rz-asm -L
_dAe  8 16       6502        LGPL3   6502/NES/C64/Tamagotchi/T-1000 CPU
adAe  8          8051        PD      8051 Intel CPU
_dA_  32         amd29k      LGPL3   AMD 29k RISC CPU (by deroad)
a___  16 32 64   arm.as      LGPL3   as ARM Assembler (use RZ_ARM32_AS and RZ_ARM64_AS environment) (by pancake)
adAe  16 32 64   arm         BSD     Capstone ARM disassembler
adAe  8 16       avr         LGPL3   AVR Atmel
adA_  16 32 64   bf          LGPL3   Brainfuck (by pancake, nibble) v4.0.0
_dA_  32         chip8       LGPL3   Chip8 disassembler
_dA_  16 32 64   cil         LGPL3   .NET Common Intermediate Language
_dA_  16         cr16        LGPL3   cr16 disassembly plugin
adA_  32 64      dalvik      LGPL3   AndroidVM Dalvik
ad__  16         dcpu16      PD      Mojang's DCPU-16
_dA_  32 64      ebc         LGPL3   EFI Bytecode (by Fedor Sakharov)
adAe  16         gb          LGPL3   GameBoy(TM) (z80-like) (by condret)
_dAe  16         h8300       LGPL3   H8/300 disassembly plugin
_dA_  32         hexagon     LGPL3   Qualcomm Hexagon (QDSP6) V6 (by Rot127)
_dA_  4          i4004       LGPL3   Intel 4004 microprocessor
_dA_  8          i8080       BSD     Intel 8080 CPU
adA_  32         java        LGPL-3  Java bytecode disassembler (by deroad)
_d__  8          lh5801      LGPL3   SHARP LH5801 disassembler
_d__  32         lm32        BSD     disassembly plugin for Lattice Micro 32 ISA (by Felix Held)
adA_  8          luac        LGPL3   luac disassemble plugin
_dA_  32         m68k        BSD     Capstone M68K disassembler
_dA_  8 32       m680x       BSD     Capstone M680X Disassembler
_dA_  32         malbolge    LGPL3   Malbolge Ternary VM (by condret)
_dA_  32         mcore       LGPL3   Motorola MCORE disassembler
_d__  16         mcs96       LGPL3   condrets car
adAe  16 32 64   mips        BSD     Capstone MIPS disassembler
_dA_  16         msp430      LGPL3   msp430 disassembly plugin
adA_  16 32 64   null        MIT     no disassemble (by pancake) v1.0.0
_dA_  32         or1k        LGPL3   OpenRISC 1000
_dAe  8          pic         LGPL3   PIC disassembler
a___  32 64      ppc.as      LGPL3   as PPC Assembler (use RZ_PPC_AS environment) (by eagleoflqj)
_dAe  32 64      ppc         BSD     Capstone PowerPC disassembler (by pancake)
_dA_  32         propeller   LGPL3   propeller disassembly plugin
_dA_  8 16       pyc         LGPL3   PYC disassemble plugin
adA_  32         rl78        LGPL3   Renesas RL78 disassembler (by Bastian Engel)
_dA_  32         rsp         LGPL3   Reality Signal Processor
_dA_  32         rx          LGPL3   Renesas RX Family disassembler (by Heersin)
adAe  32         sh          LGPL3   SuperH-4 CPU (by DMaroo)
_dA_  8 16       snes        LGPL3   SuperNES CPU
_dA_  32 64      sparc       BSD     Capstone SPARC disassembler
_dA_  16         spc700      LGPL3   spc700, snes' sound-chip
_dA_  32 64      sysz        BSD     SystemZ CPU disassembler
_dA_  32         tms320      LGPLv3  TMS320 DSP family (c54x,c55x,c55x+,c64x)
_d__  32         tms320c64x  BSD     Capstone TMS320c64x disassembler
_dAe  32         v810        LGPL3   v810 disassembly plugin (by pancake)
_dAe  32         v850        LGPL3   v850 disassembly plugin
adA_  32         wasm        MIT     WebAssembly (by cgvwzq) v0.1.0
a___  16 32 64   x86.as      LGPL3   Intel X86 GNU Assembler (Use RZ_X86_AS env)
_dAe  16 32 64   x86         BSD     Capstone X86 disassembler
a___  16 32 64   x86.nasm    LGPL3   X86 nasm assembler
a___  16 32 64   x86.nz      LGPL3   x86 handmade assembler
_dA_  16         xap         PD      XAP4 RISC (CSR)
_dA_  32         xcore       BSD     Capstone XCore disassembler (by pancake)
_dAe  32 64      riscv.cs    BSD     Capstone RISCV disassembler
_dA_  32         tricore     BSD     Siemens TriCore CPU (by billow)
_dA_  16 32      arc         GPL3    Argonaut RISC Core
_dA_  32         cris        GPL3    Axis Communications 32-bit embedded processor (by pancake)
_d__  32         hppa        GPL3    HP PA-RISC
_d__  32         lanai       GPL3    LANAI
adAe  32 64      mips.gnu    GPL3    MIPS CPU
_dA_  32         nios2       GPL3    NIOS II Embedded Processor
_dAe  32 64      riscv       GPL3    RISC-V
_dA_  32 64      sparc.gnu   GPL3    Scalable Processor Architecture
_dA_  8 32       vax         GPL3    VAX
_dAe  32         xtensa      GPL3    XTensa CPU
adA_  8          z80         GPL3    Zilog Z80 (by condret)
_dAe  8 16 32 64   ghidra      LGPL3   SLEIGH Disassembler from Ghidra (by FXTi)
```

> Note that "ad" in the first column means both assembler and disassembler are offered by a corresponding  plugin.
> "_d" indicates disassembler, "a_" means only assembler is available.



