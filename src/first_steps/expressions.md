## Expressions

Expressions in Rizin are mathematical representations of numerical values. They can be presented in various formats, compared, or employed with commands accepting numeric arguments. These expressions support traditional arithmetic operations, as well as binary and boolean operations.

To evaluate mathematical expressions, use the `%` command:

```bash
[0x00000000]> %?
Usage: %[?]   # Math commands
| %[j] <expr>            # Evaluate numerical expression <expr>
| %$ [<var>]             # Print Rizin variables and their values
| %0                     # Set first tab as the current active tab
| %1                     # Set next tab as the current active tab
| %r <lowlimit> <uplimit> # Generate a random number between <lowlimit> and <uplimit>
| %b <expr>              # Print <expr> in binary format
| %b64 <str>             # Encode <str> in Base64
| %b64- <str>            # Decode <str> from Base64
| %btw <first> <middle> <last> # Check if <middle> number is between <first> and <last>
| %B <mode>              # Get boundaries (start addr, stop addr) of different modes in Core.
| %h <<str>>             # Print hash value of string <str>
| %f <value> <bitstring> # bitstring manipulation.
| %o <expr>              # Print <expr> in octal format
| %u <expr>              # Convert <expr> to K, M, G, T etc... units
| %v[xi?]                # Show value commands (see %v?? for more details)
| %= <expr>              # Update $? (last evaluated expression) with <expr>, without printing anything
| %== <str1> <str2>      # Compare strings <str1> and <str2> and set $? register to cmp result
| %+ <cmd>               # Execute command <cmd> if $? register is greater than 0
| %- <cmd>               # Execute command <cmd> if $? register is less than 0
| %! <cmd>               # Execute command <cmd> if $? is 0
| %% <cmd>               # Execute command <cmd> if $? is not 0
| %l[q] <str>            # Calculate length of string <str>. Quite mode stores value in `$?` register.
| %X <expr>              # Show evaluated expression <expr> in hex
| %x[+-]                 # String/Numeric to hex manipulation commands (see %x?? for more details)
| %s <start> <stop> <step> # Generate sequence of numbers from <start> to <stop> with <step> increments
| %P [<paddr>]           # Convert physical to virtual address
| %p [<vaddr>]           # Virtual to physical address conversion
| %_ <input>             # HUD input
| %i[?]                  # Input commands (see %i?? for more details)
| %w <addr>              # Get references of given address
```

The supported arithmetic operations include:

- `+`: addition
- `-`: subtraction
- `*`: multiplication
- `/`: division
- `%`: modulus
- `**`: power
- `>`: shift right
- `<`: shift left
- `~`: bitwise not (complement, logical negation)
- `|`: bitwise or (logical or)
- `&`: bitwise and (logical and)
- `^`: bitwise xor (logical xor)
- `#`: rotate left
- `$`: rotate right

These operations are constrained to `64-bit integers` and `64-bit floating points`.

```bash
[0x00000000]> %vi 0x8048000
134512640
[0x00000000]> %vi 0x8048000+34
134512674
[0x00000000]> %vi 0x8048000+0x34
134512692
[0x00000000]> %vi 2**10
1024
[0x00000000]> % 1+2+3-4*3
int64   -6
uint64  18446744073709551610
hex     0xfffffffffffffffa
octal   01777777777777777777772
unit    16E
segment fffff000:0ffa
string  "\xfa\xff\xff\xff\xff\xff\xff\xff"
fvalue  -6.0
float   -6.000000f
double  -6.000000
binary  0b1111111111111111111111111111111111111111111111111111111111111010
trits   0t11112220022122120101211020120210210211201
[0x00000000]> %vi 1+2+3
6
```

Enclose the expression with double quotes to evaluate `|` as a logical OR instead of the pipe command.

```bash
[0x00000000]> % "1 | 2"
int32   3
uint32  3
hex     0x3
octal   03
unit    3
segment 0000:0003
string  "\x03"
fvalue  2.0
float   2.000000f
double  2.000000
binary  0b00000011
trits   0t10
[0x00000000]> %vi 1 \| 2
3
```

Numbers can be displayed in several formats:

```bash
0x033   # hexadecimal can be displayed
3334    # decimal
sym.fo  # resolve flag offset
10K     # KBytes  10*1024
10M     # MBytes  10*1024*1024
```

You can also use variables and seek positions to build complex expressions.

Use the `%$?` command to list all the available commands or read the refcard chapter of this book.

```bash
[0x00000000]> %$?
Usage: %$ [<var>]   # Print Rizin variables and their values

Rizin variables:
| $$       # here (current virtual seek)
| $$$      # current non-temporary virtual seek
| $?       # last comparison value
| $B       # base address (aligned lowest map address)
| $b       # block size
| $c       # get terminal width in character columns
| $Cn      # get nth call of function
| $D       # current debug map base address %v $D @ rsp
| $DB      # same as dbg.baddr, progam base address
| $DD      # current debug map size
| $Dn      # get nth data reference in function
| $e       # 1 if end of block, else 0
| $f       # jump fail address (e.g. jz 0x10 => next instruction)
| $F       # Same as $FB
| $Fb      # begin of basic block
| $FB      # begin of function
| $Fe      # end of basic block
| $FE      # end of function
| $Ff      # function false destination
| $Fi      # basic block instructions
| $FI      # function instructions
| $Fj      # function jump destination
| $fl      # flag length (size) at current address (fla; pD $l @ entry0)
| $FS      # function size (linear length)
| $Fs      # size of the current basic block
| $FSS     # function size (sum bb sizes)
| $j       # jump address (e.g. jmp 0x10, jz 0x10 => 0x10)
| $Ja      # get nth jump of function
| $l       # opcode length
| $M       # map address (lowest map address)
| $m       # opcode memory reference (e.g. mov eax,[0x10] => 0x10)
| $MM      # map size (lowest map address)
| $O       # cursor here (current offset pointed by the cursor)
| $o       # here (current disk io offset)
| $p       # getpid()
| $P       # pid of children (only in debug)
| $r       # get console height (in rows, see $c for columns)
| $s       # file size
| $S       # section offset
| $SS      # section size
| $v       # opcode immediate value (e.g. lui a0,0x8010 => 0x8010)
| $w       # get word size, 4 if asm.bits=32, 8 if 64, ...
| $Xn      # get nth xref of function
| flag     # offset of flag
| ${ev}    # get value of eval <config variable <ev>
| $alias   # alias commands (simple macros)
| $e{flag} # end of <flag> (flag->offset + flag->size)
| $k{kv}   # get value of an sdb query value
| $r{reg}  # get value of named register <reg>
| $s{flag} # get size of <flag>
[0x00005fa0]> % $m + $l
int32   3
uint32  3
hex     0x3
octal   03
unit    3
segment 0000:0003
string  "\x03"
fvalue  18446744073709551616.0
float   18446744073709551616.000000f
double  18446744073709551616.000000
binary  0b00000011
trits   0t10
```
