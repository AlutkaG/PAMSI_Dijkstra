#include <iostream>
#include <iomanip>
#include "macierzSasiedztwa.h"
#include "kopiec.h"
#include<ctime>
#include <fstream>
#include <Windows.h>
#define INF 1234567890

void ZainicjujTablice(int* tab_koszt, int* tab_poprzednik, bool* tab_QS, ListaSasiedztwa** graf,MacierzSasiedztwa **grafm, int n) {
	for (int i = 0; i < n; i++) {
		tab_koszt[i] = INF;
		tab_poprzednik[i] = -1;
		tab_QS[i] = false;
		graf[i] = NULL;
		grafm[i] = NULL;
	}
}

void OdczytDanych(int m, ListaSasiedztwa* wsk, ListaSasiedztwa** graf) {
	int x, y, w;
	for (int i = 0; i < m; i++) {
		std::cin >> x >> y >> w;
		wsk = new ListaSasiedztwa;
		wsk->v = y;
		wsk->w = w;
		wsk->nastepny = graf[x];
		graf[x] = wsk;
	}
}

void LosujDaneMacierz(int m, int n, MacierzSasiedztwa* wsk, int** mac) {
	int x, y, w;

	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			x = rand()%n;
			y = rand()%n;
			mac[x][y] = rand() % 10;
			wsk->wagi[i] = rand() % 10;
			if (i == j) mac[x][y] = 0;
		}
	}

	wsk->A = mac;
}

void LosujDaneLista(int m,int n, ListaSasiedztwa* wsk, ListaSasiedztwa** graf) {
	int x, y, w,tmp=0;
	for (int i = 0; i < m; i++) {
		wsk = new ListaSasiedztwa;
		x = rand()%n;
		y = rand() % n;
		if (tmp != x) {
			wsk->v = y;
			wsk->w = rand() % 10;
			wsk->nastepny = graf[x];
			graf[x] = wsk;
			tmp = x;
		}
		else {
			x = rand() % n;
			wsk->v = y;
			wsk->w = rand() % 10;
			wsk->nastepny = graf[x];
			graf[x] = wsk;
			tmp = x;
		}
		
	}
}

void WyswietlWyniki(int n, int* tab_kd, int* tab_pw, int* tab_S) {
	int pom = 0;
	for (int i = 0; i < n; i++) {
		std::cout << i << ": ";
		for (int j = i; j > -1; j = tab_pw[j])
			tab_S[pom++] = j;
		while (pom)
			std::cout << tab_S[--pom] << " ";
		std::cout << "$" << tab_kd[i] << std::endl;
	}
}

int main() {
	srand((int)time(NULL));
	int n, m, v,opcja; //liczba wierzcholkow, liczba krawedzi, wezel startowy
	int* tab_kd; //tablica kosztow dojscia od wierzcholka v do wierzolka i-tego wzdluz najkrotszej sciezki
	int* tab_pw; //tablica dla i-tego wierzcholka grafu zawierajaca nr wierzcholka poprzedniego na najkrotszej sciezce
	bool* QS;
	int* tab_S;
	ListaSasiedztwa* wskLista;
	ListaSasiedztwa** grafLista;
	int* wagi;
	MacierzSasiedztwa* wskMacierz;
	MacierzSasiedztwa** grafMacierz;
	int** mac;
	double czas, calkowity_czas = 0,gestosc=0;
	clock_t start, stop;
	
	std::cout << "------------Menu------------\n";
	std::cout << "1 - Reprezentacja grafu: lista sasiedztwa / Sposob testowania: testy efektywnosci\n";
	std::cout << "2 - Reprezentacja grafu: lista sasiedztwa / Sposob testowania: wczytanie danych z pliku\n";
	std::cout << "3 - Reprezentacja grafu: macierz sasiedztwa / Sposob testowania: testy efektywnosci\n";
	std::cout << "4 - Reprezentacja grafu: macierz sasiedztwa / Sposob testowania: wczytanie danych z pliku\n";
	std::cout << "5 - wyswietl ponownie menu\n";
	std::cout << "0 - zakoncz dzialanie programu\n";
	do {
		std::cout << "Wybierz opcje:\n"; std::cin >> opcja;
		switch (opcja) {
		case 1: {
			std::cout << "Podaj ilosc krawedzi, wierzcholkow i wierzcholek startowy grafu:" << std::endl;
			std::cin >> n >> v;
			std::cout << "Podaj gestosc grafu:" << std::endl;
			std::cin >> gestosc;
			m = n * (n - 1) * gestosc / 2;
			tab_kd = new int[n];
			tab_pw = new int[n];
			QS = new bool[n];
			tab_S = new int[n];

			grafLista = new ListaSasiedztwa * [n];
			wskLista = new ListaSasiedztwa[n];
			grafMacierz = new MacierzSasiedztwa * [n];
			ZainicjujTablice(tab_kd, tab_pw, QS, grafLista, grafMacierz, n);
			for (int i = 0; i < 100; i++) {
				start = clock();
				Kopiec* kopiec = new Kopiec(n);
				LosujDaneLista(m, n, wskLista, grafLista);
				kopiec->UstawKopiec();
				tab_kd[v] = 0;
				kopiec->KopiecPoZmianieKDV(v);
				for (int i = 0; i < n; i++)
					kopiec->StworzKopiec(tab_kd, tab_pw, QS, grafLista, wskLista, v);
				stop = clock();
				czas = (double)(stop - start) / CLOCKS_PER_SEC;
				calkowity_czas = calkowity_czas + czas;
			}
			calkowity_czas = calkowity_czas / 100;
			std::cout << "Czas wykonania algorytmu sortowania:" << calkowity_czas << std::endl;
			break;
		}
		case 2: {
			int n, m, w, v, x, y;


			std::fstream plik;
			plik.open("test34.txt", std::ios::in);
			if (plik.good() == true) {
				plik >> m >> n >> v;
				tab_kd = new int[n];
				tab_pw = new int[n];
				QS = new bool[n];
				tab_S = new int[n];

				grafLista = new ListaSasiedztwa * [n];
				grafMacierz = new MacierzSasiedztwa * [n];
				wskLista = new ListaSasiedztwa[n];
				ZainicjujTablice(tab_kd, tab_pw, QS, grafLista, grafMacierz, n);

				while (!plik.eof()) {
					plik >> x >> y >> w;
					wskLista = new ListaSasiedztwa;
					wskLista->v = y;
					wskLista->w = w;
					wskLista->nastepny = grafLista[x];
					grafLista[x] = wskLista;
					std::cout << x << " " << y << " " << w << std::endl;
				}
				plik.close();

				Kopiec* kopiec = new Kopiec(n);
				kopiec->UstawKopiec();
				tab_kd[v] = 0;
				kopiec->KopiecPoZmianieKDV(v);
				for (int i = 0; i < n; i++)
					kopiec->StworzKopiec(tab_kd, tab_pw, QS, grafLista, wskLista, v);
				WyswietlWyniki(n, tab_kd, tab_pw, tab_S);
			}
			break;
		}

		case 3: {
			std::cout << "Podaj ilosc krawedzi, wierzcholkow i wierzcholek startowy grafu:" << std::endl;
			std::cin >> n >> v;
			std::cout << "Podaj gestosc grafu:" << std::endl;
			std::cin >> gestosc;
			m = n * (n - 1) * gestosc / 2;
			tab_kd = new int[n];
			tab_pw = new int[n];
			QS = new bool[n];
			tab_S = new int[n];
			grafMacierz = new MacierzSasiedztwa * [n];
			grafLista = new ListaSasiedztwa * [n];
			wskMacierz = new MacierzSasiedztwa[n];
			mac = new int* [m];
			for (int i = 0; i < m; i++)
				mac[i] = new int[m];
			wagi = new int[m];
			wskMacierz->A = mac;
			wskMacierz->wagi = wagi;
			wskMacierz->StworzMacierz(n);
			ZainicjujTablice(tab_kd, tab_pw, QS, grafLista, grafMacierz, n);
			for (int i = 0; i < 100; i++) {
				mac = new int* [m];
				for (int i = 0; i < m; i++)
					mac[i] = new int[m];
				start = clock();
				LosujDaneMacierz(m, n, wskMacierz, mac);
				wskMacierz->Dijkstra(tab_kd, tab_pw, QS, mac, wskMacierz, v, n, m);

				stop = clock();
				czas = (double)(stop - start) / CLOCKS_PER_SEC;
				calkowity_czas = calkowity_czas + czas;
				delete mac;
			}
			calkowity_czas = calkowity_czas / 100;
			std::cout << "Czas wykonania algorytmu sortowania:" << calkowity_czas << std::endl;
			break;
		}
		case 4: {
			int m, n, v, i, x, y, w;
			std::fstream plik;
			plik.open("test34.txt", std::ios::in);
			if (plik.good() == true) {
				plik >> m >> n >> v;
				tab_kd = new int[n];
				tab_pw = new int[n];
				QS = new bool[n];
				tab_S = new int[n];
				grafMacierz = new MacierzSasiedztwa * [n];
				grafLista = new ListaSasiedztwa * [n];
				wskMacierz = new MacierzSasiedztwa[n];
				mac = new int* [m];
				for (int i = 0; i < m; i++)
					mac[i] = new int[m];
				wagi = new int[m];
				wskMacierz->A = mac;
				wskMacierz->wagi = wagi;
				wskMacierz->StworzMacierz(n);
				ZainicjujTablice(tab_kd, tab_pw, QS, grafLista, grafMacierz, n);
				while (!plik.eof()) {
					i = 0;
					plik >> x >> y >> w;
					mac[x][y] = w;
					wskMacierz->wagi[i] = w;
					i++;
				}
				plik.close();

				wskMacierz->Dijkstra(tab_kd, tab_pw, QS, mac, wskMacierz, v, n, m);
				WyswietlWyniki(n, tab_kd, tab_pw, tab_S);
			}
			break;
		}
		case 5: {
			std::cout << "------------Menu------------\n";
			std::cout << "1 - Reprezentacja grafu: lista sasiedztwa / Sposob testowania: testy efektywnosci\n";
			std::cout << "2 - Reprezentacja grafu: lista sasiedztwa / Sposob testowania: wczytanie danych z pliku\n";
			std::cout << "3 - Reprezentacja grafu: macierz sasiedztwa / Sposob testowania: testy efektywnosci\n";
			std::cout << "4 - Reprezentacja grafu: macierz sasiedztwa / Sposob testowania: wczytanie danych z pliku\n";
			std::cout << "5 - wyswietl ponownie menu\n";
			std::cout << "0 - zakoncz dzialanie programu\n";
			break;
		}
		case 0: std::cout << "Koniec dzialania programu...\n";
			break;
		default: std::cout << "Wprowadziles zly numer! Podaj jeszcze raz!\n";
			break;
		}
	} while (opcja != 0);
	system("PAUSE");
	return 0;
}
