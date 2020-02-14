#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

bool valid_char(char c){
    switch(c){
    case '>'://forwards
    case '<'://back
    case '+'://increment
    case '-'://decrement
    case '.'://output
    case ','://input
    case '['://loop open
    case ']'://loop close
        return true;
    default://NOP
        return false;
    }
}

program_t * newProgram(const char * filename){
    FILE * f=fopen(filename,"r");
    if(!f){
        fprintf(stderr,"Cannot Open File '%s'",filename);
        exit(1);
    }
    uint32_t len=0;
    for(int c=fgetc(f);c!=EOF;c=fgetc(f)){
        if(valid_char(c))len++;
    }
    fseek(f,0,SEEK_SET);
    program_t * p=calloc(1,sizeof(program_t)+len);
    p->len=len;
    len=0;
    for(int c=fgetc(f);c!=EOF;c=fgetc(f)){
        if(valid_char(c)){
            p->data[len++]=c;
        }
    }
    return p;
}

void deleteProgram(program_t * p){
    free(p);
}

static inline int next(program_t * p){
    if(p->pc==p->len)exit(0);
    return p->data[p->pc++];
}

void programStep(program_t * p){
    switch(next(p)){
    case '>'://forwards
        p->tp++;
        if(p->tp==TAPESIZE){
            p->tp=0;
            //fprintf(stderr,"TAPE OVERFLOW");
            //exit(1);
        }
        break;
    case '<'://back
        if(p->tp==0){
            p->tp=TAPESIZE;
            //fprintf(stderr,"TAPE UNDERFLOW");
            //exit(1);
        }
        p->tp--;
        break;
    case '+'://increment
        ++p->tape[p->tp];
        break;
    case '-'://decrement
        --p->tape[p->tp];
        break;
    case '.'://output
        fputc(p->tape[p->tp],stdout);
        //printf(":%d\n",(int)p->tape[p->tp]);
        break;
    case ','://input
        p->tape[p->tp]=getch();
        break;
    case '['://loop open
        if(p->tape[p->tp]){
            p->stack[p->sp++]=p->pc;
            if(p->sp==STACKSIZE){
                fprintf(stderr,"STACK OVERFLOW");
                exit(1);
            }
        }else{
            int b=1,c;
            while((c=next(p)),(b>0)){
                if(c=='[')b++;
                else if(c==']')b--;
            }
        }
        break;
    case ']'://loop close
        if(p->sp==0){
            fprintf(stderr,"STACK UNDERFLOW");
            exit(1);
        }
        if(p->tape[p->tp]){
            p->pc=p->stack[p->sp-1];
        }else{
            p->sp--;
        }
        break;
    default://NOP
        break;
    }
}
