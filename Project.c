#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "Project.h"
#define N 12


int main(){
   int fd;

   write_f(fd);
   read_f(fd);

   return 0;
}

void write_f(int fd){
    const char *buf = "file system";
    ssize_t wr = 0;

    fd = open_f(fd);
    wr = write(fd, buf, strlen(buf));

    if(wr == -1){

        switch(errno)
      {
         case EBADF:
            perror("Bad file descriptor!");
            break;
         case ENOSPC:
            perror("No space left on device!");
            break;
         case EINVAL:
            perror("Invalid parameter: buffer was NULL!");
            break;
         default:
            perror("Unexpected error!");
      }
    }

    close(fd);
}

void read_f(int fd){	
    char buf[N];
    ssize_t re = 0;
    off_t ret = 0;

    fd = open_f(fd);

    for(int i = 0; i <= N; i++ ){
        ret = lseek(fd, -i, SEEK_END);
        
	if(ret == -1){
            perror( "lseek to end failed" );
         }

        re = read(fd, buf, 1);
        
	if(re == -1){
            perror( "Problem reading file" );
        }

    printf( " %s\n",buf);
    }

    close(fd);
}

int open_f(int fd){
    fd = open("text", O_RDWR);
    if(fd == -1){
        perror( "Open failed on input file" );
    }
    return fd;
}
