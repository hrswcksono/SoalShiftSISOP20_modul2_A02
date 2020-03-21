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

>Source code file: [Soal1](https://github.com/hrswcksono/SoalShiftSISOP20_modul2_A02/blob/master/soal2/soal2.c)
