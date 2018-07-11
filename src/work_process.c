#include "work_process.h"


void init_wp(lpWorkProcess pthis) {
	pthis->m_pid = 0;
	bzero(pthis->m_szPsName, sizeof(pthis->m_szPsName));
	pthis->get_pid = get_pid_wp;
	pthis->start = start_wp;
	pthis->stop = stop_wp;
}


pid_t get_pid_wp(lpWorkProcess pthis) {
	return pthis->m_pid;
}

int start_wp(lpWorkProcess pthis, char *szPsName) {
	pid_t pid;
	bzero(pthis->m_szPsName, sizeof(pthis->m_szPsName));
	strncpy(pthis->m_szPsName, szPsName, strlen(szPsName));
	if ((pid = fork()) < 0) {
		LOG("WorkProcess fork error");
		return -1;
	}
	if (pid == 0)
	{
		LOG("workps name : [%s]", pthis->m_szPsName);
		int execret = execlp(pthis->m_szPsName, pthis->m_szPsName, NULL);
		if (execret != 0) {
			LOG("%s", strerror(errno));
			exit(1);
		}
	}
	else {
		pthis->m_pid = pid;
		LOG("work ps pid = %d", pthis->m_pid);
	}
	return 0;
}

int stop_wp(lpWorkProcess pthis) {
	if (pthis->m_pid <= 0)
	{
		LOG("no work ps running");
		return -1;
	}
	kill(pthis->m_pid, SIGUSR1);
	return 0;
}
