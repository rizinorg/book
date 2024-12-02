rz-bin allows you to do some modifications/extraction operations on a file. You do so with **-O** option
and one of the predefined strings to specify the required operation. All the possible strings are:

```
$ rz-bin -O h
Usage: iO [expression]:
 d/s/1024          dump symbols
 d/S/.text         dump section
 c                 show Codesign data
 C                 show LDID entitlements
```

Let's run some examples.

Change the entry point to 0x8041111 of *somefile.bin*:

```
$rz-bin  e/0x8041111  somefile.bin
```

Set permissions `rwx` (instead of the default `rw`) on the `.bss` segment of *somefile.bin*:

```
$rz-bin p/.bss/rwx   somefile.bin
```

Dump a given section (`.text`) of the file (*somefile.bin*) as a hexadecimal stream:

```
$rz-bin d/S/.text somefile.bin
```
