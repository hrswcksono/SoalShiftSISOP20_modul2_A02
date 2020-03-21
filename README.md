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

