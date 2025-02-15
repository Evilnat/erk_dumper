#include "payload.h"
#include "hvcall.h"
#include "mm.h"

#include <sys/memory.h>
#include <sys/paths.h>
#include <sys/process.h>
#include <sys/return_code.h>

#include <cell/sysmodule.h>
#include <cell/cell_fs.h>

#include <sysutil/sysutil_common.h>
#include <sysutil/sysutil_sysparam.h>
#include <sysutil/sysutil_game_common.h>
#include <sysutil/sysutil_gamecontent.h>

#define EID_ROOT_KEY_FILE_NAME "eid_root_key"

static uint8_t eid_root_key[EID_ROOT_KEY_SIZE];

static int make_patches(void) {
	/******************* LV1 Patches *******************/

	//commented in 4.50, patched in 4.65
	/* allow mapping of HTAB with write protection */
	//41 DA 00 54 E9 7F 00 A8
	lv1_poke64(0x2DD70C, 0x60000000E97F00A8ULL);

	/* allow mapping of any needed memory area */
	//2F 80 00 00 41 9E 00 28
	//39 20 00 00 4B FF FB FD
	lv1_poke64(0x2DCF54, 0x6000000048000028ULL);
	lv1_poke64(0x2DD284, 0x392000014BFFFBFDULL);

	/* allow setting all bits of SPE register MFC_SR1 */
	//39 20 00 09 E9 43 00 00
	lv1_poke64(0x2F9EB8, 0x3920FFFFE9430000ULL);

	/* change region size for lv2 hmac hash calculation, not needed since most mfw support it */
	//00 00 00 00 00 00 00 01 
	//E0 D2 51 B5 56 C5 9F 05 
	//C2 32 FC AD 55 2C 80 D7 
	//65 14 0C D2 00 00 00 00
	//lv1_poke64(0x370F28, 0x0000000000000001ULL);
	//lv1_poke64(0x370F30, 0xE0D251B556C59F05ULL);
	//lv1_poke64(0x370F38, 0xC232FCAD552C80D7ULL);
	//lv1_poke64(0x370F40, 0x65140CD200000000ULL);

	/******************* LV2 Patches *******************/

	/* permission patch */
	//F8 21 FE B1 7C 08 02 A6  FB 81 01 30 7C 9C 23 78
	//doesn't change location
	lv2_poke64(0x8000000000003D90ULL, 0x386000014E800020ULL);

	/* remove page protection bits from htab entries */
	patch_htab_entries(0);

	return 0;
}

static int dump_eid_root_key(const char* file_path) {
	int result;

	FILE* fp;
//	int poke_installed;
	int payload_installed;

	//poke_installed = 0;
	payload_installed = 0;

	/*debug_printf("install_new_poke()\n");
	result = install_new_poke();
	if (result != 0) {
		debug_printf("install_new_poke() failed: 0x%08X\n", result);
		goto error;
	}
	poke_installed = 1;*/

	debug_printf("make_patches()\n");
	result = make_patches();
	if (result != 0) {
		debug_printf("make_patches() failed: 0x%08X\n", result);
		goto error;
	}


	debug_printf("install_payload()\n");
	result = install_payload();

	if (result != 0) {
		debug_printf("install_payload() failed: 0x%08X\n", result);
		goto error;
	}
	payload_installed = 1;

	memset(eid_root_key, 0, EID_ROOT_KEY_SIZE);

	debug_printf("run_payload()\n");
	result = run_payload((uintptr_t)eid_root_key, EID_ROOT_KEY_SIZE);
	if (result != 0) {
		debug_printf("run_payload() failed: 0x%08X\n", result);
		goto error;
	}

	debug_printf("fopen()\n");
	fp = fopen(file_path, "wb");
	if (!fp) {
		result = errno;
		debug_printf("fopen() failed: 0x%08X\n", result);
		goto error;
	}

	debug_printf("fwrite()\n");
	fwrite(eid_root_key, 1, EID_ROOT_KEY_SIZE, fp);

	debug_printf("fclose()\n");
	fclose(fp);

	result = 0;

error:
	if (payload_installed) {
		debug_printf("remove_payload()\n");
		result = remove_payload();
		if (result != 0)
			debug_printf("remove_payload() failed: 0x%08X\n", result);
	}

	/*if (poke_installed) {
		debug_printf("remove_new_poke()\n");
		result = remove_new_poke();
		if (result != 0)
			debug_printf("remove_new_poke() failed: 0x%08X\n", result);
	}*/

	return result;
}

SYS_PROCESS_PARAM(1001, 0x10000)

int main(void) {
	int result;

	char dump_file_path[CELL_GAME_PATH_MAX];
	char content_info_path[CELL_GAME_PATH_MAX];
	char usrdir_path[CELL_GAME_PATH_MAX];
	unsigned int type, attributes;
	int dumped;

	dumped = 0;

	result = cellSysmoduleLoadModule(CELL_SYSMODULE_IO);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleLoadModule(CELL_SYSMODULE_IO) failed: 0x%08X\n", result);
		goto error;
	}

	result = cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleLoadModule(CELL_SYSMODULE_FS) failed: 0x%08X\n", result);
		goto error;
	}

	result = cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL) failed: 0x%08X\n", result);
		goto error;
	}

	result = cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_GAME);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_GAME) failed: 0x%08X\n", result);
		goto error;
	}

	result = cellGameBootCheck(&type, &attributes, NULL, NULL);
	if (result != CELL_OK) {
		debug_printf("cellGameBootCheck() failed: 0x%08X\n", result);
		goto error;
	}

	if (type == CELL_GAME_GAMETYPE_HDD) {
		result = cellGameContentPermit(content_info_path, usrdir_path);
		if (result != CELL_OK) {
			debug_printf("cellGameContentPermit() failed: 0x%08X\n", result);
			goto error;
		}

		snprintf(dump_file_path, sizeof(dump_file_path), "%s/%s", usrdir_path, EID_ROOT_KEY_FILE_NAME);
		dumped = dump_eid_root_key(dump_file_path) == 0;
		console_printf("Dump file path: %s\n", dump_file_path);
	} else {
		console_printf("Error! The application type is not a HDD boot game!\n");
	}

	result = cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_GAME);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_GAME) failed: 0x%08X\n", result);
		goto error;
	}

	result = cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL) failed: 0x%08X\n", result);
		goto error;
	}

	if (dumped) {
		debug_printf("cellFsUnlink()\n");
		cellFsUnlink("/dev_hdd0/tmp/turnoff");

		debug_printf("triple_beep()\n");
		triple_beep();
	}

	result = cellSysmoduleUnloadModule(CELL_SYSMODULE_FS);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleUnloadModule(CELL_SYSMODULE_FS) failed: 0x%08X\n", result);
		goto error;
	}

	result = cellSysmoduleUnloadModule(CELL_SYSMODULE_IO);
	if (result != CELL_OK) {
		debug_printf("cellSysmoduleUnloadModule(CELL_SYSMODULE_IO) failed: 0x%08X\n", result);
		goto error;
	}

	if (dumped) {
		debug_printf("reboot()\n");
		reboot();
	}

	result = 0;

error:
	sys_process_exit(result);

	return result;
}
