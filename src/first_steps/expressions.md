## Expressions

Expressions are mathematical representations of 64-bit numerical values.
They can be displayed in different formats, be compared or used with all commands
accepting numeric arguments. Expressions can use traditional arithmetic operations,
as well as binary and boolean ones.

To evaluate mathematical expressions prepend them with command `%`:
```
[0x00000000]> %?
Usage: %[?]   # Math commands
| %[j] <expr>            # Evaluate given numerical expression
| %$ [<var>]             # Print Rizin variables and their values
| %0                     # Set first tab as the current active tab
| %1                     # Set next tab as the current active tab
| %r <lowlimit> <uplimit> # Generate random number
| %b[?]                  # Base64 encode/decode and print binary commands
| %btw <first> <middle> <last> # Check if middle number is between the other two (first and last)
| %B <mode>              # Get boundaries (start addr, stop addr) of different modes in Core.
| %h <strs1> <strs2> ... # Print hash value of given input
| %f <value> <bitstring> # bitstring manipulation.
| %o <input>             # Evaluate expression and print value in octal.
| %u <input>             # Convert evaluated numbers/expressions to K, M, G, T etc... units
| %q <input>             # Update $? (last evaluated expression) without printing anything
| %v[xi?]                # Show value commands
| %= <input>             # Replace the value of last evalued expression with given value
| %== <str1> <str2>      # Compare two given strings and set $? register to cmp result
| %+ <cmd>               # Execute given command if $? register is greater than 0
| %- <cmd>               # Execute given command if $? register is less than 0
| %! <cmd>               # Execute command if result of last numeric expression evaluation (related) command was 0
| %% <cmd>               # Execute command if result of last numeric expression evaluation (related) command was not 0
| %l[q] <str>            # Calculate length of string. Quite mode stores value in `$?` register.
| %X <expr>              # Show evaluated expression in hex
| %x[+-]                 # String/Numeric to hex manipulation commands
| %s <start> <stop> <step> # Generate sequence of numbers (?s from to step)
| %P [<paddr>]           # Convert physical to virtual address
| %p [<vaddr>]           # Virtual to physical address conversion
| %_ <input>             # HUD input
| %i[nykpmf]             # Input commands
| %w <addr>              # Get references of given address
```

Some examples:
```
[0x00000000]> %vi 0x8048000
134512640
[0x00000000]> %vi 0x8048000+34
134512674
[0x00000000]> %vi 0x8048000+0x34
134512692
[0x00000000]> %vi 2**10
1024
[0x00000000]> % 1+2+3-4*3
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
```

Supported arithmetic operations are:

 *  \+ : addition
 *  \- : subtraction
 *  \* : multiplication
 *  / : division
 *  % : modulus
 *  \> : shift right
 *  < : shift left
 * \*\* : power

```
[0x00000000]> %vi 1+2+3
6
```

Enclose the expression with double quotes to evaluate `|` as logical OR instead of pipe command.

```
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

```
0x033   : hexadecimal can be displayed
3334    : decimal
sym.fo  : resolve flag offset
10K     : KBytes  10*1024
10M     : MBytes  10*1024*1024
```

You can also use variables and seek positions to build complex expressions.

Use the `%$?` command to list all the available commands or read the refcard chapter of this book.

```
$$    here (the current virtual seek)
$l    opcode length
$s    file size
$j    jump address (e.g. jmp 0x10, jz 0x10 => 0x10)
$f    jump fail address (e.g. jz 0x10 => next instruction)
$m    opcode memory reference (e.g. mov eax,[0x10] => 0x10)
$b    block size
```

Some more examples:

```
[0x4A13B8C0]> % $m + $l
140293837812900 0x7f98b45df4a4 03771426427372244 130658.0G 8b45d000:04a4 140293837812900 10100100 140293837812900.0 -0.000000
```
```
[0x4A13B8C0]> pd 1 @ +$l
0x4A13B8C2   call 0x4a13c000
```
