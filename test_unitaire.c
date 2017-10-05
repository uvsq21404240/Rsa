#include "gestion_des_clefs.h"
#include "ig.h"
mpz_t nA;
mpz_t eA;
mpz_t dA;

mpz_t dB;
mpz_t nB; 
mpz_t eB;
char* adr_fichier;
char* adr_fichier2;
char* adr_fichier3;
gchar* ID_user;

int test_Global(char *fichier_Clair,char *fichier_dechiffre){

 FILE *f_clair=NULL;
 FILE *f_dechiffre=NULL;
 char cl,ch;
 int test=1;
f_clair = fopen(fichier_Clair,"r");
f_dechiffre = fopen(fichier_dechiffre,"r");
    if (f_clair == NULL || f_dechiffre == NULL)
    {
        printf("erreur");
	return 0;
    }else{
	while ((cl = fgetc(f_clair)) != EOF && (ch = fgetc(f_dechiffre)) != EOF){
		if(cl != ch){	
				test=0;
		}
	}	
	}
  fclose(f_clair);
  fclose(f_dechiffre);
    return test;
}

int main(int argc, char **argv)
{
mpz_t exp,exp1,a,a1,p,p1,m,m1,inv,inv1,var,var1;
mpz_init(exp);
mpz_init(exp1);
mpz_init(a);
mpz_init(a1);
mpz_init(p);
mpz_init(p1);
mpz_init(m);
mpz_init(m1);
mpz_init(inv);
mpz_init(inv1);
mpz_init(var);
mpz_init(var1);
mpz_set_ui(a,423);
mpz_set_ui(a1,423);
mpz_set_ui(p,1000);
mpz_set_ui(p1,1000);
mpz_set_ui(m,1300);
mpz_set_ui(m1,1300);
mpz_set_ui(var,13);
mpz_set_ui(var1,13);
exponentiation_modulaire(exp,a,p,m);
inverse_modulaire(inv,a,m);
test_fermat(var);

test_unitaire_exponentiation_modulaire(exp1,a1,p1,m1);
test_unitaire_inverse_modulaire(inv1,a1,m1);
test_premier(var1);

if(mpz_cmp(exp,exp1)==0) gmp_printf("expo modulaire bon!\n");
if(mpz_cmp(inv,inv1)==0) gmp_printf("inv modulaire bon!\n");
if(mpz_cmp(var,var1)==0) gmp_printf("test de fermat bon!\n");

printf("\nlancement du test2\n");
printf("82");
mpz_init(nA);
mpz_init(eA);
mpz_init(dA); 
mpz_init(nB);
mpz_init(eB);
mpz_init(dB);

gtk_init(&argc, &argv);

Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
gtk_window_set_title(GTK_WINDOW(Fenetre), "Menu");
gtk_window_set_default_size(GTK_WINDOW(Fenetre), 400, 400);
g_signal_connect(G_OBJECT(Fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
Menu(Fenetre);

gtk_main();

int varTest=test_Global("dossier_test/fichierDeTest.txt","dossier_test/fichierDeTest_clair.txt");
	if(varTest==0){
		 printf("Le test à échoué \n");
	 }else{
	 printf("test bien passee\n");
	}
return EXIT_SUCCESS;

}
