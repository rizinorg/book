## Adding Metadata to Disassembly

The typical work involved in reversing binary files makes powerful annotation capabilities essential.
Rizin offers multiple ways to store and retrieve such metadata.

By following common basic UNIX principles, it is easy to write a small utility in a scripting language which uses
`objdump`, `otool` or any other existing utility to obtain information from a binary and to import it into Rizin.
For example, take a look at [python-idb](https://github.com/williballenthin/python-idb)-based
[`rz-ida.py`](https://github.com/rizinorg/rizin-extras/blob/master/rz-ida/rz-ida.py) which opens IDB files directly
without IDA Pro installed. You can load the resulting file with the `.` (dot) command into the Rizin:

```
[0x00000000]> . file.rz
```

The `C` command is used to manage comments and data conversions. You can define a range of program's bytes to be
interpreted as either code, binary data or string. It is also possible to execute external code at every specified flag
location in order to fetch some metadata, such as a comment, from an external file or database.

There are many different metadata manipulation commands, here is the glimpse of all of them:

```
[0x00404cc0]> C?
Usage: C[?]   # Code metadata (comments, format, hints, ..)
| C[j*l]    # List all meta information
| C.[j*l]   # Show all meta information at current address
| C-        # Remove meta information at current address
| C-*       # Remove all meta information
| CC[?]     # Manipulate the comments
| CS[l-r?]  # Manage metainformation spaces
| Cf[l-?]   # Manage the format string metainformation
| Cd[l.-?]  # Manage the raw data metainformation
| Ch[l-?]   # Manage the "hidden" mark metainformation
| Cm[l-?]   # Manage the "magic" mark metainformation
| Cs[?]     # Manipulate string metainformation
| Ct[l-.?]  # Manage the type metainformation
| Cv[-elrs] # Add comments to the vars or arguments
```

Simply to add the comment to a particular line/address you can use `Ca` command:

```
[0x00000000]> CC 0x0000002 this guy seems legit
[0x00000000]> pd 2
0x00000000    0000         add [rax], al
;      this guy seems legit
0x00000002    0000         add [rax], al
```

The `C?` family of commands lets you mark a range as one of several kinds of types. Three basic types are:
code (disassembly is done using asm.arch), data (an array of data elements) or string. Use the `Cs` command to define
a string, use the `Cd` command for defining an array of data elements, and use the `Cf` command to define more complex
data structures like structs.

Annotating data types is most easily done in visual mode, using the "d" key, short for "data type change". First,
use the cursor to select a range of bytes (press `c` key to toggle cursor mode and use HJKL keys to expand selection),
then press 'd' to get a menu of possible actions/types. For example, to mark the range as a string, use the 's' option
from the menu. You can achieve the same result from the shell using the `Cs` command:

```
[0x00000000]> f string_foo @ 0x800
[0x00000000]> Cs 10 @ string_foo
```

The `Cf` command is used to define a memory format string (the same syntax used by the `pf` command). Here's an example:

```
[0x7fd9f13ae630]> Cf 16 2xi foo bar
[0x7fd9f13ae630]> pd
;-- rip:
0x7fd9f13ae630 format 2xi foo bar {
0x7fd9f13ae630 [0] {
 foo : 0x7fd9f13ae630 = 0xe8e78948
 bar : 0x7fd9f13ae634 = 14696
}
0x7fd9f13ae638 [1] {
 foo : 0x7fd9f13ae638 = 0x8bc48949
 bar : 0x7fd9f13ae63c = 571928325
}
} 16
0x7fd9f13ae633    e868390000   call 0x7fd9f13b1fa0
0x7fd9f13ae638    4989c4       mov r12, rax
```

The `[sz]` argument to `Cf` is used to define how many bytes the struct should take up in the disassembly,
and is completely independent of the size of the data structure defined by the format string. This may seem confusing,
but has several uses. For example, you may want to see the formatted structure displayed in the disassembly,
but still have those locations be visible as offsets and with raw bytes. Sometimes, you find large structures,
but only identified a few fields, or only interested in specific fields. Then, you can tell Rizin to display only
those fields, using the format string and using 'skip' fields, and also have the disassembly continue after
the entire structure, by giving it full size using the `sz` argument.

Using `Cf`, it's easy to define complex structures with simple one-liners. See `pf?` for more information.
Remember that all these `C` commands can also be accessed from the visual mode by pressing the `d` (data conversion) key.
Note that unlike [`t`](../analysis/types.md) commands `Cf` doesn't change analysis results. It is only
a visual boon.

Sometimes just adding a single line of comments is not enough, in this case Rizin allows you to
create a link for a particular text file. You can use it with `CC,` command or by pressing `,` key in
the visual mode. This will open an `$EDITOR` to create a new file, or if filename does exist, just
will create a link. It will be shown in the disassembly comments:

```
[0x00003af7 11% 290 /bin/ls]> pd $r @ main+55 # 0x3af7
│0x00003af7  call sym.imp.setlocale        ;[1] ; ,(locale-help.txt) ; char *setlocale(int category, const char *locale)
│0x00003afc  lea rsi, str.usr_share_locale ; 0x179cc ; "/usr/share/locale"
│0x00003b03  lea rdi, [0x000179b2]         ; "coreutils"
│0x00003b0a  call sym.imp.bindtextdomain   ;[2] ; char *bindtextdomain(char *domainname, char *dirname)
```

Note `,(locale-help.txt)` appeared in the comments, if we press `,` again in the visual mode, it
will open the file. Using this mechanism we can create a long descriptions of some particular places
in disassembly, link datasheets or related articles.
