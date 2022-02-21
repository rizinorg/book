## Implementing a new disassembly plugin

Rizin has modular architecture, thus adding support for a new architecture is very easy, if you
are fluent in C. For various reasons it might be easier to implement it out of the tree. For this we
will need to create single C file, called `asm_mycpu.c` and makefile for it.

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

**Makefile**

```makefile
NAME=asm_mycpu
RZ_PLUGIN_PATH=$(shell rizin -H RZ_USER_PLUGINS)
LIBEXT=$(shell rizin -H LIBEXT)
CFLAGS=-g -fPIC $(shell pkg-config --cflags rz_analyss)
LDFLAGS=-shared $(shell pkg-config --libs rz_analysis)
OBJS=$(NAME).o
LIB=$(NAME).$(LIBEXT)

all: $(LIB)

clean:
	rm -f $(LIB) $(OBJS)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(LIB)

install:
	cp -f asm_mycpu.$(SO_EXT) $(RZ_PLUGIN_PATH)

uninstall:
	rm -f $(RZ_PLUGIN_PATH)/asm_mycpu.$(SO_EXT)
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
$ ./build/binrz/rz-asm/rz-asm -L |grep myc
_d__  _8_32      mycpu        LGPL3   MYCPU
```

### Moving plugin into the tree

Pushing a new architecture into the main branch of rizin requires to modify several files in order to make it fit into the way the rest of plugins are built.

List of affected files:

* `librz/asm/p/asm_mycpu.c`
That's where most of our code will be, the key part is to declare a `RzAsmPlugin` containing a valid `disassemble` field, a function pointer to the actual disassembler function.

* `librz/asm/meson.build`
The build is handled by meson, we have to add our plugin to the list of things to be compiled :
```diff
@@ -49,6 +49,7 @@ asm_plugins = [
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

Implement RzAsm plugin:
https://github.com/rizinorg/rizin/commit/933dc0ef6ddfe44c88bbb261165bf8f8b531476b

Implement RzAnalysis plugin:
https://github.com/rizinorg/rizin/commit/ad430f0d52fbe933e0830c49ee607e9b0e4ac8f2


