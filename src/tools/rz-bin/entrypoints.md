## Code Entrypoints

The `-e` option passed to rz-bin will show entrypoints for given binary.

```
$ rz-bin -e /usr/bin/ls
[Entries]
vaddr      paddr      hvaddr     haddr      type    
----------------------------------------------------
0x00005880 0x00005880 0x00000018 0x00000018 program
```
