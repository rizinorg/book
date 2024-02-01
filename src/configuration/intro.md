## Introduction

This chapter provides instructions on configuring and customizing Rizin to meet your preferences.

During the startup, Rizin loads an [initial script](initial_scripts.md) called `rizinrc`. Within this file, it is possible to incorporate configuration commands (`e` commands) to customize the tool.

All the configuration adjustments in Rizin are made through the use of `e` commands. A standard startup configuration file often resembles the following:

```bash
$ cat ~/.rizinrc
# enable colors
e scr.color=2
# enable utf8 output
e scr.utf8=true
e scr.utf8.curvy=true
# change color theme to nord
eco nord
```

Configuration adjustments can also be made using the `-e option=value` command-line option. This allows you to modify configurations from the command line while keeping the `rizinrc` file unchanged. For instance, to initiate Rizin with an empty configuration and subsequently modify `scr.color` and `asm.syntax`, the following line can be employed:

```bash
$ rizin -N -e scr.color=1 -e asm.syntax=intel -d /bin/ls
```

The evaluable variables are named using namespaces, such as `cfg.`, `file.`, `dbg.`, `scr.`, and others.

To obtain a list of all configuration variables, enter `el` in the command line prompt. If you want to filter the output by a specific namespace, append the namespace to `el`. For example, `el file` will display all evaluable variables starting with the `file` prefix.

For configuration values that can assume one of several options, you can employ the `=?` operator to obtain a list of valid values.

For guidance on the `e` command, refer to `e?`.

```bash
[0x00000000]> e?
Usage: e[?]   # List/get/set config evaluable vars
| e <key>[=<val|?>] [<key>[=<val|?>] ...]] # Get/Set value of config variable <key>
| el[j*qlJ] [<key>]      # List config variables with their descriptions
| e-                     # Reset config variables
| e! <key>               # Invert the boolean value of config variable <key>
| ec[?]                  # Set color for given key (prompt, offset, ...) (see ec?? for more details)
| ee <key>               # Open editor to change the value of config variable <key>
| er <key>               # Set config variable <key> as read-only
| es [<key>]             # List all config variable spaces or sub-keys/sub-spaces if a <key> is provided
| et <key>               # Show type of given config variable <key>
[0x00000000]> el file
           file.info: RzBin info loaded
       file.lastpath: Path of current file
      file.loadalign: Alignment of load addresses
         file.offset: Offset where the file will be mapped at
       file.openmany: Maximum number of files opened at once
           file.path: Path of current file
           file.type: Type of current file
[0x00000000]> e scr.nkey=?
fun
hit
flag
```

A more straightforward alternative to the `e` command is available in visual mode. Type `Ve` to enter this mode, utilize arrow keys (up, down, left, right) for navigation through the configuration, and press `q` to exit. The initial screen for the visual configuration edit appears as follows:

```bash
[EvalSpace]
 >  analysis                                                                                                              
    asm
    basefind
    bin
    cfg
    cmd
    dbg
    diff
    dir
    elf
    emu
    esil
    file
    flirt
    graph
    ...
```
