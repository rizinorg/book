## Writing Data

Rizin can manipulate a loaded binary file in many ways. You can resize the file, move and copy/paste bytes, insert new bytes (shifting data to the end of the block or file), or simply overwrite bytes. New data may be given as a wide-string, assembler instructions, or the data may be read in from another file.

Resize the file using the `r` command. It accepts a numeric argument. A positive value sets a new size for the file. A negative one will truncate the file to the current seek position minus N bytes.

```
r 1024      ; resize the file to 1024 bytes
r -10 @ 33  ; strip 10 bytes at offset 33
```
Write bytes using the `w` command. It accepts multiple input formats like inline assembly, endian-friendly dwords, files, hexpair files, wide strings:

```
[0x00404888]> w?
Usage: w[?]   # Write commands
| w <string>        # Write string
| wB[-]             # Set or unset bits with given value
| wv[1248]          # Write value of given size
| w0 <len>          # Write <len> bytes with value 0x00
| w<1248><+-> [<n>] # increment/decrement byte, word, ..
| w6<de>            # Write base64 [d]ecoded or [e]ncoded string
| we[?]             # Extend write operations (insert bytes instead of replacing)
| wu[?]             # Apply unified hex patch (see output of cu)
| wr <len>          # Write <len> random bytes
| wA[?]             # Alter/modify opcode at current seek (see wA?)
| wc[?]             # Write cache commands
| wz[?]             # Write zero-terminated string
| wt[?]             # Write to file
| wf[xfs]           # Write data from file, socket, offset
| ww[?]             # Write wide string
| wx[f]             # Write hexadecimal data
| wa[ifo]           # Write opcodes
| wb[?]             # Write in current block with cyclic hexstring
| wm[?]             # Set binary mask hexpair to be used as cyclic write mask
| wo[?]             # Write in block with operation
| wd[?]             # Duplicate N bytes from offset at current seek
| ws <string>       # Write 1 byte for length and then the string
```

Some examples:

```
 [0x00000000]> wx 123456 @ 0x8048300
 [0x00000000]> wv 0x8048123 @ 0x8049100
 [0x00000000]> wa "jmp 0x8048320"
```

### Write Over

The `wo` command (write over) has many subcommands, each combines the existing data with the new data using
an operator. The command is applied to the current block. Supported operators include XOR, ADD, SUB...

```
[0x4A13B8C0]> wo?
|Usage: wo[asmdxoArl24] [hexpairs] @ addr[:bsize]
|Example:
|  wox 0x90   ; xor cur block with 0x90
|  wox 90     ; xor cur block with 0x90
|  wox 0x0203 ; xor cur block with 0203
|  woa 02 03  ; add [0203][0203][...] to curblk
|  woe 02 03  ; create sequence from 2 to 255 with step 3
|Supported operations:
|  wow  ==  write looped value (alias for 'wb')
|  woa  +=  addition
|  wos  -=  subtraction
|  wom  *=  multiply
|  wod  /=  divide
|  wox  ^=  xor
|  woo  |=  or
|  woA  &=  and
|  woR  random bytes (alias for 'wr $b'
|  wor  >>= shift right
|  wol  <<= shift left
|  wo2  2=  2 byte endian swap
|  wo4  4=  4 byte endian swap
```

It is possible to implement cipher-algorithms using rizin core primitives and `wo`. A sample session performing xor(90) + add(01, 02):

```
[0x7fcd6a891630]> px
- offset -       0 1  2 3  4 5  6 7  8 9  A B  C D  E F
0x7fcd6a891630  4889 e7e8 6839 0000 4989 c48b 05ef 1622
0x7fcd6a891640  005a 488d 24c4 29c2 5248 89d6 4989 e548
0x7fcd6a891650  83e4 f048 8b3d 061a 2200 498d 4cd5 1049
0x7fcd6a891660  8d55 0831 ede8 06e2 0000 488d 15cf e600
[0x7fcd6a891630]> wox 90
[0x7fcd6a891630]> px
- offset -       0 1  2 3  4 5  6 7  8 9  A B  C D  E F
0x7fcd6a891630  d819 7778 d919 541b 90ca d81d c2d8 1946
0x7fcd6a891640  1374 60d8 b290 d91d 1dc5 98a1 9090 d81d
0x7fcd6a891650  90dc 197c 9f8f 1490 d81d 95d9 9f8f 1490
0x7fcd6a891660  13d7 9491 9f8f 1490 13ff 9491 9f8f 1490
[0x7fcd6a891630]> woa 01 02
[0x7fcd6a891630]> px
- offset -       0 1  2 3  4 5  6 7  8 9  A B  C D  E F
0x7fcd6a891630  d91b 787a 91cc d91f 1476 61da 1ec7 99a3
0x7fcd6a891640  91de 1a7e d91f 96db 14d9 9593 1401 9593
0x7fcd6a891650  c4da 1a6d e89a d959 9192 9159 1cb1 d959
0x7fcd6a891660  9192 79cb 81da 1652 81da 1456 a252 7c77
```
