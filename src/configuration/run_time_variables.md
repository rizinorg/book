## Run-Time Variables

Run-time variables (also known as environment variables) can be used to change the default behavior when running rizin or tools.

The description of these run-time variables can be accessed by executing the command `rizin -hh` on a terminal.

```bash
$ rizin -hh
...
Plugins:
 binrc            /home/username/.local/share/rizin/rc.d/bin-<format> (elf, elf64, mach0, ..)
 RZ_USER_PLUGINS  /home/username/.local/lib/rizin/plugins
 RZ_LIB_PLUGINS   /home/username/.local/lib/rizin/plugins
 RZ_EXTRA_PLUGINS
Environment:
 ANSICON             ansicon′s W & H of the buffer and w & h of the window in the form of: "WxH (wxh)"
 DEBUGINFOD_URLS     e bin.dbginfo.debuginfod_urls - use alternative debuginfod server
 COLUMNS             terminal columns to use
 RZ_ABORTLEVEL       target log level/severity when to abort (0:DEBUG, 1:VERBOSE, 2:INFO, 3:WARN, 4:ERROR, 5:FATAL)
 RZ_CURL             whether to use curl (for SSL support)
 RZ_DEBUG            if defined, show error messages and crash signal
 RZ_DEBUG_ASSERT     set a breakpoint when hitting an assert
 RZ_DEBUG_TOOL       debug tool to use when showing error messages and crash signal
 RZ_DYLDCACHE_FILTER dyld cache filter (MacOS dynamic libraries location(s) at runtime)
 RZ_HTTP_AUTHFILE    HTTP Authentification user file
 RZ_LOGCOLORS        should the log output use colors
 RZ_LOGFILE          logging output filename/path
 RZ_LOGLEVEL         target log level/severity (0:DEBUG, 1:VERBOSE, 2:INFO, 3:WARN, 4:ERROR, 5:FATAL)
 RZ_LOGSHOWSOURCES   should the log output contain src info (filename:lineno)
 RZ_PIPE_IN          rzpipe cmd input (file descriptor)
 RZ_PIPE_OUT         rzpipe cmd output (file descriptor)
 RZ_MAGICPATH        /home/username/.local/share/rizin/magic
 RZ_NOPLUGINS        do not load rizin shared plugins
 RZ_RCFILE           /home/username/.rizinrc (user preferences, batch script)
 RZ_DATAHOME         /home/username/.local/share/rizin
 RZ_VERSION          contains the current version of rizin
 SFLIBPATH           SFLib syscall library path
Paths:
 RZ_PREFIX       /home/username/.local
 RZ_EXTRA_PREFIX
 RZ_INCDIR       /home/username/.local/include/librz
 RZ_LIBDIR       /home/username/.local/lib
 RZ_SIGDB        /home/username/.local/share/rizin/sigdb
 RZ_EXTRA_SIGDB
 RZ_LIBEXT       so
```
