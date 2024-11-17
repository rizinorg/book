## List Libraries

rz-bin can list libraries used by a binary with the `-l` option:

```
$ rz-bin -l `which rizin`
rz-bin -l `which rizin`
[Libs]
library           
------------------
librz_util.so.0.7
librz_main.so.0.7
libc.so.6

```

Let's check the output with `ldd` command:

```
$ ldd `which rizin`
        linux-vdso.so.1 (0x00007ffe302dd000)
        librz_util.so.0.7 => /usr/lib64/librz_util.so.0.7 (0x00007f6bea740000)
        librz_main.so.0.7 => /usr/lib64/librz_main.so.0.7 (0x00007f6bea705000)
        libc.so.6 => /usr/lib64/libc.so.6 (0x00007f6bea531000)
        libm.so.6 => /usr/lib64/libm.so.6 (0x00007f6bea486000)
        libpcre2-8.so.0 => /usr/lib64/libpcre2-8.so.0 (0x00007f6bea3e8000)
        libz.so.1 => /usr/lib64/libz.so.1 (0x00007f6bea3ce000)
        liblzma.so.5 => /usr/lib64/liblzma.so.5 (0x00007f6bea39e000)
        libcrypto.so.3 => /usr/lib64/libcrypto.so.3 (0x00007f6be9ee7000)
        librz_demangler.so.0.7 => /usr/lib64/librz_demangler.so.0.7 (0x00007f6be9eb7000)
        librz_socket.so.0.7 => /usr/lib64/librz_socket.so.0.7 (0x00007f6be9ea5000)
        librz_flag.so.0.7 => /usr/lib64/librz_flag.so.0.7 (0x00007f6be9e99000)
        librz_cons.so.0.7 => /usr/lib64/librz_cons.so.0.7 (0x00007f6be9e6f000)
        librz_hash.so.0.7 => /usr/lib64/librz_hash.so.0.7 (0x00007f6be9e3c000)
        librz_crypto.so.0.7 => /usr/lib64/librz_crypto.so.0.7 (0x00007f6be9e27000)
        librz_il.so.0.7 => /usr/lib64/librz_il.so.0.7 (0x00007f6be9df9000)
        librz_io.so.0.7 => /usr/lib64/librz_io.so.0.7 (0x00007f6be9dab000)
        librz_reg.so.0.7 => /usr/lib64/librz_reg.so.0.7 (0x00007f6be9d9f000)
        librz_bp.so.0.7 => /usr/lib64/librz_bp.so.0.7 (0x00007f6be9d96000)
        librz_syscall.so.0.7 => /usr/lib64/librz_syscall.so.0.7 (0x00007f6be9d8d000)
        librz_parse.so.0.7 => /usr/lib64/librz_parse.so.0.7 (0x00007f6be9d68000)
        librz_asm.so.0.7 => /usr/lib64/librz_asm.so.0.7 (0x00007f6be9b2b000)
        librz_egg.so.0.7 => /usr/lib64/librz_egg.so.0.7 (0x00007f6be9b18000)
        librz_search.so.0.7 => /usr/lib64/librz_search.so.0.7 (0x00007f6be9b0f000)
        librz_analysis.so.0.7 => /usr/lib64/librz_analysis.so.0.7 (0x00007f6be9876000)
        librz_debug.so.0.7 => /usr/lib64/librz_debug.so.0.7 (0x00007f6be9822000)
        librz_config.so.0.7 => /usr/lib64/librz_config.so.0.7 (0x00007f6be981a000)
        librz_bin.so.0.7 => /usr/lib64/librz_bin.so.0.7 (0x00007f6be96ad000)
        librz_sign.so.0.7 => /usr/lib64/librz_sign.so.0.7 (0x00007f6be969d000)
        librz_core.so.0.7 => /usr/lib64/librz_core.so.0.7 (0x00007f6be93cb000)
        librz_diff.so.0.7 => /usr/lib64/librz_diff.so.0.7 (0x00007f6be93c0000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f6bea860000)
        libssl.so.3 => /usr/lib64/libssl.so.3 (0x00007f6be92d4000)
        libxxhash.so.0 => /usr/lib64/libxxhash.so.0 (0x00007f6be92c8000)
        libzip.so.5 => /usr/lib64/libzip.so.5 (0x00007f6be92ab000)
        libcapstone.so.5 => /usr/lib64/libcapstone.so.5 (0x00007f6be8ba2000)
        librz_type.so.0.7 => /usr/lib64/librz_type.so.0.7 (0x00007f6be8ab0000)
        librz_magic.so.0.7 => /usr/lib64/librz_magic.so.0.7 (0x00007f6be8aab000)
        liblz4.so.1 => /usr/lib64/liblz4.so.1 (0x00007f6be8a84000)
        libzstd.so.1 => /usr/lib64/libzstd.so.1 (0x00007f6be89c9000)
        libmspack.so.0 => /usr/lib64/libmspack.so.0 (0x00007f6be89b4000)
        librz_lang.so.0.7 => /usr/lib64/librz_lang.so.0.7 (0x00007f6be89aa000)
        libbz2.so.1 => /usr/lib64/libbz2.so.1 (0x00007f6be8996000)
        libmagic.so.1 => /usr/lib64/libmagic.so.1 (0x00007f6be896b000)
```

If you compare the outputs of `rz-bin -l` and `ldd`, you will notice that rz-bin lists fewer libraries than `ldd`.
The reason is that rz-bin does not follow and does not show dependencies of libraries.
Only direct binary dependencies are shown.
