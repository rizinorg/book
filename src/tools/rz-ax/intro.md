# Rz-ax

The `rz-ax` utility comes with the Rizin framework and aims to be a minimalistic expression evaluator for the shell.
It is useful for making base conversions between floating point values, hexadecimal representations, hexpair strings
to ascii, octal to integer. It supports endianness and can be used as a shell if no arguments are given.

This is the help message of rz-ax, this tool can be used in the command-line or interactively
(reading the values from stdin), so it can be used as a multi-base calculator.

Inside Rizin, the functionality of rz-ax is available under the `%` command. For example:

```bash
[0x00000000]> % 3+4
```

As you can see, the numeric expressions can contain mathematical expressions like addition, subtraction,
as well as group operations with parenthesis.

The syntax in which the numbers are represented define the base, for example:

* 3 : decimal, base 10
* 0xface : hexadecimal, base 16
* 0472 : octal, base 8
* 2M : units, 2 megabytes
* ...

This is the help message of rz-ax -h, which will show you a bunch more syntaxes

```bash
$ rz-ax -h
Usage: rz-ax [options] [expr ...]
  =[base]                      ;  rz-ax =10 0x46 -> output in base 10
  int     ->  hex              ;  rz-ax 10
  hex     ->  int              ;  rz-ax 0xa
  -int    ->  hex              ;  rz-ax -77
  -hex    ->  int              ;  rz-ax 0xffffffb3
  int     ->  bin              ;  rz-ax b30
  int     ->  ternary          ;  rz-ax t42
  bin     ->  int              ;  rz-ax 1010d
  ternary ->  int              ;  rz-ax 1010dt
  float   ->  hex              ;  rz-ax 3.33f
  hex     ->  float            ;  rz-ax Fx40551ed8
  oct     ->  hex              ;  rz-ax 35o
  hex     ->  oct              ;  rz-ax Ox12 (O is a letter)
  bin     ->  hex              ;  rz-ax 1100011b
  hex     ->  bin              ;  rz-ax Bx63
  ternary ->  hex              ;  rz-ax 212t
  hex     ->  ternary          ;  rz-ax Tx23
  raw     ->  hex              ;  rz-ax -S < /binfile
  hex     ->  raw              ;  rz-ax -s 414141
  -l                           ;  append newline to output (for -E/-D/-r/..
  -a      show ascii table     ;  rz-ax -a
  -b      bin -> str           ;  rz-ax -b 01000101 01110110
  -B      str -> bin           ;  rz-ax -B hello
  -d      force integer        ;  rz-ax -d 3 -> 3 instead of 0x3
  -e      swap endianness      ;  rz-ax -e 0x33
  -D      base64 decode        ;
  -E      base64 encode        ;
  -f      floating point       ;  rz-ax -f 6.3+2.1
  -F      stdin slurp code hex ;  rz-ax -F < shellcode.[c/py/js]
  -h      show this help       ;  rz-ax -h
  -i      dump as C byte array ;  rz-ax -i < bytes
  -I      IP address <-> LONG  ;  rz-ax -I 3530468537
  -k      keep base            ;  rz-ax -k 33+3 -> 36
  -L      bin -> hex(bignum)   ;  rz-ax -L 111111111 # 0x1ff
  -n      int value -> hexpairs;  rz-ax -n 0x1234 # 34120000
  -o      octalstr -> raw      ;  rz-ax -o \162 \172 # rz
  -N      binary number        ;  rz-ax -N 0x1234 # \x34\x12\x00\x00
  -r      rz style output      ;  rz-ax -r 0x1234
  -s      hexstr -> raw        ;  rz-ax -s 43 4a 50
  -S      raw -> hexstr        ;  rz-ax -S < /bin/ls > ls.hex
  -t      tstamp -> str        ;  rz-ax -t 1234567890
  -x      hash string          ;  rz-ax -x linux osx
  -u      units                ;  rz-ax -u 389289238 # 317.0M
  -w      signed word          ;  rz-ax -w 16 0xffff
  -v      version              ;  rz-ax -v
  -p      position of set bits ;  rz-ax -p 0xb3
```

Some examples:

```bash
$ rz-ax 3+0x80
0x83

$ rz-ax 0x80+3
131

$ echo 0x80+3 | rz-ax
131

$ rz-ax -s 4142
AB

$ rz-ax -S AB
4142

$ rz-ax -S < bin.foo
...

$ rz-ax -e 33
0x21000000

$ rz-ax -e 0x21000000
33

$ rz-ax -K 90203010
+--[0x10302090]---+
|Eo. .            |
| . . . .         |
|      o          |
|       .         |
|        S        |
|                 |
|                 |
|                 |
|                 |
+-----------------+
```
