#include "decryptage_verification.h"
#include "gestion_des_clefs.h"
int nombreDeBlocs(char* nomFichier)
{												           //fonction qui calcule le nombre de blocs (mot) dans un fichier 
	int inside_word=0; 
	char C;
	int NMOTS=0;
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, "r");
	while(!feof(fichier))
	{
		C=fgetc(fichier);
		if(isspace(C))          							            //les blocs sont separés par des espaces dans le fichier 
		{																// si on lit un espace cela dit que le bloc est terminé 
			if (inside_word)											//et on incrémente NMOTS;
			{
				NMOTS++;
				inside_word=0; 
			}
		}
		else
			inside_word=1;
	}
	return NMOTS;
}
void verification(mpz_t* m_Chiffree)
{
	int nombreBlocs=nombreDeBlocs(adr_fichier);
	int i;
	mpz_t calcul;
    mpz_init(calcul);                                 //fonction qui retourne un tableau de mpz_t après avoir
	
	mpz_t exp;										 //appliqué le système RSA sur chaque bloc 
    mpz_init(exp);									//avec la clef publique de l'expéditeur  eA et nA
	mpz_set(exp,eA);
	
	mpz_t mod ;
    mpz_init(mod);
	mpz_set(mod,nA);
	
	for(i=0;i<nombreBlocs;i++)
	{
		mpz_init(calcul);
		exponentiation_modulaire(calcul,m_Chiffree[i],exp,mod);
		mpz_set(m_Chiffree[i],calcul);
	}	
}
void dechiffrement(mpz_t* m_Chiffree)
{		
	int nombreBlocs=nombreDeBlocs(adr_fichier);
	int i; 													//fonction qui retourne un tableau de mpz_t après avoir
	mpz_t calcul;											//appliqué le système RSA pour décrypter le message sur le résultat de la vérification 
	
	mpz_t exp;												//avec la clef privée de l'utilisateur en cours dB et nB
	mpz_init(exp);
	mpz_set(exp,dB);
	
	mpz_t mod ;
	mpz_init(mod);
	mpz_set(mod,nB);
	
	for(i=0;i<nombreBlocs;i++)
	{
		mpz_init(calcul);
		exponentiation_modulaire(calcul,m_Chiffree[i],exp,mod);
		mpz_set(m_Chiffree[i],calcul);
	}
}
char* convertir_en_Caractere(mpz_t* m_Chiffree)
{															          //fonction qui retourne une chaine de caractère 
	int tailleBloc=4;//global
	int nombreBlocs=nombreDeBlocs(adr_fichier);                         
	char*  ascii;
	ascii=(char*)malloc(2*nombreBlocs*tailleBloc*sizeof(char));
	char  str[tailleBloc];
	int i,k,j,m;
	char* res=(char*)malloc(2*nombreBlocs*tailleBloc*sizeof(char));
	int cmp_zeros;
	int z=0;	
	for(i=0;i<nombreBlocs;i++)
	{
		for(k=0;k<tailleBloc;k++)
		{
			gmp_sprintf(str, "%Zd",m_Chiffree[i]);
			str[strlen(str)]='\0';
			cmp_zeros=tailleBloc-strlen(str);            // compter le nombre de zéros à ajouter
			for(m=0;m<cmp_zeros;m++)
			{						 				                   // à faire si cmp_zero!=0	
				ascii[k]='0';
				res[z]=	ascii[k];
				z++;						             				// ajouter autant de 0 qu'il faut si c'est 0 on va pas entrer dans la boucle
				k++;
			}
			for (j=0; j<tailleBloc-cmp_zeros;j++)
			{													     // continuer à copier les autres chiffres du bloc	
				ascii[k]=str[j]; 
			    res[z]=	ascii[k];	
				z++;   
				k++;
			}
		}
	}
	gmp_sprintf(str, "%Zd",m_Chiffree[nombreBlocs-1]);
	int N=strlen(str);
	str[N]='\0';
	int f;
	for(f=0;f<N;f++)
	{		                          //le dernier bloc on ne lui ajoute pas de "0"
		res[z]=str[f];
		z++;
	}
	return res;
}
void ecriture2(char* m_dechiffree)
{									                          //procédure qui découpe la chaine 3 par 3 et converti le mot en int 
	int tailleBloc=4;										 //et le cast en caractère et l'écrit dans le fichier de sortie 	
	int nombreBlocs=nombreDeBlocs(adr_fichier);              
	FILE* fichier_dechiffree = NULL;
	int i;
	char str[3];
	int asci=0;
	int k;
	char c;
    fichier_dechiffree = fopen(adr_fichier3, "w");
    if (fichier_dechiffree != NULL)
    {	
		int z=3;
		for(i=0;i<nombreBlocs*tailleBloc;i=i+z)
		{
			z=3;
			int j=0;
			for(k=0; k<z;k++)
			{
				c=m_dechiffree[i+k];
				if(c==' ')
					z=4;
				else
				{
					str[j]=m_dechiffree[i+k];
					j++;
				}
			}
			str[3]='\0';
			sscanf(str,"%d",&asci);
			char c=asci;
			fputc(c,fichier_dechiffree);
		}
	}
	fclose(fichier_dechiffree);
}
void decrypter_Verifier(char* nomFichier)
{																		//cette procédure est le main de ce module. On lit le fichier chiffré  
	int tailleBlocs=4;													 //et stocke chaque bloc lu en tant que mpz_t dans le tableau m_Chiffree
	FILE* fichier = NULL;												//et fait appel aux fonctions :verification , dechiffremen,convertire en caracteres, et a la procedure : ecriture2  
	fichier = fopen(nomFichier,"r");
	
	int nombreBlocs=nombreDeBlocs(nomFichier);
	int inside_word=0;
	int NMOTS=0; 
	char C;
	char mot[1000];
	
	int i;
	mpz_t* m_Chiffree=malloc(nombreBlocs*sizeof(mpz_t));
	int j=0;
	for(i=0;i<nombreBlocs;i++)
		mpz_init(m_Chiffree[i]);
		
	i=0;
	while (!feof(fichier))
	{
		C=fgetc(fichier);
		if(isspace(C))
		{
			if (inside_word)
            {
			  NMOTS++;
			  inside_word=0;
			  i=0;
			  gmp_sscanf(mot, "%Zd",m_Chiffree[j]); 
			  j++;
			  memset (mot, 0, sizeof (mot));
			}
		}
		else
			inside_word=1;
		mot[i]=C;
		i++;
	}
	verification(m_Chiffree);
	dechiffrement(m_Chiffree);
	char* chaine;
	chaine=(char*)malloc(nombreBlocs*tailleBlocs*sizeof(char));
	chaine=convertir_en_Caractere(m_Chiffree);
	ecriture2(chaine);
	
}

