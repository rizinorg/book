## Initial Scripts

Initial scripts like the `rizinrc`, `binrc` or `${filename}.rz` are loaded during startup.

It is possible to prevent Rizin from parsing the scripts, by using the `-N` or `-NN` options.

These scripts are interpreted as commands by the Rizin command-line and can be situated in the following locations:

1. **System directory** (also named as `system` within `rizin -hh`): This location is situated within the system and will be loaded by all users of the system.
2. **User home directory** (also named as `user` within `rizin -hh`): This location is user-specific and will be loaded exclusively for the individual user.
3. **Binary format directory** (also named as `binrc` within `rizin -hh`): This location is user-specific and will be loaded exclusively for the individual user; These scripts will be executed when the matching type of binary is loaded when executing rizin.
4. **Initial binary script** (also named as `file` within `rizin -hh`): When Rizin encounters a script with the same filename as the binary, along with a `.rz` extension, it is loaded and executed. Rizin will display a prompt (unless interactive mode is disabled) upon loading the binary.

The actual paths of these directories depend on the environment, build flags, and operating system, but they can be viewed by executing `rizin -hh` (with double `h`) in the terminal.

**Note**: You can also override the `rizinrc` path within the terminal by setting the `RZ_RCFILE` environment variable before executing `rizin`.

### Examples of `rizinrc` scripts

Here's a demonstration of loading an `rizinrc` file in various environments.

These examples will show the content of the `rizinrc` file and their output upon executing `rizin`.

Please note that `clippy` is a command within the Rizin command-line, and executing it will produce a message on the terminal.

- Example of `rizinrc` within **linux**, **macOS** (or any UNIX-like environements).

```bash
$ cat ~/.rizinrc
clippy 'This is executed from $HOME/.rizinrc'
$ rizin
 .--.     .--------------------------------------.
 |   \    |                                      |
 | O o   <  This is executed from $HOME/.rizinrc |
 |   | /  |                                      |
 |  ( /   `--------------------------------------'
 |   / 
 `--'
[0x00000000]> q
$ cat some/folder/myrizinrc
clippy 'This is executed elsewhere'
$ export RZ_RCFILE="some/folder/myrizinrc"
$ rizin
 .--.     .----------------------------.
 | _|_    |                            |
 | O O   <  This is executed elsewhere |
 |  ||    |                            |
 | _:|    `----------------------------'
 |   |
 `---'
[0x00000000]> q
```

- Example of `rizinrc` within **Windows**.

```bash
C:\Users\user\Desktop\rizin> type %HOME%\.rizinrc
clippy 'This is executed from %HOME%/.rizinrc'
C:\Users\user\Desktop\rizin> rizin.exe
 .--.     .---------------------------------------.
 |   \    |                                       |
 | O o   <  This is executed from %HOME%/.rizinrc |
 |   | /  |                                       |
 |  ( /   `---------------------------------------'
 |   / 
 `--'
[0x00000000]> q
C:\Users\user\Desktop\rizin> type some\folder\myrizinrc
clippy 'This is executed elsewhere'
C:\Users\user\Desktop\rizin> set RZ_RCFILE="some\folder\myrizinrc"
C:\Users\user\Desktop\rizin> rizin.exe
 .--.     .----------------------------.
 | _|_    |                            |
 | O O   <  This is executed elsewhere |
 |  ||    |                            |
 | _:|    `----------------------------'
 |   |
 `---'
[0x00000000]> q
```

### Example of initial binary script

Here's a demonstration of loading an initial Rizin script in the same directory as the binary. As previously mentioned, the script's filename must match that of the original binary, with the addition of the `.rz` extension. In this instance, the binary is named `firmware.bin`, and the accompanying script is named `firmware.bin.rz`. Upon execution, `firmware.bin.rz` will display information about the binary and proceed to disassemble the initial 10 instructions.

Please note that `clippy` is a command within the Rizin command-line, and executing it will produce a message on the terminal.

```bash
$ ls
firmware.bin firmware.bin.rz
$ cat firmware.bin.rz
clippy 'This is executed at start'
# show bin info
i
# print the first 10 instructions
pd 10
$ rizin firmware.bin
Do you want to run the 'firmware.bin.rz' script? (y/N)  y
 .--.     .---------------------------.
 | _|_    |                           |
 | O O   <  This is executed at start |
 |  ||    |                           |
 | _:|    `---------------------------'
 |   |
 `---'
fd       3
file     firmware.bin
size     0x3722
humansz  13.8K
mode     r-x
format   avr
iorw     false
block    0x100
type     ROM
arch     avr
cpu      N/A
baddr    ----------
binsz    0x00003722
bintype  N/A
bits     8
retguard false
class    N/A
compiler N/A
dbg_file N/A
endian   LE
hdr.csum N/A
guid     N/A
intrp    N/A
laddr    0x00000000
lang     N/A
machine  ATmel
maxopsz  4
minopsz  2
os       avr
cc       N/A
pcalign  2
rpath    N/A
subsys   
stripped false
crypto   false
havecode true
va       false
sanitiz  false
static   true
linenum  false
lsyms    false
canary   false
PIE      false
RELROCS  false
NX       false
            ;-- entry0:
            0x00000158      clr   r1
            0x0000015a      out   SREG, r1
            0x0000015c      ser   r28
            0x0000015e      ldi   r29, 0x10
            0x00000160      out   SPH, r29
            0x00000162      out   SPL, r28
            0x00000164      ldi   r17, 0x02
            0x00000166      ldi   r26, 0x00
            0x00000168      ldi   r27, 0x01
            0x0000016a      ldi   r30, 0xfe
 -- Add colors to your screen with 'e scr.color=X' where 1 is 16 colors, 2 is 256 colors and 3 is 16M colors
[0x00000158]> 
```

### Example of `binrc` scripts

Here's an example of loading a `binrc` file in a Linux environment (applicable elsewhere too).

The provided example showcase the content of the `binrc` file and the resulting output when executing `rizin`.

Make sure the script is stored within the `bin-<format>` directory, where `<format>` match the output of the `i~format` Rizin command.

Please note that `clippy` is a command within the Rizin command-line, and executing it will produce a message on the terminal and `-e log.level=2` increments the verbosity of the rizin logs.

```bash
$ cat ~/.local/share/rizin/rc.d/bin-elf64/myscript-for-elf64.rz
clippy 'This is executed only for ELF64 format'
$ cat ~/.local/share/rizin/rc.d/bin-pe/myscript-for-pe.rz
clippy 'This is executed only for PE format'
$ rizin -e log.level=2 example.elf64
INFO: [binrc] path: '/home/username/.local/share/rizin/rc.d/bin-elf64'
INFO: [binrc] loading 'myscript-for-elf64.rz'
 .--.     .----------------------------------------.
 | _|_    |                                        |
 | O O   <  This is executed only for ELF64 format |
 |  ||    |                                        |
 | _:|    `----------------------------------------'
 |   |
 `---'
[0x00005fa0]> i~format
format   elf64
[0x00005fa0]> q
$ rizin -e log.level=2 example.exe
INFO: [binrc] path: '/home/username/.local/share/rizin/rc.d/bin-pe'
INFO: [binrc] loading 'myscript-for-pe.rz'
 .--.     .-------------------------------------.
 |   \    |                                     |
 | O o   <  This is executed only for PE format |
 |   | /  |                                     |
 |  ( /   `-------------------------------------'
 |   / 
 `--'
[0x00005fa0]> i~format
format   pe
[0x00401260]> q
```
