// so here is all offsets i founded.
// maybe something is wrong. who knows?
// btw wrong offsets gna make kernel panic.

#ifndef OFFSETS_H
#define OFFSETS_H

#define OFFSET_POP_RDI 0x000001C0
#define OFFSET_POP_RSI 0x00009520
#define OFFSET_POP_RDX 0x002BD500
#define OFFSET_POP_RAX 0x00366360
#define OFFSET_SYSCALL 0x000001C0
#define UART_PATCH 0x01A47F40
#define PMAP_PROTECT 0x00059DF0
#define PMAP_PROTECT_P 0x00059E37
#define PMAP_STORE 0x01B2C3A0
#define UART_PATCH 0x01A47F40
#define COPYIN_PATCH_1 0x002BD747
#define COPYIN_PATCH_2 0x002BD753
#define COPYOUT_PATCH_1 0x002BD652
#define COPYOUT_PATCH_2 0x002BD65E
#define COPYINSTR_PATCH_1 0x002BDBF3
#define COPYINSTR_PATCH_2 0x002BDBFF
#define COPYINSTR_PATCH_3 0x002BDC30
#define SETLOGIN_PATCH 0x003945CC
#define PFS_SIGNATURE_CHECK_PATCH 0x0069DF40
#define DEBUG_RIF_PATCH_1 0x0064F060
#define DEBUG_RIF_PATCH_2 0x0064F090
#define DEBUG_SETTINGS_ERROR_PATCH_1 0x004E8BF8
#define DEBUG_SETTINGS_ERROR_PATCH_2 0x004E9CBE
#define DEPTH_LIMIT_PATCH 0x00030F66
#define XFAST_SYSCALL 0x000001C0  
//kernel offset ↑
#define PRISON0 0x0111FA18
#define ROOTVNODE 0x02136E90
#define M_TEMP 0x01520D00
#define MINI_SYSCORE_SELF_BINARY 0x0153D6C8
#define ALLPROC 0x01B28538
#define SBL_DRIVER_MAPPED_PAGES 0x02647350
#define SBL_PFS_SX 0x0265C080
#define SBL_KEYMGR_KEY_SLOTS 0x02668040
#define SBL_KEYMGR_KEY_RBTREE 0x02668050
#define SBL_KEYMGR_BUF_VA 0x0266C000
#define SBL_KEYMGR_BUF_GVA 0x0266C808
#define FPU_CTX 0x026542C0
#define SYSENT 0x01102B70
#define memcmp 0x003946D0
#define _sx_xlock 0x000A3840
#define _sx_xunlock 0x000A3A00
#define malloc 0x00009520
#define free 0x000096E0
#define strstr 0x0021CCD0
#define fpu_kern_enter 0x001E0060
#define fpu_kern_leave 0x001E0120
#define memcpy 0x002BD500
#define memset 0x001FA1C0
#define strlen 0x0036AEF0
#define printf 0x002E0460
#define eventhandler_register 0x00224190
#define sceSblACMgrGetPathId 0x003B3230
#define sceSblServiceMailbox 0x0062FE30
#define sceSblAuthMgrSmIsLoadable2 0x0063CCA0
#define _sceSblAuthMgrGetSelfInfo 0x0063D4E0
#define _sceSblAuthMgrSmStart 0x0063E070
#define sceSblAuthMgrVerifyHeader 0x0063CD00
#define RsaesPkcs1v15Dec2048CRT 0x0021BC80
#define Sha256Hmac 0x001F8DC0
#define AesCbcCfb128Encrypt 0x003411F0
#define AesCbcCfb128Decrypt 0x00341420
#define sceSblDriverSendMsg_0 0x0061C470
#define sceSblPfsSetKeys 0x00626BB0
#define sceSblKeymgrSetKeyStorage 0x00624C10
#define sceSblKeymgrSetKeyForPfs 0x0062B500
#define sceSblKeymgrCleartKey 0x0062B840
#define sceSblKeymgrSmCallfunc 0x0062B0D0
#define vmspace_acquire_ref 0x002F72E0
#define vmspace_free 0x002F7110
#define vm_map_lock_read 0x002F7470
#define vm_map_unlock_read 0x002F74C0
#define vm_map_lookup_entry 0x002F7AB0
#define proc_rwmem 0x00366360
#define sceSblAuthMgrIsLoadable__sceSblACMgrGetPathId_hook 0x006424BC
#define sceSblAuthMgrIsLoadable2_hook 0x0064260E
#define sceSblAuthMgrVerifyHeader_hook1 0x00642DA6
#define sceSblAuthMgrVerifyHeader_hook2 0x00643A89
#define sceSblAuthMgrSmLoadSelfSegment__sceSblServiceMailbox_hook 0x006404BD
#define sceSblAuthMgrSmLoadSelfBlock__sceSblServiceMailbox_hook 0x006410F8
#define sceSblKeymgrSetKeyStorage__sceSblDriverSendMsg_hook 0x00624CB5
#define sceSblKeymgrInvalidateKey__sx_xlock_hook 0x0062C6BD
#define sceSblKeymgrSmCallfunc_npdrm_decrypt_isolated_rif_hook 0x0064CA10
#define sceSblKeymgrSmCallfunc_npdrm_decrypt_rif_new_hook 0x0064D7DE
#define mountpfs__sceSblPfsSetKeys_hook1 0x006A3339
#define mountpfs__sceSblPfsSetKeys_hook2 0x006A356A
#define sceSblRcMgrIsAllowDebugMenuForSettings_patch 0x0001D100
#define sceSblRcMgrIsStoreMode_patch 0x0001D460
#define CreateUserForIDU_patch 0x0018B3B0
#define remote_play_menu_patch 0x00EC8902
#define SceRemotePlay_patch1 0x000ED1F5
#define SceRemotePlay_patch2 0x000ED210
#define sceKernelIsGenuineCEX_patch1 0x0016F5A4
#define sceKernelIsGenuineCEX_patch2 0x00874C14
#define sceKernelIsGenuineCEX_patch3 0x008C4F32
#define sceKernelIsGenuineCEX_patch4 0x00A287E4
#define nidf_libSceDipsw_patch1 0x0016F5D2
#define nidf_libSceDipsw_patch2 0x0024E11C
#define nidf_libSceDipsw_patch3 0x00874C42
#define nidf_libSceDipsw_patch4 0x00A28812
#define check_disc_root_param_patch 0xDEADC0DE
#define app_installer_patch 0x001389A0
#define check_system_version 0x003CA3A7
#define check_title_system_update_patch 0x003CD5F0
#define enable_data_mount_patch 0x00323380
#define enable_psvr_patch 0x00DAFB80
#define enable_fpkg_patch 0x003DE07F
#define fake_free_patch 0x00FD13F9
#define pkg_installer_patch 0x00A11D31
#define ext_hdd_patch 0x0061465D
#define debug_trophies_patch 0x0074D5E9
#define disable_screenshot_patch 0x000D2216
#define proc_p_comm_offset 0x454
#define proc_path_offset 0x474


#endif


