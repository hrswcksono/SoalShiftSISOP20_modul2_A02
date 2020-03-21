#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <wait.h>

void killer(char arr[]);

void zip(char arr[]);

void delet(char arr[]);

void download();

int main(int argc, char *argv[]) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process
  pid_t child_id,cid1;

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  killer(argv[1]);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/kali/modul2/soal2/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  while (1) {
    char buffer[50];
    struct tm * ptr_time;
    time_t time_raw_format; 
    time ( &time_raw_format );
    ptr_time = localtime ( &time_raw_format );
    strftime(buffer,50,"%Y-%m-%d_%T",ptr_time);
    pid_t child_id;
    child_id = fork();

    int status;

    if (child_id < 0){ 
      exit(EXIT_FAILURE);
    }
    if (child_id == 0)
    { 
      if (fork() == 0)
      {
        char *argv[] = {"mkdir", "-p", buffer, NULL};
        execv("/bin/mkdir", argv);
      }
      else 
      {
        while ((wait(&status)) > 0);
        for (int i = 1; i <= 20; i++)
        {
          if (fork() == 0)
          {
            chdir(buffer);
            download();
          }
          sleep(5);
        }
       cid1 = fork();
       if (cid1 <0){
          exit(EXIT_FAILURE);
       }
       if (cid1 == 0){
          zip(buffer);
       }
       else {
        while ((wait(&status)) > 0);
          delet(buffer);
        }
       }
    }
    else{
    sleep(30);
     }  
  }
}

void download(){
    int a;
    char file[50];
    struct tm * ptr_time;
    time_t time_raw_format; 
    char buffer[50];
    time ( &time_raw_format );
    ptr_time = localtime ( &time_raw_format );
    strftime(buffer,50,"%Y-%m-%d_%T",ptr_time);
    a=((int)time(NULL)%1000) + 100;
    sprintf(file,"https://picsum.photos/%d?random=1", a);
    char *argv[] = {"wget",file,"-qO" , buffer, NULL};
    execv("/bin/wget", argv);
}

void zip(char arr[]){
    char file[50];
    sprintf(file,"%s.zip",arr);
    char *argv[] = {"zip","-r",file,arr,NULL}; 
    execv("/bin/zip", argv);
}

void delet(char arr[]){
    char *argv[] = {"rm", "-r", arr, NULL};
    execv("/bin/rm", argv);
}

void killer(char arr[])
{
    FILE *kill;
    kill = fopen("killer.sh", "w");
    if(strcmp(arr, "-a")==0) 
        fprintf(kill, "rm $0\n#!/bin/bash\nkill -9 -%d", getpid());
    else if(strcmp(arr, "-b")==0)
        fprintf(kill, "rm $0\n#!/bin/bash\nkill %d", getpid());
    fclose(kill);
}
