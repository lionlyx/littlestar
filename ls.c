#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
void do_ls(char[]);
void dostat(char *);
void show_file_info(char *,struct stat *);
void mode_to_letters(int,char[]);
char * uid_to_name(uid_t);
char * gid_to_name(gid_t);

void main(int argc,char *argv[]){
    if(argc==1)
        do_ls(".");
    else
        printf("ÊäÈëÃüÁî./lsŒŽ¿É£¬²»ÒªŽøÈÎºÎ²ÎÊý¡£\n");
}

void do_ls(char dirname[]){
    DIR *dir_ptr;   //Â·Ÿ¶±äÁ¿
    struct dirent *direntp;     //ŽæŽ¢Â·Ÿ¶ÏÂÒ»žö×ÓÏîÐÅÏ¢µÄœá¹¹Ìå
    if((dir_ptr=opendir(dirname))==0)
        fprintf(stderr,"ls:cannot open %s\n",dirname);
    else{
        while((direntp=readdir(dir_ptr))!=0)
            dostat(direntp->d_name);
        closedir(dir_ptr);
    }
}

void dostat(char *filename){
    struct stat info;
    if(lstat(filename,&info)==-1)
        perror("lstat");
    else
        show_file_info(filename,&info);
}

void show_file_info(char *filename,struct stat *info_p){
    char modestr[11];
    mode_to_letters(info_p->st_mode,modestr);
    printf("%-12s",modestr);
    printf("%-4d",(int)info_p->st_nlink);
    printf("%-8s",uid_to_name(info_p->st_uid));
    printf("%-8s",gid_to_name(info_p->st_gid));
    printf("%-8ld",(long)info_p->st_size);
    time_t timelong=info_p->st_mtime;
    struct tm *htime=localtime(&timelong);
    printf("%-4d-%02d-%02d %02d:%02d",htime->tm_year+1990,htime->tm_mon+1,htime->tm_mday,htime->tm_hour,htime->tm_min);
    printf(" %s\n",filename);
}

/*Õâžöº¯ÊýÐŽµÃ²»¹»È«Ãæ£¬Ê×ÏÈÎÄŒþÀàÐÍ²»È«£¬ÆäŽÎÃ»ÓÐ¿ŒÂÇsuid,sgid,sticky*/
void mode_to_letters(int mode,char str[]){
    strcpy(str,"----------");
    if(S_ISDIR(mode))   str[0]='d';
    if(S_ISCHR(mode))   str[0]='c';
    if(S_ISBLK(mode))   str[0]='b';

    if(mode & S_IRUSR)  str[1]='r';
    if(mode & S_IWUSR)  str[2]='w';
    if(mode & S_IXUSR)  str[3]='x';

    if(mode & S_IRGRP)  str[4]='r';
    if(mode & S_IWGRP)  str[5]='w';
    if(mode & S_IXGRP)  str[6]='x';

    if(mode & S_IROTH)  str[7]='r';
    if(mode & S_IWOTH)  str[8]='w';
    if(mode & S_IXOTH)  str[9]='x';
}

#include<pwd.h>     //#include¿ÉÒÔ³öÏÖÔÚŽúÂëÖÐµÄÈÎºÎÎ»ÖÃ
char * uid_to_name(uid_t uid){
    struct passwd *pw_str;
    static char numstr[10];
    if((pw_str=getpwuid(uid))==NULL){
        sprintf(numstr,"%d",uid);       //Èç¹ûÃ»ÓÐ»ñµÃÓÃ»§Ãû£¬ÔòÖ±œÓ°Ñuidµ±×÷ÓÃ»§Ãû
        return numstr;
    }
    else
        return pw_str->pw_name;
}

#include<grp.h>
char * gid_to_name(gid_t gid){
    struct group *grp_ptr;
    static char numstr[10];
    if((grp_ptr=getgrgid(gid))==NULL){
        sprintf(numstr,"%d",gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}
