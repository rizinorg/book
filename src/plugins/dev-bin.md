## Implementing a new format

### To enable virtual addressing

In `info` add `et->has_va = 1;` and `ptr->srwx` with the `RZ_BIN_SCN_MAP;` attribute

### Create a folder with file format name in librz/bin/format

**Makefile:**

```Makefile
NAME=bin_nes
RZ_PLUGIN_PATH=$(shell rizin -H RZ_USER_PLUGINS)
LIBEXT=$(shell rizin -H LIBEXT)
CFLAGS=-g -fPIC $(shell pkg-config --cflags rz_bin)
LDFLAGS=-shared $(shell pkg-config --libs rz_bin)
OBJS=$(NAME).o
LIB=$(NAME).$(LIBEXT)

all: $(LIB)

clean:
	rm -f $(LIB) $(OBJS)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(LIB)

install:
	cp -f $(NAME).$(SO_EXT) $(RZ_PLUGIN_PATH)

uninstall:
	rm -f $(RZ_PLUGIN_PATH)/$(NAME).$(SO_EXT)

```

**bin_nes.c:**

```c
#include <rz_util.h>
#include <rz_bin.h>

static bool load_buffer(RzBinFile *bf, void **bin_obj, RzBuffer *b, ut64 loadaddr, Sdb *sdb) {
	ut64 size;
	const ut8 *buf = rz_buf_data (b, &size);
	rz_return_val_if_fail (buf, false);
	*bin_obj = rz_bin_internal_nes_load (buf, size);
	return *bin_obj != NULL;
}

static void destroy(RzBinFile *bf) {
	rz_bin_free_all_nes_obj (bf->o->bin_obj);
	bf->o->bin_obj = NULL;
}

static bool check_buffer(RzBuffer *b) {
	if (!buf || length < 4) return false;
	return (!memcmp (buf, "\x4E\x45\x53\x1A", 4));
}

static RzBinInfo* info(RzBinFile *arch) {
	RzBinInfo \*ret = RZ_NEW0 (RzBinInfo);
	if (!ret) return NULL;

	if (!arch || !arch->buf) {
		free (ret);
		return NULL;
	}
	ret->file = strdup (arch->file);
	ret->type = strdup ("ROM");
	ret->machine = strdup ("Nintendo NES");
	ret->os = strdup ("nes");
	ret->arch = strdup ("6502");
	ret->bits = 8;

	return ret;
}

struct rz_bin_plugin_t rz_bin_plugin_nes = {
	.name = "nes",
	.desc = "NES",
	.license = "BSD",
	.get_sdb = NULL,
	.load_buffer = &load_buffer,
	.destroy = &destroy,
	.check_buffer = &check_buffer,
	.baddr = NULL,
	.entries = NULL,
	.sections = NULL,
	.info = &info,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_BIN,
	.data = &rz_bin_plugin_nes,
	.version = RZ_VERSION
};
#endif

```

### Some Examples

* Java - https://github.com/rizinorg/rizin/commit/7cfddb1da8204587cdc1ba1a26bc07c9fee403dc

