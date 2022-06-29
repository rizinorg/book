Let's start our Rizin journey. This chapter is mostly a quickstart guide. Here, we'll talk about some basic Rizin usage with examples, so that you get a basic idea on how things work.

The learning curve for Rizin might feel a bit steep at the beginning. Even if so, after an hour of using it, you should easily understand how most things work, and how to combine the various tools that rizin offers. You are encouraged to read the rest of this book to understand how some non-trivial things work, and to ultimately improve your skills.

## Hello Rizin

Rizin is a command-line tool. Which means that you'll be interfacing with Rizin through the terminal or the shell.

To open Rizin, simply run `rizin` on the shell.

```
$ rizin
 -- Thank you for using rizin. Have a nice night!
[0x00000000]>
```

Here, `[0x00000000]>` is the Rizin shell where you can execute commands. `0x00000000` is the current address or the memory address where you are at now and since we didn't open a file, the seek address is obviously zero. More on this later.

Since we're in the Rizin shell, let's now look at how to run some commands.

### Basic actions

Let's look at three very basic actions that a reverse engineering framework can be used for: navigation, inspection and modification of a loaded binary file. In Rizin, they are done using seek (to position), print (buffer), and alternate (write, append) commands, respectively.

The 'seek' command is what you use to move around. It is abbreviated as `s` and accepts an expression as its argument. The expression can be something like `10`, `+0x25`, or `[0x100+ptr_table]`. If you are working with block-based files, you may prefer to set the block size to a required value with `b` command, and seek forward or backwards with positions aligned to it. Use `s++` and `s--` commands to navigate this way.

If rizin opens an executable file, by default it will open the file in Virtual Addressing (VA) mode and the sections will be mapped to their virtual addresses. In VA mode, seeking is based on the virtual address and the starting position is set to the entry point of the executable. Using `-n` option you can suppress this default behavior and ask rizin to open the file in non-VA mode for you. In non-VA mode, seeking is based on the offset from the beginning of the file.

The 'print' command is abbreviated as `p` and has a number of submodes — the second letter specifying a desired print mode. Frequent variants include `px` to print in hexadecimal, and `pd` for disassembling.

Let's just combine what we've learned so far. Let's print 20 bytes from the memory address `0x00005c60`

```bash
[0x0000000]> px 20 0x00005c60
- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F  0123456789ABCDEF
0x00005c60  f30f 1efa 803d 5de6 0100 0075 3355 4883  .....=]....u3UH.
0x00005c70  3d52 e301    
```

Everything related to writing is done using the `w` command. The `w` command can be used to write strings, hexpairs (`x` subcommand), or even assembly opcodes (`a` subcommand):

```
> w hello world         ; string
> wx 90 90 90 90        ; hexpairs
> wa jmp 0x8048140      ; assemble
> wf inline.bin         ; write contents of file
```
To be allowed to modify or write files, specify the `-w` option to rizin when opening a file.

### Basic command usage

We just ran a couple of commands. But, how will you figure out its usage and find which one you're looking for?

Appending `?` to a command will show its help message. For example, `p?` will contain information about the print command's usage, its expected arguments and about the subcommands related to it. Appending `j` to a command will print the command's output in JSON format.

Appending `?*` will show commands starting with the given string, e.g. `p?*`. This can be used to see what all similar print commands exist.

### Getting to know visual mode

The [visual mode](https://book.rizin.re/visual_mode/intro.html) is a much more user-friendly TUI interface of Rizin. To enter visual mode, run `V`. Use `p` to toggle the different modes and `q` to quit visual mode and return to the prompt.
In visual mode you can use the HJKL keys to navigate (left, down, up, and right, respectively). You can use these keys in cursor mode toggled by `c` key. To select a byte range in cursor mode, hold down `SHIFT` key, and press navigation keys HJKL to mark your selection.

While in visual mode, you can also overwrite bytes by pressing `i`. You can press `TAB` to switch between the hex (middle) and string (right) columns. Pressing `q` inside the hex panel returns you to visual mode. By pressing `p` or `P` you can scroll different visual mode representations. There is a second most important visual mode - curses-like panels interface, accessible with `V!` command.
