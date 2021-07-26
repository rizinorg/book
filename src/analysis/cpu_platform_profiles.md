# CPU and platform profiles

## The motivation 

The computer ecosystem, especially in embedded systems is vast and growing and is thus 
diverse and is full of trivial differences. CPUs and development boards differ by minor and sometimes 
large differences in their design, ports, MMIO registers and other peripherals. Rizin handles these 
differences by storing the data regarding each CPUs and platforms in [SDB](https://book.rizin.re/basic_commands/sdb.html?highlight=SDB#sdb) files in a standard format, instead of hardcoding them with each of the 
disassembler plugins. This information will be parsed and added as flags and comments during the analysis
loop and will show up in the disassembly and other places, making reverse engineering on those particular 
chips ets is much easier. This also helps in easy addition of a new port, in maintenance and in user-friendliness. 

## How it works

### CPU profiles

All the specifics pertaining to a CPU is written down in a CPU profile. It is designed in a way that allows you 
to enter CPU specefic values like: size of the RAM (`RAM_SIZE`), size of the ROM (`ROM_SIZE`) and many more. 
CPU profiles can be selected using the configuration variable `asm.cpu`. Firstly, Rizin checks whether the
a CPU profile exists for the selected CPU and architecture. If it exists, Rizin generates the filepath of the
profile and gets to a stage where it's ready to be loaded up. During analysis (`aa`), it's loaded up and the values are 
parsed and handled. CPU profiles also allow you to add information regarding the IO and extended IO registers of a CPU. 
The information pertaining to the IO and extended IO registers are added as flags at their corresponding offsets. 

The CPU profile of AVR's ATTiny88 CPU looks like this:

```config
RAM_SIZE=512
ROM_SIZE=8192
INTERRUPT_VECTOR_SIZE=2

PINB=io
PINB.address=0x03
DDRB=io
DDRB.address=0x04
PORTB=io
```
Here, `PINB` is the name and `io` is the type of the port and this will be added as a 
flag at the offset `0x03`. The type can be `ext_io` if it's an extended IO register, as well. Both will be added 
as [flags](https://book.rizin.re/basic_commands/flags.html?highlight=flags#flags) and the only difference between 
them is that they will be added in different [flagspaces](https://book.rizin.re/refcard/intro.html?highlight=flagspa#flagspaces).

CPU profiles also support mapping the ROM. According the `ROM_ADDRESS` and `ROM_SIZE`, a [section](https://book.rizin.re/basic_commands/sections.html?highlight=section#sections) named `.rom` will be added during analysis.

#### Adding CPU profiles

CPU profiles are stored in SDB files under the directory `lirbz/asm/cpus` and that's where you will have to put
your new profile. The files follow a naming convention like `arch-cpu`. You can see the complete list of things 
that are parsed at `librz/analysis/arch_profile.c` and if necessary, a new key can be easily added.

To add a new CPU profile, firstly make sure that you have the name of the CPU defined in the list of CPUs defined
by the variable `cpus` in the corresponding architecture's disassembler plugin (`RzAsmPlugin`). Then, simply add 
the SDB file in the directory, add the entry in the `meson.build` of the same directory and build again. Choose 
the right CPU and architecture and analyze again (`aa`) to load up the CPU profile.

For reference, you can see the previously added CPU profile of ATmega16 here: [librz/asm/cpus/avr-ATmega16.sdb.txt](https://github.com/rizinorg/rizin/blob/dev/librz/asm/cpus/avr-ATmega16.sdb.txt). 

### Platform profiles

Platform profiles are designed with an idea to support adding information that is pertaining to a specific board
or a micro controller. For example, most of the Raspberry Pi-s use a specific Broadcom chip and its peripherals 
like registers and interrupts will be the same for all Raspberry Pi-s. These profiles can be selected using the 
configuration variable `asm.platforms` and is loaded during analysis (`aa`). If you run `e asm.platform=?`, you 
can see the supported platforms by the selected architecture and CPU.

Let's have a look at Broadcom 2835's platform profile:

```config
AUX_IRQ=name
AUX_IRQ.address=0x7e215000
AUX_IRQ.comment=Auxiliary Interrupt status

AUX_MU_IO_REG=name
AUX_MU_IO_REG.address=0x7e215040
AUX_MU_IO_REG.comment=Mini UART I/O Data
```

Just like in CPU profiles, the `name` will be added as a flag and the `comment` as a [comment](https://book.rizin.re/disassembling/adding_metadata.html?highlight=Comment#adding-metadata-to-disassembly) (`CCu`).

#### Adding platform profiles

Platform profiles are stored in `librz/asm/platforms/` and that's where you will have to put your profile. They
follow a naming convention like `arch-cpu-platform`.

To add a new platform profile, we will have to define the name of the platform in the variable `platforms` in 
the `RzAsmPlugin` definition corresponding architecture's disassembler plugin. You will also need to add the 
CPU is it's not already added. Then, add the entry in the `meson.build` of the same directory and build again.
Choose the right CPU, architecture and platform and analyze again (`aa`).

You can also check out the platform profiles that were previously added at [librz/asm/platforms/arm-arm1176-bcm2835.sdb.txt](https://github.com/rizinorg/rizin/blob/dev/librz/asm/platforms/arm-arm1176-bcm2835.sdb.txt).
