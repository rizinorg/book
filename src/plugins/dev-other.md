## Write a debugger plugin

* Adding the debugger registers profile into the shlr/gdb/src/core.c
* Adding the registers profile and architecture support in the librz/debug/p/debug_native.c and librz/debug/p/debug_gdb.c
* Add the code to apply the profiles into the function `rz_debug_gdb_attach(RzDebug *dbg, int pid)`

If you want to add support for the gdb, you can see the register profile in the active gdb session using command
`maint print registers`.

## More to come...

* Related article: http://rizin.today/posts/extending-r2-with-new-plugins/

Some commits related to "Implementing a new architecture"

* Extensa: https://github.com/rizinorg/rizin/commit/6f1655c49160fe9a287020537afe0fb8049085d7
* Malbolge: https://github.com/rizinorg/rizin/pull/579
* 6502: https://github.com/rizinorg/rizin/pull/656
* h8300: https://github.com/rizinorg/rizin/pull/664
* GBA: https://github.com/rizinorg/rizin/pull/702
* CR16: https://github.com/rizinorg/rizin/pull/721/ && 726
* XCore: https://github.com/rizinorg/rizin/commit/bb16d1737ca5a471142f16ccfa7d444d2713a54d
* SharpLH5801: https://github.com/neuschaefer/rizin/commit/f4993cca634161ce6f82a64596fce45fe6b818e7
* MSP430: https://github.com/rizinorg/rizin/pull/1426
* HP-PA-RISC: https://github.com/rizinorg/rizin/commit/f8384feb6ba019b91229adb8fd6e0314b0656f7b
* V810: https://github.com/rizinorg/rizin/pull/2899
* TMS320: https://github.com/rizinorg/rizin/pull/596

## Implementing a new pseudo architecture

This is a simple plugin for z80 that you may use as example:

* https://github.com/rizinorg/rizin/commit/8ff6a92f65331cf8ad74cd0f44a60c258b137a06
