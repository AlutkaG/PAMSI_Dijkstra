#ifndef kopiec_h
#define kopiec_h
#include <iostream>
#include "listaSasiedztwa.h"

class Kopiec {
	int ilosc_elementow_kopca;
	int korzen;
	int* tab_nr_wierzcholka_kopca, * tab_pozycja_wierzcholka_kopca;
public:
	Kopiec(int n);
	void UstawKopiec();
	void KopiecPoZmianieKDV(int v); //Odtworz wlasnosci kopca po zmianie tab_kd[v]
	void WyswietlKopiec();
	void StworzKopiec(int* tab_kd, int* tab_pw, bool* tab_QS, ListaSasiedztwa** graf, ListaSasiedztwa* wsk, int v);
};

#endif 

