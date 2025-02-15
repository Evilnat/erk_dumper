CELL_MK_DIR ?= $(CELL_SDK)/samples/mk

include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_SRCS = main.c mm.c hvcall.c payload.c util.c
PPU_TARGET = EBOOT.ELF

#PPU_CFLAGS += -g -D_DEBUG
#PPU_LDFLAGS +=

PPU_LDLIBS = -lm -lio_stub -lfs_stub -lsysmodule_stub -lsysutil_stub -lsysutil_game_stub

include $(CELL_MK_DIR)/sdk.target.mk
