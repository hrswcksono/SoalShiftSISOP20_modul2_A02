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

void download();

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process
  pid_t child_id;

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

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

    if (child_id < 0) 
      exit(EXIT_FAILURE);

    if (child_id == 0)
    { 
      if (fork() == 0)
      {
        char *argv[] = {"mkdir", "-p", buffer, NULL};
        execv("/bin/mkdir", argv);
      }
      else 
      {
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
