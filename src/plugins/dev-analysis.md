## Implementing a new analysis plugin

After implementing disassembly plugin, you might have noticed that output
is far from being good - no proper highlighting, no reference lines
and so on. This is because rizin requires every architecture plugin
to provide also analysis information about every opcode. At the moment
the implementation of disassembly and opcodes analysis is separated between
two modules - RzAsm and RzAnalysis. Thus we need to write an analysis plugin too.
The principle is very similar - you just need to create a C file and
corresponding Makefile.

They structure of RzAnalysis plugin looks like

```c
RzAnalysisPlugin rz_analysis_plugin_v810 = {
	.name = "mycpu",
	.desc = "MYCPU code analysis plugin",
	.license = "LGPL3",
	.arch = "mycpu",
	.bits = 32,
	.op = mycpu_op,
	.esil = true,
	.set_reg_profile = set_reg_profile,
};
```

Like with disassembly plugin there is a key function - `mycpu_op` which scans the opcode and builds
RzAnalysisOp structure. On the other hand, in this example analysis plugins also performs uplifting to
ESIL, which is enabled in `.esil = true` statement. Thus, `mycpu_op` obliged to fill the
corresponding RzAnalysisOp ESIL field for the opcodes. Second important thing for ESIL uplifting and
emulation - register profile, like in debugger, which is set within `set_reg_profile` function.

**Makefile**

```makefile
NAME=analysis_mycpu
RZ_PLUGIN_PATH=$(shell rizin -H RZ_USER_PLUGINS)
LIBEXT=$(shell rizin -H LIBEXT)
CFLAGS=-g -fPIC $(shell pkg-config --cflags rz_analysis)
LDFLAGS=-shared $(shell pkg-config --libs rz_analysis)
OBJS=$(NAME).o
LIB=$(NAME).$(LIBEXT)

all: $(LIB)

clean:
	rm -f $(LIB) $(OBJS)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(LIB)

install:
	cp -f analysis_mycpu.$(SO_EXT) $(RZ_PLUGIN_PATH)

uninstall:
	rm -f $(RZ_PLUGIN_PATH)/analysis_mycpu.$(SO_EXT)
```

**analysis_mycpu.c:**
This is a dummy example please go check real life examples [in the source](https://github.com/rizinorg/rizin/blob/dev/librz/analysis/p/analysis_snes.c).

```c
/* rizin - LGPL - Copyright 2022 - user */

#include <string.h>
#include <rz_types.h>
#include <rz_lib.h>
#include <rz_asm.h>
#include <rz_analysis.h>

#define NB_INST 2

typedef struct {
	const char *name;
	ut8 len;
} mycpu_op_t;

static mycpu_op_t mycpu_op[] = {
	/*00*/	{ "nop",	2 }, //enough
	/*01*/	{ "ret",	2 },
}

static int mycpu_anop(RzAnalysis *analysis, RzAnalysisOp *op, ut64 addr, const ut8 *data, int len) {
	if (data[0] < NB_INST) {
		op->size = mycpu_op[data[0]].len;
		op->addr = addr;
		op->type = RZ_ANALYSIS_OP_TYPE_UNK;
		switch (data[0]) {
			case 0x00:
				op->type = RZ_ANALYSIS_OP_TYPE_NOP;
				break;
			case 0x01:
				op->type = RZ_ANALYSIS_OP_TYPE_RET;
				break;
		}
		return op->size;
	}
}

struct rz_analysis_plugin_t rz_analysis_plugin_mycpu = {
	.name = "mycpu",
	.desc = "MYCPU analysis plugin",
	.license = "LGPL3",
	.arch = RZ_SYS_ARCH_NONE,
	.bits = 16,
	.init = NULL,
	.fini = NULL,
	.op = &mycpu_anop,
	.set_reg_profile = NULL,
	.fingerprint_bb = NULL,
	.fingerprint_fcn = NULL,
	.diff_bb = NULL,
	.diff_fcn = NULL,
	.diff_eval = NULL
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ANALYSIS,
	.data = &rz_analysis_plugin_mycpu,
	.version = RZ_VERSION
};
#endif
```
After compiling rizin will list this plugin in the rz-asm output:
```
_dA_  _8_16      mycpu        LGPL3   MYCPU disassembly plugin
```
Note the `A` just appeared on the left column (a=asm, d=disasm, A=analyze, e=ESIL).

Examples:

* [RzAnalysis plugin for 6502](https://github.com/rizinorg/rizin/commit/64636e9505f9ca8b408958d3c01ac8e3ce254a9b)
* [RzAnalysis plugin for SNES](https://github.com/rizinorg/rizin/commit/60d6e5a1b9d244c7085b22ae8985d00027624b49)

