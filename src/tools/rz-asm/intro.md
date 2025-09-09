# Rz-asm

`rz-asm` is an inline assembler/disassembler. Its main function is to get bytes corresponding to given machine
instruction opcode.

```bash
$ rz-asm -h
Usage: rz-asm [-ACdDehLBvw] [-a arch] [-b bits] [-m plugin] [-o addr] [-s syntax]
             [-f file] [-F fil:ter] [-i skip] [-l len] 'code'|hex|-
 -a arch     Set architecture to assemble/disassemble (see -L)
 -A          Show Analysis information from given hexpairs
 -b bits     Set cpu register size (8, 16, 32, 64) (RZ_ASM_BITS)
 -B          Binary input/output (-l is mandatory for binary input)
 -c cpu      Select specific CPU (depends on arch)
 -C          Output in C format
 -d, -D      Disassemble from hexpair bytes (-D show hexpairs)
 -e          Use big endian instead of little endian
 -I          Display lifted RzIL code (same input as in -d, IL is also validated)
 -E          Display ESIL expression (same input as in -d)
 -f file     Read data from file
 -F in:out   Specify input and/or output filters (att2intel, x86.pseudo, ...)
 -h, -hh     Show this help, -hh for long
 -i len      Ignore N bytes of the input buffer
 -j          Output in JSON format
 -k kernel   Select operating system (linux, windows, darwin, ..)
 -l len      Input/Output length
 -L          List Asm plugins: (a=asm, d=disasm, A=analyze, e=ESIL, I=RzIL)
 -m plugin   List supported CPUs for the chosen plugin
 -o, -@ addr Set start address for code (default 0)
 -O file     Output file name (rz-asm -Bf a.asm -O a)
 -p          Run SPP over input for assembly
 -q          Quiet mode
 -r          Output in rizin commands
 -s syntax   Select syntax (intel, att)
 -v          Show version information
 -x          Use hex dwords instead of hex pairs when assembling.
 -w          Describe opcode
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

```bash
$ rz-asm -L
_dAeI 8 16       6502        LGPL3   6502/NES/C64/Tamagotchi/T-1000 CPU
adAeI 8          8051        PD      Intel 8051 disassembler
_dA__ 64         alpha       LGPL3   DEC Alpha Capstone-based disassembler
_dA__ 32         amd29k      LGPL3   AMD 29k RISC disassembler (by deroad)
_dA__ 16 32      arc         GPL3    Argonaut RISC Core
adAeI 16 32 64   arm         BSD     ARM Capstone-based disassembler
a____ 16 32 64   arm.as      LGPL3   as ARM Assembler (use RZ_ARM32_AS and RZ_ARM64_AS environment) (by pancake)
adAeI 8 16       avr         LGPL3   Atmel AVR disassembler
adA_I 16 32 64   bf          LGPL3   Brainfuck (by pancake, nibble) v4.0.0
_dA__ 32         chip8       LGPL3   Chip8 disassembler
_dA__ 16 32 64   cil         LGPL3   .NET CIL/MSIL (Common Intermediate Language) bytecode disassembler
_dA__ 16         cr16        LGPL3   CompactRISC CR16 disassembler
_dA__ 32         cris        GPL3    Axis Communications 32-bit embedded processor disassembler (by pancake)
adA__ 32 64      dalvik      LGPL3   Dalvik (Android VM) bytecode disassembler
ad___ 16         dcpu16      PD      Mojang′s DCPU-16 disassembler
_dA__ 32 64      ebc         LGPL3   EFI bytecode disassembler (by Fedor Sakharov)
adAeI 16         gb          LGPL3   GameBoy(TM) (z80-like) (by condret)
_dAe_ 8 16 32 64 ghidra      LGPL3   SLEIGH Disassembler from Ghidra (by FXTi)
_dAeI 16         h8300       LGPL3   Hitachi/Renesas H8/300 disassembly plugin
_dA_I 32         hexagon     LGPL3   Qualcomm Hexagon (QDSP6) V6 (by Rot127)
_d___ 32         hppa        GPL3    HP PA-RISC
_dA__ 4          i4004       LGPL3   Intel 4004 disassembler
_dA__ 8          i8080       BSD     Intel 8080 disassembler
adA__ 32         java        LGPL-3  Java bytecode disassembler (by deroad)
_d___ 32         lanai       GPL3    Google LANAI disassembler
_d___ 8          lh5801      LGPL3   SHARP LH5801 disassembler
_d___ 32         lm32        BSD     Lattice Micro 32 ISA disassembler (by Felix Held)
_dA__ 32 64      loongarch   LGPL3   Loongson LoongArch disassembler
adA__ 8          luac        LGPL3   Lua bytecode (LUAC) disassembler
_dA__ 8 32       m680x       BSD     Motorola 680X Capstone-based disassembler
_dA__ 32         m68k        BSD     Motorola 68K Capstone-based disassembler
_dA__ 32         malbolge    LGPL3   Malbolge Ternary VM bytecode disassembler (by condret)
_dA__ 32         mcore       LGPL3   Motorola MCORE disassembler
_d___ 16         mcs96       LGPL3   Intel MCS-96 disassembler (by condret)
adAeI 16 32 64   mips        BSD     MIPS Capstone-based disassembler
_dA_I 16         msp430      LGPL3   Texas Instruments MSP430 disassembler
adA__ 16 32 64   null        MIT     NULL (empty) disassembler (by pancake) v1.0.0
_dA__ 32         or1k        LGPL3   OpenRISC 1000 disassembler
_dAeI 16 32      pic         LGPL3   Microchip PIC disassembler
_dAeI 32 64      ppc         BSD     PowerPC Capstone-based disassembler (by pancake)
a____ 32 64      ppc.as      LGPL3   as PPC Assembler (use RZ_PPC_AS environment) (by eagleoflqj)
_dA__ 32         propeller   LGPL3   Parallax Propeller disassembler
_dA__ 8 16       pyc         LGPL3   Python bytecode (PYC) disassembler
_dAe_ 32 64      riscv       GPL3    RISC-V disassembler
_dA__ 32 64      riscv.cs    BSD     RISC-V Capstone-based disassembler
adA__ 32         rl78        LGPL3   Renesas RL78 disassembler (by Bastian Engel)
_dA__ 32         rsp         LGPL3   Nintendo N64 Reality Signal Processor disassembler
_dA__ 32         rx          LGPL3   Renesas RX Family disassembler (by Heersin)
adAeI 32         sh          LGPL3   Hitachi/Renesas SuperH-4 disassembler (by DMaroo)
_dA__ 8 16       snes        LGPL3   SuperNES CPU disassembler
_dA_I 32 64      sparc       BSD     Sun SPARC Capstone-based disassembler
_dA__ 16         spc700      LGPL3   Sony SPC700 (Nintendo SuperNES sound-chip) disassembler
_dA__ 32 64      sysz        BSD     IBM SystemZ (S/390) Capstone-based disassembler
_dA__ 32         tms320      LGPL3   Texas Instruments TMS320 DSP family (c54x,c55x,c55x+,c64x) disassembler
_dA_I 32         tricore     BSD     Siemens TriCore Capstone-based disassembler (by billow)
_dAeI 32         v810        LGPL3   NEC V810 disassembler (by pancake)
_dAeI 32         v850        LGPL3   NEC/Renesas V850 disassembler
_dA__ 8 32       vax         GPL3    DEC VAX disassembler
adA__ 32         wasm        MIT     WebAssembly disassembler (by cgvwzq) v0.1.0
_dAeI 16 32 64   x86         MIT     X86/X86_64 Zydis-based disassembler
a____ 16 32 64   x86.as      LGPL3   Intel X86 GNU Assembler (Use RZ_X86_AS env)
a____ 16 32 64   x86.nasm    LGPL3   X86 nasm assembler
a____ 16 32 64   x86.nz      LGPL3   x86 handmade assembler
_dA__ 16         xap         PD      Cambridge Consultants XAP4 RISC (CSR) disassembler
_dA__ 32         xcore       BSD     XCore Capstone-based disassembler (by pancake)
_dAeI 32         xtensa      LGPL3   Tensilica Xtensa Capstone-based disassembler (by billow)
adA__ 8          z80         GPL3    Zilog Z80 disassembler (by condret)
```

> Note that "ad" in the first column means both assembler and disassembler are offered by a corresponding  plugin.
> "_d" indicates disassembler, "a_" means only assembler is available.



