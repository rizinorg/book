## Exports

rz-bin is able to find exports. For example:

```
$ rz-bin -E /usr/lib64/librz_bin.so | head
ERROR: Cannot determine entrypoint, using 0x00013ea0.
[Exports]
nth paddr      vaddr      bind   type size  lib name                                           
-----------------------------------------------------------------------------------------------
366 0x000f34f0 0x000f34f0 GLOBAL FUNC 94        rz_bin_dwarf_str_from_file
367 0x0009d020 0x0009d020 GLOBAL FUNC 85        reloc_targets_map_base_64
368 0x000601b0 0x000601b0 GLOBAL FUNC 153       rz_bin_dex_resolve_class_by_idx
369 0x0001adc0 0x0001adc0 GLOBAL FUNC 70        rz_bin_reloc_size
370 0x00018580 0x00018580 GLOBAL FUNC 66        rz_bin_cur
371 0x000178c0 0x000178c0 GLOBAL FUNC 174       rz_bin_xtr_plugin_del
372 0x000e42a0 0x000e42a0 GLOBAL FUNC 33        rz_bin_dwarf_addr_free
```
