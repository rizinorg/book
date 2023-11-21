# Creating an rz-pm package of the plugin

As you remember rizin has its own [packaging manager](/tools/rz-pm/intro.md) and we can easily
add newly written plugin for everyone to access.

All packages are located in [rizin-pm](https://github.com/rizinorg/rizin-pm) repository, and have
very simple text format.

```
RZPM_BEGIN

RZPM_GIT "https://github.com/user/mycpu"
RZPM_DESC "[rizin-arch] MYCPU disassembler and analyzer plugins"

RZPM_INSTALL() {
	${MAKE} clean
	${MAKE} all || exit 1
	${MAKE} install RZPM_PLUGDIR="${RZPM_PLUGDIR}"
}

RZPM_UNINSTALL() {
	rm -f "${RZPM_PLUGDIR}/asm_mycpu."*
	rm -f "${RZPM_PLUGDIR}/analysis_mycpu."*
}

RZPM_END
```

Then add it in the `/db` directory of rizin-pm repository and send a pull request to the mainline.


