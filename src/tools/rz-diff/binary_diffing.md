# Rz-Diff (binary and text diffing utility)

## Distance

For bulk processing, you may want to have a higher-level overview of differences.

The `-d` option serves to calculate the distance between the two binaries using either myers algorithm or the levenshtein algorithm.

```
 -d --------> myers (myers algorithm)
       |----> leven (levenshtein algorithm)
```

### Myers algorithm:

In the [Myers](https://epubs.siam.org/doi/10.1137/S0097539794264810) algorithm for edit distance, the cost of an insertion or deletion is 1 and the cost of a replacement is 2. 
The theorem leads directly to an O(k) algorithm for incrementally computing a new solution from an old one, as contrasts the O(k2 ) time required to compute a solution from scratch.
Thus the algorithm performs well when the two strings are similar. 

`rz-diff -d myers /bin/true /bin/false`

output:
```
similarity: 0.974
distance: 2046
```

### Levenshtein distance:

[Levenshtein](https://en.wikipedia.org/wiki/Levenshtein_distance) distance is a string metric for measuring the difference between two sequences. Informally, the Levenshtein distance between two words is the minimum number of single-character edits (insertions, deletions or substitutions) required to change one word into the other.  

`rz-diff -d leven /bin/true /bin/false`

output:
```
similarity: 0.974
distance: 2046
```

## Hexadecimal Diffing:

`-H` The hexadecimal displays the hexdump of file0 vs file1 in a side-by-side window. Navigational keys allows easily parsing through the hexdump of the files individually.

 - `1` and `2` : to move to the next or previous page.
 - `Z` and `A` : allows parsing forward and backward through file0, byte by byte. 
 - `C` and `D` : allows parsing forward and backward through file1, byte by byte.
 - `G` and `B` : seeks the end and beginning of the files.
 - `N` and `M` : takes you to the Next and the Previous differing byte in the files respectively.
 - `/\` and `\/` : parsing both binaries simultaneously, 16 bytes a time.
 - `<` and `>` : parsing both binaries simultaneously, by 1 byte.
 - `: <seek address in hex/decimal>` : seeks the address provided and bring the window to start dump from the seeked address.
 - `?` : shows the help screen in the visual mode which can be exited with 'q'/esc keys.

The bytes that differ are: `rz-diff -H /bin/true /bin/false`

```
.---------- [   0 | 9958]( true )-------------------------------------------------------------------- [   0 | 9958]( false )---------------------------------------------------------.
|                      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F                                             0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F                     |
|0x0000000000000000 | 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00  | .ELF............ | 0x0000000000000000 | 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00  | .ELF............ |
|0x0000000000000010 | 03 00 3e 00 01 00 00 00 10 26 00 00 00 00 00 00  | ..>......&...... | 0x0000000000000010 | 03 00 3e 00 01 00 00 00 20 26 00 00 00 00 00 00  | ..>..... &...... |
|0x0000000000000020 | 40 00 00 00 00 00 00 00 d8 91 00 00 00 00 00 00  | @............... | 0x0000000000000020 | 40 00 00 00 00 00 00 00 d8 91 00 00 00 00 00 00  | @............... |
|0x0000000000000030 | 00 00 00 00 40 00 38 00 0d 00 40 00 1e 00 1d 00  | ....@.8...@..... | 0x0000000000000030 | 00 00 00 00 40 00 38 00 0d 00 40 00 1e 00 1d 00  | ....@.8...@..... |
|0x0000000000000040 | 06 00 00 00 04 00 00 00 40 00 00 00 00 00 00 00  | ........@....... | 0x0000000000000040 | 06 00 00 00 04 00 00 00 40 00 00 00 00 00 00 00  | ........@....... |
|0x0000000000000050 | 40 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00  | @.......@....... | 0x0000000000000050 | 40 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00  | @.......@....... |
|0x0000000000000060 | d8 02 00 00 00 00 00 00 d8 02 00 00 00 00 00 00  | ................ | 0x0000000000000060 | d8 02 00 00 00 00 00 00 d8 02 00 00 00 00 00 00  | ................ |
|0x0000000000000070 | 08 00 00 00 00 00 00 00 03 00 00 00 04 00 00 00  | ................ | 0x0000000000000070 | 08 00 00 00 00 00 00 00 03 00 00 00 04 00 00 00  | ................ |
|0x0000000000000080 | 18 03 00 00 00 00 00 00 18 03 00 00 00 00 00 00  | ................ | 0x0000000000000080 | 18 03 00 00 00 00 00 00 18 03 00 00 00 00 00 00  | ................ |
|0x0000000000000090 | 18 03 00 00 00 00 00 00 1c 00 00 00 00 00 00 00  | ................ | 0x0000000000000090 | 18 03 00 00 00 00 00 00 1c 00 00 00 00 00 00 00  | ................ |

...
|0x00000000000002f0 | 30 9c 00 00 00 00 00 00 30 9c 00 00 00 00 00 00  | 0.......0....... | 0x00000000000002f0 | 30 9c 00 00 00 00 00 00 30 9c 00 00 00 00 00 00  | 0.......0....... |
|0x0000000000000300 | d0 03 00 00 00 00 00 00 d0 03 00 00 00 00 00 00  | ................ | 0x0000000000000300 | d0 03 00 00 00 00 00 00 d0 03 00 00 00 00 00 00  | ................ |
`------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
 1 2 -/+0x320 | Z A file0 +/-1 | C D file1 +/-1 | G B end/begin | N M next/prev | \//\ +/-16 | < >  +/-1 | : seek

```

`-S` mode allows you to adjust the window size of the hexadecimal view to your preference.
Minimmum: `W = 120 H = 20`

Example : `rz-diff -HS 120x20 /bin/true /bin/false`

### File Type Based Diffing

`t` option computes the difference between two files based on its type.

```
 -t --------> bytes (raw bytes in the files)
       |----> lines (compares text files)
       |----> functions (compares functions found in the files)
       |----> classes (compares classes found in the files)
       |----> command (compares command output returned when executed)
       |----> entries (compares entries found in the files)
       |----> fields (compares fields found in the files)
       |----> graphs (compares 2 functions and outputs in graphviz/dot      format)
       |----> format (compares text files)
       |----> imports (compares imports found in the files)
       |----> libraries (compares libraries found in the files)
       |----> sections (compares sections found in the files)
       |----> strings (compares sections found in the files)
       |----> symbols (compares symbols found in the files)

```

### Diffing ASCII-text files:

` $ rz-diff -t lines genuine cracked`
```
--- genuine
+++ cracked
@@ -1,1 +1,1 @@
-hello1234567890
+1234567890hello
```

### Diffing functions in binaries:

It this mode, it will give you three columns for all functions: "First file offset", "Percentage of matching" and "Second file offset".

` $ rz-diff -t functions /bin/true /bin/false`

```
         sym.imp.__fprintf_chk   11 0x00000000000024e0 | MATCH   (1.000000) | 0x00000000000024e0    11 sym.imp.__fprintf_chk
               sym.imp.mbsinit   11 0x00000000000024f0 | MATCH   (1.000000) | 0x00000000000024f0    11 sym.imp.mbsinit
              sym.imp.iswprint   11 0x0000000000002500 | MATCH   (1.000000) | 0x0000000000002500    11 sym.imp.iswprint
         sym.imp.__ctype_b_loc   11 0x0000000000002510 | MATCH   (1.000000) | 0x0000000000002510    11 sym.imp.__ctype_b_loc
                  fcn.00002640   34 0x0000000000002640 | UNMATCH (0.058824) | 0x0000000000002650    34 fcn.00002650
                  fcn.00002700  840 0x0000000000002700 | UNMATCH (0.221163) | 0x0000000000002710   840 fcn.00002710
                  fcn.00002b30  176 0x0000000000002b30 | UNMATCH (0.173077) | 0x0000000000002b40   176 fcn.00002b40
                  fcn.00002bf0  208 0x0000000000002bf0 | SIMILAR (0.961538) | 0x0000000000002c00   208 fcn.00002c00
                  fcn.00002cd0 4627 0x0000000000002cd0 | SIMILAR (0.993949) | 0x0000000000002ce0  4627 fcn.00002ce0
```

### Diffing classes in binaries:

`rz-diff -t functions /bin/true /bin/false`

```
--- /bin/true
+++ /bin/false
```

### Commands


### Diffing entries in binaries

`rz-diff -t entries /bin/true /bin/false`

```
--- /bin/true
+++ /bin/false
@@ -1,3 +1,3 @@
-virt: 0x00000000000026f0 phys: 0x00000000000026f0 entry init
-virt: 0x00000000000026b0 phys: 0x00000000000026b0 entry fini
-virt: 0x0000000000002610 phys: 0x0000000000002610 entry program
+virt: 0x0000000000002700 phys: 0x0000000000002700 entry init
+virt: 0x00000000000026c0 phys: 0x00000000000026c0 entry fini
+virt: 0x0000000000002620 phys: 0x0000000000002620 entry program

```

### Diffing fields in binaries:

`rz-diff -t fields /bin/true /bin/false `

```
--- /bin/true
+++ /bin/false
```

### Diffing sections in binaries:

`rz-diff -t sections /bin/true /bin/false`

```

--- /bin/true
+++ /bin/false
```

### Diffing strings in binaries:

`rz-diff -t strings /bin/true /bin/false`

```
--- /bin/true
+++ /bin/false
@@ -11,7 +11,7 @@
 Written by %s, %s, %s,\n%s, %s, %s, %s,\nand %s.\n
 Copyright %s %d Free Software Foundation, Inc.
       --help     display this help and exit\n
-Exit with a status code indicating success.
+Exit with a status code indicating failure.
 Written by %s, %s, %s,\n%s, %s, %s, and %s.\n
 Written by %s, %s, %s,\n%s, %s, and %s.\n
 https://www.gnu.org/software/coreutils/
@@ -51,7 +51,7 @@
 --help
 ASCII
 POSIX
+false
 shell
 %s\n\n
 8.30
-true

```

### Diffing symbols in binaries:

`rz-diff -t symbols /bin/true /bin/false`

```
--- /bin/true
+++ /bin/false
```
