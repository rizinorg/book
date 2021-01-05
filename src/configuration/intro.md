# Configuration

The core reads `~/.config/rizin/rizinrc` while starting. You can add `e` commands to this file to tune the rizin configuration to your taste.

To prevent rizin from parsing this file at startup, pass it the `-N` option.

All the configuration of rizin is done with the `eval` commands. A typical startup configuration file looks like this:
```sh
$ cat ~/.rizinrc
e scr.color=1
e dbg.bep   = loader
```
The configuration can also be changed with `-e` <config=value> command-line option. This way you can adjust configuration from the command line, keeping the .rizinrc file intact. For example, to start with empty configuration and then adjust `scr.color` and `asm.syntax` the following line may be used:
```sh
$ rizin -N -e scr.color=1 -e asm.syntax=intel -d /bin/ls
```
Internally, the configuration is stored in a hash table. The variables are grouped in namespaces: `cfg.`, `file.`, `dbg.`, `scr.` and so on.

To get a list of all configuration variables just type `e` in the command line
prompt. To limit the output to a selected namespace, pass it with an ending dot to `e`. For example, `e file.` will display all variables defined inside the "file" namespace.

To get help about `e` command type `e?`:

```
[0x00000000]> e?
Usage: e[?]   # List/get/set config evaluable vars
| e <key>[=<val|?>] [<key>[=<val|?>] ...]] # Get/Set value of config variable <key>
| el[j*qlJ] [<key>]      # List config variables with their descriptions
| e-                     # Reset config variables
| e! <key>               # Invert the boolean value of config variable <var>
| ec[?]                  # Set color for given key (prompt, offset, ...)
| ee <key>               # Open editor to change the value of config variable <var>
| ed                     # Open editor to change ~/.rizinrc
| er <key>               # Set config variable <var> as read-only
| es [<key>]             # List all config variable spaces or sub-keys/sub-spaces if a <key> is provided
| et <key>               # Show type of given config variable <var>
| env [<varname>[=<varvalue>]] # Get/set environment variables
```

A simpler alternative to the `e` command is accessible from the visual mode. Type `Ve` to enter it, use arrows (up, down, left, right) to navigate the configuration, and `q` to exit it. The start screen for the visual configuration edit looks like this:

```
[EvalSpace]

    >  anal
       asm
       scr
       asm
       bin
       cfg
       diff
       dir
       dbg
       cmd
       fs
       hex
       http
       graph
       hud
       scr
       search
       io
```

For configuration values that can take one of several values, you can use the `=?` operator to get a list
of valid values:

```
[0x00000000]> e scr.nkey=?
scr.nkey = fun, hit, flag
```
