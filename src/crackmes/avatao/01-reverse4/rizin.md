## .rizin

I've decided to solve the reversing challenges using
[rizin](http://rizin.re), a free and open source reverse engineering
framework. I have first learned about rizin back in 2011. during a huge project,
where I had to reverse a massive, 11MB statically linked ELF. I simply needed
something that I could easily patch Linux ELFs with. Granted, back then I've
used rizin alongside IDA, and only for smaller tasks, but I loved the whole concept
at first sight. Since then, rizin evolved a lot, and I was planning for some
time now to solve some crackmes with the framework, and write writeups about
them. Well, this CTF gave me the perfect opportunity :)

Because this writeup aims to show some of rizin's features besides how the crackmes
can be solved, I will explain every rizin command I use in blockquote paragraphs
like this one:

> ***rizin tip:*** Always use ? or -h to get more information!

If you know rizin, and just interested in the crackme, feel free to skip those
parts! Also keep in mind please, that because of this tutorial style I'm going
to do a lot of stuff that you just don't do during a CTF, because there is no
time for proper bookkeeping (e.g. flag every memory area according to its
purpose), and with such small executables you can succeed without doing these
stuff.

A few advice if you are interested in learning rizin (and frankly, if you are
into RE, you should be interested in learning rizin :) ):

The framework has a lot of supplementary executables and a vast amount of
functionality - and they are very well documented. I encourage you to read the
available docs, and use the built-in help (by appending a ? to any command)
extensively! E.g.:

```
[0x00000000]> ?
Usage: [.][times][cmd][~grep][@[@iter]addr!size][|>pipe] ; ...
Append '?' to any char command to get detailed help
Prefix with number to repeat command N times (f.ex: 3x)
|%var =valueAlias for 'env' command
| *off[=[0x]value]     Pointer read/write data/values (see ?v, wx, wv)
| (macro arg0 arg1)    Manage scripting macros
| .[-|(m)|f|!sh|cmd]   Define macro or load rizin, cparse or rlang file
| = [cmd]              Run this command via rap://
| /                    Search for bytes, regexps, patterns, ..
| ! [cmd]              Run given command as in system(3)
| # [algo] [len]       Calculate hash checksum of current block
| #!lang [..]          Hashbang to run an rlang script
| a                    Perform analysis of code
| b                    Get or change block size

...

[0x00000000]> a?
|Usage: a[abdefFghoprxstc] [...]
| ab [hexpairs]     analyze bytes
| aa                analyze all (fcns + bbs) (aa0 to avoid sub renaming)
| ac [cycles]       analyze which op could be executed in [cycles]
| ad                analyze data trampoline (wip)
| ad [from] [to]    analyze data pointers to (from-to)
| ae [expr]         analyze opcode eval expression (see ao)
| af[rnbcsl?+-*]    analyze Functions
| aF                same as above, but using analysis.depth=1

...
```

Also, the project is under heavy development, there is no day
without commits to the GitHub repo. So, as the readme says, you should always
use the git version!

Some highly recommended reading materials:

- [Rizin Book](https://book.rizin.re)
- [Rizin Blog](https://rizin.re/posts/)
