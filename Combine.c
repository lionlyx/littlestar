#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
int wr,rd1,rd2;
char c;
rd1 = open("file.0",O_RDWR);
rd2 = open("file.1",O_RDWR);
wr = open("file.cm",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);

while (read(rd1,&c,1) == 1)
     write(wr,&c,1);

while (read(rd2,&c,1) == 1)
     write(wr,&c,1);
exit(0);
}

