## Compilation and Portability

The core of Rizin can be compiled on various systems and architectures, with primary development conducted on GNU/Linux using GCC and on MacOS X with clang. Rizin is known to compile on a wide range of systems and architectures, including compatibility with TCC and SunStudio.

For those interested in utilizing Rizin as a debugger for reverse engineering, the debugger layer is currently available on Windows, GNU/Linux (Intel x86 and x86_64, MIPS, and ARM), OS X, FreeBSD, NetBSD, and OpenBSD (Intel x86 and x86_64).

However, it's important to note that the debugger feature has more restrictive portability compared to the core. If the debugger hasn't been ported to your preferred platform, you have the option to disable the debugger layer using the meson option `-Ddebugger=false`. Refer to [BUILDING.md](https://github.com/rizinorg/rizin/blob/dev/BUILDING.md) for additional details.

Keep in mind that there are I/O plugins utilizing GDB, WinDbg, or Wine as back-ends, and they depend on the presence of corresponding third-party tools, especially in the case of remote debugging (on the target machine).

### Docker

The Rizin repository includes a [Dockerfile](https://github.com/rizinorg/rizin/blob/master/Dockerfile) that you can use with Docker for streamlined deployment.