#include "Clavier.h"

extern bool modifBuf;
extern char buf[256];
extern int posBuf;

bool Clavier::testChar() {
	return modifBuf;
}

char Clavier::getchar(){
	while(!modifBuf);
	modifBuf = false;
	posBuf = 0;
	return buf[0];
	/*
	semaphoreClavier.P();
	if (positioncourante<(TAILLE_BUF_CLAVIER-1)) {
	positioncourante=positioncourante+1;
	return buf[positioncourante-1];
	}
	else {
	positioncourante=0;
	return buf[(TAILLE_BUF_CLAVIER-1)];
	}
	*/
}

char* Clavier::getString(){
	while(!modifBuf);
	modifBuf = false;
	posBuf = 0;
	return buf;
}

void Clavier::set_leds(void) {
	ecrireOctet(0x60, 0xED);
}
