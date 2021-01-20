## Seeking

To move around the file we are inspecting we will need to change the offset at which we are using the `s` command.

The argument is a math expression that can contain flag names, parenthesis, addition, subtraction, multiplication of immediates of contents of memory using brackets.

Some example commands:

```
[0x00000000]> s 0x10
[0x00000010]> sd +4
[0x00000014]> sHu
[0x00000010]> sHr
[0x00000014]>
```

Observe how the prompt offset changes. The first line moves the current offset to the address 0x10.

The second does a relative seek 4 bytes forward.

And finally, the last 2 commands are undoing, and redoing the last seek operations in the seek history.

Instead of using just numbers, we can use complex expressions, or basic arithmetic operations to represent the address to seek.

To do this, check the ?$? Help message which describes the internal variables that can be used in the expressions. For example, this is the same as doing `sd +4` .

```
[0x00000000]> s $$+4
```

From the debugger (or when emulating) we can also use the register names as references. They are loaded as flags with the `.dr*` command, which happens under the hood.

```
[0x00000000]> s rsp+0x40
```

Here's the full help of the `s` command. We will explain in more detail below.

```
[0x00000000]> s?
Usage: s[?]   # Seek commands
| s [<addr>]          # Print current address / Seek to address
| s: [<n>]            # Print current address with <n> padded zeros (defaults to 8)
| s. <hex_offset>     # Seek honoring a base from core->offset
| sd <delta>          # Seek to a delta relative to current offset
| s-- [<n>]           # Seek blocksize bytes backward (/=n)
| s++ [<n>]           # Seek blocksize bytes forward (/=n)
| sH[j*ru-]           # Seek history commands
| s/[?]               # Seek to the first hit of a search
| sa <align> [<addr>] # Seek to current offset (or <addr>) aligned to <align>
| sb                  # Seek aligned to bb start
| sf [<fcn>]          # Seek to next function / Seek to specific function
| sf.                 # Seek to the beginning of current function
| sg                  # Seek to begin of section/file
| sG                  # Seek to end of section/file
| sn [<type>]         # Seek to next location of the given <type> or scr.nkey otherwise
| sp [<type>]         # Seek to prev location
| so [<n>]            # Seek to <n> next opcodes
| sr <reg>            # Seek to register
| sleep <seconds>     # Sleep for the specified amount of seconds


> 3s++        ; 3 times block-seeking
> s 10+0x80   ; seek at 0x80+10
```

If you want to inspect the result of a math expression, you can evaluate it using the `?` command. Simply pass the expression as an argument. The result can be displayed in hexadecimal, decimal, octal or binary formats.

```
> ? 0x100+200
0x1C8 ; 456d ; 710o ; 1100 1000
```

There are also subcommands of `?` that display the output in one specific format (base 10, base 16 ,...). See `?v` and `?vi`.

In the visual mode, you can press `u` (undo) or `U` (redo) inside the seek history to return back to previous or forward to the next location.

## Open file

As a test file, let's use a simple `hello_world.c` compiled in Linux ELF format.
After we compile it let's open it with rizin:

```
$ rizin hello_world
```

Now we have the command prompt:

```
[0x00400410]>
```

And it is time to go deeper.

## Seeking at any position

All seeking commands that take an address as a command parameter can use any numeral base
such as hex, octal, binary or decimal.

Seek to an address 0x0. An alternative command is simply `0x0`

```
[0x00400410]> s 0x0
[0x00000000]>
```

Print current address:
```
[0x00000000]> s
0x0
[0x00000000]>
```

There is an alternate way to print current position: `?v $$`.

Seek N positions forward, space is optional:

```
[0x00000000]> sd 128
[0x00000080]>
```

Undo last two seeks to return to the initial address:

```
[0x00000080]> sHu
[0x00000000]> sHu
[0x00400410]>
```

We are back at _0x00400410_.

There's also a command to show the seek history:

```
[0x00400410]> sH
0x400410 
0x40041a 
0x400410 
0x400411 
0x400410  # current seek
0x4005b4  # redo
[0x00400410]> sH*
f undo_3 @ 0x400410
f undo_2 @ 0x40041a
f undo_1 @ 0x400410
f undo_0 @ 0x400411
# Current seek @ 0x400410
f redo_0 @ 0x4005b4
```

