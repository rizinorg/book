## Command-line Options

The rizin core accepts many flags from the command line.

This is an excerpt from the usage help message:
```
$ rizin -h
Usage: rizin [-ACdfLMnNqStuvwzX] [-P patch] [-p prj] [-a arch] [-b bits] [-i file]
          [-s addr] [-B baddr] [-m maddr] [-c cmd] [-e k=v] file|pid|-|--|=
 --           run rizin without opening any file
 =            same as 'rizin malloc://512'
 -            read file from stdin (use -i and -c to run cmds)
 -=           perform !=! command to run all commands remotely
 -0           print \x00 after init and every command
 -2           close stderr file descriptor (silent warning messages)
 -a [arch]    set asm.arch
 -A           run 'aaa' command to analyze all referenced code
 -b [bits]    set asm.bits
 -B [baddr]   set base address for PIE binaries
 -c 'cmd..'   execute rizin command
 -C           file is host:port (alias for -c+=http://%s/cmd/)
 -d           debug the executable 'file' or running process 'pid'
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
```
```
 -m [addr]    map file at given address (loadaddr)
 -M           do not demangle symbol names
 -n, -nn      do not load RzBin info (-nn only load bin structures)
 -N           do not load user settings and scripts
 -q           quiet mode (no prompt) and quit after -i
 -Q           quiet mode (no prompt) and quit faster (quickLeak=true)
 -p [prj]     use project, list if no arg, load if no file
 -P [file]    apply rapatch file and quit
 -r [rz-run]  specify rz-run profile to load (same as -e dbg.profile=X)
 -R [rrzrule] specify custom rz-run directive
 -s [addr]    initial seek
 -S           start rizin in sandbox mode
 -t           load rz-bin info in thread
 -u           set bin.filter=false to get raw sym/sec/cls names
 -v, -V       show rizin version (-V show lib versions)
 -w           open file in write mode
 -x           open without exec-flag (asm.emu will not work), See io.exec
 -X           same as -e bin.usextr=false (useful for dyldcache)
 -z, -zz      do not load strings or load them even in raw
```

### Common usage patterns

Open a file in write mode without parsing the file format headers.
```
$ rizin -nw file
```
Quickly get into an rizin shell without opening any file.
```
$ rizin 
```
Quickly get into an rizin shell with malloc://512
```
$ rizin = 
```
Specify which sub-binary you want to select when opening a fatbin file:
```
$ rizin -a ppc -b 32 ls.fat
```
Run a script before showing interactive command-line prompt:
```
$ rizin -i patch.rz target.bin
```
Execute a command and quit without entering the interactive mode:
```
$ rizin -qc ij hi.bin > imports.json
```
Set the configuration variable:
```
$ rizin -e scr.color=0 blah.bin
```
Debug a program:
```
$ rizin -d ls
```
Use an existing project file:
```
$ rizin -p test
```
