#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Proyek UTS Kelompok 10
//Kelompok 10
//Bisma Alif Alghifari 2106731402
//Mikhael Morris Hapataran Siallagan 2106731491

//Deklarasi struct Data
typedef struct {
      char namamenu[100];
      int jenismenu,harimenu;
      float hargamenu;
}Data;

//function untuk melakukan write data
void write(Data dataMenu[20]){
	const char* outputdata = "{\n\t\"NAMA\": \"%s\",\n\t\"JENIS\": %d, \n\t\"HARI\": %d, \n\t\"HARGA\": %f}\n";
	int i;
	FILE* ptr;
	fopen_s(&ptr, "datamenu.dat", "w");//membuka file bernama "datamenu.dat" dengan mode write
	for (i = 0; i < 20; i++) {//forloop untuk melakukan print hasil write data
		fprintf_s(ptr, outputdata, dataMenu[i].namamenu, dataMenu[i].jenismenu, dataMenu[i].harimenu, dataMenu[i].hargamenu);
	}
	fclose(ptr);//menutup file
}

//function untuk melakukan read data
void read(Data dataMenu[20]) {
	const char* inputdata  = "{\n\t\"NAMA\": \"%[^\"]\",\n\t\"JENIS\": %d, \n\t\"HARI\": %d, \n\t\"HARGA\": %f}\n";
	int i;
	FILE* ptr;
	fopen_s(&ptr, "datamenu.dat", "r");//membuka file bernama "datamenu.dat" dengan mode read
	for (i = 0; i < 20; i++) {//forloop untuk melakukan input data yang akan disimpan dalam file
		fscanf_s(ptr, inputdata, dataMenu[i].namamenu, 100, &dataMenu[i].jenismenu, &dataMenu[i].harimenu, &dataMenu[i].hargamenu);
	}
	fclose(ptr); //menutup file
}

//Prototype function
void menu(int a, int len, Data *dataMenu,int *plen);
void opening(void);
void closing(void);
void panduan(void);
void input(int a, int *len, Data *dataMenu);
int display(int a, int *len, Data *dataMenu);
void swap(int i1,int i2,Data *dataMenu);
char *Strcasestr(const char* haystack, const char* needle);
void ascendingnama(int len, Data *dataMenu);
void descendingnama(int len, Data *dataMenu);
void quickSortA(Data *dataMenu, int low, int high);
void quickSortD(Data *dataMenu, int low, int high);
void searchingnama(int a, int len, Data *dataMenu);
void searchinghari(int a, int len, Data *dataMenu);

//Main function
int main(){
	system("Color 09");
	//deklarasi variabel, array, serta pointer 
    int a,len;
	int *plen;
	plen = &len;
    Data dataMenu[20];
    read(dataMenu);//memanggil function read
    opening();//memanggil function opening
    menu(a, len, dataMenu,plen);//memanggil function menu
    
    int choice = 0;
    return 0;
    
    
}

//function untuk menu
void menu(int a, int len, Data *dataMenu,int *plen){
    
    int choice = 0;
    
    while(choice != 4){//looping agar saat input tidak melebihi batas

        printf("======================================\n"
            "|                                    |\n"
            "|         Aplikasi Buku Menu         |\n"
            "|                                    |\n"
            "======================================\n"
            "======================================\n"
            "|            Menu Utama:             |\n"
            "|                                    |\n"
            "|  1. Display Menu                   |\n"
            "|  2. Panduan                        |\n"
            "|  3. Khusus Karyawan                |\n"
            "|  4. Exit                           |\n"
            "======================================\n");
        printf("\nMasukkan Pilihan Anda : ");
		scanf("%d", &choice);
        system("CLS");

        switch(choice){
            case 1 : //jika pilihan satu maka akan
                display(a, plen, dataMenu);//memanggil function display
                break;
            case 2 ://jika pilihan dua maka akan
                panduan();//memanggil function panduan
                break;
            case 3 ://jika pilihan tiga maka akan
                input(a, plen, dataMenu);//memanggil function input
				write(dataMenu);   
                break;
            case 4 ://jika pilihan empat maka akan
            	closing();//memanggil function closing
            	break;
            default ://jika input tidak sesuai maka akan error handling
                printf("===== Hanya masukkan piihan yang tersedia!!=====\n\n\n");
                break;
        }
    }
}

//function untuk input
void input(int a, int *len, Data *dataMenu){
    int i;
    printf("==============================================\n");
    printf("|                INPUT MENU                  |\n");
    printf("==============================================\n");
    printf("\nMasukkan Jumlah Menu Yang Akan Dimasukkan \n(Maks 20 Menu) : ");
	//input untuk memberi batasan menu, maksimal 20 menu
    do{
    	i = 0;
    	scanf("%d", len);
    	if (*len < 0 || *len > 20){//error handling jika melewati batas max
    		printf("\nInput Melebihi Batas Maks\n");
    		printf("\nMasukkan Jumlah Menu Yang Akan Dimasukkan \n(Maks 20 Menu) : ");
    		i = 1;
		}
	}while(i == 1);
	
	//looping agar meminta input sesuai jumlah menu
    for(i = 0; i < *len; i++){
    	//melakukan input nama menu
        printf("\nNama Menu : ");
        scanf(" %99[^\n]s",  dataMenu[i].namamenu);

        //melakukan input jenis makanan
        printf("Jenis Menu (Makanan : 1/Minuman : 2) : ");
        scanf("%d", &dataMenu[i].jenismenu);

        //melakukan input harga menu
        printf("Harga Menu : ");
        scanf("%f", &dataMenu[i].hargamenu);

        //melakukan input hari
        printf("--- Pilihan Hari ---\n");
		printf("1.Senin\n2.Selasa\n3.Rabu\n4.Kamis\n5.Jumat\n6.Sabtu\n7.Minggu\n8.Tersedia Setiap Hari\n");
		printf("Jadwal Hari Ekslusif: \n");
		scanf("%d", &dataMenu[i].harimenu);
  
        
    }
}
//function display
int display(int a, int *len, Data *dataMenu){
	//deklarasi variabel dan array
    char jenis[2][30] = {"Makanan","Minuman"};
    char hari[8][30] = {"Senin","Selasa","Rabu","Kamis","Jumat","Sabtu","Minggu","Tersedia Setiap Hari"};
    int choice = 0;
    printf("Berikut fitur-fitur yang tersedia : \n");
    printf("1. Sorting menu A-Z\n");
    printf("2. Sorting menu Z-A\n");
    printf("3. Sorting ascending harga\n");
    printf("4. Sorting descending harga\n");
    printf("5. Searching berdasarkan nama menu\n");
    printf("6. Searching berdasarkan nama hari\n");
    printf("7. Main Menu\n");
    printf("Masukkan Pilihan Anda : ");
    scanf("%d", &choice);
    system("CLS");

    	switch(choice){
            case 1 :ascendingnama(*len, dataMenu);//jika pilihan satu maka akan memanggil function ascendingnama
                break;
            case 2 :descendingnama(*len, dataMenu);//jika pilihan dua maka akan memanggil function descendingnama
                break;
            case 3 :quickSortA(dataMenu, 0, *len-1);//jika pilihan tiga maka akan memanggil function quickSortA
                break;
            case 4 :quickSortD(dataMenu, 0, *len-1);//jika pilihan empat maka akan memanggil function quickSortD
                break;
            case 5 :searchingnama(a, *len, dataMenu);//jika pilihan lima maka akan memanggil function searchingnama
                return 1;
				break;
                
            case 6 :searchinghari(a, *len, dataMenu);//jika pilihan enam maka akan memanggil function searchinghari
                return 1;
				break;
                
            case 7 : menu(a, *len, dataMenu,len);//jika pilihan tujuh maka akan memanggil function menu
            break;
                break;
            default :
                printf("===== Error - Hanya Masukkan Pilihan Yang Tersedia =====\n\n\n");
                break;
        }
	//melakukan print output hasil setelah memilih fitur-fitur tersebut
    printf("%20s|%20s|%20s|%30s|\n", "Nama", "Jenis", "Harga", "Hari Tersedia");
    printf("----------------------------------------------------------------------------------------------\n");
    for(a = 0; a < *len; a++){
        printf("%20s|%20s|%20.2f|%30s|\n", dataMenu[a].namamenu, jenis[dataMenu[a].jenismenu-1], dataMenu[a].hargamenu, hari[dataMenu[a].harimenu-1] );
    }
    printf("\n\n");
}

//function acsendingnama, untuk melakukan sorting ascending nama dengan metode bubblesort
void ascendingnama(int len, Data *dataMenu){
    int i, j;
    char temp[50];
       for (i = 0; i < len-1; i++){
           for (j = 0; j < len-i-1; j++){
               if (strcmp(dataMenu[j].namamenu,dataMenu[j+1].namamenu)>0){
                   swap(j,j+1,dataMenu);
            }
        }
   }
}

//function descendingnama, untuk melakukan sorting descending nama dengan metode bubblesort 
void descendingnama(int len, Data *dataMenu){
    int i, j;
    char temp[50];
       for (i = 0; i < len-1; i++){
           for (j = 0; j < len-i-1; j++){
               if (strcmp(dataMenu[j].namamenu,dataMenu[j+1].namamenu)<0){
                   swap(j,j+1,dataMenu);
            }
        }
       }
    
}

//function quickSortA, untuk melakukan sorting ascending harga dengan metode 
void quickSortA(Data *dataMenu, int low, int high) {
  if (low < high) {
      int j,pi;
      int pivot = dataMenu[high].hargamenu;
  
      int i = (low - 1);

      for (j = low; j < high; j++) {
        if (dataMenu[j].hargamenu <= pivot) {
          i++;
          swap(i,j,dataMenu);
        }
      }
      swap(i+1, high,dataMenu);
      pi = i+1;
    quickSortA(dataMenu, low, pi - 1);
    quickSortA(dataMenu, pi + 1, high);
  }
}

//function quickSortD, untuk melakukan sorting descending harga dengan metode 
void quickSortD(Data *dataMenu, int low, int high) {
  if (low < high) {
      int j,pi;
      int pivot = dataMenu[high].hargamenu;
  
      int i = (low - 1);

      for (j = low; j < high; j++) {
        if (dataMenu[j].hargamenu >= pivot) {
          i++;
          swap(i,j,dataMenu);
        }
      }
      swap(i+1, high,dataMenu);
      pi = i+1;
    quickSortD(dataMenu, low, pi - 1);
    quickSortD(dataMenu, pi + 1, high);
  }
}


//function searchingnama, untuk melakukan proses searching nama
void searchingnama(int a, int len, Data *dataMenu){
    int i,count=1;
    char search[100];
    char jenis[2][30] = {"Makanan","Minuman"};
    char hari[8][30] = {"Senin","Selasa","Rabu","Kamis","Jumat","Sabtu","Minggu","Tersedia Setiap Hari"};
    printf("Masukkan nama yang ingin dicari:");
    scanf(" %99[^\n]s", search);
    printf("\n\n");
    printf("%20s|%20s|%20s|%30s|\n", "Nama", "Jenis", "Harga", "Hari Tersedia");
    printf("----------------------------------------------------------------------------------------------\n");
    for(i=0; i<len; i++){
        if(Strcasestr(dataMenu[i].namamenu,search)){
            //melakukan print output hasil setelah memilih fitur-fitur tersebut
            printf("%20s|%20s|%20.2f|%30s|\n", dataMenu[i].namamenu, jenis[dataMenu[i].jenismenu-1], dataMenu[i].hargamenu, hari[dataMenu[i].harimenu-1] );
            count++;
        }
    }
    printf("\n\n");
}

//function searchinghari, untuk melakukan proses searching hari
void searchinghari(int a, int len, Data *dataMenu){
    int i,count=1,j;
    char search[100];
    char jenis[2][30] = {"Makanan","Minuman"};
    char hari[8][30] = {"Senin","Selasa","Rabu","Kamis","Jumat","Sabtu","Minggu","Tersedia Setiap Hari"};
    printf("Masukkan hari yang ingin dicari:");
    scanf(" %99[^\n]s", &search);
    printf("\n\n");
    printf("%20s|%20s|%20s|%30s|\n", "Nama", "Jenis", "Harga", "Hari Tersedia");
    printf("----------------------------------------------------------------------------------------------\n");
    for(i=0; i<8; i++){
        if(Strcasestr(hari[i],search)){
        	//printf("%s\n",hari[i]);
        	//printf("%d",i);
            for(j=0;j<len;j++){
            	//printf("%s,%d",dataMenu[j].namamenu,dataMenu[j].harimenu);
                if(dataMenu[j].harimenu-1 == i){
                	//melakukan print output hasil setelah memilih fitur-fitur tersebut
                    printf("%20s|%20s|%20.2f|%30s|\n", dataMenu[j].namamenu, jenis[dataMenu[j].jenismenu-1], dataMenu[j].hargamenu, hari[dataMenu[j].harimenu-1] );
                    count++;
                }
            }
            
        }
    }
    printf("\n\n");
}

//untuk melakukan compare terhadap partial search dengan data
char *Strcasestr(const char* haystack, const char* needle) {
    if (!needle[0]) return (char*) haystack;
    int i, j;

    for (i = 0; haystack[i]; i++) {
        int matches = 1;
        for (j = 0; needle[j]; j++) {
            if (!haystack[i + j]) return NULL;

            if(tolower((unsigned char)needle[j]) !=
                tolower((unsigned char)haystack[i + j])) {
                matches = 0;
                break;
            }
        }
        if (matches) return (char *)(haystack + i);
    }
    return NULL;
}

//function swap, untuk melakukan swaping pada data yang akah digunakan pada quicksort
void swap(int i1,int i2,Data *dataMenu){
    float tempf;
    int temp;
      char temparray[100];
      
      tempf = dataMenu[i1].hargamenu;
      dataMenu[i1].hargamenu = dataMenu[i2].hargamenu ;
      dataMenu[i2].hargamenu = tempf;
      
    strcpy(temparray,dataMenu[i1].namamenu);
    strcpy(dataMenu[i1].namamenu, dataMenu[i2].namamenu);
    strcpy(dataMenu[i2].namamenu,temparray);
    
    temp = dataMenu[i1].harimenu;
      dataMenu[i1].harimenu = dataMenu[i2].harimenu ;
      dataMenu[i2].harimenu = temp;
      
      temp = dataMenu[i1].jenismenu;
      dataMenu[i1].jenismenu = dataMenu[i2].jenismenu ;
      dataMenu[i2].jenismenu = temp;
    
    
    
}

//function opening, sebagai hiasan pembuka program
void opening(void){
    int loop;
	system("CLS");
	system("Color 09");
    printf("=======================================================\n");
    Sleep(500);
    printf("======|%15sBuku Menu%17s|======\n", " ", " ");
    Sleep(500);
    printf("======|%17sOleh%20s|======\n", " ", " ");
    Sleep(500);
    printf("======|%15sKelompok 2%16s|======\n", " ", " ");
    Sleep(500);
    printf("=======================================================\n");
    Sleep(500);
    printf("\n\n");
    for(loop = 1; loop <= 55; loop++) {
        printf("%c", 223);
        Sleep(12);
    }
	system("CLS");
}

//function closing, sebagai hiasan penutup program
void closing(void){
    int loop;
	system("CLS");
    printf("=======================================================\n");
	Sleep(500);
    printf("======|%14sTerima Kasih%15s|======\n", " ", " ");
	Sleep(500);
    printf("======|%19sdan%19s|======\n", " ", " ");
	Sleep(500);
    printf("======|%9sSampai berjumpa kembali%9s|======\n", " ", " ");
	Sleep(500);
    printf("=======================================================\n");
    Sleep(500);
    printf("\n\n");
    for(loop = 1; loop <= 55; loop++) {
        printf("%c", 223);
        Sleep(12);
    }
    printf("\n\n");
	Sleep(1000);
	system("CLS");	
}

//function panduan, berisi panduan program
void panduan(){
    printf("================================================================");
    printf("\n|         PROGRAM INI MERUPAKAN APLIKASI MENU RESTORAN         |");
    printf("\n================================================================\n\n");
    printf("1. Display Menu, untuk menampilkan daftar menu serta\n");
    printf("   Menjalankan fitur seperti :\n");
    printf("%5s - Sorting Nama (Ascending / Descending)\n", " ");
    printf("%5s - Sorting Harga (Ascending / Descending)\n", " ");
    printf("%5s - Mencari Nama Menu / Hari Eksklusif suatu menu\n", " ");
    printf("3. Panduan, berisi penjelasan singkat mengenai program\n");
    printf("4. Khusus Karyawan, Menginput menu oleh pihak restoran\n");
    printf("%5s - Memasukkan Nama Menu (Dapat berupa makanan atau minuman)\n", " ");
    printf("%5s - Masukkan Harga dalam mata uang rupiah\n", " ");
    printf("%5s - Tentukan apakaha menu tersebut memiliki hari eksklusif)\n", " ");
    printf("5. Exit, untuk keluar dari program\n", " ");
    printf("\n================================================================");
    printf("\n\n\n");
}

