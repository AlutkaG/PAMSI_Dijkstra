#ifndef macierzSasiedztwa_h
#define macierzSasiedztwa_h
#include <iostream>

class MacierzSasiedztwa {
public:
	int** A;
	int v;
	int* wagi;
	void StworzMacierz(int n);
	void WyswietlMacierz(int** A, int n);
	int minDistance(int dist[], bool sptSet[], int n);
	void Dijkstra(int* tab_kd, int* tab_pw, bool* tab_QS, int** mac, MacierzSasiedztwa* wsk, int v, int n, int m);
};

#endif
