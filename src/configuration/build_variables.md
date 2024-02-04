## Build Variables

When rizin is built from sources, some build variables will be hardcoded within the rizin libraries.

These build variables can be accessed by executing the command `rizin -H` on a terminal.

```bash
$ rizin -H
RZ_VERSION=X.Y.Z
RZ_PREFIX=/usr
RZ_EXTRA_PREFIX=
RZ_MAGICPATH=/usr/share/rizin/magic
RZ_INCDIR=/usr/include/librz
RZ_LIBDIR=/usr/lib
RZ_SIGDB=/usr/share/rizin/sigdb
RZ_EXTRA_SIGDB=
RZ_LIBEXT=so
RZ_CONFIGHOME=/home/username/.config/rizin
RZ_DATAHOME=/home/username/.local/share/rizin
RZ_CACHEHOME=/home/username/.cache/rizin
RZ_LIB_PLUGINS=/usr/lib/rizin/plugins
RZ_EXTRA_PLUGINS=
RZ_USER_PLUGINS=/home/username/.local/lib/rizin/plugins
RZ_IS_PORTABLE=0
```

You can also view a specific build variable by executing `-H variable`.

For example:
```bash
$ rizin -H RZ_USER_PLUGINS
/home/username/.local/lib/rizin/plugins
```
