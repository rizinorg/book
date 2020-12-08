## Compilation and Portability

Currently the core of rizin can be compiled on many systems and architectures, but the main development is done on GNU/Linux with GCC, and on MacOS X with clang. Rizin is also known to compile on many different systems and architectures (including TCC and SunStudio).

People often want to use rizin as a debugger for reverse engineering. Currently, the debugger layer can be used on Windows, GNU/Linux (Intel x86 and x86_64, MIPS, and ARM), OS X, FreeBSD, NetBSD, and OpenBSD (Intel x86 and x86_64)..

Compared to core, the debugger feature is more restrictive portability-wise. If the debugger has not been ported to your favorite platform, you can disable the debugger layer with the meson option `-Ddebugger=false`. Have a look at [BUILDING.md](https://github.com/rizinorg/rizin/blob/dev/BUILDING.md) for more information.

Note that there are I/O plugins that use GDB, WinDbg, or Wine as back-ends, and therefore rely on presence of corresponding third-party tools (in case of remote debugging - just on the target machine).

### Docker

Rizin repository ships a [Dockerfile](https://github.com/rizinorg/rizin/blob/master/Dockerfile) that you can use with Docker.