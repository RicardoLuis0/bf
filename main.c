#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>

#define STACKSIZE 128

#define TAPESIZE 0x1FFFE

uint32_t stack[STACKSIZE];
uint8_t tape[TAPESIZE];

int main(int argc,char ** argv) {
    uint32_t sp=0;
    uint32_t tp=0;
    FILE * f;
    if(argc==1){
        char buf[256];
        printf("Enter File: ");
        scanf("%s",buf);
        f=fopen(buf,"r");
        if(!f){
            fprintf(stderr,"Invalid Input File '%s'",buf);
            return 1;
        }
        system("cls");
    }else if(argc==2){
        f=fopen(argv[1],"r");
        if(!f){
            fprintf(stderr,"Invalid Input File '%s'",argv[1]);
            return 1;
        }
    }else{
        fprintf(stderr,"Too Many Arguments");
        return 1;
    }
    for(;;){
        switch(fgetc(f)){
        case '>'://forwards
            tp++;
            if(tp==TAPESIZE){
                tp=0;
                //fprintf(stderr,"TAPE OVERFLOW at %ld",ftell(f));
                //return 1;
            }
            break;
        case '<'://back
            if(tp==0){
                tp=TAPESIZE;
                //fprintf(stderr,"TAPE UNDERFLOW at %ld",ftell(f));
                //return 1;
            }
            tp--;
            break;
        case '+'://increment
            ++tape[tp];
            break;
        case '-'://decrement
            --tape[tp];
            break;
        case '.'://output
            fputc(tape[tp],stdout);
            break;
        case ','://input
            tape[tp]=getch();
            break;
        case '['://loop open
            if(tape[tp]){
                stack[sp++]=ftell(f);
                if(sp==STACKSIZE){
                    fprintf(stderr,"STACK OVERFLOW at %ld",ftell(f));
                    return 1;
                }
            }else{
                int b=1,c;
                while((c=fgetc(f)),(b>0)){
                    if(c=='[')b++;
                    else if(c==']')b--;
                }
            }
            break;
        case ']'://loop close
            if(sp==0){
                fprintf(stderr,"STACK UNDERFLOW at %ld",ftell(f));
                return 1;
            }
            if(tape[tp]){
                fseek(f,stack[sp-1],SEEK_SET);
            }else{
                sp--;
            }
            break;
        default://NOP
            break;
        }
    }
    return 1;
}
