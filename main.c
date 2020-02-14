#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>

#define STACKSIZE 128
#define DATASIZE 0xFFFF //65535 data cells, statically allocated

uint32_t stack[STACKSIZE];
uint32_t data[DATASIZE];

int main(int argc,char ** argv) {
    uint32_t sp=0,dp=0;
    if(argc!=2){
        fputs("Invalid Argument Count",stderr);
        return 1;
    }
    FILE * f=fopen(argv[1],"r");
    if(!f){
        fputs("Invalid Input File",stderr);
        return 1;
    }
    for(;;){
        switch(fgetc(f)){
        case '>'://forwards
            //TODO
            break;
        case '<'://back
            //TODO
            break;
        case '+'://increment
            //TODO
            break;
        case '-'://decrement
            //TODO
            break;
        case '.'://output
            //TODO
            break;
        case ','://input
            //TODO
            break;
        case '['://loop open
            //TODO
            break;
        case ']'://loop close
            //TODO
            break;
        default://NOP
            break;
        }
    }
    return 1;
}
