run: all clean
		./rsa
test: testU clean
		./test


all: gestion_des_clefs.o main.o cryptage_signature.o decryptage_verification.o memoire.o ig.o
	gcc -o rsa gestion_des_clefs.o  cryptage_signature.o decryptage_verification.o memoire.o ig.o main.o -lgmp  `pkg-config --libs gtk+-2.0` -g

testU: gestion_des_clefs.o test_unitaire.o memoire.o ig.o cryptage_signature.o decryptage_verification.o
	gcc -o test gestion_des_clefs.o test_unitaire.o memoire.o ig.o cryptage_signature.o decryptage_verification.o -lgmp  `pkg-config --libs gtk+-2.0` -g

memoire.o : memoire.c memoire.h
	gcc -o memoire.o -c memoire.c  -lgmp `pkg-config --cflags gtk+-2.0` -g
	
gestion_des_clefs.o: gestion_des_clefs.c memoire.o
	gcc -o gestion_des_clefs.o -c gestion_des_clefs.c  -lgmp `pkg-config --cflags gtk+-2.0` -g
	
cryptage_signature.o: cryptage_signature.c gestion_des_clefs.o memoire.o 
	gcc -o cryptage_signature.o -c cryptage_signature.c  -lgmp `pkg-config --cflags gtk+-2.0` -g

decryptage_verification.o: decryptage_verification.c gestion_des_clefs.o memoire.o
	gcc -o decryptage_verification.o -c decryptage_verification.c  -lgmp `pkg-config --cflags gtk+-2.0` -g
	
ig.o : ig.c memoire.o gestion_des_clefs.o cryptage_signature.o decryptage_verification.o
	gcc -o ig.o -c ig.c  -lgmp `pkg-config --cflags gtk+-2.0` -g
	
main.o: main.c ig.o
	gcc -o main.o -c main.c -lgmp -Wall `pkg-config --cflags gtk+-2.0` -g
	
test_unitaire.o: test_unitaire.c gestion_des_clefs.o memoire.o cryptage_signature.o decryptage_verification.o ig.o
	gcc -o test_unitaire.o -c test_unitaire.c  -lgmp `pkg-config --cflags gtk+-2.0` -g
	
clean:
	rm -rf *.o
	rm -rf *_crypte.txt
	rm -rf rsa
	rm -rf test
clean_all:
	rm -rf *.o
	rm -rf *_crypte.txt
	rm -rf *_clair.txt
	rm -rf rsa
	rm -rf test

mprproper: clean
	rm -rf rsa
	rm -rf test	
