## Rizin package manager

Rizin has its own package manager for managing external plugins (mainly from
[rizin-extras](https://github.com/rizinorg/rizin-extras)). As most of the package managers it allows you to install,
remove or update packages (plugins). There is one restriction though - currently it supports only the compilation
from sources, so providing the toolchan, necessary build tools and dependencies for each plugin is the user
responsibility. It might change in the future.

```
$ rz-pm -h
$ RZPM_DBDIR: No such file or directory.
Run 'rz-pm init' to initialize the package repository
$ rz-pm init
git clone https://github.com/rizinorg/rizin-pm
Cloning into 'rizin-pm'...
remote: Counting objects: 147, done.
remote: Compressing objects: 100% (139/139), done.
remote: Total 147 (delta 26), reused 57 (delta 7), pack-reused 0
Receiving objects: 100% (147/147), 42.68 KiB | 48.00 KiB/s, done.
Resolving deltas: 100% (26/26), done.
/home/user/.local/share/rizin/rz-pm/git/rizin-pm
rz-pm database initialized. Use 'rz-pm update' to update later today
```

As you noticed, the packages database located at [rizin-pm](https://github.com/rizinorg/rizin-pm)
repository. At any point of the time we can update the database using `rz-pm update`:

```
rz-pm update
HEAD is now at 7522928 Fix syntax
Updating 7522928..1c139e0
Fast-forward
 db/ldid2 | 18 ++++++++++++++++++
 1 file changed, 18 insertions(+)
 create mode 100644 db/ldid2
Updating /home/user/.local/share/rizin/rz-pm/db ...
Already up to date.
```

There are many commands available now:

```
rz-pm -h
Usage: rz-pm [init|update|cmd] [...]
Commands:
 -I,info                     show information about a package
 -i,install <pkgname>        install package in your home (pkgname=all)
 -gi,global-install <pkg>    install package system-wide
 -gu,global-uninstall <pkg>  uninstall pkg from systemdir
 -u,uninstall <pkgname>      rz-pm -u baleful (-uu to force)
 -l,list                     list installed pkgs
 -r,run [cmd ...args]        run shell command with RZPM_BINDIR in PATH
 -s,search [<keyword>]       search in database
 -t,test FX,XX,BR BID        check in Travis regressions
 -v,version                  show version
 -h,help                     show this message
 -H variable                 show value of given variable
 -c,clean ([git/dir])        clear source cache (GITDIR)
 -ci (pkgname)               clean install of given package
 -cp                         clean the user's home plugin directory
 -d,doc [pkgname]            show documentation for given package
 -w <pkgname>                what/where is installed
 init | update ..            initialize/update database
 cd [git/dir]                cd into given git (see 'rz-pm ls')
 ls                          ls all cloned git repos in GITDIR
 suicide                     self remove all (home + system) installations of rizin
 cache                       cache contents of rizin -H to make rz-pm rizin-independent
Environment:
 SUDO=sudo                    use this tool as sudo
 RZPM_PLUGDIR=~/.local/share/rizin/plugins   # default value, home-install for plugins
 RZPM_BINDIR=~/.local/share/rizin/prefix/bin # bindir in rizin's PATH
 RZPM_PLUGDIR=/usr/lib/rizin/last/           # for system-wide plugin installs
 RZPM_DBDIR=~/.local/share/rizin/rz-pm/db     # location of the db
 RZPM_GITDIR=~/.local/share/rizin/rz-pm/git   # cloned git repositories
```

The usual scenario of using it is to install new plugins, for example `lang-python3` (which is used
for writing rizin plugins in Python):

```
$ rz-pm -i lang-python3
...
mkdir -p ~/.config/rizin/plugins
cp -f lang_python3.so ~/.config/rizin/plugins
...
```

Note that if we used `-i` switch it installs the plugin in the `$HOME` directory, in case of `-gi`
it will install the plugin systemwide (requires `sudo`).

After this we will be able to see the plugin in the list of installed:

```
$ rz-pm -l
lang-python3
```

To uninstall the plugin just simply run

```
$ rz-pm -u lang-python3
```

