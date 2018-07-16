#include "public.h"
#include "usr_inc.h"

extern MainLck g_lock;

int main(int argc, char **argv)
{
	signal_init();
	comand(argc,argv);


    //TODO ... 功能处理
	WorkProcess work;
	init_wp(&work);
	work.get_pid(&work);
	work.start(&work, "ls");


    //阻塞主线程
	g_lock.wait(&g_lock);
	work.stop(&work);

    //TODO ... 资源回收

    LOG("%s stopped...",argv[0]);

    return 0;
}

