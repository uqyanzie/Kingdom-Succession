#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "royalTree.h"

/**
    TO-DO LIST UNTUK FINAL
    1. SELESAIIN MODUL BIODATA
    2. TAMBAH ART BUAT EVENT ANGGOTA KELUARGA BARU
    3. TAMBAH ART BUAT EVENT ANGGOTA KELUATGA YANG MATI
    4. TAMBAH ART BUAT RAJA BARU YANG NAIK TAHTA
**/

int main(){
	nbTree pTree;
	nbCreate(&pTree);
	nbAddr node, king;
	int year;
	char tombol,tombol2;
	char str[]="";
	char searchname[20];
	unsigned char choice;
//	printf("asd¯\n204:%c 186:%c 185:%c 209:%c 205:%c", 204, 186, 185, 209, 205);
//	system("Pause");
	PrintFromFile("opening.txt");
	printf("\n\n");
	system("Pause");
	system("cls");
	PrintFromFile("throne.txt");
	printf("\n");
	InsertKing(&pTree);
	do{
		system("CLS");
		king = pTree.root;
		if(king->info.age >= 80){
            deleteNode(&king, &pTree);
		}
		system("CLS");
		printf("\n\tKeadaan Pohon Keluarga:\n");
		if (pTree.root==NULL){
			printf("Tree kosong");
		}
		else{
           nbPrint(pTree.root,str);
		}
		printf("\n\n\n\t[1] Tambah anggota keluarga kerajaan\n");
		printf("\t[2] Hapus/turunkan tahta Raja sekarang\n");
		printf("\t[3] Matikan/hapus anggota keluarga kerajaan\n");
		printf("\t[4] Tambah pasangan\n");
		printf("\t[5] Lakukan Time skip\n");
		printf("\t[0] Exit\n\n");

		printf("\tPilihan %c ", 175); fflush(stdin); scanf("%c", &tombol);
		switch(tombol){
			case '1':
				InsertFamilyMember(&pTree);
				break;
            case '2':
                if (pTree.root != NULL){
                    do{
                    system("CLS");
                    fflush(stdin);
                    printf("\n\n\t Pilih penyebab turunnya tahta raja : \n");
                    printf("\t 1. Tewas karena penyakit/terbunuh atau alasan mendadak lainnya\n");
                    printf("\t   (Tahta akan diteruskan, sekaligus Raja turun tahta di umur yang sama) \n");
                    printf("\t 2. Memangku jabatan hingga pensiun\n");
                    printf("\t   (Tahta akan diteruskan, setelah Raja menginjak pensiun di umur 80 tahun) \n");
                    printf("\t 0. Kembali");
                    printf("\n\n\t Pilihan : ");
                    tombol2 = getchar();
                    if(tombol2=='1'){
                        fflush(stdin);
                        if(king != NULL){
                            printf("\tApakah anda yakin ingin menghapus data ini? [Y/N] : ");
                            choice = getchar();
                            if(choice == 'Y'){
                                printf("\tData anggota keluarga bernama \"\%s\"\ telah dihapus\n", king->info.name);
                                deleteNode(&king, &pTree);
                                system("PAUSE");
                            }
                            else{
                                printf("\tData batal dihapus\n");
                                system("PAUSE");
                            }
                        }
                        break;
                    }
                    else if(tombol2=='2'){
                        fflush(stdin);
                        if(king != NULL){
                            printf("\tApakah anda yakin ingin menghapus data ini? [Y/N] : ");
                            choice = getchar();
                            if(choice == 'Y'){
                                year = 80 - king->info.age;
                                ProceedTimeSkip(&king, year);
                                printf("\tData anggota keluarga bernama \"\%s\"\ telah dihapus\n", king->info.name);
                                deleteNode(&king, &pTree);
                                system("PAUSE");
                            }
                            else{
                                printf("Data batal dihapus\n");
                                system("PAUSE");
                            }
                        }
                        break;
                        }
                    else if(tombol2=='0'){
                        break;
                    }
                    else{
                        printf("INPUT TIDAK VALID!");
                        system("PAUSE");
                    }
                    }while(tombol2 != 0);
                }
                else{
                    printf("Anggota Keluarga Masih Kosong!\n");
                }
                break;
            case '3':
                fflush(stdin);
                system("cls");
                printf("Nama anggota keluarga yang hendak dihapus : ");
                scanf(" %[^\n]",&searchname);
                fflush(stdin);
                node = nbSearch(pTree.root, searchname);
                if (node != NULL){
                    printf("Apakah anda yakin ingin menghapus data ini? [Y/N] : ");
                    scanf("%c",&choice);
                    if(choice == 'Y'){
                        printf("Data anggota keluarga bernama \"\%s\"\ telah dihapus\n");
                        deleteNode(&node, &pTree);
                        system("PAUSE");
                        break;
                    }
                    else{
                        printf("Data batal dihapus\n");
                        system("PAUSE");
                    }
                }
                else{
                    printf("Data bernama %s tidak ditemukan di dalam daftar anggota keluarga\n");
                    system("PAUSE");
                }
			case '4':
				InsertVPartner(&pTree);
				break;
            case '5':
                printf("\tFungsi ini akan menambahkan umur semua anggota keluarga kerajaan sesuai input yang diterima\n");
                printf("\tInput jumlah tahun yang akan ditambahkan : ");
                scanf("%d",&year);
                ProceedTimeSkip(&pTree.root,year);
                fflush(stdin);
                break;
            case '0':
                system("CLS");
                printf("Sukses Keluar dari Program\n");
                system("PAUSE");
                _exit(1);
                break;
			default:
				printf("\n\t[x] Input tidak valid");
				printf("\n\tTekan tombol apapun untuk kembali");
				getch();
				break;
		}
	}while(tombol!=0);
	_exit(1);
return 0;
}
