// use 2 threads to print "ping" and "pong" alternately
#include <cstdio>
#include <pthread.h>

#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

class Autolock
{
public: 
    Autolock(pthread_mutex_t* mtx) : mpMtx(mtx) {pthread_mutex_lock(mpMtx);}
    ~Autolock() {pthread_mutex_unlock(mpMtx);}
private:
    pthread_mutex_t* mpMtx;
};

// pthread interfaces
// int pthread_join(pthread_t thread, void **retval);
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);
// int pthread_attr_init(pthread_attr_t *attr);

//autolock

// forward declaration
#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void display_pthread_attr(pthread_attr_t *attr, const char *prefix);

pthread_mutex_t mtx_pingpong = PTHREAD_MUTEX_INITIALIZER;

static int flag_pingpong = 0; //0 for ping, 1 for PONG
static int flag_disp = 1; //0 for thread1 disp, 1 for thread2 disp

void* threadLoop1(void* arg)
{
    int cnt = 0;
    while(1) 
    { 
        Autolock autolock(&mtx_pingpong);
        
        if (flag_pingpong != 0) continue;
        
        //flag_pingpong is 0
        printf("ping ");
        flag_pingpong = 1;
        //usleep(1000);
        if (++cnt>=30) break;
    }
    while(1)
    {
        Autolock autolock(&mtx_pingpong); //lock for displaying data
        // now ping is done
        if (flag_disp != 0) continue;
        // flag_disp is 0, which means thread2 disp done
        display_pthread_attr((pthread_attr_t*)arg, "[thread1]");
        break;
    }
    return NULL;
}

void* threadLoop2(void* arg)
{
    int cnt = 0;
    while (1) 
    { 
        Autolock autolock(&mtx_pingpong);

        if (flag_pingpong != 1) continue;

        //flag_pingpong is 1
        printf("PONG\n");
        flag_pingpong = 0;
        //usleep(1000);
        if (++cnt>=30) break;
    }
    //while (1)
    {
        Autolock autolock(&mtx_pingpong); //lock for displaying data
        //now PONG is done, so ping is also done, and flag_disp is 1 (initial value)
        display_pthread_attr((pthread_attr_t*)arg, "[thread2]");
        flag_disp = 0;
    }
    return NULL;
}


int main(void)
{
    pthread_attr_t attr1, attr2;
    pthread_t thd_id1, thd_id2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    int s = pthread_attr_setstacksize(&attr1, 0x10000);
    if (s) handle_error_en(s, "pthread_attr_setstacksize");
    s = pthread_attr_setstacksize(&attr2, 0x10000);
    if (s) handle_error_en(s, "pthread_attr_setstacksize");
    pthread_create(&thd_id1, &attr1, threadLoop1, &attr1);
    pthread_create(&thd_id2, &attr2, threadLoop2, &attr2);
    pthread_join(thd_id1, NULL);
    pthread_join(thd_id2, NULL);
    printf("all done.\n");
    return 0;
}




// reference of display_pthread_attr
// http://man7.org/linux/man-pages/man3/pthread_attr_init.3.html

static void
display_pthread_attr(pthread_attr_t *attr, const char *prefix)
{
   int s, i;
   size_t v;
   void *stkaddr;
   struct sched_param sp;

   s = pthread_attr_getdetachstate(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getdetachstate");
   printf("%sDetach state        = %s\n", prefix,
           (i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
           (i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
           "???");

   s = pthread_attr_getscope(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getscope");
   printf("%sScope               = %s\n", prefix,
           (i == PTHREAD_SCOPE_SYSTEM)  ? "PTHREAD_SCOPE_SYSTEM" :
           (i == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" :
           "???");

   s = pthread_attr_getinheritsched(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getinheritsched");
   printf("%sInherit scheduler   = %s\n", prefix,
           (i == PTHREAD_INHERIT_SCHED)  ? "PTHREAD_INHERIT_SCHED" :
           (i == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" :
           "???");

   s = pthread_attr_getschedpolicy(attr, &i);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getschedpolicy");
   printf("%sScheduling policy   = %s\n", prefix,
           (i == SCHED_OTHER) ? "SCHED_OTHER" :
           (i == SCHED_FIFO)  ? "SCHED_FIFO" :
           (i == SCHED_RR)    ? "SCHED_RR" :
           "???");

   s = pthread_attr_getschedparam(attr, &sp);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getschedparam");
   printf("%sScheduling priority = %d\n", prefix, sp.sched_priority);

   s = pthread_attr_getguardsize(attr, &v);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getguardsize");
   printf("%sGuard size          = %d bytes\n", prefix, v);

   s = pthread_attr_getstack(attr, &stkaddr, &v);
   if (s != 0)
       handle_error_en(s, "pthread_attr_getstack");
   printf("%sStack address       = %p\n", prefix, stkaddr);
   printf("%sStack size          = 0x%zx bytes\n", prefix, v);
}
