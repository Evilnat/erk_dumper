#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

#define KERNEL_BASE 0x8000000000000000
#define KERNEL_TOC 0x34FB10
#define KERNEL_SYSCALL_TABLE 0x363B60 //done

#define KERNEL_SYMBOL_EXTEND_KSTACK 0x700A0

#define KERNEL_SYMBOL_ALLOCATE   0x64820
#define KERNEL_SYMBOL_DEALLOCATE 0x64C5C

#define KERNEL_SYMBOL_PAGE_ALLOCATE              0x60390
#define KERNEL_SYMBOL_PAGE_DEALLOCATE            0x4348 //0x4348
#define KERNEL_SYMBOL_PAGE_EXPORT_TO_PROCESS     0x6052C
#define KERNEL_SYMBOL_PAGE_UNEXPORT_FROM_PROCESS 0x5FCE8

#define KERNEL_SYMBOL_CREATE_MEMORY_CONTAINER  0x27258C
#define KERNEL_SYMBOL_DESTROY_MEMORY_CONTAINER 0x272008

#define KERNEL_SYMBOL_MEMSET 0x4D668
#define KERNEL_SYMBOL_MEMCPY 0x7E928
#define KERNEL_SYMBOL_MEMCHR 0x4C928
#define KERNEL_SYMBOL_MEMCMP 0x4C978

#define KERNEL_SYMBOL_STRLEN   0x4D83C
#define KERNEL_SYMBOL_STRCPY   0x4D814
#define KERNEL_SYMBOL_STRNCPY  0x4D8DC
#define KERNEL_SYMBOL_STRCAT   0x4D744
#define KERNEL_SYMBOL_STRCHR   0x4D77C
#define KERNEL_SYMBOL_STRRCHR  0x4D94C
#define KERNEL_SYMBOL_STRCMP   0x4D7C0
#define KERNEL_SYMBOL_STRNCMP  0x4D868

#define KERNEL_SYMBOL_PRINTF    0x270634
#define KERNEL_SYMBOL_SPRINTF   0x4EA90
#define KERNEL_SYMBOL_SNPRINTF  0x4E9FC
#define KERNEL_SYMBOL_VSNPRINTF 0x4EB60

#define KERNEL_SYMBOL_FS_OPEN_1 0x297ABC
#define KERNEL_SYMBOL_FS_OPEN_2 0x297888 // bytes matched: 0x1C  F821FF517C0802A6FB010070FB610088FBA10098FBC100A07C7D1B78
#define KERNEL_SYMBOL_FS_READ   0x29782C // bytes matched: 0x34  2C2600007C0802A63D208001F821FF71FBE10080F80100A07CDF33786129000D
#define KERNEL_SYMBOL_FS_WRITE  0x297798 // bytes matched: 0x24****  FB410080FB6100887CDA33787CBB2B78FB810090FBA100987C9C2378F80100C0
#define KERNEL_SYMBOL_FS_LSEEK  0x296E20 // bytes matched: 0x24****  FB410080FB6100887CDA33787C9B2378FB810090FBA100987CBC2B78F80100C0
#define KERNEL_SYMBOL_FS_STAT   0x2970A4 // bytes matched: 0x18  F821FF617C0802A6FB610078FBA10088FBC100907C7D1B78
#define KERNEL_SYMBOL_FS_CLOSE  0x29BD04 // bytes matched: 0x10  F821FF617C0802A6FBC10090EBC225B0

#define KERNEL_SYMBOL_PPU_THREAD_CREATE 0x13EC4 
#define KERNEL_SYMBOL_PPU_THREAD_JOIN   0x13FD0 
#define KERNEL_SYMBOL_PPU_THREAD_DELAY  0x287A0 
#define KERNEL_SYMBOL_PPU_THREAD_EXIT   0x13F7C 

#define KERNEL_SYMBOL_CREATE_USER_THREAD1 0x25258 
#define KERNEL_SYMBOL_CREATE_USER_THREAD2 0x2507C 
#define KERNEL_SYMBOL_REGISTER_THREAD     0x2678D4
#define KERNEL_SYMBOL_START_THREAD        0x23D48
#define KERNEL_SYMBOL_RUN_THREAD          0x23578

#define KERNEL_SYMBOL_ALLOCATE_USER_STACK   0x2680BC
#define KERNEL_SYMBOL_DEALLOCATE_USER_STACK 0x268024

#define KERNEL_SYMBOL_COPY_FROM_USER    0xFA84
#define KERNEL_SYMBOL_COPY_TO_USER      0xF868
#define KERNEL_SYMBOL_COPY_FROM_PROCESS 0xF730
#define KERNEL_SYMBOL_COPY_TO_PROCESS   0xF920

#define KERNEL_SYMBOL_ID_TABLE_RESERVE_ID   0x8CD14
#define KERNEL_SYMBOL_ID_TABLE_UNRESERVE_ID 0x11910

#define KERNEL_SYMBOL_GET_OBJECT_COUNT 0x1140C
#define KERNEL_SYMBOL_GET_OBJECTS      0x11484

#define KERNEL_SYMBOL_PROCESS_SUB_8000000000003B38 0x3B38 //0x3B38

#define KERNEL_SYMBOL_PROCESS_READ_MEMORY                   0x267E48
#define KERNEL_SYMBOL_PROCESS_WRITE_MEMORY_EX               0x267CBC
#define KERNEL_SYMBOL_PROCESS_GET_INTERNAL_PPU_THREAD_COUNT 0x242C4
#define KERNEL_SYMBOL_PROCESS_GET_PARENT_PID                0x269488
#define KERNEL_SYMBOL_PROCESS_ALLOCATE_MAPPED_MEMORY_EX     0x76B74

#define KERNEL_SYMBOL_PRX_LOAD_MODULE   0x88C00
#define KERNEL_SYMBOL_PRX_START_MODULE  0x878CC
#define KERNEL_SYMBOL_PRX_STOP_MODULE   0x88CA4
#define KERNEL_SYMBOL_PRX_UNLOAD_MODULE 0x87600

#define KERNEL_SYMBOL_PRX_GET_MODULE_INFO          0x87088
#define KERNEL_SYMBOL_PRX_GET_MODULE_ID_BY_ADDRESS 0x86F98
#define KERNEL_SYMBOL_PRX_GET_MODULE_ID_BY_NAME    0x86FE8
#define KERNEL_SYMBOL_PRX_GET_MODULE_LIST          0x87108

#define KERNEL_SYMBOL_KERNEL_EA_TO_LPAR_ADDR     0x70148
#define KERNEL_SYMBOL_PROCESS_EA_TO_LPAR_ADDR_EX 0x7775C
#define KERNEL_SYMBOL_MAP_CONTIGUOUS_MEMORY      0x76534
#define KERNEL_SYMBOL_UNMAP_CONTIGUOUS_MEMORY    0x763AC

#define KERNEL_SYMBOL_SPIN_LOCK_IRQSAVE_EX    0x26D720
#define KERNEL_SYMBOL_SPIN_LOCK_IRQRESTORE_EX 0x26D6F4

#define KERNEL_SYMBOL_PANIC 0x26D550

#define KERNEL_SYMBOL_SYS_PROCESS_GETPID 0x1A210
#define KERNEL_SYMBOL_SYS_PROCESS_EXIT   0x1A4E0

#define KERNEL_SYMBOL_PROC_ID_TABLE_PTR 0x475680

#endif