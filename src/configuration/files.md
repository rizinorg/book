## Files

Use `rizin -H` to list all the environment variables that matter to know where it will
be looking for files. Those paths depend on the way (and operating system) you have
built rizin for.

```
RZ_PREFIX=/usr
MAGICPATH=/usr/share/rizin/2.8.0-git/magic
PREFIX=/usr
INCDIR=/usr/include/libr
LIBDIR=/usr/lib64
LIBEXT=so
RCONFIGHOME=/home/user/.config/rizin
RDATAHOME=/home/user/.local/share/rizin
RCACHEHOME=/home/user/.cache/rizin
LIBR_PLUGINS=/usr/lib/rizin/2.8.0-git
USER_PLUGINS=/home/user/.local/share/rizin/plugins
USER_ZIGNS=/home/user/.local/share/rizin/zigns
```

## RC Files

RC files are rizin scripts that are loaded at startup time. Those files must be in 3 different places:

### System

rizin will first try to load /usr/share/rizin/rizinrc

### Your Home

Each user in the system can have its own rizin scripts to run on startup to select the color scheme, and other custom options by having rizin commands in there.

* ~/.rizinrc
* ~/.config/rizin/rizinrc
* ~/.config/rizin/rizinrc.d/

### Target file

If you want to run a script every time you open a file, just create a file with the same name of the file
but appending `.rz` to it.
