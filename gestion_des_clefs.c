#include "gestion_des_clefs.h"
//////////////////////////////////////////Fonctions pour les tests unitaires réalisés dans chaque fonctions///////////////////////////////////////////////////////////////
void test_unitaire_exponentiation_modulaire(mpz_t exp, mpz_t a, mpz_t p, mpz_t m)
{
	mpz_powm(exp,a,p,m);
}
void test_unitaire_inverse_modulaire(mpz_t inv, mpz_t a, mpz_t m)
{
	mpz_invert(inv, a, m);
}
bool test_premier( mpz_t var1)
{
	int premier = mpz_probab_prime_p(var1,50);
	
	if(premier > 0)
		return true;
	else return false;
}




void exponentiation_modulaire(mpz_t exp, mpz_t a, mpz_t p, mpz_t m)
{
	/*
	 * exp représente lla variable de sortie
	 * a représente la base
	 * p représente l'exposant
	 * m représente le modulo
	 */
	 
//déclaration des variables
mpz_t s,pui,un,tmp;		

//initialisation des variables
mpz_init(s);mpz_init(pui);mpz_init(un),mpz_init(tmp);

//affectation des valeurs
mpz_set_ui(exp,1); //r=1
mpz_set(s,a); //s=a
mpz_set_ui(un,1); //mpz_set(p,pui);	//un=1
mpz_set(tmp, p);

	if(mpz_cmp_ui(tmp,1)==0)			//si p = 1 renvoyer a
	{	
		mpz_set(exp,s);				
		mpz_mod(exp,exp,m);			//on renvoie a%m
	}
	else if(mpz_cmp_ui(tmp,0)==0)			//si p = 0 renvoyer 1
	{
		mpz_set(exp,un);				
		mpz_mod(exp,exp,m);				//on renvoie 1
	}

	else
	{
		while((mpz_cmp_ui(tmp,0)) > 0) 	//tant que (p>0) faire:
		{
			mpz_mod_ui(pui,tmp,2);		//pui=p%2
			
			if ((mpz_cmp_ui(pui,1))==0)  	//if (pui==1)
			{
				mpz_mul(exp,exp,s);			//r=r*s
				mpz_mod(exp,exp,m);			//r=r%m	
			}
			mpz_mul(s,s,s);			//s=s*s
			mpz_mod(s,s,m);			//s=s%m		
			mpz_mdiv_ui(tmp,tmp,2);		//p=p/2
		}
		mpz_mod(exp,exp,m);					//r=r%m		
	}
	
}
void inverse_modulaire(mpz_t inv, mpz_t a0, mpz_t m0)
{
	/*
	 * inv représente la variable de sortie
	 * a représente la base
	 * m représente le modulo
	 */
	 
	//déclaration des variables
	mpz_t a,m,u,s,q,r,tmp;
	
	//initialisation de variables
	mpz_init(a);mpz_init(m);mpz_init(u);mpz_init(s);mpz_init(q);mpz_init(r);mpz_init(tmp);
	
	//affectation desvaleurs
	mpz_set(a,a0);		//a=a0
	mpz_set(m,m0);		//m=m0
	mpz_set_ui(u,1);	//u=1
	mpz_set_ui(s,0);	//s=0
	
	while(mpz_cmp_ui(m,0) != 0)		//tant que m!=0 faire:
	{
		mpz_div(q,a,m);				//q=a/m
		mpz_mod(r,a,m);				//r=a%m
		mpz_set(a,m);				//a=m
		mpz_set(m,r);				//m=r
		mpz_set(tmp,s);				//tmp=s
		mpz_mul(q,q,s);				//q=q*s
		mpz_sub(s,u,q);				//s=u-q
		mpz_set(u,tmp);				//u=tmp
	}
	if(mpz_cmp_ui(a,1) ==0)			//si a=1
	{
		while(mpz_cmp_ui(u,0) <0)		//tant que (u<0) faire:
		{
			mpz_add(u,u,m0);			//u=u+m0
		}
		mpz_set(inv, u);				//inv=u
	}
	else
		gmp_printf("%Zd n'est pas inversible modulo %Zd\n", a0, m0);
}
bool test_fermat(mpz_t var)
{
	//var est l'entier à tester
	
	//variable initialisée à 1000, cette dernière nous sert à éviter au maximum les nombres pseudo-premiers.
	mpz_t k;	
	mpz_init(k);
	mpz_set_ui(k,1000);
	
	//decaration des variables pour la fonction exponentiation modulaire
	mpz_t res,nmoins1,base,tmp;
	
	//initialisation de valeurs
	mpz_init(nmoins1);mpz_init(res);mpz_init(base);mpz_init(tmp);
	
	//affectation des valeurs
	mpz_sub_ui(nmoins1, var,1);	//nmoins1=var-1
	mpz_set(tmp, nmoins1);		//tmp=nmoins1
	mpz_set_ui(base, 2);		//base=2
	
	while(mpz_cmp(base,k)<0)		//tant que (base<k) faire:
	{
		exponentiation_modulaire(res, base, nmoins1,var);	//appel de la fonction exponentiation modulaire.
		if(mpz_cmp_ui(res,1) != 0) 							//test si la valeur de retour de l'exponentiation res!=1.
		{
		return false;						//si res!=1 var n'est pas premier
		}
		mpz_add_ui(base,base,1);			//sinon on incrémente la base pour tester si il n'y a pas de nbres pseudos-premiers.
	}
	
	return true; 
}
void creation_clef()
{
	mpz_t p,q,n,z,pmoins1, qmoins1,e,d,min,max,deux;
	mpz_init(p);
	mpz_init(q);
	mpz_init(n);
	mpz_init(z);
	mpz_init(pmoins1);
	mpz_init(qmoins1);
	mpz_init(e);
	mpz_init(d);
	mpz_init(min);
	mpz_init(max);
	mpz_init(deux);
	mpz_set_ui(deux,2);
	
	mpz_pow_ui(min,deux,512);
	mpz_pow_ui(max,deux,513);
	mpz_sub_ui(max,max,1);
	
	//Initialisation des nombres aleatoires
	int seed1;
	gmp_randstate_t etat1; 					  
	seed1 = time(NULL) ;
	gmp_randinit_default (etat1);
	gmp_randseed_ui(etat1, seed1);
	do
	{
		mpz_urandomm(p,etat1,max);
		
	}while(!test_fermat(p) || mpz_cmp(p,min)<=0);
	
	
	do
	{
		mpz_urandomm(q,etat1,max);		
		
	}while(!test_fermat(q) || mpz_cmp(q,min)<=0);
	


	mpz_mul(n,p,q);

	mpz_sub_ui(pmoins1, p, 1);
	mpz_sub_ui(qmoins1, q, 1);
	mpz_mul(z,pmoins1,qmoins1);

	mpz_t r,a,b;
	mpz_init(r);
	mpz_init(a);
	mpz_init(b);
	do
	{
		mpz_set(a,z);
		mpz_urandomm(e,etat1,z);
		mpz_set(b,e);
		mpz_set_ui(r,1);
		while(mpz_cmp_ui(r,0)!=0)
		{
			mpz_mod(r,a,b);
			mpz_set(a,b);
			mpz_set(b,r);
		}
			
	}while(mpz_cmp_ui(a,1) !=0  || mpz_cmp_ui(e,1) <= 0);

	inverse_modulaire(d,e,z);

	/////////////////////////////////////////////////////////Enregistrement dans la mémoire/////////////////////////////////////////////////
	char*fichier;
	
	fichier=malloc(sizeof(char)*15);
	strcpy(fichier,ID_user);
	strcat(fichier,".txt");
	FILE * fichier1 = fopen("annuaire.txt","a");
	FILE * fichier2 = fopen(fichier,"w");
	gmp_fprintf(fichier1,"%s %Zd %Zd\n\n",ID_user,n,e);
	gmp_fprintf(fichier2,"%Zd %Zd\n\n",d,n);
	fclose(fichier1);
	fclose(fichier2);
	mpz_clear(p);
	mpz_clear(q);
	mpz_clear(n);
	mpz_clear(z);
	mpz_clear(pmoins1);
	mpz_clear(qmoins1);
	mpz_clear(e);
	mpz_clear(d);
	mpz_clear(min);
	mpz_clear(max);
	mpz_clear(deux);

}

