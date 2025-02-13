# Python plugins

Note - in the following examples there are missing functions of the actual decoding
for the sake of readability!

For this you need to do this:

1. `import rzlang` and `from rzlang import RZ` (for constants)
2. Make a function with 2 subfunctions - `assemble` and `disassemble` and returning plugin structure - for RzAsm plugin
   ```python
   def mycpu(a):
       def assemble(s):
           return [1, 2, 3, 4]
   
       def disassemble(memview, addr):
           try:
               opcode = get_opcode(memview) # https://docs.python.org/3/library/stdtypes.html#memoryview
               opstr = optbl[opcode][1]
               return [4, opstr]
           except:
               return [4, "unknown"]
   ```
3. This structure should contain a pointers to these 2 functions - `assemble` and `disassemble`

   ```python
       return {
               "name" : "mycpu",
               "arch" : "mycpu",
               "bits" : 32,
               "endian" : RZ.RZ_SYS_ENDIAN_LITTLE,
               "license" : "GPL",
               "desc" : "MYCPU disasm",
               "assemble" : assemble,
               "disassemble" : disassemble,
       }
   ```

4. Make a function with 2 subfunctions - `set_reg_profile` and `op` and returning plugin structure - for RzAnalysis plugin

   ```python
   def mycpu_analysis(a):
          def set_reg_profile():
           profile = "=PC	pc\n" + \
           "=SP	sp\n" + \
           "gpr	r0	.32	0	0\n" + \
           "gpr	r1	.32	4	0\n" + \
           "gpr	r2	.32	8	0\n" + \
           "gpr	r3	.32	12	0\n" + \
           "gpr	r4	.32	16	0\n" + \
           "gpr	r5	.32	20	0\n" + \
           "gpr	sp	.32	24	0\n" + \
           "gpr	pc	.32	28	0\n"
           return profile
   
       def op(memview, pc):
           analysisop = {
               "type" : RZ.RZ_ANALYSIS_OP_TYPE_NULL,
               "cycles" : 0,
               "stackop" : 0,
               "stackptr" : 0,
               "ptr" : -1,
               "jump" : -1,
               "addr" : 0,
               "eob" : False,
               "esil" : "",
           }
           try:
               opcode = get_opcode(memview) # https://docs.python.org/3/library/stdtypes.html#memoryview
               esilstr = optbl[opcode][2]
               if optbl[opcode][0] == "J": # it's jump
                   analysisop["type"] = RZ.RZ_ANALYSIS_OP_TYPE_JMP
                   analysisop["jump"] = decode_jump(opcode, j_mask)
                   esilstr = jump_esil(esilstr, opcode, j_mask)
   
           except:
               result = analysisop
           # Don't forget to return proper instruction size!
           return [4, result]
   ```

5. This structure should contain a pointers to these 2 functions - `set_reg_profile` and `op`

   ```python
       return {
               "name" : "mycpu",
               "arch" : "mycpu",
               "bits" : 32,
               "license" : "GPL",
               "desc" : "MYCPU analysis",
               "esil" : 1,
               "set_reg_profile" : set_reg_profile,
               "op" : op,
       }
   ```

6. Then register those using `rzlang.plugin("asm")` and `rzlang.plugin("analysis")` respectively

   ```python
   print("Registering MYCPU disasm plugin...")
   print(rzlang.plugin("asm", mycpu))
   print("Registering MYCPU analysis plugin...")
   print(rzlang.plugin("analysis", mycpu_analysis))
   ```

You can combine everything in one file and load it using `-i` option:

```
rizin -I mycpu.py some_file.bin
```

Or you can load it from the rizin shell: `#!python mycpu.py`

### Implementing new format plugin in Python

Note - in the following examples there are missing functions of the actual decoding
for the sake of readability!

For this you need to do this:
1. `import rzlang`

2. Make a function with  subfunctions:
   - `load`
   - `load_bytes`
   - `destroy`
   - `check_bytes`
   - `baddr`
   - `entries`
   - `sections`
   - `imports`
   - `relocs`
   - `binsym`
   - `info`

   and returning plugin structure - for RzAsm plugin

   ```python
   def le_format(a):
       def load(binf):
           return [0]
   
       def check_bytes(buf):
           try:
               if buf[0] == 77 and buf[1] == 90:
                   lx_off, = struct.unpack("<I", buf[0x3c:0x40])
                   if buf[lx_off] == 76 and buf[lx_off+1] == 88:
                       return [1]
               return [0]
           except:
               return [0]
   ```
   
   and so on. Please be sure of the parameters for each function and format of returns.
   Note, that functions `entries`, `sections`, `imports`, `relocs` returns a list of special
   formed dictionaries - each with a different type.
   Other functions return just a list of numerical values, even if single element one.
   There is a special function, which returns information about the file - `info`:
   
   ```python
       def info(binf):
           return [{
                   "type" : "le",
                   "bclass" : "le",
                   "rclass" : "le",
                   "os" : "OS/2",
                   "subsystem" : "CLI",
                   "machine" : "IBM",
                   "arch" : "x86",
                   "has_va" : 0,
                   "bits" : 32,
                   "big_endian" : 0,
                   "dbg_info" : 0,
                   }]
   ```

3. This structure should contain a pointers to the most important functions like
`check_bytes`, `load` and `load_bytes`, `entries`, `relocs`, `imports`.

   ```python
       return {
               "name" : "le",
               "desc" : "OS/2 LE/LX format",
               "license" : "GPL",
               "load" : load,
               "load_bytes" : load_bytes,
               "destroy" : destroy,
               "check_bytes" : check_bytes,
               "baddr" : baddr,
               "entries" : entries,
               "sections" : sections,
               "imports" : imports,
               "symbols" : symbols,
               "relocs" : relocs,
               "binsym" : binsym,
               "info" : info,
       }
   ```

4. Then you need to register it as a file format plugin:

   ```python
   print("Registering OS/2 LE/LX plugin...")
   print(rzlang.plugin("bin", le_format))
   ```
