#include "ig.h"



mpz_t nA;   //comme ca qu'il faut faire avec les clefs en globale 
mpz_t eA;//=90421;
mpz_t dA;//=25601;

mpz_t dB;//=10127;
mpz_t nB;//=114857; 
mpz_t eB;//=112703;
char* adr_fichier;
char* adr_fichier2;
char* adr_fichier3;

gchar* ID_user;

int main(int argc, char **argv)
{	
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
    return EXIT_SUCCESS;
}

