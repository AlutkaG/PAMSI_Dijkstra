#include "macierzSasiedztwa.h"
#define INF 1234567890
void MacierzSasiedztwa::StworzMacierz(int n) {

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = 0;
}

void MacierzSasiedztwa::WyswietlMacierz(int** A, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			std::cout << A[i][j] << ' ';
		std::cout << std::endl;
	}
}

int MacierzSasiedztwa::minDistance(int dist[], bool sptSet[], int n)
{
	int min = INF, min_index = 0;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void MacierzSasiedztwa::Dijkstra(int* tab_kd, int* tab_pw, bool* tab_QS, int** mac, MacierzSasiedztwa * wsk, int v, int n, int m) {
	for (int i = 0; i < n; i++)
		tab_kd[i] = INF, tab_QS[i] = false;

	tab_kd[v] = 0;

	for (int i = 0; i < n - 1; i++)
	{
		int u = minDistance(tab_kd, tab_QS, n);

		tab_QS[u] = true;

		for (int v = 0; v < n; v++)

			if (!tab_QS[v] && mac[u][v] && tab_QS[u] != INF
				&& tab_kd[u] + mac[u][v] < tab_kd[v]) {
				tab_kd[v] = tab_kd[u] + mac[u][v];
				tab_pw[v] = u;
			}
	}
}
