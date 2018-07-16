#ifndef _INIT_MAIN_H_
#define _INIT_MAIN_H_
#include<pthread.h>

typedef struct _main_lock
{
	int _running;
	pthread_mutex_t m_mutex;
	pthread_cond_t  m_cond;
	void(*wait)(struct _main_lock* pthis);
	void(*signal)(struct _main_lock* pthis);
}MainLck;

void main_lock_wait(struct _main_lock* pthis);
void main_lock_signal(struct _main_lock* pthis);


MainLck* get_g_lock();

void sighandler(int signo);

inline void childsighandler(int signo);

inline void signal_init();

void comand(int argc, char **argv);

int srv_init();

int srv_release();

#endif
