# Rz-hash

The `rz-hash` tool can be used to compute checksums of files, disk devices or strings. By block or entirely using many different hash algorithms.

This tool is also capable of doing some encoding/decoding operations like base64 and xor encoding.

This is an example usage:

```
$ rz-hash -a md5 -s "hello world"
```

Note that rz-hash also permits to read from files in a stream, so you don't need 4GB of ram to compute the hash of a 4GB file.

## Hashing by blocks

When doing forensics, it is useful to compute partial checksums. The reason for that is because you may want to split a huge file into small portions that are easier to identify by contents or regions in the disk.

This will spot the same hash for blocks containing the same contents. For example, if is filled with zeros.

It can also be used to find which blocks have changed between more than one sample dump.

This can be useful when analyzing ram dumps from a virtual machine for example. Use this command for this:

```
$ rz-hash -b 1M -B -a sha256 /bin/ls
```

## Hashing with rz-bin

The rz-bin tool parses the binary headers of the files, but it also have the ability to use the rhash plugins to compute checksum of sections in the binary.

```
$ rz-bin -K md5 -S /bin/ls
```

## Obtaining hashes within rizin session

To calculate a checksum of current block when running rizin, use the `ph` command. Pass an algorithm name to it as a parameter. An example session:

```
$ rizin /bin/ls
[0x08049790]> bf entry0
[0x08049790]> ph md5
d2994c75adaa58392f953a448de5fba7
```

You can use all hashing algorithms supported by `rz-hash`:

```
[0x00000000]> ph?
algorithm      license    author
md4            LGPL3      deroad
md5            RSA-MD     RSA Data Security, Inc.
sha1           LGPL3      deroad
sha256         BSD-3      Aaron D. Gifford
sha384         BSD-3      Aaron D. Gifford
sha512         BSD-3      Aaron D. Gifford
fletcher8      LGPL3      deroad
fletcher16     LGPL3      deroad
fletcher32     LGPL3      deroad
fletcher64     LGPL3      deroad
adler32        LGPL3      deroad
crc8smbus      LGPL3      deroad
crc8cdma2000   LGPL3      deroad
crc8darc       LGPL3      deroad
crc8dvbs2      LGPL3      deroad
crc8ebu        LGPL3      deroad
crc8icode      LGPL3      deroad
crc8itu        LGPL3      deroad
crc8maxim      LGPL3      deroad
crc8rohc       LGPL3      deroad
crc8wcdma      LGPL3      deroad
crc15can       LGPL3      deroad
crc16          LGPL3      deroad
crc16citt      LGPL3      deroad
crc16usb       LGPL3      deroad
crc16hdlc      LGPL3      deroad
crc16augccitt  LGPL3      deroad
crc16buypass   LGPL3      deroad
crc16cdma2000  LGPL3      deroad
crc16dds110    LGPL3      deroad
crc16dectr     LGPL3      deroad
crc16dectx     LGPL3      deroad
crc16dnp       LGPL3      deroad
crc16en13757   LGPL3      deroad
crc16genibus   LGPL3      deroad
crc16maxim     LGPL3      deroad
crc16mcrf4xx   LGPL3      deroad
crc16riello    LGPL3      deroad
crc16t10dif    LGPL3      deroad
crc16teledisk  LGPL3      deroad
crc16tms37157  LGPL3      deroad
crca           LGPL3      deroad
crc16kermit    LGPL3      deroad
crc16modbus    LGPL3      deroad
crc16x25       LGPL3      deroad
crc16xmodem    LGPL3      deroad
crc24          LGPL3      deroad
crc32          LGPL3      deroad
crc32ecma267   LGPL3      deroad
crc32c         LGPL3      deroad
crc32bzip2     LGPL3      deroad
crc32d         LGPL3      deroad
crc32mpeg2     LGPL3      deroad
crc32posix     LGPL3      deroad
crc32q         LGPL3      deroad
crc32jamcrc    LGPL3      deroad
crc32xfer      LGPL3      deroad
crc64          LGPL3      deroad
crc64ecma182   LGPL3      deroad
crc64we        LGPL3      deroad
crc64xz        LGPL3      deroad
crc64iso       LGPL3      deroad
xor8           LGPL3      deroad
xor16          LGPL3      deroad
xxhash32       LGPL3      deroad
parity         LGPL3      deroad
entropy        LGPL3      deroad
entropy_fract  LGPL3      deroad
```

The `ph` command accepts an optional numeric argument to specify length of byte range to be hashed, instead of default block size. For example:

```
[0x08049A80]> ph md5 32
9b9012b00ef7a94b5824105b7aaad83b
[0x08049A80]> ph md5 64
a71b087d8166c99869c9781e2edcf183
[0x08049A80]> ph md5 1024
a933cc94cd705f09a41ecc80c0041def
```
