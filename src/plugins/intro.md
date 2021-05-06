# Plugins

rizin is implemented on top of a bunch of libraries, almost every of those
libraries support plugins to extend the capabilities of the library or add
support for different targets.

This section aims to explain what are the plugins, how to write them and use them

## Types of plugins
```
$ ls librz/*/p | grep : | awk -F / '{ print $2 }'
analysis  # analysis plugins
asm       # assembler/disassembler plugins
bin       # binary format parsing plugins
bp        # breakpoint plugins
core      # core plugins (implement new commands)
crypto    # encrypt/decrypt/hash/...
debug     # debugger backends
egg       # shellcode encoders, etc
io        # io plugins
lang      # embedded scripting languages
parse     # disassembler parsing plugins
reg       # arch register logic
```

## Listing plugins

Some rizin tools have the `-L` flag to list all the plugins associated to the
functionality.
```
rz-asm -L   # list asm plugins
rizin -L    # list io plugins
rz-bin -L   # list bin plugins
rz-hash -L  # list hash/crypto/encoding plugins
```
There are more plugins in rizin ecosystem, we can list them from inside rizin, and this is
done by using the `L` suffix.

Those are some of the commands:
```
L          # list core plugins
iL         # list bin plugins
dL         # list debug plugins
ph         # print support hash algorithms
woD?/woE?  # print support crypto/encoding algorithms
```

You can use the `?` as value to get the possible values in the associated eval vars.

```
e asm.arch=?   # list assembler/disassembler plugins
e analysis.arch=?  # list analysis plugins
```
## Notes

Note there are some inconsistencies that most likely will be fixed in the future rizin versions.

