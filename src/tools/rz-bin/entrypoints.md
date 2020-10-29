## Code Entrypoints

The `-e` option passed to rz-bin will show entrypoints for given binary. Two examples:
```
$ rz-bin -e /bin/ls
[Entrypoints]
vaddr=0x00005310 paddr=0x00005310 baddr=0x00000000 laddr=0x00000000 haddr=0x00000018 type=program

1 entrypoints

$ rz-bin -er /bin/ls
fs symbols
f entry0 1 @ 0x00005310
f entry0_haddr 1 @ 0x00000018
s entry0
```
