# Debugging with gdbserver

rizin allows remote debugging over the gdb remote protocol. So you can run a
gdbserver and connect to it with rizin for remote debugging. The syntax for
connecting is:

```
$ rizin -d gdb://<host>:<port>
```

Note that the following command does the same, rizin will use the debug plugin specified by the uri if found.

```
$ rizin -D gdb gdb://<host>:<port>
```

The debug plugin can be changed at runtime using the dL or Ld commands.

Or if the gdbserver is running in extended mode, you can attach to a process on
the host with:

```
$ rizin -d gdb://<host>:<port>/<pid>
```

It is also possible to start debugging after analyzing a file using the `doof` command
which rebases the current session's data after opening gdb

```
[0x00404870]> doof gdb://<host>:<port>/<pid>
```

After connecting, you can use the standard rizin debug commands as normal.

rizin does not yet load symbols from gdbserver, so it needs the binary to
be locally present to load symbols from it. In case symbols are not loaded even
if the binary is present, you can try specifying the path with `e dbg.exe.path`:

```
$ rizin -e dbg.exe.path=<path> -d gdb://<host>:<port>
```

If symbols are loaded at an incorrect base address, you can try specifying
the base address too with `e bin.baddr`:

```
$ rizin -e bin.baddr=<baddr> -e dbg.exe.path=<path> -d gdb://<host>:<port>
```

Usually the gdbserver reports the maximum packet size it supports. Otherwise,
rizin resorts to sensible defaults. But you can specify the maximum packet
size with the environment variable `R2_GDB_PKTSZ`. You can also check and set
the max packet size during a session with the IO system, `R!`.

```
$ export R2_GDB_PKTSZ=512
$ rizin -d gdb://<host>:<port>
= attach <pid> <tid>
Assuming filepath <path/to/exe>
[0x7ff659d9fcc0]> R!pktsz
packet size: 512 bytes
[0x7ff659d9fcc0]> R!pktsz 64
[0x7ff659d9fcc0]> R!pktsz
packet size: 64 bytes
```

The gdb IO system provides useful commands which might not fit into any
standard rizin commands. You can get a list of these commands with
`R!?`. (Remember, `R!` accesses the underlying IO plugin's `system()`).

```
[0x7ff659d9fcc0]> R!?
Usage: R!cmd args
 R!pid             - show targeted pid
 R!pkt s           - send packet 's'
 R!monitor cmd     - hex-encode monitor command and pass to target interpreter
 R!rd              - show reverse debugging availability
 R!dsb             - step backwards
 R!dcb             - continue backwards
 R!detach [pid]    - detach from remote/detach specific pid
 R!inv.reg         - invalidate reg cache
 R!pktsz           - get max packet size used
 R!pktsz bytes     - set max. packet size as 'bytes' bytes
 R!exec_file [pid] - get file which was executed for current/specified pid
```

Note that `R!dsb` and `R!dcb` are only available in special gdbserver implementations such
as [Mozilla's rr](https://github.com/mozilla/rr), the default gdbserver doesn't include
remote reverse debugging support.
Use `R!rd` to print the currently available reverse debugging capabilities.

If you are interested in debugging rizin's interaction with gdbserver you can use
`R!monitor set remote-debug 1` to turn on logging of gdb's remote protocol packets in
gdbserver's console and `R!monitor set debug 1` to show general debug messages from
gdbserver in it's console.

rizin also provides its own gdbserver implementation:

```
$ rizin =
[0x00000000]> Rg?
|Usage:  =[g] [...] # gdb server
| gdbserver:
| Rg port file [args]   listen on 'port' debugging 'file' using gdbserver
| Rg! port file [args]  same as above, but debug protocol messages (like gdbserver --remote-debug)
```

So you can start it as:

```
$ rizin =
[0x00000000]> Rg 8000 /bin/rizin -
```

And then connect to it like you would to any gdbserver. For example, with rizin:

```
$ rizin -d gdb://localhost:8000
```

