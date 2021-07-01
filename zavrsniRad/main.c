#include <stdio.h>
#include <stdlib.h>
#include"header.h"
#include "dataType.h"


int main(){

    system("color 7");

    int n;
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*         ALBUM REPOSITORY        *\n");
    printf("*                                 *\n");
    printf("***********************************\n");
    do{
    printf("\n1) Add album \n");
    printf("2) Print all albums \n");
    printf("3) Delete album \n");
    printf("4) Print artist \n");
    printf("5) Print genre \n");
    printf("6) Album search \n");
    printf("7) Delete repository \n");
    printf("8) Search \n");
    printf("9) Save changes & Exit \n");


        do {
        printf("\nEnter number: ");
        scanf("%d", &n);
        getchar();
        }while (n<1 || n>9);

    switchCase(n);

    }while(n!=9);


    return 0;


}
