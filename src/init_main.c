#include "init_main.h"
#include "public.h"

pthread_mutex_t g_mutex;
pthread_cond_t   g_cond;

void sighandler(int signo)
{
	int status;
	pthread_cond_signal(&g_cond);
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

void procsig()
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

inline void control(int argc, char **argv)
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