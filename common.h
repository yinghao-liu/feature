#ifndef _COMMON_
#define _COMMON_
#define SYS_IPCSHM_KEY	            0x0FFFFFA0
typedef struct{
	char *parray;
	char array[8];
}shm_data;

#endif
