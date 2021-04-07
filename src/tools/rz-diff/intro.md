# Rz-diff

rz-diff is a tool designed to compare binary files, similar to how regular `diff` compares text files.
```
$ rz-diff -h
Usage: rz-diff [-abBcCdjrspOxuUvV] [-A[A]] [-g sym] [-m graph_mode][-t %] [file] [file]
  -a [arch]  specify architecture plugin to use (x86, arm, ..)
  -A [-A]    run aaa or aaaa after loading each binary (see -C)
  -b [bits]  specify register size for arch (16 (thumb), 32, 64, ..)
  -B         output in binary diff (GDIFF)
  -c         count of changes
  -C         graphdiff code (columns: off-A, match-ratio, off-B) (see -A)
  -d         use delta diffing
  -D         show disasm instead of hexpairs
  -e [k=v]   set eval config var value for all RzCore instances
  -g [sym|off1,off2]   graph diff of given symbol, or between two offsets
  -G [cmd]   run an rizin command on every RzCore instance created
  -i         diff imports of target files (see -u, -U and -z)
  -j         output in json format
  -n         print bare addresses only (diff.bare=1)
  -m [aditsjJ]  choose the graph output mode
  -O         code diffing with opcode bytes only
  -p         use physical addressing (io.va=0)
  -q         quiet mode (disable colors, reduce output)
  -r         output in rizin commands
  -s         compute edit distance (no substitution, Eugene W. Myers' O(ND) diff algorithm)
  -ss        compute Levenshtein edit distance (substitution is allowed, O(N^2))
  -S [name]  sort code diff (name, namelen, addr, size, type, dist) (only for -C or -g)
  -t [0-100] set threshold for code diff (default is 70%)
  -x         show two column hexdump diffing
  -X         show two column hexII diffing
  -u         unified output (---+++)
  -U         unified output using system 'diff'
  -v         show version information
  -V         be verbose (current only for -s)
  -z         diff on extracted strings
  -Z         diff code comparing zignatures

Graph Output formats: (-m [mode])
  <blank/a>  Ascii art
  s          rizin commands
  d          Graphviz dot
  g          Graph Modelling Language (gml)
  j          json
  J          json with disarm
  k          SDB key-value
  t          Tiny ascii art
  i          Interactive ascii art
```

