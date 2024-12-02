## Implementing a new architecture

Rizin splits the logic of a CPU into several modules. You should write more than one plugin to get full support
for a specific arch. Let's see which are those:

* rz_asm : assembler and disassembler
* rz_analysis : code analysis (opcode,type,esil,..)
* rz_reg : registers
* rz_syscall : system calls
* rz_debug : debugger

The most basic feature you usually want to support from a specific architecture is the disassembler. You first need to
read into a human-readable form the bytes in there.

Bear in mind that plugins can be compiled static or dynamically, this means that the arch will be embedded inside
the core libraries, or it will distribute as a separated shared library.

You may find some examples of external plugins in [rizin-extras](https://github.com/rizinorg/rizin-extras) repository.

## Writing the rz_asm plugin

The official way to make third-party plugins is to distribute them into a separate repository. This is a sample
disasm plugin:

`meson.build` file:

```meson
project('rizin-mycpu', 'c')

plugins_dir = join_paths(get_option('prefix'), 'plugins')

rz_asm_lib = dependency('rz_asm')

library('asm_mycpu', ['mycpu.c'],
    dependencies: [rz_asm_lib],
    install: true,
    install_dir: plugins_dir,
    soversion: rz_asm_lib.version()
)
```

`mycpu.c` file:

```c
/* example rz_asm plugin by pancake at 2014 */

#include <rz_asm.h>
#include <rz_lib.h>

#define OPS 17

static const char *ops[OPS*2] = {
	"nop", NULL,
	"if", "r",
	"ifnot", "r",
	"add", "rr",
	"addi", "ri",
	"sub", "ri",
	"neg", "ri",
	"xor", "ri",
	"mov", "ri",
	"cmp", "rr",
	"load", "ri",
	"store", "ri",
	"shl", "ri",
	"br", "r",
	"bl", "r",
	"ret", NULL,
	"sys", "i"
};

/* Main function for disassembly */
//b for byte, l for length
static int disassemble (RzAsm *a, RzAsmOp *op, const ut8 *b, int l) {
	char arg[32];
        int idx = (b[0]&0xf)\*2;
	op->size = 2;
	if (idx>=(OPS*2)) {
		strcpy (op->buf_asm, "invalid");
		return -1;
	}
	strcpy (op->buf_asm, ops[idx]);
	if (ops[idx+1]) {
		const char \*p = ops[idx+1];
		arg[0] = 0;
		if (!strcmp (p, "rr")) {
			sprintf (arg, "r%d, r%d", b[1]>>4, b[1]&0xf);
		} else
		if (!strcmp (p, "i")) {
			sprintf (arg, "%d", (char)b[1]);
		} else
		if (!strcmp (p, "r")) {
			sprintf (arg, "r%d, r%d", b[1]>>4, b[1]&0xf);
		} else
		if (!strcmp (p, "ri")) {
			sprintf (arg, "r%d, %d", b[1]>>4, (char)b[1]&0xf);
		}
		if (*arg) {
			strcat (op->buf_asm, " ");
			strcat (op->buf_asm, arg);
		}
	}
	return op->size;
}

/* Structure of exported functions and data */
RzAsmPlugin rz_asm_plugin_mycpu = {
        .name = "mycpu",
        .arch = "mycpu",
        .license = "LGPL3",
        .bits = 32,
        .desc = "My CPU disassembler",
        .disassemble = &disassemble,
};

#ifndef CORELIB
struct rz_lib_struct_t rizin_plugin = {
        .type = RZ_LIB_TYPE_ASM,
        .data = &rz_asm_plugin_mycpu
};
#endif
```

To build and install this plugin just type this:

```bash
meson build
ninja -C build && ninja -C build install
```
