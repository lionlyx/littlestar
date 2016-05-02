#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

long position_seek();

int main()
{
int op,wr1,wr2;
long i,length;
char c;
op = open("file",O_RDWR);
wr1 = open("file.0",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
wr2 = open("file.1",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
length = position_seek();
length = length/2;
for (i=0;i<length;i++)
{    read(op,&c,1);
     write(wr1,&c,1);
}
while (read(op,&c,1) == 1)
     write(wr2,&c,1);
exit(0);
}

long position_seek()
{  
 long n;
 int fp;
 fp = open("file",O_RDONLY);
  n = lseek(fp,0,SEEK_END);
close(fp);
return n;
}


