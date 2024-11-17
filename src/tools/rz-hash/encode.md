# Encoding with rz-hash

As mentioned before, this tool also provide the tooling needed to encode and decode between different encodings

```
$ rz-hash -L | grep "^..e"
__ed__ base64         LGPL-3     rakholiyajenish.07
__ed__ base91         LGPL-3     rakholiyajenish.07
__ed__ punycode       LGPL-3     pancake
```

For example, to encode a string into base64 use the following line:

```
$ rz-hash -E base64 -s hello
0x00000000-0x00000005 base64: aGVsbG8=
```

You can decode it by using the -D flag instead of -E.

## Encryption/Decryption

For encrypting data check the crypto hash plugins:

```
$ rz-hash -L | grep "^E\|^_D"
ED____ aes-ecb        LGPL3      Nettle project (algorithm implementation), pancake (plugin)
ED____ aes-cbc        LGPL-3     rakholiyajenish.07
ED____ blowfish       LGPL3      kishorbhat
ED____ cps2           LGPL-3     pancake,esanfelix,pof
ED____ des-ecb        LGPL-3     deroad
ED____ rc2            LGPL-3     lionaneesh
ED____ rc4            LGPL-3     pancake
ED____ rc6            LGPL-3     rakholiyajenish.07
E_____ rol            LGPL-3     pancake
_D____ ror            LGPL-3     pancake
ED____ rot            LGPL-3     pancake
ED____ serpent-ecb    LGPL-3     NicsTr
ED____ xor            LGPL-3     pancake
ED____ sm4-ecb        LGPL-3     0xSh4dy
```

Here's an example usage to encrypt a string using rz-hash:

```
$ rz-hash -qqE xor -K s:password -s hello | hexdump -C
00000000  18 04 1f 1f 18                                    |.....|
00000005
```
