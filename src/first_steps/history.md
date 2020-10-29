## History

In 2006, Sergi Àlvarez (aka pancake) was working as a forensic analyst. Since he wasn't allowed to use the company software for his personal needs, he decided to write a small tool-a hexadecimal editor-with very basic characteristics:

* be extremely portable (unix friendly, command line, c, small)
* open disk devices, this is using 64bit offsets
* search for a string or hexpair
* review and dump the results to disk

The editor was originally designed to recover a deleted file from an HFS+ partition.

After that, pancake decided to extend the tool to have a pluggable io to be able to attach to processes and implemented the debugger functionalities, support for multiple architectures, and code analysis.

Since then, the project has evolved to provide a complete framework for analyzing binaries, while making use of basic UNIX concepts. Those concepts include the famous "everything is a file", "small programs that interact using stdin/stdout", and "keep it simple" paradigms.

The need for scripting showed the fragility of the initial design: a monolithic tool made the API hard to use, and so a deep refactoring was needed. In 2009 rizin (r2) was born as a fork of rizin1. The refactor added flexibility and dynamic features. This enabled much better integration, paving the way to use rizin [from different programming languages](https://github.com/rizinorg/rizin-bindings). Later on, the [rz-pipe API](https://github.com/rizinorg/rizin-rz-pipe) allowed access to rizin via pipes from any language.

What started as a one-man project, with some eventual contributions, gradually evolved into a big community-based project around 2014. The number of users was growing fast, and the author-and main developer-had to switch roles from coder to manager in order to integrate the work of the different developers that were joining the project.

Instructing users to report their issues allows the project to define new directions to evolve in. Everything is managed in [rizin's GitHub](https://github.com/rizinorg/rizin) and discussed in the Telegram channel.

The project remains active at the time of writing this book, and there are several side projects that provide, among other things, a graphical user interface ([Cutter](https://github.com/rizinorg/cutter)), a decompiler ([r2dec](https://github.com/wargio/r2dec-js), [radeco](https://github.com/rizinorg/radeco)), Frida integration ([r2frida](https://github.com/nowsecure/r2frida)), Yara, Unicorn, Keystone, and many other projects indexed in the [rz-pm](https://github.com/rizinorg/rizin-pm) (the rizin package manager).

Since 2016, the community gathers once a year in [r2con](https://www.rizin.org/con/), a congress around rizin that takes place in Barcelona.
