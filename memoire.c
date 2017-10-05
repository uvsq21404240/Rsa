#include "memoire.h"

//renvoie le contenu de la ligne où se trouve l'ID et NULL sinon

char* Renvoie_ligne(char* ID)
{
	int i = 0;
	int trouve = 0;
	FILE* f = NULL;
	char* ligne = malloc(sizeof(char)*TAILLE);
	f = fopen("annuaire.txt", "r");
	while(fgets(ligne, 10000, f) && trouve!= 8)
	{
		trouve = 0;
		for(i = 0; i < 8; i++)
			if(ligne[i] == ID[i])
				trouve += 1;
	}
	if(trouve==8)
		return ligne;
	else return NULL;
}

char* Renvoie_n(char* ID)
{
	char* ligne = Renvoie_ligne(ID);
	if(ligne == NULL)
	return NULL;
	int i = 9;									//on part du 9e caractere pour virer le numero etudiant
	char* n = malloc(sizeof(char)*TAILLE / 2);
	while(ligne[i] != ' ' && ligne[i] !='\n')
	{															//on copie n
		n[i - 9] = ligne[i];
		i++;
	}
	return n;
}

char* Renvoie_e(char* ID)
{
	char* ligne = Renvoie_ligne(ID);
	if(ligne == NULL)
		return NULL;
	int i = 9;									//on part du 9e caractere pour virer le numero etudiant
	int k = 0;
	char* e = malloc(sizeof(char)*TAILLE / 2);
	while(ligne[i] != ' ')						//on passe n
		i++;
	
	i++;	
	while(ligne[i] != '\n')
	{														//on copie e
		e[k] = ligne[i];
		k++;
		i++;
	}
	return e;
}
char* Renvoie_d(char* ID)
{
	FILE* f = NULL;
	char* ligne = malloc(sizeof(char)*TAILLE);
	char* fichier;
	fichier=malloc(sizeof(char)*350);
	strcpy(fichier,ID);
	strcat(fichier,".txt");
	f = fopen(fichier, "r");
	
	fgets(ligne, 10000, f);
	if(ligne == NULL)
		return NULL;
	int i = 0;									//on part du 9e caractere pour virer le numero etudiant
	char* n = malloc(sizeof(char)*TAILLE / 2);
	
	while(ligne[i] != ' ' && ligne[i] !='\n')
	{															//on copie n
		n[i] = ligne[i];
		i++;
	}
	return n;
}
void set_crypte()
{
	adr_fichier2=malloc(sizeof(char)*(strlen(adr_fichier)+7));
	strcpy(adr_fichier2,adr_fichier);
	adr_fichier2[strlen(adr_fichier2)-4]='\0';
	strcat(adr_fichier2,"_crypte.txt");
}
void set_clair()
{
	adr_fichier3=malloc(sizeof(char)*(strlen(adr_fichier)+6));
	strcpy(adr_fichier3,adr_fichier);
	adr_fichier3[strlen(adr_fichier3)-11]='\0';
	strcat(adr_fichier3,"_clair.txt");
}
