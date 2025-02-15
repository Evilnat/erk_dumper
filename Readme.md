# FLATZ's eid root key dumper v1.0

### Supported CFW

* 4.70 [CEX] 
* 4.75 [CEX] 
* 4.80 [CEX/DEX] 
* 4.81 [CEX/DEX]
* 4.82 [CEX/DEX]
* 4.83 [CEX/DEX]
* 4.84 [CEX/DEX/DECR]
* 4.85 [CEX]
* 4.86 [CEX]
* 4.87 [CEX]
* 4.88 [CEX]
* 4.89 [CEX]
* 4.90 [CEX]
* 4.91 [CEX]

### Files need edited / ported 

* source/common.h 
* source/main.c 
* payload/symbols.h 
* payload/main.c

### Files need compiled

**payload.bin** from payload folder converted c code from payload.bin **payload.shellcode.inc** and then build source to compile EBOOT.ELF/self

The file **make.sh** will do compile everything

Then launch build.bat from main folder it will look for eboot.elf from source folder to generate EBOOT.BIN

[Don't forget to edit make.sh to change app version [4.70/4.75/4.80 and etc]

Edit PARAM.SFO and build pkg with EBOOT.BIN