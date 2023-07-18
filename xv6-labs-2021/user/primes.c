#include "kernel/types.h"
#include "user/user.h"
#include "stddef.h"

void mapping(int n,int p[2]){
    close(n);
    dup(p[n]);
    close(p[0]);
    close(p[1]);
}

void prime(){
    int pre,next;
    int p[2];
    if(read(0,&pre,sizeof(pre)) != 0){
        printf("prime %d\n",pre);
        pipe(p);
        if(fork() == 0){
            mapping(1,p);
            while(read(0,&next,sizeof(next)) != 0){
                if(next % pre != 0){
                    write(1,&next,sizeof(next));
                }
            }
        } else{
            wait(NULL);
            mapping(0,p);
            prime();
        }
    }
}

int main(int argc,char* argv[]){
    if(argc != 1){
        fprintf(2,"usage primes\n");
        exit(1);
    }
    int p[2];
    pipe(p);
    if(fork() == 0){
        mapping(1,p);
        for(int i = 2;i <= 35;i++){
            write(1,&i,sizeof(i));
        }
    } else{
        wait(NULL);
        mapping(0,p);
        prime();
    }
    exit(0);
}