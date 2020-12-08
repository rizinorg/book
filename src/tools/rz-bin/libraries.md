## List Libraries

rz-bin can list libraries used by a binary with the `-l` option:
```
$ rz-bin -l `which rizin`
[Linked libraries]
librz_core.so
librz_parse.so
librz_search.so
librz_cons.so
librz_config.so
librz_bin.so
librz_debug.so
librz_analysis.so
librz_reg.so
librz_bp.so
librz_io.so
librz_fs.so
librz_asm.so
librz_syscall.so
librz_hash.so
librz_magic.so
librz_flag.so
librz_egg.so
librz_crypto.so
librz_util.so
libpthread.so.0
libc.so.6

22 libraries
```
Lets check the output with `ldd` command:
```
$ ldd `which rizin`
linux-vdso.so.1 (0x00007fffba38e000)
librz_core.so => /usr/lib64/librz_core.so (0x00007f94b4678000)
librz_parse.so => /usr/lib64/librz_parse.so (0x00007f94b4425000)
librz_search.so => /usr/lib64/librz_search.so (0x00007f94b421f000)
librz_cons.so => /usr/lib64/librz_cons.so (0x00007f94b4000000)
librz_config.so => /usr/lib64/librz_config.so (0x00007f94b3dfa000)
librz_bin.so => /usr/lib64/librz_bin.so (0x00007f94b3afd000)
librz_debug.so => /usr/lib64/librz_debug.so (0x00007f94b38d2000)
librz_analysis.so => /usr/lib64/librz_analysis.so (0x00007f94b2fbd000)
librz_reg.so => /usr/lib64/librz_reg.so (0x00007f94b2db4000)
librz_bp.so => /usr/lib64/librz_bp.so (0x00007f94b2baf000)
librz_io.so => /usr/lib64/librz_io.so (0x00007f94b2944000)
librz_fs.so => /usr/lib64/librz_fs.so (0x00007f94b270e000)
librz_asm.so => /usr/lib64/librz_asm.so (0x00007f94b1c69000)
librz_syscall.so => /usr/lib64/librz_syscall.so (0x00007f94b1a63000)
librz_hash.so => /usr/lib64/librz_hash.so (0x00007f94b185a000)
librz_magic.so => /usr/lib64/librz_magic.so (0x00007f94b164d000)
librz_flag.so => /usr/lib64/librz_flag.so (0x00007f94b1446000)
librz_egg.so => /usr/lib64/librz_egg.so (0x00007f94b1236000)
librz_crypto.so => /usr/lib64/librz_crypto.so (0x00007f94b1016000)
librz_util.so => /usr/lib64/librz_util.so (0x00007f94b0d35000)
libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f94b0b15000)
libc.so.6 => /lib64/libc.so.6 (0x00007f94b074d000)
librz_lang.so => /usr/lib64/librz_lang.so (0x00007f94b0546000)
librz_socket.so => /usr/lib64/librz_socket.so (0x00007f94b0339000)
libm.so.6 => /lib64/libm.so.6 (0x00007f94affaf000)
libdl.so.2 => /lib64/libdl.so.2 (0x00007f94afdab000)
/lib64/ld-linux-x86-64.so.2 (0x00007f94b4c79000)
libssl.so.1.0.0 => /usr/lib64/libssl.so.1.0.0 (0x00007f94afb3c000)
libcrypto.so.1.0.0 => /usr/lib64/libcrypto.so.1.0.0 (0x00007f94af702000)
libutil.so.1 => /lib64/libutil.so.1 (0x00007f94af4ff000)
libz.so.1 => /lib64/libz.so.1 (0x00007f94af2e8000)
```

If you compare the outputs of `rz-bin -l` and `ldd`, you will notice that rz-bin lists fewer libraries than `ldd`. The reason is that rz-bin does not follow and does not show dependencies of libraries. Only direct binary dependencies are shown.
