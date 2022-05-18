#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "royalTree.h"

void nbCreate(nbTree *X){
	(*X).root=NULL;
}

nbAddr nbCNode(nbAddr parent, nbType name, int age, bool gender){
	nbAddr newNode;
	newNode=(nbAddr) malloc(sizeof(nbTreeNode));

	if (newNode != NULL){
		newNode->fs=NULL;
		newNode->nb=NULL;
		newNode->parent=parent;
		strcpy(newNode->info.name, name);
		newNode->info.age=age;
		newNode->info.gender=gender;
		newNode->partner=NULL;
	}
	return newNode;
}

pairAddr nbCPartnerNode(nbType name, int age, bool gender, nbAddr partner){
	pairAddr   newNode;
	newNode = (pairAddr) malloc(sizeof(nbPairNode));

	if (newNode != NULL){
		strcpy(newNode->info.name, name);
		newNode->info.age = age;
		newNode->info.gender = gender;
		newNode->partner = partner;
	}
	return newNode;
}

void nbDNode(nbAddr *Node)
{
	(*Node)->fs=NULL;
	(*Node)->fs=NULL;
	(*Node)->parent=NULL;
	free(*Node);
}

void InsertKing(nbTree *pTree){
	nbAddr king;
	nbType name;
	int age, temp;
	bool gender;
	/*Insert nama*/
	printf("\n\tMasukan Identitas Raja/ Ratu:\n");
	printf("\n\t%c Nama: ", 175);
	scanf(" %[^\n]", &name);
	/*Insert jenis kelamin*/
	do{
		printf("\n\t%c Pilih jenis kelamin\n", 175);
		printf("\t  0. Wanita\n");
		printf("\t  1. Pria\n");
		printf("\t  Pilihan: ");
		scanf(" %d", &temp);
		if(temp != 0 && temp != 1){
			printf("\t[x] Input tidak valid\n");
		}else{
			gender = temp;
			break;
		}
	}while(1);
	/*Insert umur raja atau ratu*/
	do{
		printf("\n\t%c Umur (Minimal 50 tahun): ", 175);
		scanf(" %d", &age);
		if(age < 50){
			printf("\t[x] Input tidak valid\n");
		}
	}while(age < 50);

	/*Alokasi node*/
	king = nbCNode(NULL, name, age, gender);

	/*Insert ke tree*/
	InsertNode(pTree, king);
	printf("\n\t[o] Raja/ ratu berhasil ditambahkan");
	getch();
}

void InsertFamilyMember(nbTree *pTree){
	nbAddr parentNode, newMemberNode;
	nbType name, parentName;
	int temp;
	int age;
	bool gender;

	/*Cari parent*/
	printf("\n\tMasukan 'q' untuk kembali\n");
	do{
		printf("\n\t%c Nama orang tua: ", 175);
		scanf(" %[^\n]", &parentName);
		if(strcmp(parentName, "q")==0){
			return;
		}
		parentNode = nbSearch((*pTree).root, parentName);
		if(parentNode == NULL){
			printf("\t[x] Nama orang tua tidak ditemukan\n");
		}else if(parentNode->partner == NULL){
			printf("\t[x] Orang tersebut tidak memiliki pasangan\n");
		}else{
			break;
		}
	}while(1);

	/*Insert nama*/
	do{
		printf("\n\t%c Masukan nama: ", 175);
		scanf(" %[^\n]", &name);
		if(nbSearch((*pTree).root, name)!=NULL){ /*Check jika ada node yg memiliki nama yg sama di tree*/
			printf("\t[x] Nama orang tersebut sudah ada pada pohon keluarga\n");
		}else{
			break;
		}
	}while(1);

	/*Insert umur*/
	do{
		printf("\n\tUmur anak minimal 19 tahun lebih muda dari kedua orang tua\n");
		printf("\n\t%c Masukan umur: ", 175);
		scanf(" %d", &age);
		if(age >= 1 && age <= parentNode->info.age - 19 && age <= parentNode->partner->info.age - 19){ //Umur minimal 19 tahun lebih muda dari parent
			break;
		}else{
			printf("\t[x] Input tidak valid\n");
		}
	}while(1);

	/*Insert jenis kelamin*/
	do{
		printf("\n\t%c Pilih jenis kelamin\n", 175);
		printf("\t  0. Wanita\n");
		printf("\t  1. Pria\n");
		printf("\t  Pilihan: ");
		scanf(" %d", &temp);
		if(temp != 0 && temp != 1){
			printf("\t[x] Input tidak valid\n");
		}else{
			gender = temp;
			break;
		}
	}while(1);

	/*Alokasi node*/
	newMemberNode = nbCNode(parentNode, name, age, gender);

	/*Insert ke tree*/
	InsertNode(pTree, newMemberNode);
	printf("\n\t[o] Anggota keluarga berhasil ditambahkan");
	getch();
}

void InsertVPartner(nbTree *pTree){
	nbAddr srcNode;
	pairAddr partner;
	bool gender;
	nbType name, partnerName;
	int age;

	/*Search node*/
	printf("\n\tMasukan 'q' untuk kembali\n");
	printf("\tUmur minimal untuk menikah adalah 18 tahun\n");
	do{
		printf("\n\t%c Nama anggota keluarga yang akan menikah: ", 175);
		scanf(" %[^\n]", &name);
		if(strcmp(name, "q")==0){
			return;
		}
		srcNode=nbSearch((*pTree).root, name);

		if(srcNode == NULL){
			printf("\t[x] Anggota keluarga tidak ditemukan\n");
		}else if(srcNode->partner != NULL){
			printf("\t[x] Anggota keluarga tersebut sudah memiliki pasangan\n");
		}else if(srcNode->info.age < 18){
			printf("\t[x] Anggota keluarga tersebut masih dibawah umur\n");
		}else{
			break;
		}
	}while(1);

	/*Get gender*/
	if(srcNode->info.gender == 0){
		gender = true;
	}else{
		gender = false;
	}

	/*Insert identitas partner*/
	do{
		printf("\n\t%c Masukan nama pasangan: ", 175);
		scanf(" %[^\n]", &partnerName);
		if(nbSearch((*pTree).root, partnerName)!=NULL){ /*Check jika ada node yg memiliki nama yg sama di tree*/
			printf("\t[x] Nama orang tersebut sudah ada pada pohon keluarga\n");
		}else{
			break;
		}
	}while(1);
	do{
		fflush(stdin);
		printf("\n\tUmur pasangan minimal 18 tahun\n");
		printf("\t%c Masukan umur pasangan: ", 175);
		scanf(" %d", &age);

		if(age < 18){
			printf("\t[x] Pasangan masih dibawah umur\n");
		}else{
			break;
		}
	}while(true);

	/*Alokasi partner*/
	partner = nbCPartnerNode(partnerName, age, gender, srcNode);

	/*Insert ke tree*/
	InsertPartner(srcNode, partner);
	printf("\n\t[o] Pasangan berhasil ditambahkan");
	getch();
}

void InsertPartner(nbAddr familyMember, pairAddr partner){
	familyMember->partner = partner;
	partner->partner = familyMember;
}

void InsertNode(nbTree *tRoot, nbAddr newNode){
	nbAddr temp;
	if (newNode!=NULL){ //Jika penciptaan node baru berhasil
		if (newNode->parent==NULL){
            //Jika belum terdapat root
			tRoot->root=newNode;
		}else{
			temp=newNode->parent;
			if (temp->fs != NULL){ //Jika memiliki first child
	            if(newNode->info.age > temp->fs->info.age && temp->fs->info.gender == newNode->info.gender || temp->fs->info.gender == 0 && newNode->info.gender == 1){
					newNode->nb = temp->fs;
					temp->fs = newNode;
	            }else{ //Jika sudah ada first child
	                temp=temp->fs;
	                if(newNode->info.gender == 0){ //Jika newNode laki-laki
	                	while(temp->nb!=NULL && temp->nb->info.gender == 0 && newNode->info.age <= temp->nb->info.age){
	                		temp=temp->nb;
						}
					}else{ //Jika newNode perempuan
						while(temp->nb!=NULL && temp->nb->info.gender == 0 || temp->nb!=NULL && newNode->info.age <= temp->nb->info.age){
							temp=temp->nb;
						}
					}
	            	if(temp->nb == NULL){ //Jika newNode paling muda
	                	temp->nb=newNode;
	                }else{
	                    newNode->nb = temp->nb;
	                    temp->nb = newNode;
	                }
                }
			}else{	//Jika tdk memiliki first child maka temp jadi first child
				temp->fs=newNode;
			}
        }
	}
}

void ShowNodeInfo(nbAddr node){
	nbAddr temp;

	printf("Nama: %s\n", &(node->info.name));
	printf("Umur: %d\n", node->info.age);
	printf("Jenis kelamin: %s\n", node->info.gender ? "Pria" : "Wanita");
	if(node->partner != NULL){
		printf("\nPasangan\n");
		printf("Nama: %s\n", &(node->partner->info.name));
		printf("Umur: %d\n", node->partner->info.age);
		printf("Jenis kelamin: %s\n", node->partner->info.gender ? "Pria" : "Wanita");
	}

	if(node->parent != NULL){
		printf("\nOrang tua\n");
		printf("Nama: %s\n", &(node->parent->info.name));
		printf("Umur: %s\n", node->parent->info.age);
		printf("Jenis kelamin: %s\n\n", node->parent->info.gender ? "Pria" : "Wanita");

		printf("Nama: %s\n", &(node->parent->partner->info.name));
		printf("Umur: %s\n", node->parent->partner->info.age);
		printf("Jenis kelamin: %s\n", node->parent->partner->info.gender ? "Pria" : "Wanita");
	}

	if(node->fs != NULL){
		printf("\nAnak\n");
		temp = node->fs;
		while(temp != NULL){
			printf("Nama: %s\n", &(node->info.name));
			printf("Umur: %d\n", node->info.age);
			printf("Jenis kelamin: %s\n", node->info.gender ? "Pria" : "Wanita");
			temp = temp->nb;
		}
	}
}

nbAddr nbSearch(nbAddr root, nbType src){
	nbAddr nSrc;
	if (root!=NULL){
		if (strcmp(root->info.name, src)==0){
			return root;
		}

		if(root->partner!=NULL){
			if(strcmp(root->partner->info.name, src)==0){
				return root;
			}
		}
		nSrc=nbSearch(root->fs,src);
		if (nSrc==NULL)
			return nbSearch(root->nb,src);
		else
			return nSrc;
	}
	return NULL;
}

void nbPrint(nbAddr node, char tab[]){
	char tempTab[255];
	strcpy(tempTab, tab);
	strcat(tempTab, "-");
	if (node!=NULL){
		if(node->partner != NULL){
			printf("\t%s%s [%d] [%s] x %s [%d] [%s]\n",tab,&(node->info.name),node->info.age, node->info.gender ? "P" : "W", &(node->partner->info.name), node->partner->info.age, node->partner->info.gender ? "P" : "W");
		}else{
			printf("\t%s%s [%d] [%s]\n", tab,&(node->info.name),node->info.age, node->info.gender ? "P" : "W");
		}
		nbPrint(node->fs,tempTab);
		nbPrint(node->nb,tab);
	}
}

void TimeSkip(nbAddr node, int year){
	if (node!=NULL){
		if(node->partner != NULL){
            node->info.age += year;
			node->partner->info.age += year;
		}else{
			node->info.age += year;
		}
		TimeSkip(node->fs,year);
		TimeSkip(node->nb,year);
	}
}

void nbUpgrade(nbAddr *root){
	nbAddr temp;
	temp= (*root)->nb;
	if ((*root)->fs==NULL)
		(*root)->fs=temp;
	while(temp!=NULL){
		temp->parent= *root;
		temp=temp->nb;
	}
}

void PrintFromFile(const char* name){
	FILE *read;
	char c;

	read=fopen(name, "rt");
	while((c=fgetc(read))!=EOF){
		printf("%c", c);
	}

	fclose(read);
}

void ProceedTimeSkip(nbAddr *root, int year)
{
    TimeSkip(*root,year);
}

void deleteNode(nbAddr *pDel, nbTree *pTree){
	nbAddr pCur;
	pCur=*pDel;

	if((*pTree).root == NULL) //kondisi ketika root kosong
	{
		printf("Tree Kosong");
		return;
	}
	if (pCur==(*pTree).root) //kondisi ketika yang dihapus adalah root
	{
	    if(pCur->fs != NULL){
            if(pCur->fs->info.gender == MALE){
                if(pCur->fs->info.age < 19){
                    int timespan = 19 - pCur->fs->info.age;
                    TimeSkip((*pTree).root, timespan);
                }
            }
	    }
	    else{
		(*pTree).root=NULL;
		return;
	    }
	}
	//kondisi node merupakan leaf dan jika merupakan first son maka next brothernya menjadi first son
	if(pCur->fs == NULL)
	{
		if(pCur->parent->fs == pCur) //kondisi ketika node merupakan anak pertama dari parent
		{
			if(pCur->nb != NULL) //ketika first son memiliki sibling
				pCur->parent->fs = pCur->nb;
			else
				pCur->parent->fs = NULL;
			nbDNode(&(*pDel));
		}else //kondisi ketika node bukan merupakan anak pertama
		{
			pCur = pCur->parent->fs; //pCur ditunjuk ke anak pertama
			while(pCur->nb != *pDel) //pencarian node sebelum pDel
				pCur = pCur->nb;
			if((*pDel)->nb == NULL) //kondisi ketika pDel merupakan last son
			{
				pCur->nb = NULL;
				nbDNode(&(*pDel));
			}
			else //kondisi ketika pDel bukan merupakan last son
			{
                pCur->nb = (*pDel)->nb;
				nbDNode(&(*pDel));
			}
		}
		return;
	}
	else //kondisi node memiliki child
	{
		while( pCur->fs!=NULL )
			pCur = pCur->fs; // pcur diisi dengan First son sampai null
		while (pCur != *pDel){
			nbUpgrade(&pCur);
			if (pCur->parent!=NULL)
				pCur->nb=pCur->parent->nb;
			else
				pCur->nb=NULL;
			pCur= pCur->parent;
		}

		pCur = *pDel;
		if(pCur->parent != NULL ) // ketika node memiliki parent
		{
			if(pCur->parent->fs == *pDel) //kondisi node merupakan first son dari parentnya
			{
				pCur->parent->fs=pCur->fs;
				pCur->fs->parent = pCur->parent;
				nbDNode(&(*pDel));
			}else //kondisi node bukan merupakan first son
			{
				pCur = (*pDel)->parent->fs;
				while(pCur->nb != *pDel) //pencarian node sebelum pDel
					pCur = pCur->nb;
				pCur->nb = (*pDel)->fs;
				if((*pDel)->nb == NULL)
					(*pDel)->fs->nb = NULL;
				else
					(*pDel)->fs->nb = (*pDel)->nb;
				nbDNode(&(*pDel));
			}
			return;
		}
		else //kondisi ketika yang dihapus merupakan root
		{
			(*pTree).root = pCur->fs	;
			(*pTree).root->parent = NULL;
			nbDNode(&(*pDel));
			return;
		}
	}
}
