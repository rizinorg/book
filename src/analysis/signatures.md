# Signatures

Rizin supports the [HexRays FLIRT](https://hex-rays.com/products/ida/tech/flirt/) signature format, enabling users to effortlessly create, parse, or apply signatures on the go. Additionally, Rizin can automatically apply these signatures when the user defines the [sigdb](https://github.com/rizinorg/sigdb) via the `flirt.sigdb.path` variable. All applied signatures are then stored within the `flirt` flag space.

The HexRays FLIRT format has two formats:

- `.pat` A human-readable text string format
- `.sig` A compressed format, which includes a name, version and the architecture type utilized for generating the signature.

Signature commands are available under the `F` command namespace:
```bash
[0x00000000]> F?
Usage: F<cdsfal>   # FLIRT signature management
| Fc <filename> # Create a FLIRT file (.pat or .sig)
| Fd <filename> # Open a FLIRT file (.pat or .sig) and dumps its contents
| Fs <filename> # Open a FLIRT file (.pat or .sig) and tries to apply the signatures to the loaded binary
| Ff            # Outputs the flirt function signature info
| Fa [<filter>] # Apply signatures from sigdb
| Fl[t]         # Lists all available signatures in sigdb
```

## Signature matching

Before applying a signature, **you must first analyze the binary** (see [code analysis](code_analysis.md) chapter).

In Rizin, there are two methods to apply signatures to a file: using sigdb or manually specifying the signature file.

If `e flirt.sigdb.path` is configured before executing the analysis (`aaa` command), then `sigdb` files are automatically applied to the binary.
However, if a manual approach is preferred, it is possible to select the FLIRT signature file from `sigdb` using the `Fa` command. To list all available signature files in sigdb, use the `Fl` command.

An example of selecting sigdb signatures via `Fa` could be:
```bash
[0x00409c70]> pdf
            ; CALL XREF from main @ 0x4017c1
/ fcn.00409c70 (int64_t arg1, int64_t arg2, int64_t arg3, int64_t arg4, int64_t arg5, int64_t arg6, int64_t arg7, int64_t arg8, int64_t arg9, int64_t arg10, int64_t arg11, int64_t arg_e0h);
|           ; var int64_t var_4h_2 @ rsp+0x4
|           ; var int64_t var_8h_2 @ rsp+0x8
|           ; var int64_t var_10h_2 @ rsp+0x10
|           ; var int64_t var_18h_2 @ rsp+0x18
|           ; var int64_t var_20h_2 @ rsp+0x20
|           ; var int64_t var_30h_2 @ rsp+0x30
|           ; var int64_t var_38h_2 @ rsp+0x38
|           ; var int64_t var_40h_2 @ rsp+0x40
[0x00409c70]> e flirt.sigdb.path=/path/to/sigdb
[0x00409c70]> Fa?
Usage: Fa [<filter>]   # Apply signatures from sigdb
[0x00409c70]> Fl?
Usage: Fl[t]   # Lists all available signatures in sigdb (table mode)
| Flt    # Lists all available signatures in sigdb (table mode)
[0x00409c70]> Flt:name/str/gcc
bin arch bits name                 modules details                                          
--------------------------------------------------------------------------------------------
elf x86  64   ubuntu-libgcc-10.sig 487     Ubuntu GCC support library Version 10 (rizin.re)
elf x86  64   ubuntu-libgcc-11.sig 298     Ubuntu GCC support library Version 11 (rizin.re)
elf x86  64   ubuntu-libgcc-12.sig 307     Ubuntu GCC support library Version 12 (rizin.re)
elf x86  64   ubuntu-libgcc-7.sig  247     Ubuntu GCC support library Version 7 (rizin.re)
elf x86  64   ubuntu-libgcc-8.sig  520     Ubuntu GCC support library Version 8 (rizin.re)
elf x86  64   ubuntu-libgcc-9.sig  535     Ubuntu GCC support library Version 9 (rizin.re)
[0x00409c70]> Fa gcc
Applying elf/x86/64/ubuntu-libgcc-10.sig signature file
Applying elf/x86/64/ubuntu-libgcc-11.sig signature file
Applying elf/x86/64/ubuntu-libgcc-12.sig signature file
Applying elf/x86/64/ubuntu-libgcc-7.sig signature file
Applying elf/x86/64/ubuntu-libgcc-8.sig signature file
Applying elf/x86/64/ubuntu-libgcc-9.sig signature file
[0x00409c70]> pdf
            ; CALL XREF from main @ 0x4017c1
            ;-- fcn.00409c70:
/ flirt.printf (int64_t arg1, int64_t arg2, int64_t arg3, int64_t arg4, int64_t arg5, int64_t arg6, int64_t arg7, int64_t arg8, int64_t arg9, int64_t arg10, int64_t arg11, int64_t arg_e0h);
|           ; var int64_t var_4h @ rsp+0xdc
|           ; var int64_t var_8h @ rsp+0xe0
|           ; var int64_t var_10h @ rsp+0xe8
|           ; var int64_t var_18h @ rsp+0xf0
| 
```

To manually apply a signature file, you need to use the `Fs` command.
```bash
$ rizin /path/to/binary/with/stripped.elf
[0x00009690]> aaa
[0x00009690]> Fs signature.sig # relative or absolutes paths are accepted
Found 536 FLIRT signatures via signature.sig
[0x00009690]>
```

## Signature creation

Before creating a signature, **you must first analyze the binary** (see [code analysis](code_analysis.md) chapter).

You can generate the signature by invoking the `Fc <filename>` command. You can customize the behavior of signature creation using the following options:

- Signature creation options:
    - `flirt.ignore.unknown`: When enabled, during FLIRT creation, it will disregard any function starting with `fcn.`, `default: true`.
    - `flirt.node.optimize`: FLIRT optimization option when creating a signature file (none: 0, normal: 1, smallest: 2), `default: 2`.
- `.sig` (compressed format) specific options: 
    - `flirt.sig.deflate`: Enables or disables the FLIRT zlib compression when creating a signature file (available only for .sig files), `default: true`.
    - `flirt.sig.file`: FLIRT file list (comma separated) for `.sig` format (msdos, win, os2, netware, unix, other, all, none), `default: all`.
    - `flirt.sig.library`: FLIRT library name for `.sig` format, `default: Built with rizin x.y.z`.
    - `flirt.sig.os`: FLIRT operating system list (comma separated) for `.sig` format (aixar, aout, ar, bin, coff, dos:com, dos:com:old, dos:exe, dos:exe:old, dosdrv, elf, intelhex, le, loader, lx, moshex, ne, nlm, omf, omflib, pe, pilot, srec, w32run, zip, all, none), `default: all`.
    - `flirt.sig.version`: FLIRT version for `.sig` format `default: 10`.
- [sigdb](https://github.com/rizinorg/sigdb) specific options:
    - `analysis.apply.signature`: Enables or disables the automatic application of signatures to the loaded binary, `default: true`.
    - `flirt.sigdb.load.extra`: Load signatures from the extra path, `default: true` and its path can be found via `rizin -H RZ_EXTRA_SIGDB`.
    - `flirt.sigdb.load.home`: Load signatures from the home path, `default: true`.
    - `flirt.sigdb.load.system`: Load signatures from the system path, `default: true` and its path can be found via `rizin -H RZ_SIGDB`.
    - `flirt.sigdb.path`: Additional user defined rizin sigdb location to load on the filesystem `default: (empty)`.

Example of signature creation in `.sig` (compressed) format:
```bash
$ rizin /path/to/binary/with/symbols.elf
[0x00009690]> aa
[0x00009690]> # setting library name
[0x00009690]> e flirt.sig.library="My Awesome Library Name"
[0x00009690]> # creating signature
[0x00009690]> Fc signature.sig # relative or absolutes paths are accepted
704 FLIRT signatures were written in 'signature.sig'
[0x00009690]>
```

Example of signature creation in `.pat` (human readable) format:
```bash
$ rizin /path/to/binary/with/symbols.elf
[0x00009690]> aa
[0x00009690]> # disable internal node optimization
[0x00009690]> e flirt.node.optimize=0
[0x00009690]> # creating signature
[0x00009690]> Fc signature.pat # relative or absolutes paths are accepted
704 FLIRT signatures were written in 'signature.pat'
[0x00009690]>
```

You can view the contents of a FLIRT signature file via `Fd <filename>`.
```bash
[0x00009690]> Fd signature.sig
SIG format
Signature:    Built with rizin x.y.z, 704 modules
Version:      10
Architecture: 0 (x86)
09CA74..C30F1F00E9:
 0. 00 0000 000D 0000:sock_state_cb
0F:
 B6:
  07:
   3C..74..84C074..4C8D86FF000000EB..0F1F40003C..74..4939F074:
    0. 00 0000 0103 0000:Curl_auth_digest_get_pair
   84C0:
    0F84........0FB60E84C90F84........4885D20F84........53:
     0. 01 A5A9 0105 0000:Curl_strncasecompare
    75..E9........0F1F400041......448D50E0448D429F4189C345:
     0. 07 6545 009B 0000:Curl_strcasecompare
  4F080FB7570883....66C1C20880....74..83....41B8010000006681..:
   0. 00 0000 008A 0000:Curl_ipv6_scope.part.0
  87910B00008B9748010000F7D0C0E80781..........0F9EC108C874..31:
   0. 11 F2A8 00AF 0000:http_should_fail
 B707:
  66C1C008C3:
   0. 00 0000 0008 0000:Curl_read16_be
  C3:
   0. 00 0000 0004 0000:Curl_read16_le
```

You can also utilize `rz-sign` to automatically create, convert, or dump FLIRT signatures:
```bash
$ rz-sign -h
Usage: rz-sign [-aqv] [-e k=v] (-c pat sig | -o sig bin | -d sig)
 -h                      Show this help
 -a, -aa                 Add extra 'a' to analysis command (available only with -o option)
 -e k=v                  Set an evaluable config variable (available only with -o option)
 -c output.pat input.sig Parse a FLIRT signature and convert it to its other format
 -o output.sig input.bin Perform an analysis on the binary and generate the FLIRT signature
 -d flirt.sig            Parse a FLIRT signature and dump its content
 -q                      Quiet mode
 -v                      Show version information
Examples:
  rz-sign -d signature.sig
  rz-sign -c new_signature.pat old_signature.sig
  rz-sign -o libc.sig libc.so.6

$ rz-sign -e "flirt.sig.library=My Awesome Library Name" -o signature.sig /path/to/binary/with/symbols.elf
```

For library files that use the `.a` or `.la` formats, it is highly recommended to unpack them using `ar` and utilize the `.o` files as sources for the signature files.

## Signature database creation

It is possible to create personal `sigdb` using the [sigdb tools](https://github.com/rizinorg/sigdb-tools) and the scripts in [sigdb source](https://github.com/rizinorg/sigdb-source/tree/main/.scripts) available in the RizinOrg repository.

- [sigdb tools](https://github.com/rizinorg/sigdb-tools)
    - `generate-pat-from-obj.py` Generates unoptimized `.pat` signatures from `.o`, `.lo`, or `.obj` object files. The tool creates a new file with the same name as the original object file but with the extension `.pat`.
    - `generate-obj-from-lib.py` Unpacks Windows `.lib` files into `.o` (object files). This tool accepts a folder containing all the `.lib` files to unpack as input and generates multiple directories (named after the respective libraries) along with their contents (beware that this tool requires linux utilities).
    - `launchpad-deb-scraper.py` This script downloads `deb` packages from launchpad leveraging high-performance asynchronous i/o. It is possible to filter the `deb` packages by architecture.

- [sigdb source](https://github.com/rizinorg/sigdb-source/tree/main/.scripts)
    - `generate-pat.py` is a tool that generates a `.pat` file from one or multiple `.pat` files. It offers various options to automatically resolve conflicts. Additionally, it is possible to run it in **test mode** (also known as a dry run) to preview its actions without making any actual changes.
    - `generate-sig.py` is a tool that is only used to generate `.sig` files for the release version of a signature database. this compress and automatically names the libraries following the [sigdb source format](https://github.com/rizinorg/sigdb-source/blob/main/README.md#mandatory-folder-structure). 

Example of sigdb generation using the tools mentioned above:

```bash
# create output folders
$ mkdir mysigdb mysigdb-extract mysigdb-source

# check if there are lib files
$ find libs/ -type f -name '*.lib'
libs/libcrypto.lib
libs/libssl.lib
# unpack all lib files
$ python ~/sigdb-tools/generate-obj-from-lib.py -v --input libs/
input dir: libs/
found 2 file to ingest

[1|2] parsing libssl.lib
[2|2] parsing libcrypto.lib

done.

# create a sigdb source folder from the extracted files.
$ python ~/sigdb-tools/generate-pat-from-obj.py -i libs/ --output mysigdb-extract
input dir: libs/
found 580 file to ingest

done.
$ find mysigdb-extract/ -type f -name '*.pat' | head
mysigdb-extract/coff/x86/64/libcrypto.lib.ext/bf_ofb64.c.obj.pat
mysigdb-extract/coff/x86/64/libcrypto.lib.ext/aes_cfb.c.obj.pat
mysigdb-extract/coff/x86/64/libcrypto.lib.ext/t_req.c.obj.pat
mysigdb-extract/coff/x86/64/libcrypto.lib.ext/md5-mingw64-x86_64.S.obj.pat
mysigdb-extract/coff/x86/64/libcrypto.lib.ext/tasn_utl.c.obj.pat
mysigdb-extract/coff/x86/64/libcrypto.lib.ext/asn1_par.c.obj.pat
...

# create sigdb source folder structure.
$ mkdir -p "mysigdb-source/coff/x86/64/openssl_3_0_0"

# create sigdb library description files.
# see https://github.com/rizinorg/sigdb-source/blob/main/README.md#mandatory-folder-structure
$ echo "OpenSSL 3.0.0 for Windows" > "mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.description"
$ sha1sum openssl.3.0.0.zip > "mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.src.sha1"

# create sigdb source .pat from extracted files in mysigdb-extract
$ python ~/sigdb-source/.scripts/generate-pat.py --auto --recursive -d "mysigdb-extract/" -o "mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.pat"
output: mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.pat
input:  577 pat files
parsed a total of 6163 signatures and dropped 2082 (~34%) signatures.                   
There were 452 duplicates out of 4081 signatures (~11%).
mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.pat has been created

# sigdb source directory is now complete.
$ find mysigdb-source/ -type f
mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.description
mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.pat
mysigdb-source/coff/x86/64/openssl_3_0_0/openssl_3_0_0.src.sha1

# create release compressed files in mysigdb/ using mysigdb-source/.
$ python generate-sig.py -s mysigdb-source/ -o mysigdb
source: mysigdb-source
output: mysigdb
Generating OpenSSL 3.0.0 for Windows signature (as openssl_3_0_0.sig) from openssl_3_0_0.pat

# Use the generated sigdb with rizin.
$ rizin -e "flirt.sigdb.path=mysigdb/" -qc 'Fl'
bin  arch bits name              modules details                              
------------------------------------------------------------------------------
coff x86  64   openssl_3_0_0.sig 3357    OpenSSL 3.0.0 for Windows (rizin.re)
```
