## Imports

rz-bin is able to find imported objects by an executable, as well as their offsets in its PLT.
This information is useful, for example, to understand what external function is invoked by `call` instruction.
Pass `-i` flag to rz-bin to get a list of imports. An example:

```
$ rz-bin -i /usr/bin/ls
[Imports]
nth vaddr      bind   type   lib name                        
-------------------------------------------------------------
1   0x000036a0 GLOBAL FUNC       __ctype_toupper_loc
2   0x000036b0 GLOBAL FUNC       getenv
3   0x000036c0 GLOBAL FUNC       sigprocmask
4   0x000036d0 GLOBAL FUNC       __snprintf_chk
5   0x000036e0 GLOBAL FUNC       raise
6   ---------- GLOBAL FUNC       __libc_start_main
7   0x000036f0 GLOBAL FUNC       abort
8   0x00003700 GLOBAL FUNC       __errno_location
9   0x00003710 GLOBAL FUNC       strncmp
10  ---------- WEAK   NOTYPE     _ITM_deregisterTMCloneTable
11  0x00003720 GLOBAL FUNC       localtime_r
12  0x00003730 GLOBAL FUNC       _exit
13  0x00003740 GLOBAL FUNC       strcpy
14  0x00003750 GLOBAL FUNC       __fpending
15  0x00003760 GLOBAL FUNC       isatty
16  0x00003770 GLOBAL FUNC       sigaction
17  0x00003780 GLOBAL FUNC       iswcntrl
18  0x00003790 GLOBAL FUNC       reallocarray
19  0x000037a0 GLOBAL FUNC       localeconv
20  0x000037b0 GLOBAL FUNC       faccessat
21  0x000037c0 GLOBAL FUNC       readlink
...
```
