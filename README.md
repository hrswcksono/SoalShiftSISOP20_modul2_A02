# SoalShiftSISOP20_modul2_A02

## Soal1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

a. Program menerima 4 argumen berupa:

   i. Detik: 0-59 atau * (any value)
   
   ii. Menit: 0-59 atau * (any value)
   
   iii. Jam: 0-23 atau * (any value)
   
   iv. Path file .sh
   
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

>Source code file: [Soal1](https://github.com/hrswcksono/SoalShiftSISOP20_modul2_A02/blob/master/soal1/soal1.c)

```javascript
#include <ctype.h>
int digits_only(const char *s)
  {
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }
   
        return 1;
 }
```
fungsi untuk check character hanya mengandung digit

```javascript
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
```
fungsi untuk check apakah character terdiri dari digit atau * atau character yang lain

```javascript
   if((jam==arr[3]||strcmp(argv[3],"*")==0)){
       if(menit==arr[2]||strcmp(argv[2],"*")==0){
             if(detik==arr[1]||strcmp(argv[1],"*")==0){
```
untuk check apakah jam, menit, atau detik sekarang sama dengan yang diinputkan, jika terdiri dari character * maka akan otomatis berjalan

## Soal 2

Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program.

a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].

b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.

e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).

>Source code file: [Soal2](https://github.com/hrswcksono/SoalShiftSISOP20_modul2_A02/blob/master/soal2/soal2.c)

```while (1) {
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
```
Program untuk membuat folder dengan format nama file yaitu waktu pada saat program di jalankan

```
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
```
program untuk mendownload gambar dari link yang di sediakan dan mengubah format nama gambar yang telah di download menjadi waktu pada saat gambar tersebut telah di download

```
void zip(char arr[]){
    char file[50];
    sprintf(file,"%s.zip",arr);
    char *argv[] = {"zip","-r",file,arr,NULL}; 
    execv("/bin/zip", argv);
}
```
program untuk mengubah folder menjadi bentuk zip

```
void delet(char arr[]){
    char *argv[] = {"rm", "-r", arr, NULL};
    execv("/bin/rm", argv);
}
```
proses untuk menghapus folder yang telah di ubah menjadi zip

```
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
```
Program untuk membuat program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).


## Soal3

Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).

a. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.

c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.

d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).

Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat

>Source code file: [Soal3](https://github.com/hrswcksono/SoalShiftSISOP20_modul2_A02/blob/master/soal3/soal3.c)
