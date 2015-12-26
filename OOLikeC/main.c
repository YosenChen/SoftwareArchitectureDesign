#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "CircularList\CircularQ.h"
#include "CircularList\CircularList.h"


int main(void)
{
    FILE *fp = fopen("out.txt", "w");
    struct CircularList st;
    struct CircularList* tmp;
    struct CircularQ q;

    int a = 10, b=100, c=1000, h;
    char d = 'd', e = 'e', f = 'f', g = 'g', j = 65;
    int out, ret;
    BOOL chk;

    printf("This is OO-like C program test\n");

    if (!fp) 
    {
        printf("Error opening .txt file!\n");
        system("pause");
    }
    //#define LOG(str, ...) printf(str, __VA_ARGS__)
    #define LOG(str, ...) fprintf(fp, str, __VA_ARGS__)
   
    LOG("======================stack/queue implememtation using array====================\n");

    CircularList_ctor(&st, 3);
    tmp = CircularList_operator_new(3);
    LOG("st.getSize()=%d, st.isEmpty()=%d, st.isFull()=%d\n"
		, st._base.getSize((struct CircularQ*)&st)
		, st._base.isEmpty((struct CircularQ*)&st)
		, st._base.isFull((struct CircularQ*)&st));

    chk = st.push(&st, 5); LOG("push chk = %d, ", chk);
    st.push(&st, a); st.push(&st, b); chk = st.push(&st, c); LOG("push chk = %d\n", chk);
    for (;!st._base.isEmpty((struct CircularQ*)&st);)
    {
        st.pop(&st, &h);
        LOG("st.pop h=%d st.getSize()=%d, \n", h, st._base.getSize((struct CircularQ*)&st));
    }
    ret = st.pop(&st, &h);
    LOG("when Empty, st.pop(h)=%d, h=%d\n", ret, h);
    LOG("st.getSize()=%d, st.isEmpty()=%d, st.isFull()=%d\n"
		, st._base.getSize((struct CircularQ*)&st)
		, st._base.isEmpty((struct CircularQ*)&st)
		, st._base.isFull((struct CircularQ*)&st));



    CircularQ_ctor(&q, 3);
    LOG("q.getSize()=%d, q.isEmpty()=%d, q.isFull()=%d\n", q.getSize(&q), q.isEmpty(&q), q.isFull(&q));
    q.enQ(&q, 'a'); q.enQ(&q, 'b'); q.enQ(&q, 'c');
    LOG("q.isFull() = %d\n", q.isFull(&q));
    for (; !q.isEmpty(&q); )
    {
        q.deQ(&q, &out);
        LOG("q.deQue out=%c q.getSize()=%d, \n", out, q.getSize(&q));
    }
    LOG("2nd round test: \n");
    q.enQ(&q, d); q.enQ(&q, e); q.deQ(&q, &out); q.enQ(&q, f); q.deQ(&q, &out); q.enQ(&q, g); q.enQ(&q, j); q.enQ(&q, j);
    for (; !q.isEmpty(&q); )
    {
        q.deQ(&q, &out);
        LOG("q.deQue out=%c q.getSize()=%d, \n", out, q.getSize(&q));
    }

    CircularList_dtor(&st);
    CircularList_operator_delete(tmp);

    CircularQ_dtor(&q);

	printf("\n\n\n");











    fclose(fp);

    getchar();
    return 0;
}
