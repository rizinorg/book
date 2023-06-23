## Implementing a new disassembly plugin

Rizin has modular architecture, thus adding support for a new architecture is very easy, if you
are fluent in C. For various reasons it might be easier to implement it out of the tree. For this we
will need to create single C file, called `asm_mycpu.c` and a meson file for it.

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

**Meson**

```bash
project('asm_mycpu', 'c')

rz_asm_dep = dependency('rz_asm')
plugins_dir = get_option('prefix') / rz_asm_dep.get_variable(pkgconfig: 'plugindir', cmake: 'rz_asm_PLUGINDIR')
message('Plugins install directory: ' + plugins_dir)

library('asm_mycpu',
  ['asm_mycpu.c'],
  dependencies: [rz_asm_dep],
  install: true,
  install_dir: plugins_dir,
)
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

After compiling rizin will list this plugin in the rz-asm output:
```
$ rz-asm -L |grep myc
_d__  _8_32      mycpu        LGPL3   MYCPU disassembly plugin
```

### Moving plugin into the tree

Pushing a new architecture into the main branch of rizin requires to modify several files in order to make it fit into the way the rest of plugins are built.

__List of affected files:__

* `librz/asm/p/asm_mycpu.c`
That's where most of our code will be, the key part is to declare a `RzAsmPlugin` containing a valid `disassemble` field, a function pointer to the actual disassembler function.

* `librz/asm/meson.build`
The build is handled by meson, we have to add our plugin to the list of things to be compiled :
```diff
@@ -49,6 +49,7 @@ asm_plugins_list = [
   'x86_nz',
   'xap',
   'xcore_cs',
+  'mycpu',
 ]

@@ -129,6 +130,7 @@ rz_asm_sources = [
   #'p/asm_x86_vm.c',
   'p/asm_xap.c',
   'p/asm_xcore_cs.c',
+  'p/asm_mycpu.c',
   #'arch/6502/6502dis.c',
   'arch/amd29k/amd29k.c',
   #'arch/8051/8051_disas.c',
+  'arch/mycpu/mycpu_disas.c',
   'arch/arm/armass.c',

@@ -129,6 +130,7 @@ rz_asm_inc = [
+	'arch/mycpu',
]
```

* `librz/include/rz_asm.h`
Make Rizin aware of our plugin by defining our struct :
```diff
@@ -265,6 +265,7 @@ extern RzAsmPlugin rz_asm_plugin_xcore_cs;
 extern RzAsmPlugin rz_asm_plugin_xtensa;
 extern RzAsmPlugin rz_asm_plugin_z80;
 extern RzAsmPlugin rz_asm_plugin_pyc;
+extern RzAsmPlugin rz_asm_plugin_mycpu;

 #endif
```

Check out how the NIOS II CPU disassembly plugin was implemented by reading those commits:

[The RzAsm plugin](https://github.com/rizinorg/rizin/commit/933dc0ef6ddfe44c88bbb261165bf8f8b531476b)

[The RzAnalysis plugin](https://github.com/rizinorg/rizin/commit/ad430f0d52fbe933e0830c49ee607e9b0e4ac8f2)


