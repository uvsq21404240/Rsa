#include "cryptage_signature.h"
#include "gestion_des_clefs.h"

int tailleFichier(FILE * f) //cette fonction calcule la taille d'un fichier en nombre de caractères 
{             
	int taille=0;						
	char c=' ';
	if(f!=NULL)
	{
		while(fscanf(f,"%c",&c)!=EOF)
			taille++;
	}
	return taille;	
}
int nombreDebloc(char* nomFichier)     // cette fonction renvoie le nombre de blocs possible pour un fichier
{
	int tailleBloc=4;					//fichier spécifique et de taille de blocs spécifique	
	FILE* fich = NULL;
	fich = fopen(nomFichier, "r");
	int TAILLEMAX=tailleFichier(fich);	                //calcule la taille du fichier
	fseek(fich, 0, SEEK_SET);
	int nombreDeBlocs=(int)TAILLEMAX*3/tailleBloc;
	if((TAILLEMAX*3%tailleBloc)!=0)
		nombreDeBlocs=nombreDeBlocs+1;
	fclose(fich);
	return nombreDeBlocs;
}
void decoupage_Blocs(mpz_t* m_Clair_Decouper,mpz_t* m_Clair_ASCII)
{
	int i;									//cette fonction retourne un tableau de mpz_t 
	int j=0;								//apres avoir decouper le message en blocs de tailles égales et
	int tailleBloc=4;						//de taille inferieur à N 
	FILE* fich = NULL;						
	fich = fopen(adr_fichier, "r");
	int TAILLEMAX=tailleFichier(fich);
	fseek(fich, 0, SEEK_SET);
	int tailleAscii=TAILLEMAX*3;		
	char texte_ASCII[tailleAscii];         //tous les caractères du fichier en ascii
	char str[3];	                        //une chaine de caractères a 3 cases car un caractere en ascii au maximum  
	char tmp[3];			       	        //s'ecrit sur 3 chiffres
	int taille;    
	 
	mpz_t nombre_Bloc; 
	mpz_init(nombre_Bloc); 
	
	char* BLOC;
	int k;
	for(i=0; i<TAILLEMAX; i++)
	{
		int a=mpz_get_ui(m_Clair_ASCII[i]);
		sprintf(str, "%d",a);	                   //stocke le chiffre dans str en tant que chaine 
		taille=strlen(str); 
		if(taille==3)
		{
			for(k=0;k<3;k++)
			{
				texte_ASCII[j]=str[k];
				j++;
			}
		}
		else
		{
			tmp[0]='0';                      //on ajoute un "0" pour ceux qui sont écrits à deux chiffres
			tmp[1]=str[0];
			tmp[2]=str[1];
			for(k=0;k<3;k++)
			{
				texte_ASCII[j]=tmp[k];
				j++;
			}	 
		}
	}
	int f=0,m;
	BLOC=(char*)malloc(tailleAscii*sizeof(char));                      //découpage en bloc à tailles égales à tailleBloc
	for(m=0;m<tailleAscii;m=m+tailleBloc)								//et stocke le résultat en tant que mpz_t dans un tableau
	{	
		for(k=0;k<tailleBloc;k++)										//de type mpz_t "m_claire_decouper"
			BLOC[k]=texte_ASCII[m+k];
			
		gmp_sscanf(BLOC, "%Zd", nombre_Bloc ); 
		mpz_init_set(m_Clair_Decouper[f],nombre_Bloc);
		f++;	
	}
}
void chiffrement(mpz_t* m_chiffre,mpz_t* m_Claire_Decouper)
{
	int nombreDeBlocs=nombreDebloc(adr_fichier);
	int i;																	//fonction qui retourne un tableau de mpz_t après avoir
	mpz_t calcul;															//appliqué le système RSA sur chaque bloc 
	mpz_init(calcul);													//avec la clef publique du destinataire eB et nB
	
	mpz_t exp;
	mpz_init(exp);
	mpz_set(exp,eB);
	
	mpz_t mod ;
	mpz_init(mod);
	mpz_set(mod,nB);
	
	for(i=0;i<nombreDeBlocs;i++)
	{
		exponentiation_modulaire(calcul,m_Claire_Decouper[i],exp,mod);
		mpz_init_set(m_chiffre[i],calcul);
	}

}
void signer(mpz_t* m_signe,mpz_t* m_chiffre)
{
	int nombreDeBlocs=nombreDebloc(adr_fichier);
	int i;
	mpz_t calcul;													//fonction qui retourne un tableau de mpz_t après avoir
	mpz_init(calcul);												//appliqué le système RSA pour signer le message sur le résultat du chiffrement 
	
	mpz_t exp;														//avec la clef privée de l'expéditeur dA et nA
	mpz_init(exp);
	mpz_set(exp,dA);
	
	mpz_t mod ;
	mpz_init(mod);
	mpz_set(mod,nA);
	
	for(i=0;i<nombreDeBlocs;i++)
	{
		exponentiation_modulaire(calcul,m_chiffre[i],exp,mod);
		mpz_init_set(m_signe[i],calcul);
	}
}
void ecriture1(mpz_t* m_signe)
{            								                  //cette procédure écrit le résultat du chiffrement dans le fichier 
	FILE* fichier_chiffre = NULL;								//de sortie adr_fichier2
	int nombreDeBlocs=nombreDebloc(adr_fichier);
	int i;
	int j=0;
    fichier_chiffre = fopen(adr_fichier2, "w");
    if (fichier_chiffre != NULL)
    {
		for(i=0;i<nombreDeBlocs;i++)
		{
			gmp_fprintf(fichier_chiffre, "%Zd ", m_signe[i]);	
			j++;
			if((j%6)==0)
				fprintf(fichier_chiffre,"\n");
		}   
        fclose(fichier_chiffre);
	}
}
void crypter_Signer(char* nomFichier)
{												              //cette procédure est le main de ce module. la fonction transforme en ascii 
	FILE* fichier = NULL;                                    //chaque caractère et le stocke dans un tableau
	fichier=fopen(nomFichier, "r");
	int TAILLEMAX=tailleFichier(fichier);
	fseek(fichier, 0, SEEK_SET);
	int carcatereActuel=0;										
	int nombreDeBlocs=nombreDebloc(nomFichier);					//allocation de la mémoire au tableau mpz_t nécessaire 
	
	mpz_t* ascii=malloc((TAILLEMAX+1)* sizeof(mpz_t));
	mpz_t* m_Claire_Decouper=malloc(nombreDeBlocs*sizeof(mpz_t));
	mpz_t* m_chiffre=malloc(nombreDeBlocs*sizeof(mpz_t));
    mpz_t* m_signe=malloc(nombreDeBlocs*sizeof(mpz_t));
    
    int i=0;
	if (fichier != NULL)
    {
        do                                               // Boucle de lecture des caractères un par un							
        {
            carcatereActuel = fgetc(fichier);            //lecture dans le fichier et remplissage du tableau 
			mpz_init_set_ui(ascii[i],carcatereActuel);   //ascii chaque ascii[i] sera le code ascii du carectère lu
			i++;
        } while (carcatereActuel!= EOF); 
		fclose(fichier);
	}
	decoupage_Blocs(m_Claire_Decouper,ascii);
	chiffrement(m_chiffre,m_Claire_Decouper);	
	//~ chiffrement(m_signe,m_Claire_Decouper);	
	signer(m_signe,m_chiffre);
	ecriture1(m_signe);
}
