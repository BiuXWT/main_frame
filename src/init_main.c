#include "init_main.h"
#include "public.h"

MainLck g_lock = { 0,PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,main_lock_wait,main_lock_signal };


inline void main_lock_wait(struct _main_lock* pthis)
{
	pthread_mutex_lock(&pthis->m_mutex);
	pthread_cond_wait(&pthis->m_cond, &pthis->m_mutex);
	pthread_mutex_unlock(&pthis->m_mutex);
}

inline void main_lock_signal(struct _main_lock * pthis)
{
	pthread_mutex_lock(&pthis->m_mutex);
	pthread_cond_signal(&pthis->m_cond);
	pthread_mutex_unlock(&pthis->m_mutex);
}

MainLck* get_g_lock()
{
	return &g_lock;
}

void sighandler(int signo)
{
	g_lock.signal(&g_lock);
	LOG("recv signal %d", signo);
}
void childsighandler(int signo)
{
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		LOG("child pid [%d] exit.", pid);
	}
}

void signal_init()
{
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGHUP, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGCHLD, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	sigaction(SIGTTIN, &act, NULL);
	sigaction(SIGTTOU, &act, NULL);
	sigaction(SIGTSTP, &act, NULL);

	act.sa_handler = childsighandler;
	sigaction(SIGCHLD, &act, NULL);

	act.sa_handler = sighandler;
	sigaction(SIGUSR1, &act, NULL);
}

inline void comand(int argc, char **argv)
{
	int lockfd;
	char szBuff[128];
	char szPid[128];
	int iRetVal;
	if (argc != 2)
	{
		LOG("Usage: %s <cmd> ", argv[0]);
		LOG("    start:        start %s. ", argv[0]);
		LOG("    stop:         stop %s. ", argv[0]);
		exit(0);
	}

	if (strcmp(argv[1], "start") == 0)
	{
		lockfd = open("./lockfile.lock", O_RDWR | O_CREAT, 0640);
		if (lockfd < 0)
		{
			LOG("start %s failure[open lock error]!!", argv[0]);
			exit(-1);
		}

		iRetVal = lockf(lockfd, F_TLOCK, 0);
		if (iRetVal < 0)
		{
			LOG("%s is already running!!", argv[0]);
			close(lockfd);
			exit(-1);
		}

		memset(szBuff, 0x00, sizeof(szBuff));
		sprintf(szBuff, "%6d\n", getpid());
		write(lockfd, szBuff, strlen(szBuff));
	}
	else if (strcmp(argv[1], "stop") == 0)
	{
		lockfd = open("./lockfile.lock", O_RDWR | O_CREAT, 0640);
		if (lockfd < 0)
		{
			LOG("stop %s failure[open lock error]!!", argv[0]);
			exit(-1);
		}
		memset(szPid, 0x00, sizeof(szPid));
		iRetVal = read(lockfd, szPid, sizeof(szPid));
		LOG("pid = %s", szPid);
		close(lockfd);
		kill(atoi(szPid), SIGUSR1);
		exit(0);
	}
	else
	{
		LOG("command error");
		exit(-1);
	}
}

int srv_init()
{

	return 0;
}

int srv_release()
{
	return 0;
}
