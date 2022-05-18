#ifndef royalTree_H
#define royalTree_H

#define MALE 1
#define FEMALE 0

typedef char nbType[20];
typedef struct royalTree *nbAddr;
typedef struct pair *pairAddr;

struct identity{
	nbType name;
	int age;
	bool gender;
};

typedef struct pair{
	identity info;
	nbAddr partner;
}nbPairNode;

typedef struct royalTree{
	nbAddr fs;
	nbAddr nb;
	nbAddr parent;
	identity info;
	pairAddr partner;
}nbTreeNode;

struct nbTree{
	nbAddr root;
};

void nbCreate(nbTree *X);
/*Membuat tree kosong*/

nbAddr nbCNode(nbAddr parent, nbType name, int age, bool gender);
/*Alokasi node*/

pairAddr nbCPartnerNode(nbType name, int age, bool gender, nbAddr partner);
/*Alokasi partner node*/

void InsertNode(nbTree *tRoot, nbAddr newNode);
/*Insert node berdasarkan address*/

void InsertFamilyMember(nbTree *pTree);
/*Insert node ke tree*/

void InsertKing(nbTree *pTree);

void deleteNode(nbAddr *pDel, nbTree *pTree);

nbAddr nbSearch(nbAddr root, nbType src);
/*Search node tree dan mengembalikan address */

void nbPrint(nbAddr node, char tab[]);

void PrintFromFile(const char* name);

void ShowNodeInfo(nbAddr node);

void InsertVPartner(nbTree *pTree);
/*Insert partner berdasarkan variable*/

void InsertPartner(nbAddr familyMember, pairAddr partner);
/*Insert partner berdasarkan alamat*/

void TimeSkip(nbAddr node, int year);

void ProceedTimeSkip(nbAddr *node, int year);

#endif
