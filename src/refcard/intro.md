# Rizin Reference Card

This chapter is based on the Radare 2 reference card by Thanat0s, which is under the GNU GPL. Original license is as follows:

```
This card may be freely distributed under the terms of the GNU
general public licence — Copyright by Thanat0s - v0.1 -
```

## Survival Guide

Those are the basic commands you will want to know and use for moving
around a binary and getting information about it.

| Command                 | Description                             |
|:------------------------|:----------------------------------------|
| help                    | First introduction                      |
| s (tab)                 | Seek to a different place               |
| aa[a]                   | Auto analyze (three `a` for more)       |
| afl                     | List functions                          |
| afvl                    | List function local vars and args       |
| avg                     | List globals                            |
| t                       | List types                              |
| iz[z]                   | List strings (two `z` for more)         |
| pdf @ [funcname](Tab)   | Disassemble function (main, fcn, etc)   |
| x [nbytes]              | Hexdump of nbytes, $b by default        |
| wx [nbytes]             | Write hexadecimal string                |
| axt @ [flag/address]    | Find cross reference to a flag/address  |

## Flags

Flags are like bookmarks, but they carry some extra information like size, tags or associated flagspace. Use `f` commands to list, set, get them.

| Command             | Description           |
|:--------------------|:----------------------|
| f name              | Add flag "name"       |
| f- name             | Remove flag "name"    |
| fl                  | List flags            |
| fd $$               | Describe an offset    |
| fN [name]           | Show the real name    |
| fx [flagname]       | Show hexdump of flag  |
| fC [name] [comment] | Set flag comment      |

## Functions and variables

Functions appear after auto-analysis or after adding them manually with the `af` command.

| Command             | Description               |
|:--------------------|:--------------------------|
| af                  | Analyze function          |
| af- name            | Remove function "name"    |
| afb                 | List basic blocks         |
| afi                 | Show function information |
| afs                 | Show function signature   |
| afvl                | Show function variables   |
| agf                 | Show function graph       |

## Global variables

Global variables appear after auto-analysis or after adding them manually.

| Command             | Description               |
|:--------------------|:--------------------------|
| avg                 | Show all globals          |
| avg name            | Show global "name"        |
| avga name type      | Add global variable       |
| avgp name           | Print global variable     |
| avgx name           | Show xrefs to the global  |

## Information

Binary files have information stored inside the headers. The `i` command uses the RzBin API and allows us to the same things rz-bin does. Those are the most common ones.

| Command | Description                 |
|:--------|:----------------------------|
| ii      | Information on imports      |
| iI      | Info on binary              |
| ie      | Display entrypoint          |
| iS      | Display sections            |
| ir      | Display relocations         |

## Print string

There are different ways to represent a string in memory. The `ps` command
allows us to print it in UTF8, UTF-16, Pascal, zero-terminated, .. formats.

| Command        | Description                            |
|:---------------|:---------------------------------------|
| ps @ [offset]  | Print auto-detected string             |
| psb @ [offset] | Print all strings in the current block |
| psp @ [offset] | Print Pascal string                    |
| psw @ [offset] | Print UTF-16 LE string                 |
| psm @ [offset] | Print UTF-16 BE string                 |
| psW @ [offset] | Print UTF-32 LE string                 |
| psM @ [offset] | Print UTF-32 BE string                 |

## Visual mode

The visual mode is the standard interactive interface of rizin.

To enter in visual mode use the `v` or `V` command, and then you'll only
have to press keys to get the actions happen instead of commands.

| Command        | Description                                       |
|:---------------|:--------------------------------------------------|
| V              | Enter visual mode                                 |
| p/P            | Rotate modes (hex, disasm, debug, words, buf)     |
| c              | Toggle (c)ursor                                   |
| q              | Back to rizin shell                               |
| hjkl           | Move around (or HJKL) (left-down-up-right)        |
| Enter          | Follow address of jump/call                       |
| sS             | Step/step over                                    |
| o              | Toggle asm.pseudo and asm.esil                    |
| .              | Seek to program counter                           |
| /              | In cursor mode, search in current block           |
| :cmd           | Run rizin command                                 |
| ;[-]cmt        | Add/remove comment                                |
| /*+-[]         | Change block size, [] = resize hex.cols           |
| <,>            | Seek aligned to block size                        |
| i/a/A          | (i)nsert hex, (a)ssemble code, visual (A)ssembler |
| b              | Toggle breakpoint                                 |
| B              | Browse evals, symbols, flags, classes, ...        |
| d[f?]          | Define function, data, code, ..                   |
| D              | Enter visual diff mode (set diff.from/to)         |
| e              | Edit eval configuration variables                 |
| f/F            | Set/unset flag                                    |
| gG             | Go seek to begin and end of file (0-$s)           |
| mK/’K          | Mark/go to Key (any key)                          |
| n/N            | Seek next/prev function/flag/hit (scr.nkey)       |
| C              | Toggle (C)olors                                   |
| R              | Randomize color palette (ecr)                     |
| tT             | Tab related. see also [tab](../visual_mode/visual_panels.md)     |
| v              | Visual code analysis menu                         |
| V              | (V)iew graph (agv?)                               |
| wW             | Seek cursor to next/prev word                     |
| uU             | Undo/redo seek                                    |
| x              | Show xrefs of current func from/to data/code      |
| yY             | Copy and paste selection                          |
| z              | fold/unfold comments in disassembly               |

## Searching

There are many situations where we need to find a value inside a binary
or in some specific regions. Use the `e search.in=?` command to choose
where the `/` command may search for the given value.

| Command        | Description                                   |
|:---------------|:----------------------------------------------|
| / foo\00       | Search for string ’foo\0’                     |
| /b             | Search backwards                              |
| //             | Repeat last search                            |
| /w foo         | Search for wide string ’f\0o\0o\0’            |
| /wi foo        | Search for wide string ignoring case          |
| /! ff          | Search for first occurrence not matching      |
| /i foo         | Search for string ’foo’ ignoring case         |
| /e /E.F/i      | Match regular expression                      |
| /x a1b2c3      | Search for bytes; spaces and uppercase nibbles are allowed, same as /x A1 B2 C3|
| /x a1..c3      | Search for bytes ignoring some nibbles (auto-generates mask, in this example: ff00ff)|
| /x a1b2:fff3   | Search for bytes with mask (specify individual bits)|
| /d 101112      | Search for a deltified sequence of bytes      |
| /!x 00         | Inverse hexa search (find first byte != 0x00) |
| /c jmp [esp]   | Search for asm code (see search.asmstr)       |
| /a jmp eax     | Assemble opcode and search its bytes          |
| /A             | Search for AES expanded keys                  |
| /r sym.printf  | Analyze opcode reference an offset            |
| /R             | Search for ROP gadgets                        |
| /P             | Show offset of previous instruction           |
| /m magicfile   | Search for matching magic file                |
| /p patternsize | Search for pattern of given size              |
| /z min max     | Search for strings of given size              |
| /v[?248] num   | Look for a asm.bigendian 32bit value          |

## Usable variables in expression

The `%$?` command will display the variables that can be used in any math
operation inside the rizin shell. For example, using the `% $$` command to evaluate
a number or `%v` to just the value in one format.

All commands in rizin that accept a number supports the use of those variables.

| Command       | Description                                                 |
|:--------------|:------------------------------------------------------------|
| $$            | here (current virtual seek)                                 |
| $?            | last comparison value                                       |
| $B            | base address (aligned lowest map address)                   |
| $b            | block size                                                  |
| $D            | current debug map base address ?v $D @ rsp                  |
| $DB           | same as dbg.baddr, progam base address                      |
| $Fb           | begin of basic block                                        |
| $FB           | begin of function                                           |
| $Fe           | end of basic block                                          |
| $FE           | end of function                                             |
| $FS           | function size (linear length)                               |
| $Fs           | size of the current basic block                             |
| $FSS          | function size (sum bb sizes)                                |
| $s            | file size                                                   |
| $S            | section offset                                              |
| $SS           | section size                                                |
| ${ev}         | get value of eval <config variable <ev>                     |
| $r{reg}       | get value of named register <reg>                           |
