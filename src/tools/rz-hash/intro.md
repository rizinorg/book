# Rz-hash

The `rz-hash` tool can be used to compute checksums of files, disk devices or strings. By block or entirely using
many different hash algorithms.

This tool is also capable of doing some encoding/decoding operations like base64 and xor encoding.

This is an example usage:

```
$ rz-hash -a md5 -s "hello world"
string: 0x00000000-0x0000000b md5: 5eb63bbbe01eeed093cb22bb8f5acdc3
```

Note that rz-hash also permits to read from files in a stream, so you don't need 4GB of ram to compute the hash
of a 4GB file.

## Hashing by blocks

When doing forensics, it is useful to compute partial checksums. The reason for that is because you may want to split
a huge file into small portions that are easier to identify by contents or regions in the disk.

This will spot the same hash for blocks containing the same contents. For example, if is filled with zeros.

It can also be used to find which blocks have changed between more than one sample dump.

This can be useful when analyzing ram dumps from a virtual machine for example. Use this command for this:

```
$ rz-hash -b 1M -B -a sha256 /usr/bin/ls
/usr/bin/ls: 0x00000000-0x00000001 sha256: 620bfdaa346b088fb49998d92f19a7eaf6bfc2fb0aee015753966da1028cb731
/usr/bin/ls: 0x00000001-0x00000002 sha256: a9f51566bd6705f7ea6ad54bb9deb449f795582d6529a0e22207b8981233ec58
/usr/bin/ls: 0x00000002-0x00000003 sha256: 72dfcfb0c470ac255cde83fb8fe38de8a128188e03ea5ba5b2a93adbea1062fa
/usr/bin/ls: 0x00000003-0x00000004 sha256: f67ab10ad4e4c53121b6a5fe4da9c10ddee905b978d3788d2723d7bfacbe28a9
/usr/bin/ls: 0x00000004-0x00000005 sha256: dbc1b4c900ffe48d575b5da5c638040125f65db0fe3e24494b76ea986457d986
/usr/bin/ls: 0x00000005-0x00000006 sha256: 4bf5122f344554c53bde2ebb8cd2b7e3d1600ad631c385a5d7cce23c7785459a
/usr/bin/ls: 0x00000006-0x00000007 sha256: 4bf5122f344554c53bde2ebb8cd2b7e3d1600ad631c385a5d7cce23c7785459a
/usr/bin/ls: 0x00000007-0x00000008 sha256: 6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d
/usr/bin/ls: 0x00000008-0x00000009 sha256: 6e340b9cffb37a989ca544e6bb780a2c78901d3fb33738768511a30617afa01d
...
```

## Hashing with rz-bin

The rz-bin tool parses the binary headers of the files, but it also have the ability to use the rhash plugins to compute checksum of sections in the binary.

```
$ rz-bin -K md5 -S /usr/bin/ls
[Sections]
paddr      size    vaddr      vsize   align perm name               type       flags         md5                              
------------------------------------------------------------------------------------------------------------------------------
0x00000000 0x0     ---------- 0x0     0x0   ----                    NULL       
0x00000318 0x1c    0x00000318 0x1c    0x0   -r-- .interp            PROGBITS   alloc         91476dafa5ef669483350538fa6ec4cb
0x00000338 0x50    0x00000338 0x50    0x0   -r-- .note.gnu.property NOTE       alloc         b020406d0153b9a8b093dc5320cf1858
0x00000388 0x20    0x00000388 0x20    0x0   -r-- .note.ABI-tag      NOTE       alloc         3ac31b2ebb8a59ed3542fd7de044fbeb
0x000003a8 0x98    0x000003a8 0x98    0x0   -r-- .gnu.hash          GNU_HASH   alloc         66294f432dce133a6929d846de86169d
0x00000440 0xaf8   0x00000440 0xaf8   0x0   -r-- .dynsym            DYNSYM     alloc         774725bcfcbbb51079e3fd2973c3aa41
0x00000f38 0x564   0x00000f38 0x564   0x0   -r-- .dynstr            STRTAB     alloc         1fe7093dac1a162ed80703082430bc66
0x0000149c 0xea    0x0000149c 0xea    0x0   -r-- .gnu.version       VERSYM     alloc         b28fd251f91eb3d1be5a1d68a83499b0
0x00001588 0xe0    0x00001588 0xe0    0x0   -r-- .gnu.version_r     VERNEED    alloc         443b0d1c61039ec732b43fea288b2e65
0x00001668 0x150   0x00001668 0x150   0x0   -r-- .rela.dyn          RELA       alloc         dbbe4ca304f452516463a3d53b66410d
0x000017b8 0x948   0x000017b8 0x948   0x0   -r-- .rela.plt          RELA       alloc,info    0b50c15bd0eea13bd064b74d0854f55a
0x00002100 0x50    0x00002100 0x50    0x0   -r-- .relr.dyn          NUM        alloc         888d536429b8c32d615ee09e6f48bc8e
0x00003000 0x1b    0x00003000 0x1b    0x0   -r-x .init              PROGBITS   alloc,execute 34780ae97b075b73ee8ed3c08929bb2d
0x00003020 0x640   0x00003020 0x640   0x0   -r-x .plt               PROGBITS   alloc,execute 6fb9ff6fe33cf9724ff1881cae5ddc3a
0x00003660 0x40    0x00003660 0x40    0x0   -r-x .plt.got           PROGBITS   alloc,execute c3f69157c5b164dde89f4d93d01a2fbb
0x000036a0 0x630   0x000036a0 0x630   0x0   -r-x .plt.sec           PROGBITS   alloc,execute 100ad3792d4e9afca167c23151a4b81d
0x00003cd0 0x14972 0x00003cd0 0x14972 0x0   -r-x .text              PROGBITS   alloc,execute 90839f5851706a61bb3f87f0fba97be2
0x00018644 0xd     0x00018644 0xd     0x0   -r-x .fini              PROGBITS   alloc,execute 7f954257b760b556cf4c5678b9b1ba6c
0x00019000 0x5453  0x00019000 0x5453  0x0   -r-- .rodata            PROGBITS   alloc         a6452d25e0a10ac8e59df34eba3237fc
0x0001e454 0x9b4   0x0001e454 0x9b4   0x0   -r-- .eh_frame_hdr      PROGBITS   alloc         ad1d1656aae20f61478eafef5735ad02
0x0001ee08 0x3348  0x0001ee08 0x3348  0x0   -r-- .eh_frame          PROGBITS   alloc         abb13e58f45411038e69c9ea963cf132
0x00022f50 0x8     0x00023f50 0x8     0x0   -rw- .init_array        INIT_ARRAY write,alloc   b7e2f760e1a646fcbdbc90e96e559b98
0x00022f58 0x8     0x00023f58 0x8     0x0   -rw- .fini_array        FINI_ARRAY write,alloc   c8fb88b08b2f528a3e4be0ed611f5ceb
0x00022f60 0xaf8   0x00023f60 0xaf8   0x0   -rw- .data.rel.ro       PROGBITS   write,alloc   c269cce7d0d0d50ffefd4cc280e04dda
0x00023a58 0x220   0x00024a58 0x220   0x0   -rw- .dynamic           DYNAMIC    write,alloc   361d08a3c3a340966033f22e686839c2
0x00023c78 0x370   0x00024c78 0x370   0x0   -rw- .got               PROGBITS   write,alloc   7731c689f4ca5fa4d6327707418424ce
0x00024000 0x280   0x00025000 0x280   0x0   -rw- .data              PROGBITS   write,alloc   408649c72414b451e99cabc3b72cc401
0x00024280 0x0     0x00025280 0x12d8  0x0   -rw- .bss               NOBITS     write,alloc
0x00024280 0x105   ---------- 0x105   0x0   ---- .shstrtab          STRTAB                   87b94c07525325673cb9303007685933
```

## Obtaining hashes within rizin session

To calculate a checksum of current block when running Rizin, use the `ph` command. Pass an algorithm name to it
as a parameter. An example session:

```
$ rizin /usr/bin/ls
[0x00005880]> bf entry0
[0x00005880]> ph md5
6334c2ae05c2421c687f516772b817da
```

You can use all hashing algorithms supported by `rz-hash`:

```
[0x00000000]> phl
algorithm      license    author
md2            LGPL3      swedenspy
md4            Apache 2.0 OpenSSL Team
md5            Apache 2.0 OpenSSL Team
sha1           Apache 2.0 OpenSSL Team
sha256         Apache 2.0 OpenSSL Team
sha384         Apache 2.0 OpenSSL Team
sha512         Apache 2.0 OpenSSL Team
sm3            Apache 2.0 OpenSSL Team
blake3         CC0        Samuel Neves,Jack O'Connor
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
ssdeep         LGPL3      deroad
parity         LGPL3      deroad
entropy        LGPL3      deroad
entropy_fract  LGPL3      deroad
```

The `ph` command accepts an optional numeric argument to specify length of byte range to be hashed, instead of
default block size. For example:

```
[0x08049A80]> ph md5 32
9b9012b00ef7a94b5824105b7aaad83b
[0x08049A80]> ph md5 64
a71b087d8166c99869c9781e2edcf183
[0x08049A80]> ph md5 1024
a933cc94cd705f09a41ecc80c0041def
```
