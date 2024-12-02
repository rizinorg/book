## Yank/Paste

Rizin has an internal clipboard to save and write portions of memory loaded from the current io layer.

This clipboard can be manipulated with the `y` command.

The two basic operations are

* copy (yank)
* paste

The yank operation will read N bytes (specified by the argument) into the clipboard. We can later use the `yy` command
to paste what we read before into a file.

You can yank/paste bytes in visual mode selecting them with the cursor mode (`Vc`) and then using the `y` and `Y` key
bindings which are aliases for `y` and `yy` commands of the command-line interface.

```
[0x00000000]> y?
Usage: y[?]   # Yank/paste bytes from/to memory
| y[j*q] [<len>]    # Yank bytes / Show yank contents
| ye                # Open cfg.editor to edit the clipboard
| yf <len> <file>   # Yank <len> bytes from file
| yfa <file>        # Yank whole file into clipboard
| yp [<len>]        # Print contents of clipboards as raw data
| ys [<len>]        # Print contents of clipboards as string
| yt <len> <offset> # Copy <len> bytes from current seek to <offset>
| ywx <string>      # Yank from hexpairs string
| yx [<len>]        # Print contents of clipboard in hexadecimal
| yy [<len>]        # Paste <len> bytes from yank clipboard
| yz [<len>]        # Copy NULL-terminated string into clipboard
```

Sample session:

```
[0x00000000]> s 0x100    ; seek at 0x100
[0x00000100]> y 100      ; yanks 100 bytes from here
[0x00000200]> s 0x200    ; seek 0x200
[0x00000200]> yy         ; pastes 100 bytes
```

You can perform a yank and paste in a single line by just using the `yt` command (yank-to). The syntax is as follows:

```
[0x4A13B8C0]> x
   offset   0 1  2 3  4 5  6 7  8 9  A B  0123456789AB
0x4A13B8C0, 89e0 e839 0700 0089 c7e8 e2ff ...9........
0x4A13B8CC, ffff 81c3 eea6 0100 8b83 08ff ............
0x4A13B8D8, ffff 5a8d 2484 29c2           ..Z.$.).

[0x4A13B8C0]> yt 8 0x4A13B8CC @ 0x4A13B8C0

[0x4A13B8C0]> x
   offset   0 1  2 3  4 5  6 7  8 9  A B  0123456789AB
0x4A13B8C0, 89e0 e839 0700 0089 c7e8 e2ff ...9........
0x4A13B8CC, 89e0 e839 0700 0089 8b83 08ff ...9........
0x4A13B8D8, ffff 5a8d 2484 29c2           ..Z.$.).
```
