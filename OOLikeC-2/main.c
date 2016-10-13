#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Interface.h"


int main(void)
{
    FILE *fp = fopen("out.txt", "w");
    struct Interface *pInterfaceA = 0, *pInterfaceB = 0;
    struct Interface *pInterfaceA_2 = 0, *pInterfaceB_2 = 0;

    printf("This is OO-like C program test\n");

    if (!fp) 
    {
        printf("Error opening .txt file!\n");
        system("pause");
    }
    //#define LOG(str, ...) printf(str, __VA_ARGS__)
    #define LOG(str, ...) fprintf(fp, str, __VA_ARGS__)

    printf("====================visual function and abstract class in C===================\n"
           "=== create-on-demand version ===\n");
    pInterfaceA = createInterface(EImpType_A);
    pInterfaceB = createInterface(EImpType_B);
    pInterfaceA_2 = createInterface(EImpType_A);
    pInterfaceB_2 = createInterface(EImpType_B);

    pInterfaceA->enter(pInterfaceA, 65);
    pInterfaceA->execute(pInterfaceA, "A is here!");
    pInterfaceA->exit(pInterfaceA);

    pInterfaceB->enter(pInterfaceB, 66);
    pInterfaceB->execute(pInterfaceB, "B is here!");
    pInterfaceB->exit(pInterfaceB);

    destroyInterface(&pInterfaceA, EImpType_A);
    destroyInterface(&pInterfaceB, EImpType_B);
    destroyInterface(&pInterfaceA_2, EImpType_A);
    destroyInterface(&pInterfaceB_2, EImpType_B);



    printf("\n\n=== static version (Singleton) ===\n");

    pInterfaceA = initStaticInterface(EImpType_A);
    pInterfaceB = initStaticInterface(EImpType_B);

    pInterfaceA->enter(pInterfaceA, 65);
    pInterfaceA->execute(pInterfaceA, "A is here!");
    pInterfaceA->exit(pInterfaceA);

    pInterfaceB->enter(pInterfaceB, 66);
    pInterfaceB->execute(pInterfaceB, "B is here!");
    pInterfaceB->exit(pInterfaceB);

    uninitStaticInterface(&pInterfaceA, EImpType_A);
    uninitStaticInterface(&pInterfaceB, EImpType_B);

    printf("\n\n\n");

    fclose(fp);

    getchar();
    return 0;
}
