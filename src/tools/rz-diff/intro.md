# Rz-diff

`rz-diff` is a tool designed to compare binary files, similar to how regular `diff` compares text files.

```bash
$ rz-diff -h
Usage: rz-diff [options] <file0> <file1>
 -a [arch] Specify architecture plugin to use (x86, arm, ..)
 -b [bits] Specify register size for arch (16 (thumb), 32, 64, ..)
 -d [algo] Compute edit distance based on the chosen algorithm:
              myers  | Eugene W. Myers' O(ND) algorithm (no substitution)
              leven  | Levenshtein O(N^2) algorithm (with substitution)
              ssdeep | Context triggered piecewise hashing comparison
 -i        Use command line arguments instead of files (only for -d)
 -H        Hexadecimal visual mode
 -h        Show this help
 -j        JSON output
 -q        Quite output
 -V        Show version information
 -v        Be more verbose (stderr output)
 -e [k=v]  Set an evaluable config variable
 -A        Compare virtual and physical addresses
 -B        Run 'aaa' when loading the bin
 -C        Disable colors
 -T        Show timestamp information
 -S [WxH]  Set the width and height of the terminal for visual mode
 -0 [cmd]  Input for file0 when option -t 'commands' is given.
           The same value will be set for file1, if -1 is not set.
 -1 [cmd]  Input for file1 when option -t 'commands' is given.
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
palette colors can be changed by adding the following lines
inside the $HOME/.rizinrc file
ec diff.unknown blue   | offset color
ec diff.match   green  | match color
ec diff.unmatch red    | mismatch color
```

