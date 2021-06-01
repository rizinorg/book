# Rz-diff

`rz-diff` is a tool designed to compare binary files, similar to how regular `diff` compares text files.

```
$ rz-diff -h
Usage: rz-diff [options] <file0> <file1>
  -a [arch] specify architecture plugin to use (x86, arm, ..)
  -b [bits] specify register size for arch (16 (thumb), 32, 64, ..)
  -d [algo] compute edit distance based on the choosen algorithm:
              myers | Eugene W. Myers' O(ND) algorithm (no substitution)
              leven | Levenshtein O(N^2) algorithm (with substitution)
  -H        hexadecimal visual mode
  -h        this help message
  -j        json output
  -q        quite output
  -v        show version information
  -A        compare virtual and physical addresses
  -C        disable colors
  -T        show timestamp information
  -S [WxH]  sets the width and height of the terminal for visual mode
  -0 [cmd]  input for file0 when option -t 'commands' is given.
            the same value will be set for file1, if -1 is not set.
  -1 [cmd]  input for file1 when option -t 'commands' is given.
  -t [type] compute the difference between two files based on its type:
              bytes      | compares raw bytes in the files (only for small files)
              lines      | compares text files
              functions  | compares functions found in the files
              classes    | compares classes found in the files
              command    | compares command output returned when executed in both files
                         | requires -0 <cmd> and -1 <cmd> is optional
              entries    | compares entries found in the files
              fields     | compares fields found in the files
              graphs     | compares 2 functions and outputs in graphviz/dot format
                         | requires -0 <fcn name|offset> and -1 <fcn name|offset> is optional
              imports    | compares imports found in the files
              libraries  | compares libraries found in the files
              sections   | compares sections found in the files
              strings    | compares strings found in the files
              symbols    | compares symbols found in the files
  palette colors can be changed by adding the following lines
          inside the $HOME/.rizinrc file
  ec diff.unknown blue   | offset color
  ec diff.match   green  | match color
  ec diff.unmatch red    | mismatch color
```

