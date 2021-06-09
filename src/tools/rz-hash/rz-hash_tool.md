## Examples

The rz-hash tool can be used to calculate checksums and has functions of byte streams, files, text strings.

```
$ rz-hash -h
Usage: rz-hash [-vhBkjLq] [-b S] [-a A] [-c H] [-E A] [-D A] [-s S] [-x S] [-f O] [-t O] [files|-] ...
 -v          Shows version
 -h          Shows this help page
 -           Input read from stdin instead from a file
 -a algo     Hash algorithm to use and you can specify multiple ones by
             appending a comma (example: sha1,md4,md5,sha256)
 -B          Outputs the calculated value for each block
 -b size     Sets the block size
 -c value    Compare calculated value with a given one (hexadecimal)
 -e endian   Sets the endianness (default: 'big' accepted: 'big' or 'little')
 -D algo     Decrypt the given input; use -S to set key and -I to set IV (if needed)
 -E algo     Encrypt the given input; use -S to set key and -I to set IV (if needed)
 -f from     Starts the calculation at given offset
 -t to       Stops the calculation at given offset
 -I iv       Sets the initialization vector (IV)
 -i times    Repeat the calculation N times
 -j          Outputs the result as a JSON structure
 -k          Outputs the calculated value using openssh's randomkey algorithm
 -L          List all algorithms
 -q          Sets quiet mode (use -qq to get only the calculated value)
 -S seed     Sets the seed for -a, use '^' to append it before the input, use '@'
             prefix to load it from a file and '-' from read it
 -K key      Sets the hmac key for -a and the key for -E/-D, use '@' prefix to
             load it from a file and '-' from read it
             from stdin (you can combine them)
 -s string   Input read from a zero-terminated string instead from a file
 -x hex      Input read from a hexadecimal value instead from a file

             All the inputs (besides -s/-x/-c) can be hexadecimal or strings
             if 's:' prefix is specified
```

To obtain an MD5 hash value of a text string, use the `-s` option:

```
$ rz-hash -q -a md5 -s 'hello world'
string: md5: 5eb63bbbe01eeed093cb22bb8f5acdc3
```

It is possible to calculate hash values for contents of files. But do not attempt to do it for very large files because rz-hash buffers the whole input in memory before computing the hash.

To apply all algorithms known to rz-hash, use `all` as an algorithm name:

```
$ rz-hash -a all /bin/ls
/bin/ls: 0x00000000-0x00022a70 md4: 4f34e90ff19613695bfe8ecbddc1ae6d
/bin/ls: 0x00000000-0x00022a70 md5: 27ac5e2f7573020dbff16b3b9c03e678
/bin/ls: 0x00000000-0x00022a70 sha1: 0ca5dcdf79d00cbc893a5cca29695f2afddc193d
/bin/ls: 0x00000000-0x00022a70 sha256: f8b09fba9fda9ffebae86611261cf628bd71022fb4348d876974f7c48ddcc6d5
/bin/ls: 0x00000000-0x00022a70 sha384: ae8404125de3ae798fe85635533dc93744136d812fe279eaa92d1f31896ba4bf9fa0e240ab1b3f234b870f243c5754da
/bin/ls: 0x00000000-0x00022a70 sha512: 4ec188a733c402e277f60d59240aba3279b2fdc261ac479188a28aab899b81be4281283988ccbf78f7ca214eb3fbfb49811743ccdb62a459a52414075e9eae8f
/bin/ls: 0x00000000-0x00022a70 fletcher8: 8d
/bin/ls: 0x00000000-0x00022a70 fletcher16: 8d78
/bin/ls: 0x00000000-0x00022a70 fletcher32: a5e716ad
/bin/ls: 0x00000000-0x00022a70 fletcher64: ae7b1b422fd65611
/bin/ls: 0x00000000-0x00022a70 adler32: e1028925
/bin/ls: 0x00000000-0x00022a70 crc8smbus: 9e
/bin/ls: 0x00000000-0x00022a70 crc8cdma2000: 73
/bin/ls: 0x00000000-0x00022a70 crc8darc: ac
/bin/ls: 0x00000000-0x00022a70 crc8dvbs2: f7
/bin/ls: 0x00000000-0x00022a70 crc8ebu: 6d
/bin/ls: 0x00000000-0x00022a70 crc8icode: 85
/bin/ls: 0x00000000-0x00022a70 crc8itu: cb
/bin/ls: 0x00000000-0x00022a70 crc8maxim: 38
/bin/ls: 0x00000000-0x00022a70 crc8rohc: ef
/bin/ls: 0x00000000-0x00022a70 crc8wcdma: 52
/bin/ls: 0x00000000-0x00022a70 crc15can: 65ec
/bin/ls: 0x00000000-0x00022a70 crc16: f97a
/bin/ls: 0x00000000-0x00022a70 crc16citt: e73b
/bin/ls: 0x00000000-0x00022a70 crc16usb: 2ed9
/bin/ls: 0x00000000-0x00022a70 crc16hdlc: d7cd
/bin/ls: 0x00000000-0x00022a70 crc16augccitt: 2366
/bin/ls: 0x00000000-0x00022a70 crc16buypass: 9eac
/bin/ls: 0x00000000-0x00022a70 crc16cdma2000: d62b
/bin/ls: 0x00000000-0x00022a70 crc16dds110: 02d4
/bin/ls: 0x00000000-0x00022a70 crc16dectr: 9262
/bin/ls: 0x00000000-0x00022a70 crc16dectx: 9263
/bin/ls: 0x00000000-0x00022a70 crc16dnp: d64b
/bin/ls: 0x00000000-0x00022a70 crc16en13757: 9227
/bin/ls: 0x00000000-0x00022a70 crc16genibus: 18c4
/bin/ls: 0x00000000-0x00022a70 crc16maxim: 0685
/bin/ls: 0x00000000-0x00022a70 crc16mcrf4xx: 2832
/bin/ls: 0x00000000-0x00022a70 crc16riello: 0e39
/bin/ls: 0x00000000-0x00022a70 crc16t10dif: dbb5
/bin/ls: 0x00000000-0x00022a70 crc16teledisk: 4fee
/bin/ls: 0x00000000-0x00022a70 crc16tms37157: ba7d
/bin/ls: 0x00000000-0x00022a70 crca: a525
/bin/ls: 0x00000000-0x00022a70 crc16kermit: b131
/bin/ls: 0x00000000-0x00022a70 crc16modbus: d126
/bin/ls: 0x00000000-0x00022a70 crc16x25: d7cd
/bin/ls: 0x00000000-0x00022a70 crc16xmodem: 27a2
/bin/ls: 0x00000000-0x00022a70 crc24: 007476f5
/bin/ls: 0x00000000-0x00022a70 crc32: 09ad52f8
/bin/ls: 0x00000000-0x00022a70 crc32ecma267: 4da033c1
/bin/ls: 0x00000000-0x00022a70 crc32c: ad8aa54c
/bin/ls: 0x00000000-0x00022a70 crc32bzip2: 2db14275
/bin/ls: 0x00000000-0x00022a70 crc32d: 1a82c6fe
/bin/ls: 0x00000000-0x00022a70 crc32mpeg2: d24ebd8a
/bin/ls: 0x00000000-0x00022a70 crc32posix: 58bb93aa
/bin/ls: 0x00000000-0x00022a70 crc32q: fa075365
/bin/ls: 0x00000000-0x00022a70 crc32jamcrc: f652ad07
/bin/ls: 0x00000000-0x00022a70 crc32xfer: bd66a285
/bin/ls: 0x00000000-0x00022a70 crc64: 02bfeb9d3cc5ba89
/bin/ls: 0x00000000-0x00022a70 crc64ecma182: 02bfeb9d3cc5ba89
/bin/ls: 0x00000000-0x00022a70 crc64we: 45f4fd1aca1b6d00
/bin/ls: 0x00000000-0x00022a70 crc64xz: 7ad92fbc2cb7bbaa
/bin/ls: 0x00000000-0x00022a70 crc64iso: 69770b2efe4f8aae
/bin/ls: 0x00000000-0x00022a70 xor8: 92
/bin/ls: 0x00000000-0x00022a70 xor16: 594c
/bin/ls: 0x00000000-0x00022a70 xxhash32: 95374b80
/bin/ls: 0x00000000-0x00022a70 parity: 01000000
/bin/ls: 0x00000000-0x00022a70 entropy: 5.84008688
/bin/ls: 0x00000000-0x00022a70 entropy_fract: 0.73001086
```
