## Shell Command-line Options

The `rizin` command line tool supports various options from the shell command line.

Here is the usage help message:

```
$ rizin -h
Usage: rizin [-ACdfLMnNqStuvwzX] [-P patch] [-p prj] [-a arch] [-b bits] [-i file]
             [-s addr] [-B baddr] [-m maddr] [-c cmd] [-e k=v] file|pid|-|--|=
 --           run rizin without opening any file
 =            same as 'rizin malloc://512
 -            read file from stdin
 -=           perform R=! command to run all commands remotely
 -0           print \x00 after init and every command
 -2           close stderr file descriptor (silent warning messages)
 -a [arch]    set asm.arch
 -A           run 'aaa' command to analyze all referenced code
 -b [bits]    set asm.bits
 -B [baddr]   set base address for PIE binaries
 -c 'cmd..'   execute rizin command
 -C           file is host:port (alias for -cR+http://%%s/cmd/)
 -d           debug the executable 'file' or running process 'pid
 -D [backend] enable debug mode (e cfg.debug=true)
 -e k=v       evaluate config var
 -f           block size = file size
 -F [binplug] force to use that rbin plugin
 -h, -hh      show help message, -hh for long
 -H ([var])   display variable
 -i [file]    run script file
 -I [file]    run script file before the file is opened
 -k [OS/kern] set asm.os (linux, macos, w32, netbsd, ...)
 -l [lib]     load plugin file
 -L           list supported IO plugins
 -m [addr]    map file at given address (loadaddr)
 -M           do not demangle symbol names
 -n, -nn      do not load RzBin info (-nn only load bin structures)
 -N           do not load user settings and scripts
 -NN          do not load any script or plugin
 -q           quiet mode (no prompt) and quit after -i
 -qq          quit after running all -c and -i
 -Q           quiet mode (no prompt) and quit faster (quickLeak=true)
 -p [p.rzdb]  load project file
 -r [rz-run]  specify rz-run profile to load (same as -e dbg.profile=X)
 -R [rule]    specify custom rz-run directive
 -s [addr]    initial seek
 -T           do not compute file hashes
 -u           set bin.filter=false to get raw sym/sec/cls names
 -v, -V       show rizin version (-V show lib versions)
 -w           open file in write mode
 -x           open without exec-flag (asm.emu will not work), See io.exec
 -X           same as -e bin.usextr=false (useful for dyldcache)
 -z, -zz      do not load strings or load them even in raw
```

### Common usage patterns

- To open a file in write mode without parsing the file format headers, use the following command:

```
$ rizin -nw file
```

- To quickly enter an Rizin shell without opening any file, you can use the following command:

```
$ rizin 
```

- To quickly enter an Rizin shell and allocate 512 bytes of writable buffer (equivalent of `malloc://512`), you can use the following command:

```
$ rizin = 
```

- To specify which architecture and bits you want to open the file with, you can use the following command:

```
$ rizin -a ppc -b 32 ls.fat
```

- To run a script **before** before the file is opened, you can use the `-i` option followed by the path to your script. Here's an example:

```
$ rizin -i /path/to/patch.rz target.bin
```

- To execute a command and quit without entering the interactive mode in Rizin, you can use the `-qc` option followed by the command you want to execute. Here's an example:

```
$ rizin -qc 'iij' hi.bin > imports.json
```

- To set a environment variable in Rizin, you can use the `-e` option followed by the environment variable assignment. Here's an example:

```
$ rizin -e "pdb.server=https://msdl.microsoft.com/download/symbols" blah.bin
```

To debug a program using Rizin, you can use the following option:

```
$ rizin -d /bin/ls
```

To use an existing project file in Rizin, you can specify the project file when opening Rizin. Here's an example:

```
$ rizin -p test.rzdb
```
