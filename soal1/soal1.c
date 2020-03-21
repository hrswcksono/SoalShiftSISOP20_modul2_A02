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
#include <ctype.h>

int digits_only(const char *s)
  {
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }
   
        return 1;
 }

int main(int argc, char *argv[]) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  int jam,menit,detik;

  int arr[4],iter=0;

  if(argc == 5){
      for(iter=1; iter<4; iter++){
      if(digits_only(argv[iter])){
        arr[iter]=atoi(argv[iter]);
      }
      else if(strcmp(argv[iter],"*")==0){
      }
      else{exit(EXIT_FAILURE);}
    }
  }

  else if(argc!=5){
      exit(EXIT_FAILURE);
  }

  if(arr[1] > 59 || arr[1] < 0){
     exit(EXIT_FAILURE);
  }

  if(arr[2] > 59 || arr[2] < 0){
     exit(EXIT_FAILURE);
  }

  if(arr[3] > 23 || arr[3] < 0){
     exit(EXIT_FAILURE);
  }

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

  if ((chdir("/home/kali/modul2/soal1/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  


  while (1) {

  time_t now = time(0);
  struct tm tstruct = *localtime(&now);
  jam = tstruct.tm_hour;
  menit = tstruct.tm_min;
  detik = tstruct.tm_sec;
  char *argcv[] = {"sh", argv[4], NULL};
   if((jam==arr[3]||strcmp(argv[3],"*")==0)){
       if(menit==arr[2]||strcmp(argv[2],"*")==0){
             if(detik==arr[1]||strcmp(argv[1],"*")==0){
                pid_t child_id;
                child_id = fork();
                if (child_id == 0){
                     execv("/bin/sh", argcv);
                } 
             }
       }
   }
   sleep(1);
  }
}
