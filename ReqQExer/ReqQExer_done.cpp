#include <cstdio>
#include <pthread.h>
#include <list>
#include <unistd.h> // for usleep(useconds_t usec);

using namespace std;

class Autolock
{
public: 
    Autolock(pthread_mutex_t* mtx) : mpMtx(mtx) {pthread_mutex_lock(mpMtx);}
    ~Autolock() {pthread_mutex_unlock(mpMtx);}
private:
    pthread_mutex_t* mpMtx;
};

struct Req_T
{
    int idx;
    int val;
    Req_T():idx(-1),val(0){}
    Req_T(int i, int v):idx(i),val(v){}
};

inline void ssleep(float sec) {usleep(1000000.0*sec);}

class ReqQExer
{
public:
    ReqQExer()
    : mMtx(PTHREAD_MUTEX_INITIALIZER)
    , mCond(PTHREAD_COND_INITIALIZER)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&mThd, &attr, reqQExeLoop, this);
        printf("[%s]\n", __FUNCTION__);
    }
    
    ~ReqQExer()
    {
        printf("[%s]\n", __FUNCTION__);
        pthread_join(mThd, NULL);
    }
    
    void enQReq(Req_T const &rReq)
    {
        Autolock autolock(&mMtx);
        printf("[%s] +\n", __FUNCTION__);
        mReqQ.push_back(rReq);
        pthread_cond_broadcast(&mCond);
        printf("[%s] -\n", __FUNCTION__);
    }
    
    bool deQReq(Req_T &rReq)
    {
        Autolock autolock(&mMtx);
        printf("[%s] +, size(%d)\n", __FUNCTION__, mReqQ.size());
        if (!mReqQ.size()) pthread_cond_wait(&mCond, &mMtx);
        
        rReq = mReqQ.front();
        mReqQ.pop_front();
        printf("[%s] - Req#%d = %d\n", __FUNCTION__, rReq.idx, rReq.val);
        if (rReq.val == -1) return false;
        else return true;
    }
    
    void executeReq(Req_T req)
    {
        printf("[%s] Req#%d = %d) +\n", __FUNCTION__, req.idx, req.val);
        ssleep(0.5); // 0.5 secs
        printf("[%s] -\n", __FUNCTION__);
    }
    
    static void* reqQExeLoop(void* arg)
    {
        Req_T rReq;
        ReqQExer* _this = (ReqQExer*)arg;
        printf("[%s] +\n", __FUNCTION__);
        while(_this->deQReq(rReq))
        {
            _this->executeReq(rReq);
        }
        printf("[%s] -\n", __FUNCTION__);
        return NULL;
    }
    
private:
    pthread_mutex_t mMtx;
    list<Req_T> mReqQ;
    pthread_cond_t mCond;
    pthread_t mThd;
};

int main()
{
    Req_T a(1,1), b(2,2), c(3,3), d(4,4), e(5,5), f(6,-1);
    {
        ReqQExer reqQE;
        ssleep(1);
        reqQE.enQReq(a);
        reqQE.enQReq(b);
        reqQE.enQReq(c);
        ssleep(3);
        reqQE.enQReq(d);
        ssleep(2);
        reqQE.enQReq(e);
        reqQE.enQReq(f);
    }
    getchar();
    return 0;
}

/*
How to compile it?
g++ -pthread -o ReqQExer ReqQExer_done.cpp 2>&1 | tee build.log

-------------- result ---------------

idfs@idfs-K42Jr:~/GitHubWorkSpace/SoftwareArchitectureDesign/ReqQExer$ ./ReqQExer 
[ReqQExer]
[reqQExeLoop] +
[deQReq] +, size(0)
[enQReq] +
[enQReq] -
[enQReq] +
[enQReq] -
[enQReq] +
[enQReq] -
[deQReq] - Req#1 = 1
[executeReq] Req#1 = 1) +
[executeReq] -
[deQReq] +, size(2)
[deQReq] - Req#2 = 2
[executeReq] Req#2 = 2) +
[executeReq] -
[deQReq] +, size(1)
[deQReq] - Req#3 = 3
[executeReq] Req#3 = 3) +
[executeReq] -
[deQReq] +, size(0)
[enQReq] +
[enQReq] -
[deQReq] - Req#4 = 4
[executeReq] Req#4 = 4) +
[executeReq] -
[deQReq] +, size(0)
[enQReq] +
[enQReq] -
[enQReq] +
[enQReq] -
[~ReqQExer]
[deQReq] - Req#5 = 5
[executeReq] Req#5 = 5) +
[executeReq] -
[deQReq] +, size(1)
[deQReq] - Req#6 = -1
[reqQExeLoop] -

idfs@idfs-K42Jr:~/GitHubWorkSpace/SoftwareArchitectureDesign/ReqQExer$ 


*/
