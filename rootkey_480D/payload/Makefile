CC      := ppu-gcc
CXX     := ppu-g++
LD      := ppu-ld 
OBJCOPY := ppu-objcopy
OBJDUMP := ppu-objdump
AR      := ppu-ar
STRIP   := ppu-strip
BIN2C   := bin2c

INCPATH = .
LIBPATH = .
LIBS =

TARGET = payload

# -ffreestanding -nostdinc
CFLAGS = -std=c99 -m64 -fno-builtin -fno-exceptions -fdata-sections -ffunction-sections -Os -Wno-strict-aliasing -Wno-multichar -Wall $(foreach dir,$(INCPATH),-I$(dir))
ifeq ($(BUILD_TYPE),debug)
	CFLAGS += -DDEBUG
endif
CFLAGS += -D__STDC_FORMAT_MACROS
ASFLAGS = -m64 -Os -Wall $(foreach dir,$(INCPATH),-I$(dir))
ASFLAGS += -D__ASSEMBLY__
ifeq ($(BUILD_TYPE),debug)
	ASFLAGS += -DDEBUG
endif
LDFLAGS = -Tldscript.ld -nostartfiles -nostdlib -nodefaultlibs -Wl,--gc-sections -Wl,-Map=payload.map $(foreach dir,$(LIBPATH),-L$(dir))

C_FILES = main.c device.c network.c mm.c kernel.c hypervisor.c spu.c debug.c util.c dumper.c
S_FILES = start.S kernel.S hypervisor.S syscalls.S util.S

OBJS = $(S_FILES:.S=.S.o) $(C_FILES:.c=.c.o)

all: $(TARGET).bin

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).elf: $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^

%.S.o: %.S
	$(CC) $(ASFLAGS) -c $< -o $@

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

objdump: $(TARGET).bin
	$(OBJDUMP) -D -EB -b binary -m powerpc:common64 $@

code: $(TARGET).bin
	$(BIN2C) -n $(TARGET) -o $(TARGET).inc $<

clean:
	rm -f *.S.o *.c.o *.elf *.bin *.map $(TARGET).inc
