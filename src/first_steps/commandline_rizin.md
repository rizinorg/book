## Rizin Command-line

The Rizin command line initially displays the current address enclosed by brackets (e.g., `[0x00000000]>`).

Following these brackets, users can input commands. Typically, commands are represented by a single case-sensitive character.

Rizin includes special commands that enable the execution of shell-like commands. These can be accessed through the help command `shell?`.

The standard format for Rizin commands is as follows:

```bash
# executes a rizin command at at the current address (0x00000000)
[0x00000000]> command <params>
# executes a rizin command with a special temporary modifier
[0x00000000]> command <params> @<temporay modifier>
# executes a shell command
[0x00000000]> !<shell command>
# executes a rizin command and pipes its contents to a shell command
[0x00000000]> command <params> | <shell command>
```

This format will be consistently used throughout the book.

### Help commands

Every shell command is accompanied by a description that can be accessed by adding `?`. This displays the help descriptions for the individual command and all its subcommands.

Appending `??` instead provides the help message for the single command (excluding subcommands) along with an extended description, which may include possible examples.

```bash
[0x00000000]> e?
Usage: e[?]   # List/get/set config evaluable vars
| e <key>[=<val|?>] [<key>[=<val|?>] ...]] # Get/Set value of config variable <key>
| el[j*qlJ] [<key>]  # List config variables with their descriptions
| e-                 # Reset config variables
| e! <key>           # Invert the boolean value of config variable <key>
| ec[?]              # Set color for given key (prompt, offset, ...) (see ec?? for more details)
| ee <key>           # Open editor to change the value of config variable <key>
| er <key>           # Set config variable <key> as read-only
| es [<key>]         # List all config variable spaces or sub-keys/sub-spaces if a <key> is provided
| et <key>           # Show type of given config variable <key>
[0x00000000]> e??
Usage: e <key>[=<val|?>] [<key>[=<val|?>] ...]]   # Get/Set value of config variable <key>

Examples:
| e asm.bytes          # Show current value of config variable `asm.bytes`
| e asm.bytes=true     # Set config variable `asm.bytes` to `true`
| e search.in=?        # Show all possible values for config variable `search.in`
| e search.in=??       # Show all possible values for config variable `search.in` together with description
| e asm.bytes=true asm.offset=false # Set asm.bytes to true and asm.offset to false

```

### Shell command within rizin command line

Executing shell commands within the Rizin command line is achievable through various methods, each with distinct behaviors.

The initial method involves using the `!` command. The syntax for this approach is as follows: `!<shell command>`.

```bash
[0x00000000]> !?
Usage: ![!]   # Run given commands as in system(3) or shows command history
| !<command> [<args1> <args2> ...]  # Runs given commands in system(3)
| !!<command> [<args1> <args2> ...] # Runs a given commands in system(3) and pipes stdout to rizin
# executes `ls /path/to/dir` within the shell of the operating system
[0x00000000]> !ls /path/to/dir
somefile
```

The second method involves using the pipe command `|`, enabling the redirection of a command's output (`stdout`) to an external shell command.

```bash
[0x00000000]> |?
Usage: <cmd> |[<program>|H|T|.|]   # Pipe help ('|')
| <cmd> |           # Disable scr.html and scr.color
| <cmd> |H          # Enable scr.html, respect scr.color
| <cmd> | <program> # Pipe output of command to program
| <cmd> |.          # Alias for .<cmd>
# executes the `iz` rizin command and redirects the output to the external command `grep "hello"`
[0x00000000]> iz | grep "hello"
```

### Temporary modifiers

When utilizing the Rizin command-line, users may encounter situations where they need to temporarily modify specific values or configurations before executing a command. This can be accomplished using the `@` commands.

```bash
[0x00000000]> @?
Usage: <cmd> <@> <args>   # '@' help, temporary modifiers
| <cmd> @ <addr>             # Temporary seek to <addr>
| <cmd> @ ..<addr>           # Temporary partial address seek (see s..)
| <cmd> @!<blocksize>        # Temporary change the block size
| <cmd> @(<from> <to>)       # Temporary set from and to for commands supporting ranges
| <cmd> @a:<arch>[:<bits>]   # Temporary set arch and bits, if specified
| <cmd> @b:<bits>            # Temporary set asm.bits
| <cmd> @B:<nth>             # Temporary seek to nth instruction in current basic block (negative numbers too)
| <cmd> @e:<k>=<v>[,<k>=<v>] # Temporary change eval vars (multiple vars separated by comma)
| <cmd> @f:<file>            # Temporary replace block with file contents
| <cmd> @F:<flagspace>       # Temporary change flag space
| <cmd> @i:<nth.op>          # Temporary seek to the Nth relative instruction
| <cmd> @k:<key>             # Temporary seek at value of sdb key `key`
| <cmd> @o:<fd>              # Temporary switch to another fd
| <cmd> @r:<reg>             # Temporary seek to register value
| <cmd> @s:<string>          # Temporary replace block with string
| <cmd> @v:<value>           # Temporary replace block with value, written according to asm.bits and cfg.bigendian
| <cmd> @x:<hexstring>       # Temporary replace block with hexstring
# execute `px 16` (print hexadecimal) at address 0x100
[0x00000000]> px 16 @ 0x100
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x00000100  ffff ffff ffff ffff ffff ffff ffff ffff  ................
# execute `px` (print hexadecimal) with a block size of `10 bytes` 
# and replace the block with 00112233445566778822 hex bytes.
[0x00000000]> px @!10 @x:00112233445566778822
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x00000000  0011 2233 4455 6677 8822                 .."3DUfw."
```

Multiple temporary commands can be used simultaneously, requiring them to be space-separated. For instance: `@!10 @x:0011223344 @e:cfg.bigendian=true @ 0x12345`.

### Pipe output to file

In certain situations, users may need to save output to a file. This can be achieved by using `>`, similar to how it's done in the UNIX shell.

```bash
[0x00000000]> >?
Usage: <cmd> > <arg>   # Redirection help ('>')
| <cmd> > <file>|<$alias>  # Redirect STDOUT of <cmd> to <file> or save it to an alias (see $?)
| <cmd> 2> <file>|<$alias> # Redirect STDERR of <cmd> to <file> or save it to an alias (see $?)
| <cmd> H> <file>|<$alias> # Redirect HTML output of <cmd> to <file> or save it to an alias (see $?)
# execute `iij` (print import as JSON) and redirect the output to file
[0x00000000]> iij > imports.json
# execute `pr 128` (raw print) of 128 bytes at the address 0x1234 and 
# redirect the output to file.
# this allows to dump n-bytes at the current address to a file
[0x00000000]> pr 128 @ 0x1234 > dump.bin
[0x00000000]> !hexdump -C dump.bin 
00000000  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000080
```

### Executing multiple commands on a single line

The Rizin command line employs the `;` character to separate commands, enabling the execution of multiple commands in a single line.

```bash
[0x00000000]> px 20 ; pd 3 ; px 40
```

### Repeat a command n-times

It is possible to execute a command repeatedly, by prepending the command with a numerical value:

```bash
# executes `px`
[0x00000000]> px
# executes `px` 3 times
[0x00000000]> 3 px
```

### Filtering (grep) output lines

Filtering the output of an Rizin command is possible with any shell program that reads from stdin, such as `grep`, `less`, or `wc`, by utilizing the `|` pipe command. However, if spawning external processes is not desirable, possible, or the target system lacks essential UNIX tools (as is the case for Windows or embedded systems), you can also employ the built-in grep (`~`).

```bash
[0x00000000]> ~?
Usage: <command>~[modifier][word,word][endmodifier][[column]][:line]   # Internal grep help ('~')

Modifiers:
| &      # All words must match to grep the line
| $[n]   # Sort numerically / alphabetically the Nth column
| $!     # Sort in inverse order
| ,      # Token to define another keyword
| +      # Set the grep as the opposite of search.case_sensitive
| ^      # Words must be placed at the beginning of line
| <      # Perform zoom operation on the buffer
| !      # Negate grep
| ?      # Count number of matching lines
| ?.     # Count number chars
| :s..e  # Show lines s-e
| ..     # Internal 'less'
| ...    # Internal 'hud' (like V_)
| {:     # Human friendly indentation (yes, it's a smiley)
| {:..   # Less the output of {:
| {:...  # Hud the output of {:
| {}     # Json indentation
| {}..   # Less json indentation
| {}...  # Hud json indentation
| {path} # Json path grep

EndModifiers:
| $ # Words must be placed at the end of line

Columns:
| [n]     # Show only columns n
| [n-m]   # Show column n to m
| [n-]    # Show all columns starting from column n
| [i,j,k] # Show the columns i, j and k

Examples:
| i~:0     # Show first line of 'i' output
| i~:-2..  # Show from the second-last line to the last line of 'i' output
| i~:..3   # Show first three lines of 'i' output
| i~:2..5  # Show three lines of 'i' output starting from 2nd line
| pd~mov   # Disasm and grep for mov
| pi~[0]   # Show only opcode
| i~0x400$ # Show lines ending with 0x400
```

Moreover, you can employ grep for either columns (using `[n]`) or rows (using `:n`). For instance:

```bash
# get first row
[0x00000000]> pd 20~call:0 
# get second row
[0x00000000]> pd 20~call:1 
# get first column
[0x00000000]> pd 20~call[0]
# get second column
[0x00000000]> pd 20~call[1]
# Alternatively, you can combine them.
# This filters the first column of the first row matching 'call'.
[0x00000000]> pd 20~call:0[0]
```

The internal grep function is a crucial feature for scripting in Rizin.

### Iterators and loops

It allows iteration over a list of offsets or data generated by the disassembler, ranges, or any other command. For more information, refer to the [loops](../scripting/loops.md) section (iterators).

### Examples of shell usage.

Here are a few examples of shell usage:

```bash
[0x00000000]> ds                    # call the debugger's 'step' command
[0x00000000]> px 200 @ esp          # show 200 hex bytes at esp
[0x00000000]> pc > file.c           # dump buffer as a C byte array to file.c
[0x00000000]> wx 90 @@is            # write a nop on every symbol
[0x00000000]> pd 2000 | grep eax    # grep opcodes that use the 'eax' register
```

The `@` character is used to specify a temporary offset at which the command to its left will be executed.
The original seek position in a file is then restored.

For example, `pd 5 @ 0x100000fce` to disassemble 5 instructions at address 0x100000fce.

Most of the commands offer autocompletion support using `<TAB>` key, for example `s`eek or `f`lags commands.
It offers autocompletion using all possible values, taking flag names in this case.
Note that it is possible to see the history of the commands
using the `!~...` command - it offers a visual mode to scroll through the rizin command history.

To extend the autocompletion support to handle more commands or enable autocompletion to your own commands defined in core, I/O plugins you must use the `!!!` command.
