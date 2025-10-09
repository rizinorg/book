## Examples

The rz-hash tool can be used to calculate checksums and has functions of byte streams, files, text strings.

```bash
$ rz-hash -h
Usage: rz-hash [-vhBkjLq] [-b S] [-a A] [-c H] [-E A] [-D A] [-s S] [-x S] [-f O] [-t O] [files|-] ...
 -v        Show version information
 -h        Show this help
 -         Input read from stdin instead from a file
 -a algo   Hash algorithm to use and you can specify multiple ones by
           Appending a comma (example: sha1,md4,md5,sha256)
 -B        Output the calculated value for each block
 -b size   Set the block size
 -c value  Compare calculated value with a given one (hexadecimal)
 -e endian Set the endianness (default: 'big' accepted: 'big' or 'little')
 -D algo   Decrypt the given input; use -S to set key and -I to set IV (if needed)
 -E algo   Encrypt the given input; use -S to set key and -I to set IV (if needed)
 -f from   Start the calculation at given offset
 -t to     Stop the calculation at given offset
 -I iv     Set the initialization vector (IV)
 -i times  Repeat the calculation N times
 -j        Output the result as a JSON structure
 -k        Output the calculated value using openssh′s randomkey algorithm
 -L        List all algorithms
 -q        Set quiet mode (use -qq to get only the calculated value)
 -S seed   Set the seed for -a, use '^' to append it before the input, use '@'
           Prefix to load it from a file and '-' from read it
 -K key    Set the hmac key for -a and the key for -E/-D, use '@' prefix to
           Load it from a file and '-' from read it
           From stdin (you can combine them)
 -s string Input read from a zero-terminated string instead from a file
 -x hex    Input read from a hexadecimal value instead from a file

           All the input (besides -s/-x/-c) can be hexadecimal or strings
           If 's:' prefix is specified
```

To obtain an MD5 hash value of a text string, use the `-s` option:

```bash
$ rz-hash -q -a md5 -s 'hello world'
```
```
string: md5: 5eb63bbbe01eeed093cb22bb8f5acdc3
```

It is possible to calculate hash values for contents of files. But do not attempt to do it for very large files
because rz-hash buffers the whole input in memory before computing the hash.

To apply all algorithms known to rz-hash, use `all` as an algorithm name:

```bash
$ rz-hash -a all /usr/bin/ls
```
```
/usr/bin/ls: 0x00000000-0x00024ac8 md2: 9a2a86a52e9cb44b2e06a58a00fee15e
/usr/bin/ls: 0x00000000-0x00024ac8 md4: 725fc3498847e96d031ce4d1f4872b28
/usr/bin/ls: 0x00000000-0x00024ac8 md5: bcf16aef7487e6ea478a168c180c07fa
/usr/bin/ls: 0x00000000-0x00024ac8 sha1: ccb226a119fe301b2ad2dc8a7013faf6f6296ea1
/usr/bin/ls: 0x00000000-0x00024ac8 sha256: 1ba437f3522d9e416f66425fdb816dfbaf32b4140d2092f2b8922b2825e4065a
/usr/bin/ls: 0x00000000-0x00024ac8 sha384: fd51260b6db6940f37a3177b033e1a7e9c1cedd3ee5c9c45e3dfdac135a65edf991313da7083551f091ef553e2f4fe29
/usr/bin/ls: 0x00000000-0x00024ac8 sha512: de26d5385088825cce3fcb87645ddf2148e4c71013ff98170ccd106795d6cf4669e1b71053593472667ff64f17a0190ab3d99430d784a0489c7bc6344d5605db
/usr/bin/ls: 0x00000000-0x00024ac8 sm3: 9410230b34c9ab0c527c21cbdb9f953cc747479c89d019a4f6ae4c7cffd40bb0
/usr/bin/ls: 0x00000000-0x00024ac8 blake3: 5805f287d8c0107ffdc7960b6112b586940d9767e888023048543daefa4cf6e5
/usr/bin/ls: 0x00000000-0x00024ac8 fletcher8: dd
/usr/bin/ls: 0x00000000-0x00024ac8 fletcher16: ddf3
/usr/bin/ls: 0x00000000-0x00024ac8 fletcher32: dd003c1a
/usr/bin/ls: 0x00000000-0x00024ac8 fletcher64: 5952f47d393a5468
/usr/bin/ls: 0x00000000-0x00024ac8 adler32: 86e2c3a1
/usr/bin/ls: 0x00000000-0x00024ac8 crc8smbus: 15
/usr/bin/ls: 0x00000000-0x00024ac8 crc8cdma2000: d9
/usr/bin/ls: 0x00000000-0x00024ac8 crc8darc: 3b
/usr/bin/ls: 0x00000000-0x00024ac8 crc8dvbs2: 3d
/usr/bin/ls: 0x00000000-0x00024ac8 crc8ebu: 67
/usr/bin/ls: 0x00000000-0x00024ac8 crc8icode: 67
/usr/bin/ls: 0x00000000-0x00024ac8 crc8itu: 40
/usr/bin/ls: 0x00000000-0x00024ac8 crc8maxim: b3
/usr/bin/ls: 0x00000000-0x00024ac8 crc8rohc: ad
/usr/bin/ls: 0x00000000-0x00024ac8 crc8wcdma: ab
/usr/bin/ls: 0x00000000-0x00024ac8 crc15can: 7126
/usr/bin/ls: 0x00000000-0x00024ac8 crc16: f310
/usr/bin/ls: 0x00000000-0x00024ac8 crc16citt: be97
/usr/bin/ls: 0x00000000-0x00024ac8 crc16usb: 9f67
/usr/bin/ls: 0x00000000-0x00024ac8 crc16hdlc: 282a
/usr/bin/ls: 0x00000000-0x00024ac8 crc16augccitt: 5c10
/usr/bin/ls: 0x00000000-0x00024ac8 crc16buypass: fc1c
/usr/bin/ls: 0x00000000-0x00024ac8 crc16cdma2000: d203
/usr/bin/ls: 0x00000000-0x00024ac8 crc16dds110: 98aa
/usr/bin/ls: 0x00000000-0x00024ac8 crc16dectr: 0485
/usr/bin/ls: 0x00000000-0x00024ac8 crc16dectx: 0484
/usr/bin/ls: 0x00000000-0x00024ac8 crc16dnp: d2fd
/usr/bin/ls: 0x00000000-0x00024ac8 crc16en13757: f12e
/usr/bin/ls: 0x00000000-0x00024ac8 crc16genibus: 4168
/usr/bin/ls: 0x00000000-0x00024ac8 crc16maxim: 0cef
/usr/bin/ls: 0x00000000-0x00024ac8 crc16mcrf4xx: d7d5
/usr/bin/ls: 0x00000000-0x00024ac8 crc16riello: ecaa
/usr/bin/ls: 0x00000000-0x00024ac8 crc16t10dif: faeb
/usr/bin/ls: 0x00000000-0x00024ac8 crc16teledisk: bee3
/usr/bin/ls: 0x00000000-0x00024ac8 crc16tms37157: 60a7
/usr/bin/ls: 0x00000000-0x00024ac8 crca: e518
/usr/bin/ls: 0x00000000-0x00024ac8 crc16kermit: 0dcc
/usr/bin/ls: 0x00000000-0x00024ac8 crc16modbus: 6098
/usr/bin/ls: 0x00000000-0x00024ac8 crc16x25: 282a
/usr/bin/ls: 0x00000000-0x00024ac8 crc16xmodem: 26cc
/usr/bin/ls: 0x00000000-0x00024ac8 crc24: 0078edb6
/usr/bin/ls: 0x00000000-0x00024ac8 crc32: ea7111a0
/usr/bin/ls: 0x00000000-0x00024ac8 crc32ecma267: d7f2cb8a
/usr/bin/ls: 0x00000000-0x00024ac8 crc32c: bb2af410
/usr/bin/ls: 0x00000000-0x00024ac8 crc32bzip2: b307ddba
/usr/bin/ls: 0x00000000-0x00024ac8 crc32d: 5de137a9
/usr/bin/ls: 0x00000000-0x00024ac8 crc32mpeg2: 4cf82245
/usr/bin/ls: 0x00000000-0x00024ac8 crc32posix: 35f6bff2
/usr/bin/ls: 0x00000000-0x00024ac8 crc32q: 54013d42
/usr/bin/ls: 0x00000000-0x00024ac8 crc32jamcrc: 158eee5f
/usr/bin/ls: 0x00000000-0x00024ac8 crc32xfer: 7d03019b
/usr/bin/ls: 0x00000000-0x00024ac8 crc64: 60f233ef3032deac
/usr/bin/ls: 0x00000000-0x00024ac8 crc64ecma182: 60f233ef3032deac
/usr/bin/ls: 0x00000000-0x00024ac8 crc64we: c52bf0d6179e06ef
/usr/bin/ls: 0x00000000-0x00024ac8 crc64xz: eab2da06f0ff2682
/usr/bin/ls: 0x00000000-0x00024ac8 crc64iso: 8734628b8dc355f3
/usr/bin/ls: 0x00000000-0x00024ac8 xor8: fd
/usr/bin/ls: 0x00000000-0x00024ac8 xor16: 67ec
/usr/bin/ls: 0x00000000-0x00024ac8 xxhash32: 8a1da333
/usr/bin/ls: 0x00000000-0x00024ac8 ssdeep: 3072:HANnWPSHOTx1XPglbUXVoaJzbuWXod7QHwOP1hKYfrMJM:HABAIi162VjJzCpJQHwWhHr0
/usr/bin/ls: 0x00000000-0x00024ac8 parity: 01
/usr/bin/ls: 0x00000000-0x00024ac8 entropy: 5.95354820
/usr/bin/ls: 0x00000000-0x00024ac8 entropy_fract: 0.74419352
```
