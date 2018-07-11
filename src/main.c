#include "public.h"
#include "usr_inc.h"

extern pthread_mutex_t  g_mutex ;
extern pthread_cond_t   g_cond ;


int main(int argc, char **argv)
{
    procsig();
    control(argc,argv);


    //TODO ... 功能处理
	WorkProcess work;
	init_wp(&work);
	work.get_pid(&work);
	work.start(&work, "ls");


    //阻塞主线程
    pthread_mutex_lock(&g_mutex);
	pthread_cond_wait(&g_cond, &g_mutex);
	pthread_mutex_unlock(&g_mutex);
	work.stop(&work);

    //TODO ... 资源回收

    LOG("%s stopped...",argv[0]);

    return 0;
}

