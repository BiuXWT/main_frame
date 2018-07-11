#ifndef _WORK_PROCESS_H_
#define _WORK_PROCESS_H_
#include "public.h"

struct _work_process;

typedef	struct _work_process {
	//void(*init)(struct _work_process* pthis);
	pid_t(*get_pid)(struct _work_process* pthis);
	int(*start)(struct _work_process* pthis, char *szPsName);
	int(*stop)(struct _work_process* pthis);


	pid_t m_pid;
	char m_szPsName[64];
}WorkProcess, *lpWorkProcess;

void init_wp(lpWorkProcess pthis);

pid_t get_pid_wp(lpWorkProcess pthis);

int start_wp(lpWorkProcess pthis, char *szPsName);

int stop_wp(lpWorkProcess pthis);

#endif // !_WORK_PROCESS_H_
