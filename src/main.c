#include "public.h"

extern pthread_mutex_t  g_mutex ;
extern pthread_cond_t   g_cond ;


int main(int argc, char **argv)
{
    procsig();
    control(argc,argv);


    //TODO ... 功能处理


    //阻塞主线程
    pthread_mutex_lock(&g_mutex);
	pthread_cond_wait(&g_cond, &g_mutex);
	pthread_mutex_unlock(&g_mutex);

    //TODO ... 资源回收

    LOG("%s stopped...",argv[0]);

    return 0;
}
