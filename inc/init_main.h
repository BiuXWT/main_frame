#ifndef _INIT_MAIN_H_
#define _INIT_MAIN_H_
void sighandler(int signo);

inline void childsighandler(int signo);

inline void procsig();

void control(int argc, char **argv);

#endif
