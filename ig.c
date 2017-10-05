#include "ig.h"
/**
 * \brief Cette fonction sert à supprimer tous les widgets de la fenêtre
 * \param container Un pointeur sur la fenêtre
 */
/////////////////////////////////Fonction pour vider le cache////////////////////////////////////
void ViderContenir(GtkContainer * container) //cette fonction permet de supprimer tout les GtkWidget qui sont dans les fenetres
{
		GList * fils =gtk_container_get_children(container);
		while(fils)
			{
				gtk_widget_destroy(fils->data);
				fils = g_list_next(fils);
			}
		g_list_free(fils);
}

/**
 * \brief Cette fonction affiche le Menu Principal
 */
 
//////////////////////////En-ete/////////////////////////////////////////////////////
void Menu(GtkWidget* Fenetre)
{	
	ViderContenir(GTK_CONTAINER(Fenetre));//vide le contenaire de la fenetre
	GtkWidget *pImage;
	Fenetre=gtk_widget_get_toplevel(Fenetre);
	ViderContenir(GTK_CONTAINER(Fenetre));
	GtkWidget *bouton, *box1, *bouton2;
	box1=gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(Fenetre), box1);// ajoute une vbox dans la fenetre , elle permet de stocker plus du Widget a la fois
	pImage = gtk_image_new_from_file("Image/1.png");//on charge une image dans pImage
    gtk_box_pack_start(GTK_BOX(box1), pImage, FALSE, FALSE, 0);// on ajoute l'image dans la vbox 
	bouton=gtk_toggle_button_new();// créer  un nouveau bouton
	pImage = gtk_image_new_from_file("Image/2.png");
	gtk_container_add(GTK_CONTAINER(bouton),pImage);
	g_signal_connect(G_OBJECT(bouton), "clicked",G_CALLBACK(Menu_principale),NULL);//si on click sur le bouton on lance la fonction Menu_principale
	gtk_box_pack_start(GTK_BOX(box1),bouton, TRUE, TRUE, 0);
	bouton2=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/3.png");
	gtk_container_add(GTK_CONTAINER(bouton2),pImage);
	g_signal_connect(G_OBJECT(bouton2), "clicked",G_CALLBACK(A_propos),NULL);
	gtk_box_pack_start(GTK_BOX(box1),bouton2, TRUE, TRUE, 0);
	pImage = gtk_image_new_from_file("Image/4.png");
    gtk_box_pack_start(GTK_BOX(box1), pImage, FALSE, FALSE, 0);
	gtk_widget_show_all(Fenetre);
}

/**
 * \brief Cette fonction affiche les informations à propos du projet
 */

void A_propos(Fenetre)
{
	ViderContenir(GTK_CONTAINER(Fenetre));
	GtkWidget *pImage;
	Fenetre=gtk_widget_get_toplevel(Fenetre);
	ViderContenir(GTK_CONTAINER(Fenetre));
	GtkWidget *bouton, *bo;
	bo=gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(Fenetre), bo);
	bouton=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/sanstitre.png");
	gtk_container_add(GTK_CONTAINER(bouton),pImage);
	g_signal_connect(G_OBJECT(bouton), "clicked",G_CALLBACK(Menu),NULL);
	gtk_box_pack_start(GTK_BOX(bo),bouton, TRUE, TRUE, 0);
	gtk_widget_show_all(Fenetre);
}

/**
 * \brief Cette fonction affiche le second menu (rentrer son ID, créer un nouvel utilisateur, etc)
 */
//////////// Fenetre principale pour s'identifier //////////////////////////////////////
void Menu_principale(GtkWidget* Fenetre)
{	
	GtkWidget *box;
	ViderContenir(GTK_CONTAINER(Fenetre));
	Fenetre=gtk_widget_get_toplevel(Fenetre);
	GtkWidget *pImage;
	ViderContenir(GTK_CONTAINER(Fenetre));
	GtkWidget *bouton, *bouton2, *bouton3;
	box=gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(Fenetre), box);
	pImage = gtk_image_new_from_file("Image/menup1.png");
    gtk_box_pack_start(GTK_BOX(box), pImage, FALSE, FALSE, 0);
	bouton3=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/menup2.png");
	gtk_container_add(GTK_CONTAINER(bouton3),pImage);
	g_signal_connect(G_OBJECT(bouton3), "clicked",G_CALLBACK(Menu_test),NULL);
	gtk_box_pack_start(GTK_BOX(box),bouton3, TRUE, TRUE, 0);
	bouton2=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/menup3.png");
	gtk_container_add(GTK_CONTAINER(bouton2),pImage);
	g_signal_connect(G_OBJECT(bouton2), "clicked",G_CALLBACK(Menu_creation_de_cle),NULL);
	gtk_box_pack_start(GTK_BOX(box),bouton2, TRUE, TRUE, 0);
	bouton=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/menup4.png");
	gtk_container_add(GTK_CONTAINER(bouton),pImage);
	g_signal_connect(G_OBJECT(bouton), "clicked",G_CALLBACK(Menu),NULL);
	gtk_box_pack_start(GTK_BOX(box),bouton, TRUE, TRUE, 0);
	gtk_widget_show_all(Fenetre);
}
/**
 * \brief Cette fonction vérifie si l'ID de l'utilisateur existe
 */
void Menu_test(GtkWidget* Fenetre)
{
	GtkWidget *Boite,*Entrer;
    gchar* texte;
    GtkTextBuffer* Buffer;
    GtkTextIter debut;
    GtkTextIter fin;
	Fenetre = gtk_widget_get_toplevel (Fenetre);
    Boite = gtk_dialog_new_with_buttons("Id utilisateur",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    Entrer= gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);
    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);
    switch(gtk_dialog_run(GTK_DIALOG(Boite)))/////Gere les evenements de la boite dialogue
        {
            case GTK_RESPONSE_OK: 
                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                gtk_text_buffer_get_start_iter(Buffer,&debut);
                gtk_text_buffer_get_end_iter(Buffer,&fin);
                texte = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
				ID_user = texte;
				if(Renvoie_ligne(ID_user)==NULL)
				{	avertissement(Fenetre); 
					Menu_principale2(Fenetre);}
				else Choix_expe(Fenetre);
                break;
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
            default:
                break;
        }       
    gtk_widget_destroy(Boite);
}
/**
 * \brief Cette fonction crée une nouvelle paire de clés
 */
void Menu_creation_de_cle(GtkWidget* Fenetre)
{
	GtkWidget *Boite,*Entrer;
    gchar* texte;
    GtkTextBuffer* Buffer;
    GtkTextIter debut;
    GtkTextIter fin;
	Fenetre = gtk_widget_get_toplevel (Fenetre);
    Boite = gtk_dialog_new_with_buttons("Saisie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    Entrer= gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);
    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);
    switch(gtk_dialog_run(GTK_DIALOG(Boite)))
        {
            case GTK_RESPONSE_OK:
                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                gtk_text_buffer_get_start_iter(Buffer,&debut);
                gtk_text_buffer_get_end_iter(Buffer,&fin);
                texte = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
				ID_user = texte;
				if(Renvoie_ligne(ID_user)==NULL && strlen(ID_user) == 8)
					{
						creation_clef();
						Choix_expe(Fenetre);
					}
				else
						{
						avertissement2(Fenetre); ////boite de dialogue , elle permet d'avertir l'user d'un probleme
						}
                break;
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
            default:
                break;
        }
    gtk_widget_destroy(Boite);	
}
/**
 * \brief Dans le cas où l'utilisateur a tapé un mauvais ID, cette fonction est appellée
 */
void Menu_principale2(GtkWidget* Fenetre)
{
	ViderContenir(GTK_CONTAINER(Fenetre));
	Fenetre=gtk_widget_get_toplevel(Fenetre);
	ViderContenir(GTK_CONTAINER(Fenetre));
	GtkWidget *bouton, *bouton2;
	GtkWidget *pImage;
	GtkWidget *box;
	box=gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(Fenetre), box);
	pImage = gtk_image_new_from_file("Image/menu21.png");
    gtk_box_pack_start(GTK_BOX(box), pImage, FALSE, FALSE, 0);
	bouton2=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/menu22.png");
	gtk_container_add(GTK_CONTAINER(bouton2),pImage);
	g_signal_connect(G_OBJECT(bouton2), "clicked",G_CALLBACK(Menu_creation_de_cle),NULL);
	gtk_box_pack_start(GTK_BOX(box),bouton2, TRUE, TRUE, 0);
	bouton=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/menu23.png");
	gtk_container_add(GTK_CONTAINER(bouton),pImage);
	g_signal_connect(G_OBJECT(bouton), "clicked",G_CALLBACK(Menu_principale),NULL);
	gtk_box_pack_start(GTK_BOX(box),bouton, TRUE, TRUE, 0);
	gtk_widget_show_all(Fenetre);
}

/**
 * \brief Cette fonction permet à l'utilisateur de choisir son interlocuteur
 */
////////////Fenetre pour choisir l'expediteur/////////////////////////////////////////
void Choix_expe(GtkWidget* Fenetre)
{
	ViderContenir(GTK_CONTAINER(Fenetre));
	Fenetre=gtk_widget_get_toplevel(Fenetre);
	ViderContenir(GTK_CONTAINER(Fenetre));
	GtkWidget *bouton, *bouton2;
	GtkWidget *pImage, *boxx;
	boxx=gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(Fenetre), boxx);
	pImage = gtk_image_new_from_file("Image/expo1.png");
    gtk_box_pack_start(GTK_BOX(boxx), pImage, FALSE, FALSE, 0);
	bouton2=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/expo2.png");
	gtk_container_add(GTK_CONTAINER(bouton2),pImage);
	g_signal_connect(G_OBJECT(bouton2), "clicked",G_CALLBACK(Menu_test2),NULL);
	gtk_box_pack_start(GTK_BOX(boxx),bouton2, TRUE, TRUE, 0);
	bouton=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/expo3.png");
	gtk_container_add(GTK_CONTAINER(bouton),pImage);
	gtk_box_pack_start(GTK_BOX(boxx),bouton, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(bouton), "clicked",G_CALLBACK(Menu_principale),NULL);
	gtk_box_pack_start(GTK_BOX(boxx),bouton, TRUE, TRUE, 0);
	gtk_widget_show_all(Fenetre);
}
/**
 * \brief Cette fonction vérifie si l'interlocuteur existe
 */
void Menu_test2(GtkWidget* Fenetre)
{	
	GtkWidget *Boite,*Entrer;
    gchar* texte;
    GtkTextBuffer* Buffer;
    GtkTextIter debut;
    GtkTextIter fin;
	Fenetre = gtk_widget_get_toplevel (Fenetre);
    Boite = gtk_dialog_new_with_buttons("Sasie du texte",GTK_WINDOW(Fenetre),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    Entrer= gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Boite)->vbox), Entrer, TRUE, TRUE,10);
    gtk_widget_show_all(GTK_DIALOG(Boite)->vbox);
    switch(gtk_dialog_run(GTK_DIALOG(Boite)))
        {
            case GTK_RESPONSE_OK:
                Buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(Entrer));
                gtk_text_buffer_get_start_iter(Buffer,&debut);
                gtk_text_buffer_get_end_iter(Buffer,&fin);
                texte = gtk_text_buffer_get_text(Buffer,&debut,&fin,FALSE);
                ID_user2 = texte;          
                if(Renvoie_ligne(ID_user2)!=NULL)
					{				
						Ouvrir_un_fichier(Fenetre);
					}
				else
					{
						avertissement(Fenetre); ////boite de dialogue , elle permet d'avertir l'user d'un probleme
					}
                break;
            case GTK_RESPONSE_CANCEL:
            case GTK_RESPONSE_NONE:
            default:
                break;
        }   
    gtk_widget_destroy(Boite);
}
/**
 * \brief Cette fonction permet à l'utilisateur de choisir l'adresse d'un fichier
 */
/////////////// Fenetre pour trouver addresse d'un fichier///////////////////////////////
void Ouvrir_un_fichier(GtkWidget* Fenetre)
{
	Fenetre=gtk_widget_get_toplevel(Fenetre);
	ViderContenir(GTK_CONTAINER(Fenetre));
	GtkWidget *boxXX, *bouton, *pImage;
	boxXX=gtk_vbox_new(TRUE,0);
	gtk_container_add(GTK_CONTAINER(Fenetre), boxXX);
	bouton=gtk_toggle_button_new();
	pImage = gtk_image_new_from_file("Image/source.png");
	gtk_container_add(GTK_CONTAINER(bouton),pImage);
	g_signal_connect(G_OBJECT(bouton), "clicked",G_CALLBACK(creer_file_selection),NULL);
	gtk_box_pack_start(GTK_BOX(boxXX),bouton, TRUE, TRUE, 0);
	gtk_widget_show_all(Fenetre);
}
void creer_file_selection()
{
    GtkWidget *selection;
    selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
    gtk_widget_show(selection);
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(recuperer_chemin), selection ); 
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
    const gchar* chemin1;
    GtkWidget *dialog;
    chemin1 = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );
    adr_fichier = chemin1;
    dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"Vous avez choisi :\n%s", chemin1);
    							// fonction pour créer une adr_fichier2
     							// fonction pour créer une adr_fichier3
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
    MenuPrincipal(Fenetre);
}
/**
 * \brief Cette fonction permet de choisir l'action à effectuer
 */
///////////////////////////Fenetre pour choisir decrypter ou crypter///////////////////////
void MenuPrincipal(GtkWidget *Fenetre)
{
	ViderContenir(GTK_CONTAINER(Fenetre));
    Fenetre = gtk_widget_get_toplevel (Fenetre);
	GtkWidget *Box,*Bouton1, *Bouton2, *pImage;
    Box = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(Fenetre), Box);
    pImage = gtk_image_new_from_file("Image/last1.png");
    gtk_box_pack_start(GTK_BOX(Box), pImage, FALSE, FALSE, 0);
    Bouton1 = gtk_toggle_button_new();
    pImage = gtk_image_new_from_file("Image/last2.png");
	gtk_container_add(GTK_CONTAINER(Bouton1),pImage);
    g_signal_connect(G_OBJECT(Bouton1), "clicked", G_CALLBACK(signerr), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton1, TRUE, TRUE, 0);
    Bouton2 = gtk_toggle_button_new();
    pImage = gtk_image_new_from_file("Image/last3.png");
    gtk_container_add(GTK_CONTAINER(Bouton2),pImage);
    g_signal_connect(G_OBJECT(Bouton2), "clicked", G_CALLBACK(verifierr), NULL);
    gtk_box_pack_start(GTK_BOX(Box), Bouton2, TRUE, TRUE, 0);
	gtk_widget_show_all(Fenetre);
}

void signerr()
{             
	set_crypte(); 
	char* Na;
	char* Da;
	char* Ea;
	char* Nb;
	char* Db;
	char* Eb;
	Na = Renvoie_n(ID_user);
	Ea = Renvoie_e(ID_user);
	Da = Renvoie_d(ID_user);
	if(Ea==NULL) printf("ea nul");
	if(Na==NULL) printf("na nul");
	if(Da==NULL) printf("da nul");
	gmp_sscanf(Ea, "%Zd", eA);
	gmp_sscanf(Na, "%Zd", nA);
	gmp_sscanf(Da, "%Zd", dA);
	Eb = Renvoie_e(ID_user2);
	Nb = Renvoie_n(ID_user2);
	Db = Renvoie_d(ID_user2);
	if(Eb==NULL) printf("eb nul");
	if(Nb==NULL) printf("nb nul");
	if(Db==NULL) printf("db nul");
	gmp_sscanf(Eb, "%Zd", eB);	
	gmp_sscanf(Nb, "%Zd", nB);
	gmp_sscanf(Db, "%Zd", dB);
	crypter_Signer(adr_fichier);
	signer_dialogue(Fenetre);
	mpz_clear(eB);
	mpz_clear(nB);
	mpz_clear(dB);
	mpz_clear(eA);
	mpz_clear(nA);
	mpz_clear(dA);
	Menu(Fenetre);
}
void verifierr()
{
	set_clair(); 
	char tmp[8];
	strcpy(tmp,ID_user);
	strcpy(ID_user,ID_user2);
	strcpy(ID_user2,tmp);
	char* Na;
	char* Da;
	char* Ea;
	char* Nb;
	char* Db;
	char* Eb;
	Na = Renvoie_n(ID_user);
	Ea = Renvoie_e(ID_user);
	Da = Renvoie_d(ID_user);
	if(Ea==NULL) printf("ea nul");
	if(Na==NULL) printf("na nul");
	if(Da==NULL) printf("da nul");
	gmp_sscanf(Ea, "%Zd", eA);
	gmp_sscanf(Na, "%Zd", nA);
	gmp_sscanf(Da, "%Zd", dA);
	Eb = Renvoie_e(ID_user2);
	Nb = Renvoie_n(ID_user2);
	Db = Renvoie_d(ID_user2);
	if(Eb==NULL) printf("eb nul");
	if(Nb==NULL) printf("nb nul");
	if(Db==NULL) printf("db nul");	
	gmp_sscanf(Eb, "%Zd", eB);	
	gmp_sscanf(Nb, "%Zd", nB);
	gmp_sscanf(Db, "%Zd", dB);
	decrypter_Verifier(adr_fichier);
	verifier_dialogue(Fenetre);
	mpz_clear(eB);
	mpz_clear(nB);
	mpz_clear(dB);
	mpz_clear(eA);
	mpz_clear(nA);
	mpz_clear(dA);
	Menu(Fenetre);
}
////////////////////////////////////////Boite de dialogue////////////////////////////
void avertissement(GtkWidget* Fenetre)
{
	GtkWidget *Boite;
    gchar *sSite= "Cet utilisateur n'existe pas";
	Fenetre = gtk_widget_get_toplevel (Fenetre);
    Boite  = gtk_message_dialog_new (GTK_WINDOW(Fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_WARNING,
        GTK_BUTTONS_OK,
        "Avertissement\n%s",
        sSite);
	gtk_dialog_run(GTK_DIALOG(Boite));
    gtk_widget_destroy(Boite); /* Destruction de la boite de message */
}
void avertissement2(GtkWidget* Fenetre)
{
	GtkWidget *Boite;
    gchar *sSite= "Impossible de créer un nouvel utilisateur, veuillez saisir un id de taille 8 ";
	Fenetre = gtk_widget_get_toplevel (Fenetre);
    Boite  = gtk_message_dialog_new (GTK_WINDOW(Fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "Avertissement\n%s",
        sSite);
	gtk_dialog_run(GTK_DIALOG(Boite));
    gtk_widget_destroy(Boite);
}
void signer_dialogue(GtkWidget* Fenetre)
{
	GtkWidget *Boite;
	gchar *ite= adr_fichier;
    gchar *sSite= ID_user;
    gchar *Site= ID_user2;
	Fenetre = gtk_widget_get_toplevel (Fenetre);
    Boite  = gtk_message_dialog_new (GTK_WINDOW(Fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Information\n Votre fichier %s a bien été signé par: %s \n et envoyé à votre correpondant %s " ,
        ite,sSite ,Site );
	gtk_dialog_run(GTK_DIALOG(Boite));
    gtk_widget_destroy(Boite);
}
void verifier_dialogue(GtkWidget* Fenetre)
{
	GtkWidget *Boite;
	gchar *ite= adr_fichier;
    gchar *sSite= ID_user;
    gchar *Site= ID_user2;
	Fenetre = gtk_widget_get_toplevel (Fenetre);
    Boite  = gtk_message_dialog_new (GTK_WINDOW(Fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Information\n Votre Fichier %s a bien été envoyé par  %s \n pour: %s",
        ite,Site,sSite);
	gtk_dialog_run(GTK_DIALOG(Boite));
    gtk_widget_destroy(Boite);
}

