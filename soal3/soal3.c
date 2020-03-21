#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <stdio.h>

int main() {
  pid_t child_id,chd1,chd2,chd3,chd4,chd5,chd6;
  int status;

  child_id = fork();
  
  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
    char *argv[] = {"mkdir", "-p", "/home/kali/modul2/indomie", NULL};
    execv("/bin/mkdir", argv);
  } else {
    // this is parent
    while ((wait(&status)) > 0);
    sleep(5);
    chd1 = fork();
    if (chd1 < 0) {
      exit(EXIT_FAILURE);
    }
    if (chd1 == 0) {
      char *argv[] = {"mkdir", "-p", "/home/kali/modul2/sedaap", NULL};
      execv("/bin/mkdir", argv);
    } else {
    while ((wait(&status)) > 0);
    chd2 = fork();
    if (chd2 < 0) {
      exit(EXIT_FAILURE);
    }
    if (chd2 == 0) {
      char *argv[] = {"unzip", "/home/kali/modul2/jpg.zip", "-d", "/home/kali/modul2/", NULL};
      execv("/bin/unzip", argv);
    } else {
    while ((wait(&status)) > 0);
    chd3 = fork();
    if (chd3 < 0) {
      exit(EXIT_FAILURE);
    }
    if (chd3 == 0) {
    struct dirent *de;
    DIR *dr = opendir("/home/kali/modul2/jpg");
    while ((de = readdir(dr)) != NULL){
    if (de->d_type == DT_REG)
    {
      pid_t cid1;
      cid1 = fork();
      if (cid1 < 0) {
         exit(EXIT_FAILURE);
      }
      if (cid1 == 0) {
        char file[50] = {};
        sprintf(file,"/home/kali/modul2/jpg/%s", de->d_name);
        char *argv[] = {"mv", file, "/home/kali/modul2/sedaap", NULL};
        execv("/bin/mv", argv);
      }
    }
    else {
      pid_t cid2;
      cid2 = fork();
      if (cid2 < 0) {
         exit(EXIT_FAILURE);
      }
      if (cid2 == 0) {
        char file[50] = {};
        sprintf(file,"/home/kali/modul2/jpg/%s", de->d_name);
        char *argv[] = {"mv", file, "/home/kali/modul2/indomie", NULL};
        execv("/bin/mv", argv);
      }
    }
   }
   closedir(dr);
   } else {
   while ((wait(&status)) > 0);
   sleep(1);
   chd4 = fork();
   if (chd4 < 0) {
     exit(EXIT_FAILURE);
   }
   if (chd4 == 0) {
    struct dirent *df;
    DIR *dr = opendir("/home/kali/modul2/indomie");  
    while ((df = readdir(dr)) != NULL){
      char file[50];
      sprintf(file, "/home/kali/modul2/indomie/%s/coba1.txt", df->d_name);
      pid_t cid3;
      cid3 = fork();
      if (cid3 < 0) {
         exit(EXIT_FAILURE);
      }
      if (cid3 == 0) {
        char *argv[] = {"touch", file, NULL};
        execv("/bin/touch", argv);
      }
   }
   closedir(dr);
   } else {
   while ((wait(&status)) > 0);
   sleep(3);
   chd5 = fork();
   if (chd5 < 0) {
     exit(EXIT_FAILURE);
   }
   if (chd5 == 0) {
    struct dirent *df;
    DIR *dr = opendir("/home/kali/modul2/indomie");  
    while ((df = readdir(dr)) != NULL){
      char file[50];
      sprintf(file, "/home/kali/modul2/indomie/%s/coba2.txt", df->d_name);
      pid_t cid3;
      cid3 = fork();
      if (cid3 < 0) {
         exit(EXIT_FAILURE);
      }
      if (cid3 == 0) {
        char *argv[] = {"touch", file, NULL};
        execv("/bin/touch", argv);
      }
   }
   closedir(dr);
   } else {
   while ((wait(&status)) > 0);
   sleep(1);
   chd6 = fork();
   if (chd6 < 0) {
     exit(EXIT_FAILURE);
   }
   if (chd6 == 0) {
        char *argv[] = {"rm", "/home/kali/modul2/indomie/coba2.txt", "/home/kali/modul2/indomie/coba1.txt", "/home/kali/modul2/coba1.txt", "/home/kali/modul2/coba2.txt", NULL};
        execv("/bin/rm", argv);
}
}
}}}}
}}
