#include "kopiec.h"

Kopiec::Kopiec(int n) {
	this->ilosc_elementow_kopca = n;
	tab_nr_wierzcholka_kopca = new int[n];
	tab_pozycja_wierzcholka_kopca = new int[n];
	this->korzen = 0;
}

void Kopiec::UstawKopiec() {
	for (int i = 0; i < ilosc_elementow_kopca; i++) {
		tab_nr_wierzcholka_kopca[i] = i;
		tab_pozycja_wierzcholka_kopca[i] = i;
	}
}

void Kopiec::WyswietlKopiec() {
	for (int i = 0; i < ilosc_elementow_kopca; i++) {
		std::cout << tab_nr_wierzcholka_kopca[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < ilosc_elementow_kopca; i++) {
		std::cout << tab_nr_wierzcholka_kopca[i];
	}
	std::cout << std::endl;
}

void Kopiec::KopiecPoZmianieKDV(int v) { //Odtworz wlasnosci kopca po zmianie tab_kd[v]
	int tmp;
	tmp = tab_nr_wierzcholka_kopca[0];
	tab_nr_wierzcholka_kopca[0] = tab_nr_wierzcholka_kopca[v];
	tab_nr_wierzcholka_kopca[v] = tmp;
	tab_pozycja_wierzcholka_kopca[0] = v;
	tab_pozycja_wierzcholka_kopca[v] = 0;
}

void Kopiec::StworzKopiec(int* tab_kd, int* tab_pw, bool* tab_QS, ListaSasiedztwa** graf, ListaSasiedztwa* wsk, int v) {
	int rodzic, potomek, lewy, prawy, kd_min, pw_min, tmp;
	korzen = tab_nr_wierzcholka_kopca[0];
	tab_nr_wierzcholka_kopca[0] = tab_nr_wierzcholka_kopca[ilosc_elementow_kopca - 1];
	ilosc_elementow_kopca = ilosc_elementow_kopca - 1;
	tab_pozycja_wierzcholka_kopca[tab_nr_wierzcholka_kopca[0]] = 0;
	rodzic = 0;
	for (;;) {
		lewy = 2 * rodzic + 1;
		prawy = lewy + 1;
		if (lewy >= ilosc_elementow_kopca) break;
		kd_min = tab_kd[tab_nr_wierzcholka_kopca[lewy]];
		pw_min = lewy;
		if ((prawy < ilosc_elementow_kopca) && (kd_min > tab_kd[tab_nr_wierzcholka_kopca[prawy]])) {
			kd_min = tab_kd[tab_nr_wierzcholka_kopca[prawy]];
			pw_min = prawy;
		}
		if (tab_kd[tab_nr_wierzcholka_kopca[rodzic]] <= kd_min) break;
		tmp = tab_nr_wierzcholka_kopca[rodzic];
		tab_nr_wierzcholka_kopca[rodzic] = tab_nr_wierzcholka_kopca[pw_min];
		tab_nr_wierzcholka_kopca[pw_min] = tmp;
		tab_pozycja_wierzcholka_kopca[tab_nr_wierzcholka_kopca[rodzic]] = rodzic;
		tab_pozycja_wierzcholka_kopca[tab_nr_wierzcholka_kopca[pw_min]] = pw_min;
		rodzic = pw_min;
	}
	tab_QS[korzen] = true;
	for (wsk = graf[korzen]; wsk; wsk = wsk->nastepny) {
		if (!tab_QS[wsk->v] && (tab_kd[wsk->v] > tab_kd[korzen] + wsk->w)) {
			tab_kd[wsk->v] = tab_kd[korzen] + wsk->w;
			tab_pw[wsk->v] = korzen;

			potomek = tab_pozycja_wierzcholka_kopca[wsk->v];
			for (;;) {
				if (potomek == 0) break;
				rodzic = potomek / 2;
				if (tab_kd[tab_nr_wierzcholka_kopca[rodzic]] <= tab_kd[tab_nr_wierzcholka_kopca[potomek]]) break;
				tmp = tab_nr_wierzcholka_kopca[rodzic];
				tab_nr_wierzcholka_kopca[rodzic] = tab_nr_wierzcholka_kopca[potomek];
				tab_nr_wierzcholka_kopca[potomek] = tmp;
				tab_pozycja_wierzcholka_kopca[tab_nr_wierzcholka_kopca[rodzic]] = rodzic;
				tab_pozycja_wierzcholka_kopca[tab_nr_wierzcholka_kopca[potomek]] = potomek;
				potomek = rodzic;
			}
		}
	}
}
