# Rz-Diff (binary and text diffing utility)

## Distance

For bulk processing, you may want to have a higher-level overview of differences.

The `-d` option serves to calculate the distance between the two binaries using either Myers algorithm or
the Levenshtein algorithm.

```
 -d --------> myers (myers algorithm)
       |----> leven (levenshtein algorithm)
```

### Myers algorithm:

In the [Myers](https://epubs.siam.org/doi/10.1137/S0097539794264810) algorithm for edit distance, the cost of
an insertion or deletion is 1 and the cost of a replacement is 2. 
The theorem leads directly to an O(k) algorithm for incrementally computing a new solution from an old one,
as contrasts the O(k2) time required to compute a solution from scratch.
Thus, the algorithm performs well when the two strings are similar. 

```shell
$  rz-diff -d myers /usr/bin/true /usr/bin/false
similarity: 0.997
distance: 242
```

### Levenshtein distance:

[Levenshtein](https://en.wikipedia.org/wiki/Levenshtein_distance) distance is a string metric for measuring
the difference between two sequences. Informally, the Levenshtein distance between two words is the minimum number
of single-character edits (insertions, deletions or substitutions) required to change one word into the other.  

```shell
$ rz-diff -d leven /bin/true /bin/false
similarity: 0.997
distance: 130
```

## Hexadecimal Diffing:

`-H` The hexadecimal displays the hexdump of file0 vs file1 in a side-by-side window. Navigational keys allows easily
parsing through the hexdump of the files individually.

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
$ rz-bin -s /usr/bin/ls | head
[Symbols]
nth paddr      vaddr      bind   type   size lib name                            
---------------------------------------------------------------------------------
104 ---------- 0x00025280 GLOBAL OBJ    8        __progname
105 ---------- 0x00025290 GLOBAL OBJ    4        optind
107 ---------- 0x000252a8 WEAK   OBJ    8        program_invocation_name
┌─────────────────────────── [a8c8]( true )─────────────────────────────────────────────────────────────────────────── [a8c8]( false )─────────────────────────────────────────────────────────────────────────────────────────────────────┐
│                                                 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F                                             0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F                                                │
│                           0x0000000000000000 | 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00  | .ELF............ | 0x0000000000000000 | 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00  | .ELF............ |                          │
│                           0x0000000000000010 | 03 00 3e 00 01 00 00 00 80 26 00 00 00 00 00 00  | ..>......&...... | 0x0000000000000010 | 03 00 3e 00 01 00 00 00 80 26 00 00 00 00 00 00  | ..>......&...... |                          │
│                           0x0000000000000020 | 40 00 00 00 00 00 00 00 88 a1 00 00 00 00 00 00  | @............... | 0x0000000000000020 | 40 00 00 00 00 00 00 00 88 a1 00 00 00 00 00 00  | @............... |                          │
│                           0x0000000000000030 | 00 00 00 00 40 00 38 00 0d 00 40 00 1d 00 1c 00  | ....@.8...@..... | 0x0000000000000030 | 00 00 00 00 40 00 38 00 0d 00 40 00 1d 00 1c 00  | ....@.8...@..... |                          │
│                           0x0000000000000040 | 06 00 00 00 04 00 00 00 40 00 00 00 00 00 00 00  | ........@....... | 0x0000000000000040 | 06 00 00 00 04 00 00 00 40 00 00 00 00 00 00 00  | ........@....... |                          │
│                           0x0000000000000050 | 40 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00  | @.......@....... | 0x0000000000000050 | 40 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00  | @.......@....... |                          │
│                           0x0000000000000060 | d8 02 00 00 00 00 00 00 d8 02 00 00 00 00 00 00  | ................ | 0x0000000000000060 | d8 02 00 00 00 00 00 00 d8 02 00 00 00 00 00 00  | ................ |                          │
│                           0x0000000000000070 | 08 00 00 00 00 00 00 00 03 00 00 00 04 00 00 00  | ................ | 0x0000000000000070 | 08 00 00 00 00 00 00 00 03 00 00 00 04 00 00 00  | ................ |                          │
│                           0x0000000000000080 | 18 03 00 00 00 00 00 00 18 03 00 00 00 00 00 00  | ................ | 0x0000000000000080 | 18 03 00 00 00 00 00 00 18 03 00 00 00 00 00 00  | ................ |                          │
│                           0x0000000000000090 | 18 03 00 00 00 00 00 00 1c 00 00 00 00 00 00 00  | ................ | 0x0000000000000090 | 18 03 00 00 00 00 00 00 1c 00 00 00 00 00 00 00  | ................ |                          │

...

│                           0x0000000000000360 | 07 00 00 00 00 00 00 00 01 00 01 c0 04 00 00 00  | ................ | 0x0000000000000360 | 07 00 00 00 00 00 00 00 01 00 01 c0 04 00 00 00  | ................ |                          │
│                           0x0000000000000370 | 19 00 00 00 00 00 00 00 02 00 01 c0 04 00 00 00  | ................ | 0x0000000000000370 | 19 00 00 00 00 00 00 00 02 00 01 c0 04 00 00 00  | ................ |                          │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
 1 2 -/+0x390 | Z A file0 +/-1 | C D file1 +/-1 | G B end/begin | N M next/prev | ᐯ ᐱ  +/-16 | ᐸ ᐳ  +/-1 | : seek
```

`-S` mode allows you to adjust the window size of the hexadecimal view to your preference.
Minimmum: `W = 120 H = 20`

Example : `rz-diff -HS 120x20 /bin/true /bin/false`

### File Type Based Diffing

`t` option computes the difference between two files based on its type.

```
 -t [type] Compute the difference between two files based on its type:
              bytes      | compare raw bytes in the files (only for small files)
              lines      | compare text files
              functions  | compare functions found in the files
              classes    | compare classes found in the files
              command    | compare command output returned when executed in both files
                         | require -0 <cmd> and -1 <cmd> is optional
              entries    | compare entries found in the files
              fields     | compare fields found in the files
              graphs     | compare 2 functions and outputs in graphviz/dot format
                         | require -0 <fcn name|offset> and -1 <fcn name|offset> is optional
              imports    | compare imports found in the files
              libraries  | compare libraries found in the files
              sections   | compare sections found in the files
              strings    | compare strings found in the files
              symbols    | compare symbols found in the files
```

### Diffing ASCII-text files:

```
$ rz-diff -t lines genuine cracked
--- genuine
+++ cracked
@@ -1,1 +1,1 @@
-hello1234567890
+1234567890hello
```

### Diffing functions in binaries:

It this mode, it will give you three columns for all functions: "First file offset", "Percentage of matching" and "Second file offset".

```
rz-diff  -t functions /usr/bin/true /usr/bin/false
.-----------------------------------------------------------------------------------------------------------------------------------.
| name0                          | size0 | addr0      | type     | similarity | addr1      | size1 | name1                          |
)-----------------------------------------------------------------------------------------------------------------------------------(
| fcn.000022c0                   | 10    | 0x000022c0 | COMPLETE | 1.000000   | 0x000022c0 | 10    | fcn.000022c0                   |
| sym.imp.free                   | 10    | 0x000022d0 | COMPLETE | 1.000000   | 0x000022d0 | 10    | sym.imp.free                   |
| sym.imp.abort                  | 10    | 0x000022e0 | COMPLETE | 1.000000   | 0x000022e0 | 10    | sym.imp.abort                  |
| sym.imp.__errno_location       | 10    | 0x000022f0 | COMPLETE | 1.000000   | 0x000022f0 | 10    | sym.imp.__errno_location       |
| sym.imp.strncmp                | 10    | 0x00002300 | COMPLETE | 1.000000   | 0x00002300 | 10    | sym.imp.strncmp                |
| sym.imp._exit                  | 10    | 0x00002310 | COMPLETE | 1.000000   | 0x00002310 | 10    | sym.imp._exit                  |
| sym.imp.__fpending             | 10    | 0x00002320 | COMPLETE | 1.000000   | 0x00002320 | 10    | sym.imp.__fpending             |
| sym.imp.reallocarray           | 10    | 0x00002330 | COMPLETE | 1.000000   | 0x00002330 | 10    | sym.imp.reallocarray           |
| sym.imp.textdomain             | 10    | 0x00002340 | COMPLETE | 1.000000   | 0x00002340 | 10    | sym.imp.textdomain             |
| sym.imp.fclose                 | 10    | 0x00002350 | COMPLETE | 1.000000   | 0x00002350 | 10    | sym.imp.fclose                 |
| sym.imp.bindtextdomain         | 10    | 0x00002360 | COMPLETE | 1.000000   | 0x00002360 | 10    | sym.imp.bindtextdomain         |
| sym.imp.dcgettext              | 10    | 0x00002370 | COMPLETE | 1.000000   | 0x00002370 | 10    | sym.imp.dcgettext              |
| sym.imp.__ctype_get_mb_cur_max | 10    | 0x00002380 | COMPLETE | 1.000000   | 0x00002380 | 10    | sym.imp.__ctype_get_mb_cur_max |
| sym.imp.strlen                 | 10    | 0x00002390 | COMPLETE | 1.000000   | 0x00002390 | 10    | sym.imp.strlen                 |
| sym.imp.__stack_chk_fail       | 10    | 0x000023a0 | COMPLETE | 1.000000   | 0x000023a0 | 10    | sym.imp.__stack_chk_fail       |
| sym.imp.strrchr                | 10    | 0x000023b0 | COMPLETE | 1.000000   | 0x000023b0 | 10    | sym.imp.strrchr                |
| sym.imp.lseek                  | 10    | 0x000023c0 | COMPLETE | 1.000000   | 0x000023c0 | 10    | sym.imp.lseek                  |
| sym.imp.memset                 | 10    | 0x000023d0 | COMPLETE | 1.000000   | 0x000023d0 | 10    | sym.imp.memset                 |
| sym.imp.mbrtoc32               | 10    | 0x000023e0 | COMPLETE | 1.000000   | 0x000023e0 | 10    | sym.imp.mbrtoc32               |
| sym.imp.memcmp                 | 10    | 0x000023f0 | COMPLETE | 1.000000   | 0x000023f0 | 10    | sym.imp.memcmp                 |
| sym.imp.fputs_unlocked         | 10    | 0x00002400 | COMPLETE | 1.000000   | 0x00002400 | 10    | sym.imp.fputs_unlocked         |
| sym.imp.calloc                 | 10    | 0x00002410 | COMPLETE | 1.000000   | 0x00002410 | 10    | sym.imp.calloc                 |
| sym.imp.strcmp                 | 10    | 0x00002420 | COMPLETE | 1.000000   | 0x00002420 | 10    | sym.imp.strcmp                 |
| sym.imp.fputc_unlocked         | 10    | 0x00002430 | COMPLETE | 1.000000   | 0x00002430 | 10    | sym.imp.fputc_unlocked         |
| sym.imp.memcpy                 | 10    | 0x00002440 | COMPLETE | 1.000000   | 0x00002440 | 10    | sym.imp.memcpy                 |
| sym.imp.fileno                 | 10    | 0x00002450 | COMPLETE | 1.000000   | 0x00002450 | 10    | sym.imp.fileno                 |
| sym.imp.malloc                 | 10    | 0x00002460 | COMPLETE | 1.000000   | 0x00002460 | 10    | sym.imp.malloc                 |
| sym.imp.nl_langinfo            | 10    | 0x00002480 | COMPLETE | 1.000000   | 0x00002480 | 10    | sym.imp.nl_langinfo            |
| sym.imp.__freading             | 10    | 0x00002490 | COMPLETE | 1.000000   | 0x00002490 | 10    | sym.imp.__freading             |
| sym.imp.realloc                | 10    | 0x000024a0 | COMPLETE | 1.000000   | 0x000024a0 | 10    | sym.imp.realloc                |
| sym.imp.setlocale              | 10    | 0x000024b0 | COMPLETE | 1.000000   | 0x000024b0 | 10    | sym.imp.setlocale              |
| sym.imp.__printf_chk           | 10    | 0x000024c0 | COMPLETE | 1.000000   | 0x000024c0 | 10    | sym.imp.__printf_chk           |
| sym.imp.error                  | 10    | 0x000024d0 | COMPLETE | 1.000000   | 0x000024d0 | 10    | sym.imp.error                  |
| sym.imp.exit                   | 10    | 0x00002500 | COMPLETE | 1.000000   | 0x00002500 | 10    | sym.imp.exit                   |
| sym.imp.fwrite                 | 10    | 0x00002510 | COMPLETE | 1.000000   | 0x00002510 | 10    | sym.imp.fwrite                 |
| sym.imp.__fprintf_chk          | 10    | 0x00002520 | COMPLETE | 1.000000   | 0x00002520 | 10    | sym.imp.__fprintf_chk          |
| sym.imp.mbsinit                | 10    | 0x00002530 | COMPLETE | 1.000000   | 0x00002530 | 10    | sym.imp.mbsinit                |
| sym.imp.iswprint               | 10    | 0x00002540 | COMPLETE | 1.000000   | 0x00002540 | 10    | sym.imp.iswprint               |
| sym.imp.__ctype_b_loc          | 10    | 0x00002550 | COMPLETE | 1.000000   | 0x00002550 | 10    | sym.imp.__ctype_b_loc          |
| fcn.000026b0                   | 34    | 0x000026b0 | COMPLETE | 1.000000   | 0x000026b0 | 34    | fcn.000026b0                   |
| fcn.00002770                   | 833   | 0x00002770 | PARTIAL  | 0.979592   | 0x00002770 | 833   | fcn.00002770                   |
| fcn.00002ba0                   | 166   | 0x00002ba0 | PARTIAL  | 0.993976   | 0x00002ba0 | 166   | fcn.00002ba0                   |
| fcn.00002c50                   | 79    | 0x00002c50 | PARTIAL  | 0.987342   | 0x00002c50 | 79    | fcn.00002c50                   |
| fcn.00002cb0                   | 220   | 0x00002cb0 | PARTIAL  | 0.972727   | 0x00002cb0 | 220   | fcn.00002cb0                   |
| fcn.00002da0                   | 5447  | 0x00002da0 | PARTIAL  | 0.998348   | 0x00002da0 | 5447  | fcn.00002da0                   |
| fcn.00004370                   | 486   | 0x00004370 | COMPLETE | 1.000000   | 0x00004370 | 486   | fcn.00004370                   |
| fcn.00004c20                   | 120   | 0x00004c20 | COMPLETE | 1.000000   | 0x00004c20 | 120   | fcn.00004c20                   |
| fcn.00005070                   | 1092  | 0x00005070 | PARTIAL  | 0.991758   | 0x00005070 | 1092  | fcn.00005070                   |
| fcn.000055c0                   | 210   | 0x000055c0 | COMPLETE | 1.000000   | 0x000055c0 | 210   | fcn.000055c0                   |
| fcn.000057f0                   | 28    | 0x000057f0 | COMPLETE | 1.000000   | 0x000057f0 | 28    | fcn.000057f0                   |
| fcn.00005a80                   | 241   | 0x00005a80 | COMPLETE | 1.000000   | 0x00005a80 | 241   | fcn.00005a80                   |
| fcn.00005c20                   | 54    | 0x00005c20 | COMPLETE | 1.000000   | 0x00005c20 | 54    | fcn.00005c20                   |
| fcn.00005d20                   | 56    | 0x00005d20 | PARTIAL  | 0.964286   | 0x00005d20 | 56    | fcn.00005d20                   |
| fcn.00005d60                   | 93    | 0x00005d60 | COMPLETE | 1.000000   | 0x00005d60 | 93    | fcn.00005d60                   |
| fcn.00005dc0                   | 88    | 0x00005dc0 | COMPLETE | 1.000000   | 0x00005dc0 | 88    | fcn.00005dc0                   |
| fcn.00005e20                   | 124   | 0x00005e20 | COMPLETE | 1.000000   | 0x00005e20 | 124   | fcn.00005e20                   |
| fcn.00005eb0                   | 63    | 0x00005eb0 | COMPLETE | 1.000000   | 0x00005eb0 | 63    | fcn.00005eb0                   |
| fcn.00005ef0                   | 109   | 0x00005ef0 | COMPLETE | 1.000000   | 0x00005ef0 | 109   | fcn.00005ef0                   |
| fcn.00005f70                   | 54    | 0x00005f70 | PARTIAL  | 0.962963   | 0x00005f70 | 54    | fcn.00005f70                   |
| fcn.00005fb0                   | 180   | 0x00005fb0 | PARTIAL  | 0.994444   | 0x00005fb0 | 180   | fcn.00005fb0                   |
| fcn.00006070                   | 116   | 0x00006070 | COMPLETE | 1.000000   | 0x00006070 | 116   | fcn.00006070                   |
| fcn.000060f0                   | 128   | 0x000060f0 | COMPLETE | 1.000000   | 0x000060f0 | 128   | fcn.000060f0                   |
| fcn.000061b0                   | 18    | 0x000061b0 | COMPLETE | 1.000000   | 0x000061b0 | 18    | fcn.000061b0                   |
`-----------------------------------------------------------------------------------------------------------------------------------'
```

### Diffing classes in binaries:

```
rz-diff -t classes /usr/bin/true /usr/bin/false
--- /usr/bin/true
+++ /usr/bin/false
```

### Commands


### Diffing entries in binaries

```
rz-diff -t entries /usr/bin/true /usr/bin/false
--- /usr/bin/true
+++ /usr/bin/false
```

### Diffing fields in binaries:

```
rz-diff -t fields /usr/bin/true /usr/bin/false
--- /usr/bin/true
+++ /usr/bin/false
```

### Diffing sections in binaries:

```
rz-diff -t sections /usr/bin/true /usr/bin/false
--- /usr/bin/true
+++ /usr/bin/false
```

### Diffing strings in binaries:

```
rz-diff -t strings /usr/bin/true /usr/bin/false
--- /usr/bin/true
+++ /usr/bin/false
@@ -10,7 +10,7 @@
       --help        display this help and exit

 Written by %s, %s, %s,
%s, %s, %s, %s,
and %s.

 Copyright %s %d Free Software Foundation, Inc.
-Exit with a status code indicating success.
+Exit with a status code indicating failure.
 Written by %s, %s, %s,
%s, %s, %s, and %s.

 Written by %s, %s, %s,
%s, %s, and %s.

 https://www.gnu.org/software/coreutils/
@@ -59,6 +59,6 @@
 ASCII
 POSIX
 UTF-8
+false
 shell
 %s


-true

```

### Diffing symbols in binaries:

```
rz-diff -t symbols /usr/bin/true /usr/bin/false
--- /usr/bin/true
+++ /usr/bin/false
```
