# Signatures

Rizin supports the [HexRays FLIRT](https://hex-rays.com/products/ida/tech/flirt/) signature format which allows you to create,
parse or apply the signatures on the fly. Rizin is also capable of applying
the signatures automatically, when the [sigdb](https://github.com/rizinorg/sigdb) is defined by the user via the
variable `flirt.sigdb.path`. All the applied signatures are stored in the `flirt`
flag space.

The HexRays FLIRT format is made by two formats:

- `.pat` text string format
- `.sig` compressed format which includes the architecture type used to generate the signature

Signature commands are available under the `zf` command namespace:
```
[0x00000000]> zf?
Usage: zf<cds>   # Manage FLIRT signatures
| zfc <filename> # Create a FLIRT file (.pac or .sig)
| zfd <filename> # Open a FLIRT file (.pac or .sig) and dumps its contents
| zfs <filename> # Open a FLIRT file (.pac or .sig) and tries to apply the signatures to the loaded binary
```

To apply a signature file manually or a folder of signatures, you need to call `zfs`
```
$ rizin /path/to/binary/with/stripped.elf
[0x000051c0]> aaa
[0x000051c0]> zfs signature.sig # relative or absolutes paths are accepted
Found 206 FLIRT signatures via signature.sig
[0x000051c0]>
```

To create signature you need to analyze the binary first, then you can create it by calling `zfc`.
You can modify the behaviour of the signature creation via the following options:

- `flirt.node.optimize` - FLIRT optimization option when creating a signature file (none: 0, normal: 1, smallest: 2), `default: 2`
- `flirt.sig.deflate` - enables/disables FLIRT zlib compression when creating a signature file (available only for .sig files), `default: true`
- `flirt.sig.file` - FLIRT file list (comma separated) for sig format (msdos, win, os2, netware, unix, other, all, none), `default: all`
- `flirt.sig.library` - FLIRT library name for sig format, `default: Built with rizin x.y.z`
- `flirt.sig.os` - FLIRT operating system list (comma separated) for sig format (aixar, aout, ar, bin, coff, dos:com, dos:com:old, dos:exe, dos:exe:old, dosdrv, elf, intelhex, le, loader, lx, moshex, ne, nlm, omf, omflib, pe, pilot, srec, w32run, zip, all, none), `default: all`
- `flirt.sig.version` - FLIRT version for sig format, `default: 10`

Example of signature creation with `.sig` format:
```
$ rizin /path/to/binary/with/symbols.elf
[0x000051c0]> aa
[0x000051c0]> # setting library name
[0x000051c0]> e flirt.sig.library="My Awesome Signature"
[0x000051c0]> # creating signature
[0x000051c0]> zfc signature.sig # relative or absolutes paths are accepted
707 FLIRT signatures were written in 'signature.sig'
[0x000051c0]>
```

Example of signature creation with `.pat` format:
```
$ rizin /path/to/binary/with/symbols.elf
[0x000051c0]> aa
[0x000051c0]> # setting internal node optimization to none
[0x000051c0]> e flirt.node.optimize=0
[0x000051c0]> # creating signature
[0x000051c0]> zfc signature.pat # relative or absolutes paths are accepted
707 FLIRT signatures were written in 'signature.pat'
[0x000051c0]>
```

You can print the contents of a FLIRT signature file via `zfd`
```
[0x000051c0]> zfd signature.sig
SIG format
Signature:    Built with rizin 0.4.0-git, 8 modules
Version:      1
Architecture: 0 (x86)
F30F:
 1EFA:
  31ED4989D15E4889E24883E4F050544C............48..........:
   0. 09 CDDC 002E 0000:entry0 (REF )
  41574C............41564989D641554989F541544189FC5548....:
   0. 45 7595 0065 0000:__libc_csu_init (REF )
  4883EC0848:
   83C408C3......................................:
    0. 00 0000 000D 0000:_fini (REF )
   ............4885C074..FFD04883C408C3..........:
    0. 00 0000 001B 0000:_init (REF )
  80............75..5548..............4889E574..48........:
   0. 21 300E 0041 0000:__do_global_dtors_aux (REF )
  C3......................................................:
   0. 00 0000 0005 0000:__libc_csu_fini (REF )
  E9......................................................:
   0. 00 0000 0009 0000:entry.init0 (REF )
 6F866E0100004889F84189C80F1187F8130000F30F6F8E7E0100000F118F:
  0. A7 A662 00C8 0000:Curl_persistconninfo (REF )
[0x000051c0]>
```

It is also possible to use `rz-sign` to create (automatically) or to convert or to dump FLIRT signatures:
```
$ rz-sign -h
Usage: rz-sign [options] [file]
 -h                          this help message
 -a [-a]                     add extra 'a' to analysis command (available only with -o option)
 -e [k=v]                    set an evaluable config variable (available only with -o option)
 -c [output.pat] [input.sig] parses a FLIRT signature and converts it to its other format
 -o [output.sig] [input.bin] performs an analysis on the binary and generates the FLIRT signature.
 -d [flirt.sig]              parses a FLIRT signature and dump its content
 -q                          quiet mode
 -v                          show version information
Examples:
  rz-sign -d signature.sig
  rz-sign -c new_signature.pat old_signature.sig
  rz-sign -o libc.sig libc.so.6

$ rz-sign -e "flirt.sig.library=My Awesome Signature" -o signature.sig /path/to/binary/with/symbols.elf
```

If instead you want to manually select the FLIRT signature file from `sigdb`
you have to use `aaF` commands:
```
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
[0x00409c70]> aaF?
Usage: aaF  [l] # applies signatures from sigdb automatically
| aaF <filter>  applies signatures from sigdb automatically
| aaFl          lists all the signatures available in sigdb
[0x00409c70]> aaFl~gcc
elf/x86/64/ubuntu-libgcc-10.sig
elf/x86/64/ubuntu-libgcc-11.sig
elf/x86/64/ubuntu-libgcc-7.sig
elf/x86/64/ubuntu-libgcc-8.sig
[0x00409c70]> aaF ubuntu-libgcc
Applying elf/x86/64/ubuntu-libgcc-10.sig signature file
Applying elf/x86/64/ubuntu-libgcc-11.sig signature file
Applying elf/x86/64/ubuntu-libgcc-7.sig signature file
Applying elf/x86/64/ubuntu-libgcc-8.sig signature file
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
