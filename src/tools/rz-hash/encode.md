# Encoding with rz-hash

As mentioned before, this tool also provide the tooling needed to encode and decode between different encodings

```
$ rz-hash -L | grep ^e
e  base64
e  base91
e  punycode
```

For example, to encode a string into base64 use the following line:

```
$ rz-hash -E base64 -s hello
```

You can decode it by using the -D flag instead of -E.

## Encryption/Decryption

For encrypting data check the crypto hash plugins:

```
$ rz-hash -L | grep ^c
c  rc2
c  rc4
c  rc6
c  aes-ecb
c  aes-cbc
c  ror
c  rol
c  rot
c  blowfish
c  cps2
c  des-ecb
c  xor
c  serpent-ecb
```

Here's an example usage to encrypt a string using rz-hash:

```
$ rz-hash -E xor -S s:password -s hello | hexdump -C
00000000  18 04 1f 1f 18
```
