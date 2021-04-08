# Remote Access Capabilities

Rizin can be run locally, or it can be started as a server process which is controlled by a local
rizin process. This is possible because everything uses rizin's IO subsystem which abstracts access to system(), cmd() and all basic IO operations so to work over a network.

Help for commands useful for remote access to rizin:

```
[0x00000000]> R?
Usage: R[?]   # Connect with other instances of rizin
| R [[<fd>] <cmd>]        # List all open connections / Exec <cmd> at remote <fd>
| R< [<fd> <cmd>]         # Send output of local <cmd> to remote <fd>
| R![<cmd>]               # Run <cmd> via rz_io_system
| R+ <[proto://]host:port> # Connect to remote host:port
| R- [<fd>]               # remove all hosts or host 'fd'
| R= <fd>                 # Open remote session with host 'fd', 'q' to quit
| R!= <fd>=0              # Enable remote cmd mode, sending commands to remote <fd> server
| R=!                     # Disable remote cmd mode
| Rr <[host:]port> [<cmd>] # Start the rap server (o rap://9999) / Execute <cmd> on rap server
| Rg[?]                   # Start the gdbserver
| Rh[?]                   # Start the http webserver
| RH[?]                   # Start the http webserver (and launch the web browser)
| Rt <[host:]port> [<cmd>] # Start the tcp server
| R&r <port>              # Start rap server in background (same as '&_=h')
```

You can learn rizin remote capabilities by displaying the list of supported IO plugins: `rizin -L`.

A little example should make this clearer. A typical remote session might look like this:

At the remote host1:

```
$ rizin rap://:1234
```

At the remote host2:

```
$ rizin rap://:1234
```

At localhost:

```
$ rizin =
```

Add hosts

```
[0x004048c5]> R+ rap://<host1>:1234//bin/ls
Connected to: <host1> at port 1234
waiting... ok

[0x004048c5]> R
0 - rap://<host1>:1234//bin/ls
```

You can open remote files in debug mode (or using any IO plugin) specifying URI when adding hosts:

```
[0x004048c5]> R+ R+ rap://<host2>:1234/dbg:///bin/ls
Connected to: <host2> at port 1234
waiting... ok
0 - rap://<host1>:1234//bin/ls
1 - rap://<host2>:1234/dbg:///bin/ls
```

To execute commands on host1:

```
[0x004048c5]> R 0 px
[0x004048c5]> R s 0x666
```

To open a session with host2:

```
[0x004048c5]> R= 1
fd:6> pi 1
...
fd:6> q
```

To remove hosts (and close connections):

```
[0x004048c5]> R-
```

You can also redirect rizin output to a TCP or UDP server (such as `nc -l`). First, Add the server with 'R+ tcp://' or 'R+ udp://', then you can redirect the output of a command to be sent to the server:

```
[0x004048c5]> R+ tcp://<host>:<port>/
Connected to: <host> at port <port>
5 - tcp://<host>:<port>/
[0x004048c5]> R<5 cmd...
```

The `R<` command will send the output from the execution of `cmd` to the remote connection number N (or the last one used if no id specified).

