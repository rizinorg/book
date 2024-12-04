# IO plugins

All access to files, network, debugger and all input/output in general is wrapped by an IO abstraction layer that
allows Rizin to treat all data as if it were just a file.

IO plugins are the ones used to wrap the open, read, write and 'system' on virtual file systems. You can make Rizin
understand anything as a plain file. E.g. a socket connection, a remote rizin session, a file, a process, a device,
a gdb session.

So, when rizin reads a block of bytes, it is the task of an IO plugin to get these bytes from any place and put them
into internal buffer. An IO plugin is chosen by a file's URI to be opened. Some examples:

* Debugging URIs
```
$ rizin dbg:///bin/ls<br />
$ rizin pid://1927
```

* Remote sessions
```
$ rizin rap://:1234<br />
$ rizin rap://<host>:1234//bin/ls
```

* Virtual buffers
```
$ rizin malloc://512<br />
shortcut for
$ rizin =
```
You can get a list of the rizin IO plugins by typing `rizin -L`:
```
$ rizin -L
rw_  ar       Open ar/lib files (LGPL3) ar://,lib:// xarkes
rw_  bfdbg    Attach to brainfuck Debugger instance (LGPL3) bfdbg://
rwd  bochs    Attach to a BOCHS debugger instance (LGPL3) bochs://
r_d  debug    Attach to native debugger instance (LGPL3) dbg://,pidof://,waitfor:// v0.2.0 pancake
rw_  default  Open local files (LGPL3) file://,nocache://
rw_  dmp      Debug a Windows DMP file (LGPL3) dmp://
rw_  fd       Local process filedescriptor IO (MIT) fd://
rwd  gdb      Attach to gdbserver instance (LGPL3) gdb://
rw_  gzip     Read/write gzipped files (LGPL3) gzip://
rw_  http     Make http get requests (LGPL3) http://
rw_  ihex     Open intel HEX file (LGPL) ihex://
r__  mach     mach debug io (unsupported in this platform) (LGPL)
rw_  malloc   Memory allocation plugin (LGPL3) malloc://,hex://
rw_  null     Null plugin (LGPL3) null://
rw_  procpid  Open /proc/[pid]/mem io (LGPL3) procpid://
rwd  ptrace   Ptrace and /proc/pid/mem (if available) io plugin (LGPL3) ptrace://,attach://
rwd  qnx      Attach to QNX pdebug instance (LGPL3) qnx://
rw_  rap      Remote binary protocol plugin (MIT) rap://,raps://
rw_  rzpipe   rzpipe io plugin (MIT) rzpipe://
rw_  rzweb    rzweb io client plugin (LGPL3) rzweb://
rw_  self     Read memory from self (LGPL3) self://
rw_  shm      Shared memory resources plugin (MIT) shm://
rw_  sparse   Sparse buffer allocation plugin (LGPL3) sparse://
rw_  srec     Motorola S-record file format (LGPL-3) srec://
rw_  tcp      Load files via TCP (listen or connect) (LGPL3) tcp://
rw_  vfile    Virtual Files provided by RzBin Files (LGPL) vfile://
rwd  winedbg  Wine-dbg io and debug.io plugin (MIT) winedbg://
rwd  winkd    Attach to a KD debugger (LGPL3) winkd://
rw_  zip      Open zip files (BSD) zip://,apk://,ipa://,jar://,zipall://,apkall://,ipaall://,jarall://
```
