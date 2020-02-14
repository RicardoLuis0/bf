#include <stdio.h>
#include <stdlib.h>

#include "program.h"

int main(int argc,char ** argv) {
    program_t * p;
    if(argc==1){
        char buf[256];
        printf("Enter File: ");
        scanf("%s",buf);
        p=newProgram(buf);
        system("cls");
    }else if(argc==2){
        p=newProgram(argv[1]);
    }else{
        fprintf(stderr,"Too Many Arguments");
        return 1;
    }
    for(;;){
        programStep(p);
    }
    return 1;
}
