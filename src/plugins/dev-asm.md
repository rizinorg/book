## Implementing a new disassembly plugin

Rizin has modular architecture, thus adding support for a new architecture is very easy, if you
are fluent in C. For various reasons it might be easier to implement it out of the tree. For this we
will need two C files mainly, called `asm_mycpu.c` in `librz/arch/p/asm/` , `arch_mycpu.c` in `librz/arch/p/` and declare the asm plugin in architecture plugin file .
Add the newly created architecture plugin file in meson.build

The key thing of RzAsm plugin is a structure

```c
RzAsmPlugin rz_asm_plugin_mycpu = {
	.name = "mycpu",
	.license = "LGPL3",
	.desc = "MYCPU disassembly plugin",
	.arch = "mycpu",
	.bits = 32,
	.endian = RZ_SYS_ENDIAN_LITTLE,
	.disassemble = &disassemble
};
```

where `.disassemble` is a pointer to disassembly function, which accepts the bytes buffer
and length:

```c
static int disassemble(RzAsm *a, RzAsmOp *op, const ut8 *buf, int len)
```

**asm_mycpu.c**

```c
/* rizin - LGPL - Copyright 2018 - user */

#include <stdio.h>
#include <string.h>
#include <rz_types.h>
#include <rz_lib.h>
#include <rz_asm.h>

static int disassemble(RzAsm *a, RzAsmOp *op, const ut8 *buf, int len) {
	struct op_cmd cmd = {
		.instr = "",
		.operands = ""
	};
	if (len < 2) return -1;
	int ret = decode_opcode (buf, len, &cmd);
	if (ret > 0) {
		snprintf (op->buf_asm, rz_asm_BUFSIZE, "%s %s",
			  cmd.instr, cmd.operands);
	}
	return op->size = ret;
}

RzAsmPlugin rz_asm_plugin_mycpu = {
	.name = "mycpu",
	.license = "LGPL3",
	.desc = "MYCPU disassembly plugin",
	.arch = "mycpu",
	.bits = 32,
	.endian = RZ_SYS_ENDIAN_LITTLE,
	.disassemble = &disassemble
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_mycpu,
	.version = RZ_VERSION
};
#endif
```

**arch_mycpu.c**

This file is an architecture plugin wrapper that ties together assembler,analysis, and (optionally) parsing components into a single `RzArchPlugin` which is registered using macros from `deprecated_arch_helper.h`

```c
#include <deprecated_arch_helper.h>

#include "analysis/analysis_mycpu.c"
#include "asm/asm_mycpu.c"

RZ_ARCH_PLUGIN_DEFINE_DEPRECATED(mycpu); // or any other suitable macro from deprecated_arch_helper.h
```

**If neeeded also add:**

- `librz/arch/isa/mycpu/` — create this directory with your ISA definition files (instruction tables, opcode maps, disassembler/assembler logic)

- `librz/arch/opcodes/mycpu.sdb.txt` — optional, human-readable instruction descriptions

### Moving plugin into the tree

Pushing a new architecture into the main branch of rizin requires to modify several files in order to make it fit
into the way the rest of plugins are built.

**List of affected files:**

- `librz/arch/p/asm_mycpu.c`
  That's where most of our code will be, the key part is to declare a `RzAsmPlugin` containing a valid `disassemble`
  field, a function pointer to the actual disassembler function.

- `librz/arch/meson.build`
  The build is handled by meson, we have to add our plugin to the list of things to be compiled :

```diff
@@ -49,6 +49,7 @@ arch_plugins_list = [
   'x86_nz',
   'xap',
   'xcore_cs',
+  'mycpu',
 ]

@@ -129,6 +130,7 @@ arch_plugin_sources = [
   #'p/arch_x86_vm.c',
   'p/arch_xap.c',
   'p/arch_xcore_cs.c',
+  'p/arch_mycpu.c',
]

@@ -129,6 +131,8 @@ arch_isa_sources = [
+	'isa/mycpu/disas.c',
+   'isa/mycpu/mycpu.c', // any other related files if exist
]
```

After compiling rizin will list this plugin in the rz-asm output:

```
$ rz-asm -L |grep myc
_d__  _8_32      mycpu        LGPL3   MYCPU disassembly plugin
```

Check out how the NIOS II CPU disassembly plugin was implemented by reading those commits:

[The RzAsm plugin](https://github.com/rizinorg/rizin/commit/933dc0ef6ddfe44c88bbb261165bf8f8b531476b)

[The RzAnalysis plugin](https://github.com/rizinorg/rizin/commit/ad430f0d52fbe933e0830c49ee607e9b0e4ac8f2)
