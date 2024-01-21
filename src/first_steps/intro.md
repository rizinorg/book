## Basic Rizin Usage

The initial learning curve tends to be relatively steep. However, within an hour of usage, you should grasp the workings of most features and learn how to effectively utilize the different tools provided by `rizin`.

For a quick introduction to basic commands, execute `rizin` on the command line and enter `?` to obtain an overview.

```bash
[0x00000000]> ?
| ![!]                  # Run given commands as in system(3) or shows command history (see !?? for more details)
...
| a[?]                  # Analysis commands
...
| p[?]                  # Print commands
...

```

**Note**: You have the option to add a `?` before any command to access its help.

Additionally, remember that a comprehensive search for _all_ commands, settings, and their descriptions can be performed by typing `?*`.

### Internal grep, list commands and environment variables

When utilizing the `rizin` command line, the internal grep (line filter) is denoted by the character `~`.

This feature enables users to conveniently locate values, commands, or configurations within Rizin.

An illustrative example of using the internal grep is to identify commands that users might not recall or be aware of.

For instance, the subsequent command displays all the print commands (`p`) and selectively shows only those lines containing the keyword `base64` (case-insensitive):

```bash
[0x00000000]> ?* p~base64
| p6e                  # Base64 encoding
| p6d                  # Base64 decoding
```

Is possible to achieve the same outcome by listing all available commands using the `?*` command and then filtering the lines containing a specific keyword using `~`, as previously explained.

The following example lists all the commands and shows only those containing the keyword `summarize` (case-insensitive):

```bash
?*~summarize
| pds [<n_bytes>]      # Summarize N bytes
| pdsf                 # Summarize the current function
| pdsb                 # Summarize current block
```

Similarly, you can perform the same action for listing all environment variables and selectively displaying lines that may contain the specified keyword. Use `el*` and apply the `~` filter as previously described.

For example, the following command filters by the lines containing the keyword `color` within the environment variables and values.

```bash
[0x00000000]> el*~color
e log.colors=false
e scr.color=3
e scr.color.args=true
e scr.color.bytes=true
e scr.color.grep=false
e scr.color.ops=true
e scr.color.pipe=false
```

If you are searching for descriptions of Rizin environment variables and want to display only those lines containing the keyword `color`, you can use the following command:

```bash
[0x00000000]> el~color
         emu.str.inv: Color-invert emu.str strings
      graph.gv.graph: Graphviz global style attributes. (bgcolor=white)
       graph.gv.node: Graphviz node style. (color=gray, style=filled shape=box)
          log.colors: Should the log output use colors (TODO)
           scr.color: Enable colors (0: none, 1: ansi, 2: 256 colors, 3: truecolor)
      scr.color.args: Colorize arguments and variables of functions
     scr.color.bytes: Colorize bytes that represent the opcodes of the instruction
      scr.color.grep: Enable colors when using ~grep
       scr.color.ops: Colorize numbers and registers in opcodes
      scr.color.pipe: Enable colors when using pipes
     scr.prompt.mode: Set prompt color based on vi mode
         scr.rainbow: Shows rainbow colors depending of address
         scr.randpal: Random color palete or just get the next one from 'eco'
     scr.visual.mode: Visual mode (0: hexdump, 1: disassembly, 2: debug, 3: color blocks, 4: strings)
```

Feel free to explore the rest of this book to gain insights into how certain non-trivial concepts operate and enhance your skills over time.

### Navigate and print

Navigation, inspection, and modification of a loaded binary file involve three straightforward actions: seek (to position), print (buffer), and alternate (write, append).

The 'seek' command is abbreviated as `s` and takes an expression as its argument. The expression can be something like `10`, `+0x25`, or `[0x100+ptr_table]`. When dealing with block-based files, you might prefer setting the block size to a required value with the `b` command and navigating forward or backward with positions aligned to it using `s++` and `s--` commands.

When rizin opens an executable file, it defaults to Virtual Addressing (VA) mode, mapping sections to their virtual addresses. In VA mode, seeking is based on the virtual address, and the starting position is set to the entry point of the executable. You can use the `-n` option to suppress this default behavior and open the file in non-VA mode. In non-VA mode, seeking is based on the offset from the beginning of the file.

The 'print' command is abbreviated as `p` and has various submodes, with the second letter specifying the desired print mode. Common variants include `px` for hexadecimal printing and `pd` for disassembling.

To enable file writing, specify the `-w` option when opening a file with rizin. The `w` command allows you to write strings, hexpairs (`x` subcommand), or even assembly opcodes (`a` subcommand).

Examples:

```
> w hello world         # string
> wx 90 90 90 90        # hexpairs
> wa jmp 0x8048140      # assemble
> wf inline.bin         # write contents of file
```

### Visual mode and panels

Rizin also offers visual mode via `V` and visual panels via `v`.

Once you enter visual mode/panel, you can use `q` to exit visual mode and return to the prompt, and `?` to toggle the help message explaining how to navigate within visual mode.

In visual mode, the HJKL keys are used for navigation (left, down, up, and right, respectively). These keys are applicable in cursor mode, toggled by the `c` key. To select a byte range in cursor mode, hold down the `SHIFT` key and press the navigation keys HJKL to mark your selection.

While in visual mode, you can overwrite bytes by pressing `i`. Press `TAB` to switch between the hex (middle) and string (right) columns. Pressing `q` inside the hex panel returns you to visual mode. By pressing `p` or `P`, you can scroll through different representations in visual mode. Another significant visual mode is the curses-like panels interface, accessible with the `V!` command.

In visual panel, you can use the mouse cursor and keyboard arrows to move around.
