# Remote Access Capabilities

Rizin can be run locally, or it can be started as a server process which is controlled by a local
rizin process. This is possible because everything uses rizin's IO subsystem which abstracts access to system(), cmd() and all basic IO operations so to work over a network.

Help for commands useful for remote access to rizin:

```
[0x00405a04]> =?
Usage: =[?]   # Connect with other instances of rizin
| = [[<fd>] <cmd>]        # List all open connections / Exec <cmd> at remote <fd>
| =< [<fd> <cmd>]         # Send output of local <cmd> to remote <fd>
| =![<cmd>]               # Run <cmd> via rz_io_system
| =+ <[proto://]host:port> # Connect to remote host:port
| =- [<fd>]               # remove all hosts or host 'fd'
| == <fd>                 # Open remote session with host 'fd', 'q' to quit
| =!= <fd>=0              # Enable remote cmd mode, sending commands to remote <fd> server
| !=!                     # Disable remote cmd mode
| =r <[host:]port> [<cmd>] # Start the rap server (o rap://9999) / Execute <cmd> on rap server
| =g[?]                   # Start the gdbserver
| =h[?]                   # Start the http webserver
| =H[?]                   # Start the http webserver (and launch the web browser)
| =t <[host:]port> [<cmd>] # Start the tcp server
| =&r <port>              # Start rap server in background (same as '&_=h')
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
$ rizin -
```

Add hosts

```
[0x004048c5]> =+ rap://<host1>:1234//bin/ls
Connected to: <host1> at port 1234
waiting... ok

[0x004048c5]> =
0 - rap://<host1>:1234//bin/ls
```

You can open remote files in debug mode (or using any IO plugin) specifying URI when adding hosts:

```
[0x004048c5]> =+ =+ rap://<host2>:1234/dbg:///bin/ls
Connected to: <host2> at port 1234
waiting... ok
0 - rap://<host1>:1234//bin/ls
1 - rap://<host2>:1234/dbg:///bin/ls
```

To execute commands on host1:

```
[0x004048c5]> =0 px
[0x004048c5]> = s 0x666
```

To open a session with host2:

```
[0x004048c5]> ==1
fd:6> pi 1
...
fd:6> q
```

To remove hosts (and close connections):

```
[0x004048c5]> =-
```

You can also redirect rizin output to a TCP or UDP server (such as `nc -l`). First, Add the server with '=+ tcp://' or '=+ udp://', then you can redirect the output of a command to be sent to the server:

```
[0x004048c5]> =+ tcp://<host>:<port>/
Connected to: <host> at port <port>
5 - tcp://<host>:<port>/
[0x004048c5]> =<5 cmd...
```

The `=<` command will send the output from the execution of `cmd` to the remote connection number N (or the last one used if no id specified).

