# Basic Debugger Session

As outlined in the command line chapter, to debug a program, initiate Rizin with the `-d` option. It's worth noting that you can attach to a running process by specifying its PID, or you can launch a new program by providing its name and parameters:

```bash
$ pidof mc
32220
$ rizin -d 32220
$ rizin -d /bin/ls
$ rizin -a arm -b 16 -d gdb://192.168.1.43:9090
```

The debugger commands are accessible under the `d` command.

```bash
[0xb7f0c8c0]> d?
Usage: d<?>   # Debugger commands
| db[?]           # Breakpoints commands (see db?? for more details)
| dc[?]           # Continue execution (see dc?? for more details)
| dd[-lsdrw]      # Debug file descriptors commands (see dd?? for more details)
| de[lcs?]        # Manage ESIL watchpoints (see de?? for more details)
| dg [<filename>] # Generate core dump file
| do<rec>         # Debug (re)open commands
| ds[?]           # Debug step commands (see ds?? for more details)
| dt[?]           # Trace commands (see dt?? for more details)
| di[j*q]         # Debug information
| dk[lnNo]        # Debug signals management (see dk?? for more details)
| dl[l]           # Debug handler (see dl?? for more details)
| dm[?]           # Memory map commands (see dm?? for more details)
| dp[?]           # List or attach to process or thread (see dp?? for more details)
| dr[?]           # CPU Registers (see dr?? for more details)
| dw [<pid>]      # Block prompt until <pid> dies
| dW[i]           # Windows process commands (see dW?? for more details)
| dx[aers]        # Code injection commands (see dx?? for more details)
```

When Rizin is in debugger mode, it forks and loads the debuggee `ls` program into memory.

Execution pauses early in the `ld.so` dynamic linker, making the entrypoint and any shared libraries invisible at this stage.

To override this behavior and set another name for an entry breakpoint, add a Rizin command `e dbg.bep=entry` or `e dbg.bep=main` to your startup script (the `rizinrc` paths can be found by executing `rizin -hh`).

An alternative method to continue until a specific address is by using the `dcu` command, meaning "debug continue until." Provide the address where you want to stop, for example:

```bash
[0xb7f0c8c0]> dcu main
```

Be cautious, as certain malware or other intricate programs may execute code before `main()`, making it challenging to control them (e.g., program constructor or TLS initializers).

Here is a list of the most common commands used with the debugger:

```bash
[0xb7f0c8c0]> d?              # get help on debugger commands
[0xb7f0c8c0]> ds 3            # step 3 times
[0xb7f0c8c0]> db @ 0x8048920  # setup a breakpoint
[0xb7f0c8c0]> db- @ 0x8048920 # remove a breakpoint
[0xb7f0c8c0]> dc              # continue process execution
[0xb7f0c8c0]> dcs             # continue until syscall
[0xb7f0c8c0]> dd              # manipulate file descriptors
[0xb7f0c8c0]> dm              # show process maps
[0xb7f0c8c0]> dmp A S rwx     # change permissions of page at A and size S
[0xb7f0c8c0]> dr eax=33       # set register value. eax = 33
```

There is another option for debugging in rizin, which may be easier: using visual mode.

That way you will neither need to remember many commands nor to keep program state in your mind.

To enter visual debugger mode, use `Vpp`:

```bash
[0xb7f0c8c0]> Vpp
```

Upon entering visual mode, the initial view is a hexdump of the current target program counter (e.g., EIP for x86). Pressing `p` or `P` allows you to cycle through other visual mode views. Utilize F7 or `s` to step into and F8 or `S` to step over the current instruction. The `c` key toggles cursor mode to mark a byte range selection (e.g., for later overwriting with NOP). Breakpoints can be set with the `F2` key.

In visual mode, you can input regular Rizin commands by prefixing them with `:`. For instance, to dump a block of memory contents at ESI:

```bash
<Press ':'>
x @ esi
```

To obtain help on visual mode, press `?`. Use arrows to scroll through the help screen, and to exit the help view, press `q`.

A commonly used command is `dr`, which is employed to read or write values of the target's general-purpose registers. For a more concise register value representation, you can use the `dr=` command. Additionally, you have the ability to manipulate the hardware and extended/floating-point registers.
