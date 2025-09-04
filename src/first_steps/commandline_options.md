## Shell Command-line Options

The `rizin` command line tool supports various options from the shell command line.

Here is the usage help message:

```
$ rizin -h
Usage: rizin [-ACdfLMnNqStuvwzX] [-P patch] [-p prj] [-a arch] [-b bits] [-i file]
             [-s addr] [-B baddr] [-m maddr] [-c cmd] [-e k=v] file|pid|-|--|=
 --         Run rizin without opening any file
 =          Same as 'rizin malloc://512
 -          Read file from stdin
 -=         Perform R=! command to run all commands remotely
 -0         Print \x00 after init and every command
 -1         Redirect stderr to stdout
 -2         Close stderr file descriptor (silent warning messages)
 -a arch    Set asm.arch
 -A         Run 'aaa' command to analyze all referenced code
 -b bits    Set asm.bits
 -B baddr   Set base address for PIE binaries
 -c 'cmd..' Execute rizin command
 -C         File is host:port (alias for -cR+http://%%s/cmd/)
 -d         Debug the executable 'file' or running process 'pid
 -D backend Enable debug mode (e cfg.debug=true)
 -e k=v     Evaluate config var
 -f         Block size = file size
 -F binplug Force to use that rbin plugin
 -h, -hh    Show help message, -hh for long
 -H [var]   Display variable
 -i file    Run script file
 -I file    Run script file before the file is opened
 -k OS/kern Set asm.os (linux, macos, w32, netbsd, ...)
 -l lib     Load plugin file
 -L         List supported IO plugins
 -m addr    Map file at given address (loadaddr)
 -M         Do not demangle symbol names
 -n, -nn    Do not load RzBin info (-nn only load bin structures)
 -N         Do not load user settings and scripts
 -NN        Do not load any script or plugin
 -q         Quiet mode (no prompt) and quit after -i and -c
 -qq        Quiet mode (no prompt) and force quit
 -p p.rzdb  Load project file
 -r rz-run  Specify rz-run profile to load (same as -e dbg.profile=X)
 -R rule    Specify custom rz-run directive
 -s addr    Initial seek
 -T         Do not compute file hashes
 -u         Set bin.filter=false to get raw sym/sec/cls names
 -v, -V     Show rizin version (-V show lib versions)
 -w         Open file in write mode
 -x         Open without exec-flag (asm.emu will not work), See io.exec
 -X         Same as -e bin.usextr=false (useful for dyldcache)
 -z, -zz    Do not load strings or load them even in raw
```

### Common usage patterns

- To open a file in write mode without parsing the file format headers, use the following command:

```bash
$ rizin -nw file
```

- To quickly enter an Rizin shell without opening any file, you can use the following command:

```bash
$ rizin 
```

- To quickly enter an Rizin shell and allocate 512 bytes of writable buffer (equivalent of `malloc://512`), you can use the following command:

```bash
$ rizin = 
```

- To specify which architecture and bits you want to open the file with, you can use the following command:

```bash
$ rizin -a ppc -b 32 ls.fat
```

- To run a script **before** before the file is opened, you can use the `-i` option followed by the path to your script. Here's an example:

```bash
$ rizin -i /path/to/patch.rz target.bin
```

- To execute a command and quit without entering the interactive mode in Rizin, you can use the `-qc` option followed by the command you want to execute. Here's an example:

```bash
$ rizin -qc 'iij' hi.bin > imports.json
```

- To set a environment variable in Rizin, you can use the `-e` option followed by the environment variable assignment. Here's an example:

```bash
$ rizin -e "pdb.server=https://msdl.microsoft.com/download/symbols" blah.bin
```

- To debug a program using Rizin, you can use the following option:

```bash
$ rizin -d /bin/ls
```

- To use an existing project file in Rizin, you can specify the project file when opening Rizin. Here's an example:

```bash
$ rizin -p test.rzdb
```
