# Debugger

Debuggers are implemented as IO plugins. Therefore, rizin can handle different URI types for spawning,
attaching and controlling processes. The complete list of IO plugins can be viewed with `rizin -L`.
Those that have "d" in the first column ("rwd") support debugging. For example:

```
r_d  debug       Debug a program or pid. dbg:///bin/ls, dbg://1388 (LGPL3)
rwd  gdb         Attach to gdbserver, 'qemu -s', gdb://localhost:1234 (LGPL3)
```

There are different backends for many target architectures and operating systems, e.g., GNU/Linux, Windows, macOS,
Net/Free/OpenBSD and Solaris.

Process memory is treated as a plain file. All mapped memory pages of a debugged program and its libraries can be
read and interpreted as code or data structures.

Communication between Rizin and the debugger IO layer is wrapped into `system()` calls, which accept a string
as an argument, and executes it as a command. An answer is then buffered in the output console, its contents
can be additionally processed by a script. Access to the IO system is achieved with `R!`. Most IO plugins provide
help with `R!?` or `R!help`. For example:

```
$ rizin -d /bin/ls
...
[0x7fc15afa3cc0]> R!help
Usage: R!cmd args
 R!ptrace   - use ptrace io
 R!mem      - use /proc/pid/mem io if possible
 R!pid      - show targeted pid
 R!pid <#>  - select new pid
```

In general, debugger commands are portable between architectures and operating systems. Still, as Rizin tries
to support the same functionality for all target architectures and operating systems, certain things have
to be handled separately. They include injecting shellcodes and handling exceptions. For example, in MIPS targets
there is no hardware-supported single-stepping feature. In this case, Rizin provides its own implementation
for single-step by using a mix of code analysis and software breakpoints.

To get basic help for the debugger, type `d?`:

```
[0x000000000000]> d?
Usage: d<?>   # Debugger commands
| db[?]           # Breakpoints commands
| dc[?]           # Continue execution
| dd[-lsdrw]      # Debug file descriptors commands
| de[lcs?]        # Manage ESIL watchpoints
| dg [<filename>] # Generate core dump file
| do<rec>         # Debug (re)open commands
| ds[?]           # Debug step commands
| dt[?]           # Trace commands
| di[j*q]         # Debug information
| dk[lnNo]        # Debug signals management
| dl[l]           # Debug handler
| dm[?]           # Memory map commands
| dp[?]           # List or attach to process or thread
| dr[?]           # CPU Registers
| dw [<pid>]      # Block prompt until <pid> dies
| dW[i]           # Windows process commands
| dx[aers]        # Code injection commands
```

To restart your debugging session, you can use one of `oo` commands, depending on desired behavior:

```
[0x00000000]> oo?
Usage: oo[+bcdmn?]   # Reopen current file
| oo [<fd>]     # Reopen current file or file <fd>
| oo+ [<fd>]    # Reopen current file or file <fd> in write mode
| oob [<baddr>] # Reopen current file and reload binary information
| ooc           # Reopen current file as if restarting rizin
| ood[fr]       # Reopen current file in debug mode
| oom           # Reopen curent file in malloc://
| oon           # Reopen curent file without loading binary information
| oon+          # Reopen curent file in write-mode without loading binary information
| oonn          # Reopen curent file without loading binary information but with header flags
| oonn+         # Reopen curent file in write-mode without loading binary information but with header flags
```
