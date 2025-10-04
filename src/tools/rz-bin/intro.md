# Rz-bin — Show Properties of a Binary

Rz-bin is a powerful tool to handle binaries, to get information on imports, sections, headers and other data.
It can present this information in several formats accepted by other tools, including Rizin itself.
rz-bin understands many file formats: Java CLASS, ELF, PE, Mach-O or any format supported by plugins,
and it is able to obtain symbol import/exports, library dependencies, strings of data sections, xrefs,
entrypoint address, sections, architecture type.

```bash
$ rz-bin -h
Usage: rz-bin [-AcdeEghHiIjlLMqrRsSUvVxzZ] [-@ at] [-a arch] [-b bits] [-B addr]
              [-C F:C:D] [-f str] [-m addr] [-n str] [-N m:M] [-P pdb]
              [-o str] [-O str] [-k query] [-D lang symname] file
 -@ addr      Show section, symbol, or import at the given address
 -A           List sub-binaries and their arch-bits pairs
 -a arch      Set arch (x86, arm, .. or <arch>_<bits>)
 -b bits      Set bits (32, 64 ...)
 -B addr      Override base address (pie bins)
 -c           List classes
 -cc          List classes in header format
 -C fmt:C:D   Create [elf,mach0,pe] with Code and Data hexpairs (see -a)
 -d           Show debug/dwarf information
 -dd          Load debug/dwarf information from debuginfod server
 -D lang name Demangle symbol name (-D all for bin.demangle=true)
 -e           Entrypoint
 -ee          Constructor/destructor entrypoints
 -E           Globally exportable symbols
 -f mach      Select sub-binary for the machine [mach].
 -F binfmt    Force to use that bin plugin (ignore header check)
 -g           Same as -SMZIHVResizcld -SS -SSS -ee (show all info)
 -G addr      Load address . offset to header
 -h           Show this help
 -H           Header fields
 -i           Import (symbols imported from libraries)
 -I           Binary info
 -j           Output in JSON
 -k sdb-query Run sdb query. for example: '*'
 -K algo      Calculate checksums (md5, sha1, ..)
 -l           Linked libraries
 -L [plugin]  List supported bin plugins or plugin details
 -m addr      Show source line at addr
 -M           Main (show address of main symbol)
 -n str       Show section, symbol or import named str
 -N min:max   Force min:max number of chars per string (see -z and -zz)
 -o str       Output file/folder for write operations (out by default)
 -O str       Write/extract operations (-O help)
 -p           Show physical addresses
 -P           Show debug/pdb information
 -PP          Download pdb file for binary
 -q           Quiet mode, just show fewer data
 -qq          Show less info (no offset/size for -z for ex.)
 -Q           Show load address used by dlopen (non-aslr libs)
 -r           Show output in rizin format
 -R           Show relocations
 -s           Symbols
 -S           Sections
 -SS          Segments
 -SSS         Sections mapping to segments
 -T           Display file signature
 -u           Unfiltered (no rename duplicated symbols/sections)
 -U           Resources
 -v           Show version information
 -V           Show binary version information
 -w           Display try/catch blocks
 -x           Extract bins contained in file
 -Y           Calculate all the possibles base address candidates of a firmware bin
 -z           Show strings (from data section)
 -zz          Show strings (from raw strings from bin)
 -zzz         Dump raw strings to stdout (for huge files)
 -Z           Guess size of binary program
Environment:
 RZ_BIN_CODESIGN_VERBOSE:                               # make code signatures verbose
 RZ_BIN_DEBUGINFOD_URLS:  e bin.dbginfo.debuginfod_urls # use alternative debuginfod server
 RZ_BIN_DEMANGLE=0:       e bin.demangle                # do not demangle symbols
 RZ_BIN_LANG:             e bin.lang                    # assume lang for demangling
 RZ_BIN_MAXSTRBUF:        e search.str.max_length       # specify maximum buffer size
 RZ_BIN_PDBSERVER:        e pdb.server                  # use alternative PDB server
 RZ_BIN_PREFIX:           e bin.prefix                  # prefix symbols/sections/relocs with a specific string
 RZ_BIN_STRFILTER:        e bin.str.filter              # rizin -qc 'e bin.str.filter=??' -
 RZ_BIN_STRPURGE:         e bin.str.purge               # try to purge false positives
 RZ_BIN_SYMSTORE:         e pdb.symstore                # path to downstream PDB symbol store
 RZ_CONFIG:                                             # config file
 RZ_NOPLUGINS:                                          # do not load plugins
```
